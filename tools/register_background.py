#!/usr/bin/env python3
"""Register a 256x256 indexed BMP as a room background in game and editor.

From the game root:
    python tools/register_background.py templo_1
    python tools/register_background.py C:/images/templo_1.bmp
"""

from __future__ import annotations

import argparse
import ast
import os
from pathlib import Path
import re
import struct
import sys
import tempfile


def replace_once(source: str, old: str, new: str, location: str) -> str:
    count = source.count(old)
    if count != 1:
        raise ValueError(f"Expected one {location} anchor; found {count}")
    return source.replace(old, new, 1)


def update_enum(source: str, symbol: str) -> tuple[str, str]:
    pattern = r"(enum class RoomBackgroundId\s*\{\n)(.*?)(\n\};)"
    match = re.search(pattern, source, re.DOTALL)
    if not match:
        raise ValueError("RoomBackgroundId enum not found")
    names = [line.strip().rstrip(",") for line in match.group(2).splitlines() if line.strip()]
    if not all(re.fullmatch(r"[A-Z][A-Z0-9_]*", name) for name in names):
        raise ValueError("RoomBackgroundId has an unexpected format")
    if symbol not in names:
        body = match.group(2).rstrip()
        body += ",\n    " + symbol
        source = source[:match.start(2)] + body + source[match.end(2):]
        names.append(symbol)
    return source, names[-1]


def update_game(name: str, root: Path, originals: dict[Path, bytes]) -> dict[Path, bytes]:
    symbol = name.upper()
    result = {}

    enum_path = root / "include" / "room_manager.h"
    enum_text, last_symbol = update_enum(originals[enum_path].decode("utf-8"), symbol)
    result[enum_path] = enum_text.encode("utf-8")

    manager_path = root / "src" / "room_manager.cpp"
    manager = originals[manager_path].decode("utf-8")
    bound = r"int\(room\.background_id\) > int\(RoomBackgroundId::[A-Z0-9_]+\)"
    if len(re.findall(bound, manager)) != 1:
        raise ValueError("Saved background validation bound not found exactly once")
    manager = re.sub(bound, f"int(room.background_id) > int(RoomBackgroundId::{last_symbol})", manager)
    result[manager_path] = manager.encode("utf-8")

    importer_path = root / "tools" / "import_room.py"
    importer = originals[importer_path].decode("utf-8")
    match = re.search(r"^BACKGROUNDS = (\{[^\n]*\})$", importer, re.MULTILINE)
    if not match:
        raise ValueError("Importer's BACKGROUNDS dictionary not found")
    backgrounds = ast.literal_eval(match.group(1))
    if name in backgrounds and backgrounds[name] != symbol:
        raise ValueError(f"Importer already maps {name} to {backgrounds[name]}")
    if name not in backgrounds:
        dictionary = match.group(1)[:-1] + f', "{name}": "{symbol}"' + "}"
        importer = importer[:match.start(1)] + dictionary + importer[match.end(1):]
    result[importer_path] = importer.encode("utf-8")

    main_path = root / "src" / "main.cpp"
    main = originals[main_path].decode("utf-8")
    header = f'#include "bn_regular_bg_items_{name}.h"\n'
    if header not in main:
        anchor = '#include "bn_regular_bg_items_boss_2.h"\n'
        main = replace_once(main, anchor, anchor + header, "background include")
    branch = f"else if (background_id == RoomBackgroundId::{symbol})"
    if branch not in main:
        anchor = "        // El fondo nuevo nace durante el fade a negro;"
        code = (
            f"        else if (background_id == RoomBackgroundId::{symbol})\n"
            "        {\n"
            f"            room_special_bg.emplace(bn::regular_bg_items::{name}.create_bg(0, 0));\n"
            "            room_special_bg->set_priority(3);\n"
            "        }\n\n"
        )
        main = replace_once(main, anchor, code + anchor, "background drawing branch")
    result[main_path] = main.encode("utf-8")
    return result


def bump_version(source: str, pattern: str, location: str) -> str:
    matches = list(re.finditer(pattern, source))
    if len(matches) != 1:
        raise ValueError(f"Expected one {location} version; found {len(matches)}")
    match = matches[0]
    old = match.group(1)
    return source[:match.start(1)] + str(int(old) + 1) + source[match.end(1):]


def update_editor(name: str, editor: Path, originals: dict[Path, bytes]) -> dict[Path, bytes]:
    result = {}
    core_path = editor / "editor-core.js"
    core = originals[core_path].decode("utf-8")
    match = re.search(r"(export const BACKGROUNDS = \[\n)(.*?)(\n\];)", core, re.DOTALL)
    if not match:
        raise ValueError("Editor's BACKGROUNDS list not found")
    entry = f"sprite('{name}', '{name.replace('_', ' ').title()}', '{name}', 'background', 256, 256),"
    if not re.search(rf"sprite\('{re.escape(name)}',\s*'[^']*',\s*'{re.escape(name)}',\s*'background'", match.group(2)):
        body = match.group(2).rstrip()
        if not body.endswith(","):
            body += ","
        body += "\n  " + entry
        core = core[:match.start(2)] + body + core[match.end(2):]
    allow_pattern = r"if\(!\[([^\n]*?)\]\.includes\(room\.background\)\)"
    allow = re.search(allow_pattern, core)
    if not allow:
        raise ValueError("Editor's game background allowlist not found")
    allowed = re.findall(r"'([^']+)'", allow.group(1))
    if name not in allowed:
        core = core[:allow.end(1)] + f",'{name}'" + core[allow.end(1):]
    result[core_path] = core.encode("utf-8")

    if result[core_path] != originals[core_path]:
        js_path = editor / "editor.js"
        html_path = editor / "editor.html"
        js = originals[js_path].decode("utf-8")
        html = originals[html_path].decode("utf-8")
        js = bump_version(js, r"\./editor-core\.js\?v=(\d+)", "editor-core.js")
        html = bump_version(html, r"editor-loader\.js\?v=(\d+)", "editor-loader.js")
        result[js_path] = js.encode("utf-8")
        result[html_path] = html.encode("utf-8")
    return result


def validate_bmp(image: Path) -> bytes:
    data = image.read_bytes()
    if len(data) < 54 or data[:2] != b"BM":
        raise ValueError(f"{image} is not a BMP image")
    width, height = struct.unpack_from("<ii", data, 18)
    bits_per_pixel = struct.unpack_from("<H", data, 28)[0]
    compression = struct.unpack_from("<I", data, 30)[0]
    if (width, abs(height), bits_per_pixel, compression) != (256, 256, 8, 0):
        raise ValueError("Background BMP must be 256x256, 8-bit indexed, uncompressed")
    return data


def write_atomic(path: Path, data: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = None
    try:
        with tempfile.NamedTemporaryFile(dir=path.parent, prefix=".background-", delete=False) as file:
            temporary = Path(file.name)
            file.write(data)
        os.replace(temporary, path)
    finally:
        if temporary is not None and temporary.exists():
            temporary.unlink()


def main() -> int:
    parser = argparse.ArgumentParser(description="Register a new room background in the game and editor")
    parser.add_argument("image", help="BMP file path or the name of an existing graphics/<name>.bmp")
    parser.add_argument("--editor-dir", type=Path, default=Path.home() / "OneDrive" / "Escritorio" / "Pagina GBA")
    parser.add_argument("--dry-run", action="store_true", help="Validate and list changes without writing")
    args = parser.parse_args()

    root = Path(__file__).resolve().parent.parent
    argument = Path(args.image)
    name = argument.stem if argument.suffix.lower() == ".bmp" else args.image
    if not re.fullmatch(r"[a-z][a-z0-9_]*", name):
        raise ValueError("Use a lowercase name with letters, digits and underscores, starting with a letter")
    image = argument if argument.suffix.lower() == ".bmp" and argument.is_file() else root / "graphics" / f"{name}.bmp"
    if not image.is_file():
        raise FileNotFoundError(f"BMP not found: {image}")
    bitmap = validate_bmp(image)
    editor = args.editor_dir.expanduser().resolve()

    game_files = [root / path for path in (
        "include/room_manager.h", "src/room_manager.cpp", "tools/import_room.py", "src/main.cpp")]
    editor_files = [editor / path for path in ("editor-core.js", "editor.js", "editor.html")]
    missing = [path for path in game_files + editor_files if not path.is_file()]
    if missing or not (editor / "assets_game").is_dir():
        raise FileNotFoundError("Game/editor files missing: " + ", ".join(str(path) for path in missing))

    game_image = root / "graphics" / f"{name}.bmp"
    editor_image = editor / "assets_game" / f"{name}.bmp"
    sidecar = root / "graphics" / f"{name}.json"
    for target in (game_image, editor_image):
        if target.is_file() and target.read_bytes() != bitmap:
            raise ValueError(f"Existing image differs from supplied BMP: {target}")
    if sidecar.is_file():
        import json
        if json.loads(sidecar.read_text(encoding="utf-8")).get("type") != "regular_bg":
            raise ValueError(f"Existing sidecar is not a regular_bg: {sidecar}")

    originals = {path: path.read_bytes() for path in game_files + editor_files}
    changes = update_game(name, root, originals)
    changes.update(update_editor(name, editor, originals))
    changes[game_image] = bitmap
    changes[editor_image] = bitmap
    if not sidecar.is_file():
        changes[sidecar] = b'{\n    "type": "regular_bg"\n}\n'
    changes = {path: data for path, data in changes.items()
               if not path.is_file() or path.read_bytes() != data}
    if not changes:
        print(f"Background '{name}' is already registered.")
        return 0
    if args.dry_run:
        print("Would update:")
        for path in changes:
            print(" ", path)
        return 0

    previous = {path: path.read_bytes() if path.is_file() else None for path in changes}
    applied = []
    try:
        for path, data in changes.items():
            write_atomic(path, data)
            applied.append(path)
    except Exception:
        for path in reversed(applied):
            old = previous[path]
            if old is None:
                path.unlink(missing_ok=True)
            else:
                write_atomic(path, old)
        raise
    print(f"Registered '{name}' in game and editor. Use \"background\": \"{name}\" in a room JSON.")
    print("Compile the game yourself to generate the Butano asset and room catalog.")
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except (OSError, ValueError, SyntaxError) as error:
        print(f"Error: {error}", file=sys.stderr)
        sys.exit(1)
