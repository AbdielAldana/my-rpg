"""Editor visual de objetos pasivos de Another Dungeon.

Ejecutar desde la raiz del proyecto:

    python tools/passive_item_editor.py

El editor registra el objeto en passive_shop.h y main.cpp, copia su BMP a
graphics/ y crea el JSON de Butano. Los cambios se preparan en memoria y se
escriben juntos; si algo falla, restaura los archivos originales.
"""

from __future__ import annotations

import re
import shutil
import struct
import tkinter as tk
from pathlib import Path
from tkinter import filedialog, messagebox, ttk


ROOT = Path(__file__).resolve().parents[1]
SHOP_HEADER = ROOT / "include" / "passive_shop.h"
MAIN_CPP = ROOT / "src" / "main.cpp"
GRAPHICS = ROOT / "graphics"

BG = "#101a2c"
PANEL = "#1b2940"
PANEL_LIGHT = "#263957"
INK = "#f4e6bd"
MUTED = "#a9b8c8"
GOLD = "#f4c95d"
CYAN = "#6fd3d7"


def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8")


def replace_once(text: str, old: str, new: str, label: str) -> str:
    count = text.count(old)
    if count != 1:
        raise ValueError(f"No se encontro un unico punto para {label} (encontrados: {count}).")
    return text.replace(old, new, 1)


def replace_once_in_block(text: str, block_start: str, block_end: str,
                          old: str, new: str, label: str) -> str:
    start = text.find(block_start)
    if start < 0:
        raise ValueError(f"No se encontro el inicio de {label}.")
    end = text.find(block_end, start + len(block_start))
    if end < 0:
        raise ValueError(f"No se encontro el final de {label}.")
    end += len(block_end)
    block = text[start:end]
    count = block.count(old)
    if count != 1:
        raise ValueError(f"No se encontro un unico punto para {label} (encontrados: {count}).")
    updated = block.replace(old, new, 1)
    return text[:start] + updated + text[end:]


def bmp_dimensions(path: Path) -> tuple[int, int]:
    with path.open("rb") as source:
        header = source.read(26)
    if len(header) < 26 or header[:2] != b"BM":
        raise ValueError("El sprite debe ser un BMP valido.")
    width, height = struct.unpack_from("<ii", header, 18)
    return abs(width), abs(height)


def validate_sprite_bmp(path: Path) -> tuple[int, int]:
    data = path.read_bytes()
    if len(data) < 54 or data[:2] != b"BM":
        raise ValueError("El sprite debe ser un BMP valido.")
    width, height = bmp_dimensions(path)
    bits = struct.unpack_from("<H", data, 28)[0]
    compression = struct.unpack_from("<I", data, 30)[0]
    if compression != 0 or bits != 8:
        raise ValueError("Butano necesita un BMP indexado de 8 bits sin compresion.")
    if width != height or width not in (8, 16, 32, 64):
        raise ValueError("El icono debe ser cuadrado de 8, 16, 32 o 64 pixeles.")
    return width, height


def bmp_photo(master: tk.Misc, path: Path, crop_width: int | None = None,
              crop_height: int | None = None) -> tk.PhotoImage:
    """Carga BMP indexado/RGB sin depender de Pillow."""
    data = path.read_bytes()
    if data[:2] != b"BM" or len(data) < 54:
        raise ValueError("BMP invalido")
    pixel_offset = struct.unpack_from("<I", data, 10)[0]
    dib_size = struct.unpack_from("<I", data, 14)[0]
    width, signed_height = struct.unpack_from("<ii", data, 18)
    planes, bits = struct.unpack_from("<HH", data, 26)
    compression = struct.unpack_from("<I", data, 30)[0]
    if planes != 1 or compression != 0 or bits not in (4, 8, 24, 32):
        raise ValueError("Solo se admiten BMP sin compresion de 4, 8, 24 o 32 bits")
    source_height = abs(signed_height)
    height = min(source_height, crop_height or source_height)
    shown_width = min(width, crop_width or width)
    colors_used = struct.unpack_from("<I", data, 46)[0] if dib_size >= 40 else 0
    palette: list[tuple[int, int, int]] = []
    if bits <= 8:
        color_count = colors_used or (1 << bits)
        palette_start = 14 + dib_size
        for index in range(color_count):
            blue, green, red, _ = struct.unpack_from("<BBBB", data, palette_start + index * 4)
            palette.append((red, green, blue))
    row_bytes = ((width * bits + 31) // 32) * 4
    photo = tk.PhotoImage(master=master, width=shown_width, height=height)
    transparent: list[tuple[int, int]] = []
    for output_y in range(height):
        source_y = output_y if signed_height < 0 else source_height - 1 - output_y
        row_start = pixel_offset + source_y * row_bytes
        colors: list[str] = []
        for x in range(shown_width):
            alpha = 255
            palette_index = -1
            if bits == 4:
                value = data[row_start + x // 2]
                palette_index = value >> 4 if x % 2 == 0 else value & 15
                red, green, blue = palette[palette_index]
            elif bits == 8:
                palette_index = data[row_start + x]
                red, green, blue = palette[palette_index]
            elif bits == 24:
                blue, green, red = struct.unpack_from("<BBB", data, row_start + x * 3)
            else:
                blue, green, red, alpha = struct.unpack_from("<BBBB", data, row_start + x * 4)
            colors.append(f"#{red:02x}{green:02x}{blue:02x}")
            if palette_index == 0 or alpha == 0:
                transparent.append((x, output_y))
        photo.put("{" + " ".join(colors) + "}", to=(0, output_y))
    try:
        for x, y in transparent:
            photo.transparency_set(x, y, True)
    except tk.TclError:
        pass
    return photo


def parse_existing(header: str) -> list[tuple[str, str, int]]:
    passive_match = re.search(r"constexpr int passive_count = (\d+);", header)
    enum_match = re.search(r"enum class ItemId : uint8_t\s*\{(.*?)\n\};", header, re.S)
    definitions_match = re.search(r"constexpr ItemDefinition definitions\[\]\s*=\s*\{(.*?)\n\};", header, re.S)
    if not passive_match or not enum_match or not definitions_match:
        raise ValueError("No se pudo leer la estructura actual de passive_shop.h")
    count = int(passive_match.group(1))
    identifiers = re.findall(r"^\s*([A-Z][A-Z0-9_]*)\s*(?:=\s*\d+)?\s*,?", enum_match.group(1), re.M)
    definitions = re.findall(r'\{"([^"]+)",\s*(\d+)\}', definitions_match.group(1))
    if len(identifiers) < count or len(definitions) < count:
        raise ValueError("La lista de pasivos esta incompleta")
    return [(identifiers[index], definitions[index][0], int(definitions[index][1]))
            for index in range(count)]


def stat_case(header: str, identifier: str) -> str:
    pattern = re.compile(
        rf"^        case ItemId::{re.escape(identifier)}:.*?"
        r"(?=^        (?:case ItemId::|default:))", re.M | re.S)
    match = pattern.search(header)
    if not match:
        raise ValueError(f"No se encontraron los modificadores de {identifier}.")
    return match.group(0)


def sprite_for(main: str, identifier: str) -> str:
    match = re.search(
        rf"case ItemId::{re.escape(identifier)}:\s*return\s+"
        r"bn::sprite_items::([a-zA-Z0-9_]+)\.create_sprite",
        main)
    if not match:
        raise ValueError(f"No se encontro el sprite de {identifier}.")
    return match.group(1)


def graphic_path(sprite_id: str) -> Path:
    direct = GRAPHICS / f"{sprite_id}.bmp"
    if direct.is_file():
        return direct
    matches = list(GRAPHICS.rglob(f"{sprite_id}.bmp"))
    if len(matches) == 1:
        return matches[0]
    if not matches:
        raise ValueError(f"No se encontro graphics/{sprite_id}.bmp ni en sus subcarpetas.")
    raise ValueError(f"Hay varios sprites llamados {sprite_id}.bmp; deja solo uno.")


def parsed_modifiers(header: str, identifier: str) -> dict[str, object]:
    case = stat_case(header, identifier)

    def multiplier(variable: str) -> float:
        match = re.search(
            rf"{variable}\s*=\s*multiply_milli\({variable},\s*(\d+)\)", case)
        return int(match.group(1)) / 1000 if match else 1.0

    speed_match = re.search(r"direct_speed\s*\+=\s*(-?\d+)", case)
    projectile_match = re.search(r"direct_projectiles\s*\+=\s*(\d+)", case)
    if projectile_match:
        projectiles = int(projectile_match.group(1))
    else:
        projectiles = case.count("++direct_projectiles")
    pattern = "Trina" if "triple = true" in case else (
        "Gemela" if "twin = true" in case else "Normal")
    return {
        "speed": multiplier("speed_factor"),
        "size": multiplier("size_factor"),
        "frequency": multiplier("frequency_factor"),
        "reserve": multiplier("reserve_factor"),
        "direct_speed": int(speed_match.group(1)) / 1000 if speed_match else 0.0,
        "projectiles": projectiles,
        "pattern": pattern,
    }


def replace_stat_case(header: str, identifier: str, replacement: str) -> str:
    original = stat_case(header, identifier)
    return replace_once(header, original, replacement, f"modificadores de {identifier}")


class NumberField(ttk.Frame):
    def __init__(self, master: tk.Misc, label: str, variable: tk.StringVar, width: int = 9):
        super().__init__(master)
        ttk.Label(self, text=label).pack(anchor="w")
        ttk.Entry(self, textvariable=variable, width=width).pack(fill="x", pady=(3, 0))


class PassiveEditor(tk.Tk):
    def __init__(self) -> None:
        super().__init__()
        self.title("Another Dungeon - Taller de pasivos")
        self.geometry("1050x720")
        self.minsize(920, 650)
        self.configure(bg=BG)
        self.option_add("*Font", ("Segoe UI", 10))
        self._images: list[tk.PhotoImage] = []
        self.sprite_source: Path | None = None
        self.existing: list[tuple[str, str, int]] = []
        self.editing_id: str | None = None

        self.item_id = tk.StringVar()
        self.display_name = tk.StringVar()
        self.price = tk.StringVar(value="5")
        self.sprite_id = tk.StringVar()
        self.speed_multiplier = tk.StringVar(value="1.00")
        self.size_multiplier = tk.StringVar(value="1.00")
        self.frequency_multiplier = tk.StringVar(value="1.00")
        self.reserve_multiplier = tk.StringVar(value="1.00")
        self.direct_speed = tk.StringVar(value="0.00")
        self.extra_projectiles = tk.StringVar(value="0")
        self.pattern = tk.StringVar(value="Normal")
        self.status = tk.StringVar(value="Listo para crear un pasivo.")
        self.form_title = tk.StringVar(value="NUEVO OBJETO")
        self.save_button_text = tk.StringVar(value="AGREGAR PASIVO AL JUEGO")

        self._configure_style()
        self._build_header()
        self._build_body()
        self._build_footer()
        self.reload_existing()

    def _configure_style(self) -> None:
        style = ttk.Style(self)
        try:
            style.theme_use("clam")
        except tk.TclError:
            pass
        style.configure("TFrame", background=PANEL)
        style.configure("TLabel", background=PANEL, foreground=INK)
        style.configure("Muted.TLabel", foreground=MUTED)
        style.configure("Title.TLabel", font=("Segoe UI", 17, "bold"), foreground=GOLD)
        style.configure("Section.TLabel", font=("Segoe UI", 11, "bold"), foreground=CYAN)
        style.configure("TEntry", fieldbackground="#0e1726", foreground=INK, insertcolor=INK)
        style.configure("TCombobox", fieldbackground="#0e1726", foreground=INK)
        style.configure("TButton", background=PANEL_LIGHT, foreground=INK, padding=(10, 6))
        style.map("TButton", background=[("active", "#375276")])
        style.configure("Gold.TButton", background="#8f6925", foreground="#fff3c4")
        style.map("Gold.TButton", background=[("active", "#b98a32")])
        style.configure("Treeview", background="#111c2d", fieldbackground="#111c2d",
                        foreground=INK, rowheight=26)
        style.configure("Treeview.Heading", background=PANEL_LIGHT, foreground=GOLD)

    def _build_header(self) -> None:
        canvas = tk.Canvas(self, height=108, bg="#09111f", highlightthickness=0)
        canvas.pack(fill="x")
        for x in range(0, 1100, 32):
            canvas.create_rectangle(x, 76, x + 31, 107, fill="#14233a", outline="#1b3150")
        canvas.create_text(525, 34, text="TALLER DE OBJETOS PASIVOS", fill=GOLD,
                           font=("Segoe UI", 22, "bold"))
        canvas.create_text(525, 62, text="ANOTHER DUNGEON", fill=MUTED,
                           font=("Segoe UI", 10, "bold"))
        decorations = [
            ("coin.bmp", 38, 40, 8),
            ("aventure_1.bmp", 92, 51, 16),
            ("campfire.bmp", 948, 48, 16),
            ("coin_sack.bmp", 1002, 43, 16),
        ]
        for filename, x, y, crop in decorations:
            try:
                image = bmp_photo(self, GRAPHICS / filename, crop, crop).zoom(3, 3)
                self._images.append(image)
                canvas.create_image(x, y, image=image)
            except (OSError, ValueError, tk.TclError):
                canvas.create_rectangle(x - 8, y - 8, x + 8, y + 8,
                                        fill=PANEL_LIGHT, outline=GOLD)

    def _build_body(self) -> None:
        body = tk.Frame(self, bg=BG)
        body.pack(fill="both", expand=True, padx=16, pady=14)
        body.grid_columnconfigure(0, weight=4)
        body.grid_columnconfigure(1, weight=6)
        body.grid_rowconfigure(0, weight=1)

        left = ttk.Frame(body, padding=14)
        left.grid(row=0, column=0, sticky="nsew", padx=(0, 8))
        right = ttk.Frame(body, padding=14)
        right.grid(row=0, column=1, sticky="nsew", padx=(8, 0))
        self._build_existing_panel(left)
        self._build_form(right)

    def _build_existing_panel(self, panel: ttk.Frame) -> None:
        ttk.Label(panel, text="PASIVOS REGISTRADOS", style="Section.TLabel").pack(anchor="w")
        ttk.Label(panel, text="Selecciona uno para cargarlo y editarlo.",
                  style="Muted.TLabel").pack(anchor="w", pady=(2, 10))
        columns = ("id", "name", "price")
        self.tree = ttk.Treeview(panel, columns=columns, show="headings", selectmode="browse")
        self.tree.heading("id", text="# / ID")
        self.tree.heading("name", text="Nombre")
        self.tree.heading("price", text="Precio")
        self.tree.column("id", width=135, anchor="w")
        self.tree.column("name", width=180, anchor="w")
        self.tree.column("price", width=55, anchor="center")
        scrollbar = ttk.Scrollbar(panel, orient="vertical", command=self.tree.yview)
        self.tree.configure(yscrollcommand=scrollbar.set)
        self.tree.bind("<<TreeviewSelect>>", self.load_selected)
        self.tree.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")

    def _build_form(self, panel: ttk.Frame) -> None:
        ttk.Label(panel, textvariable=self.form_title, style="Section.TLabel").grid(
            row=0, column=0, columnspan=4, sticky="w")
        ttk.Label(panel, text="Los multiplicadores usan 1.00 como valor neutral.",
                  style="Muted.TLabel").grid(row=1, column=0, columnspan=4, sticky="w", pady=(2, 12))

        NumberField(panel, "ID C++ (MAYUSCULAS)", self.item_id, 20).grid(
            row=2, column=0, columnspan=2, sticky="ew", padx=(0, 6), pady=4)
        NumberField(panel, "Nombre visible", self.display_name, 24).grid(
            row=2, column=2, columnspan=2, sticky="ew", padx=(6, 0), pady=4)
        NumberField(panel, "Precio", self.price).grid(row=3, column=0, sticky="ew", padx=(0, 6), pady=4)

        sprite_frame = ttk.Frame(panel)
        sprite_frame.grid(row=3, column=1, columnspan=3, sticky="ew", padx=(6, 0), pady=4)
        sprite_frame.grid_columnconfigure(0, weight=1)
        ttk.Label(sprite_frame, text="Sprite BMP").grid(row=0, column=0, sticky="w")
        ttk.Entry(sprite_frame, textvariable=self.sprite_id, state="readonly").grid(
            row=1, column=0, sticky="ew", pady=(3, 0))
        ttk.Button(sprite_frame, text="Elegir...", command=self.choose_sprite).grid(
            row=1, column=1, padx=(8, 0), pady=(3, 0))

        separator = ttk.Separator(panel)
        separator.grid(row=4, column=0, columnspan=4, sticky="ew", pady=13)
        ttk.Label(panel, text="MODIFICADORES DEL PROYECTIL", style="Section.TLabel").grid(
            row=5, column=0, columnspan=4, sticky="w", pady=(0, 6))
        fields = [
            ("Velocidad x", self.speed_multiplier),
            ("Tamano x", self.size_multiplier),
            ("Frames entre disparos x", self.frequency_multiplier),
            ("Reserva x", self.reserve_multiplier),
            ("Velocidad directa +px/frame", self.direct_speed),
            ("Proyectiles adicionales", self.extra_projectiles),
        ]
        for index, (label, variable) in enumerate(fields):
            row = 6 + index // 2
            column = (index % 2) * 2
            NumberField(panel, label, variable).grid(row=row, column=column, columnspan=2,
                                                     sticky="ew", padx=(0 if column == 0 else 6,
                                                                        6 if column == 0 else 0),
                                                     pady=4)
        ttk.Label(panel, text="Patron especial").grid(row=9, column=0, columnspan=2, sticky="w", pady=(8, 2))
        ttk.Combobox(panel, textvariable=self.pattern, state="readonly",
                     values=("Normal", "Gemela", "Trina")).grid(
            row=10, column=0, columnspan=2, sticky="ew", padx=(0, 6))

        preview_box = tk.Frame(panel, bg="#0b1422", width=130, height=100,
                               highlightbackground=PANEL_LIGHT, highlightthickness=1)
        preview_box.grid(row=9, column=2, rowspan=3, columnspan=2, sticky="nsew", padx=(8, 0), pady=(8, 0))
        preview_box.grid_propagate(False)
        self.preview = tk.Label(preview_box, text="SPRITE\nSIN ELEGIR", fg=MUTED, bg="#0b1422")
        self.preview.place(relx=.5, rely=.5, anchor="center")

        ttk.Button(panel, text="NUEVO / LIMPIAR", command=self.clear_form).grid(
            row=12, column=0, sticky="ew", pady=(18, 0), padx=(0, 6), ipady=5)
        self.save_button = ttk.Button(
            panel, textvariable=self.save_button_text, style="Gold.TButton",
            command=self.save_passive)
        self.save_button.grid(
            row=12, column=1, columnspan=3, sticky="ew", pady=(18, 0), ipady=5)

        for column in range(4):
            panel.grid_columnconfigure(column, weight=1)

    def _build_footer(self) -> None:
        footer = tk.Frame(self, bg=BG)
        footer.pack(fill="x", padx=16, pady=(0, 14))
        tk.Label(footer, textvariable=self.status, bg=BG, fg=MUTED, anchor="w").pack(
            side="left", fill="x", expand=True)
        ttk.Button(footer, text="Recargar", command=self.reload_existing).pack(side="right", padx=(8, 0))

    def reload_existing(self) -> None:
        try:
            self.existing = parse_existing(read_text(SHOP_HEADER))
        except (OSError, ValueError) as error:
            messagebox.showerror("No se pudo cargar", str(error), parent=self)
            return
        for row in self.tree.get_children():
            self.tree.delete(row)
        for index, (identifier, name, price) in enumerate(self.existing, start=1):
            self.tree.insert("", "end", iid=identifier,
                             values=(f"{index:02d}  {identifier}", name, price))
        self.status.set(f"{len(self.existing)} de 32 espacios de pasivos ocupados.")

    @staticmethod
    def _decimal(value: float) -> str:
        return f"{value:.2f}"

    def clear_form(self) -> None:
        self.editing_id = None
        self.form_title.set("NUEVO OBJETO")
        self.save_button_text.set("AGREGAR PASIVO AL JUEGO")
        self.item_id.set("")
        self.display_name.set("")
        self.price.set("5")
        self.sprite_id.set("")
        self.sprite_source = None
        self.speed_multiplier.set("1.00")
        self.size_multiplier.set("1.00")
        self.frequency_multiplier.set("1.00")
        self.reserve_multiplier.set("1.00")
        self.direct_speed.set("0.00")
        self.extra_projectiles.set("0")
        self.pattern.set("Normal")
        self.preview.configure(image="", text="SPRITE\nSIN ELEGIR")
        for selected in self.tree.selection():
            self.tree.selection_remove(selected)
        self.status.set("Formulario limpio. Listo para crear un pasivo.")

    def load_selected(self, _event: object = None) -> None:
        selection = self.tree.selection()
        if not selection:
            return
        identifier = selection[0]
        item = next((entry for entry in self.existing if entry[0] == identifier), None)
        if not item:
            return
        try:
            header = read_text(SHOP_HEADER)
            main = read_text(MAIN_CPP)
            modifiers = parsed_modifiers(header, identifier)
            sprite_id = sprite_for(main, identifier)
            sprite_path = graphic_path(sprite_id)
            width, height = bmp_dimensions(sprite_path)
            image = bmp_photo(self, sprite_path, min(width, height), min(width, height)).zoom(4, 4)
        except (OSError, ValueError, tk.TclError) as error:
            messagebox.showerror("No se puede editar", str(error), parent=self)
            return

        self.editing_id = identifier
        self.form_title.set(f"EDITANDO: {item[1]}")
        self.save_button_text.set("GUARDAR CAMBIOS")
        self.item_id.set(identifier)
        self.display_name.set(item[1])
        self.price.set(str(item[2]))
        self.sprite_id.set(sprite_id)
        self.sprite_source = sprite_path
        self.speed_multiplier.set(self._decimal(float(modifiers["speed"])))
        self.size_multiplier.set(self._decimal(float(modifiers["size"])))
        self.frequency_multiplier.set(self._decimal(float(modifiers["frequency"])))
        self.reserve_multiplier.set(self._decimal(float(modifiers["reserve"])))
        self.direct_speed.set(self._decimal(float(modifiers["direct_speed"])))
        self.extra_projectiles.set(str(modifiers["projectiles"]))
        self.pattern.set(str(modifiers["pattern"]))
        self._images.append(image)
        self.preview.configure(image=image, text="")
        self.status.set("Edita los campos y pulsa Guardar cambios.")

    def choose_sprite(self) -> None:
        selected = filedialog.askopenfilename(parent=self, title="Seleccionar sprite del pasivo",
                                              initialdir=GRAPHICS,
                                              filetypes=(("Imagen BMP", "*.bmp"), ("Todos", "*.*")))
        if not selected:
            return
        path = Path(selected)
        try:
            width, height = validate_sprite_bmp(path)
            image = bmp_photo(self, path, min(width, height)).zoom(4, 4)
        except (OSError, ValueError, tk.TclError) as error:
            messagebox.showerror("Sprite no valido", str(error), parent=self)
            return
        self.sprite_source = path
        self.sprite_id.set(path.stem.lower().replace("-", "_").replace(" ", "_"))
        self._images.append(image)
        self.preview.configure(image=image, text="")

    def _values(self) -> dict[str, object]:
        identifier = self.item_id.get().strip().upper()
        display_name = self.display_name.get().strip().upper()
        sprite_id = self.sprite_id.get().strip().lower()
        if not re.fullmatch(r"[A-Z][A-Z0-9_]*", identifier):
            raise ValueError("El ID debe comenzar con letra y usar MAYUSCULAS, numeros o guion bajo.")
        if not re.fullmatch(r"[A-Z0-9 ]{2,28}", display_name):
            raise ValueError("El nombre visible admite 2-28 letras, numeros y espacios sin acentos.")
        if not re.fullmatch(r"[a-z][a-z0-9_]*", sprite_id):
            raise ValueError("El nombre del sprite no es valido.")
        if self.sprite_source is None or not self.sprite_source.is_file():
            raise ValueError("Selecciona un archivo BMP para el objeto.")
        price = int(self.price.get())
        if not 1 <= price <= 255:
            raise ValueError("El precio debe estar entre 1 y 255.")
        multipliers = {
            "speed": float(self.speed_multiplier.get()),
            "size": float(self.size_multiplier.get()),
            "frequency": float(self.frequency_multiplier.get()),
            "reserve": float(self.reserve_multiplier.get()),
        }
        for label, value in multipliers.items():
            if not 0.25 <= value <= 4:
                raise ValueError(f"El multiplicador {label} debe estar entre 0.25 y 4.00.")
        direct_speed = float(self.direct_speed.get())
        extra_projectiles = int(self.extra_projectiles.get())
        if not -2 <= direct_speed <= 2:
            raise ValueError("La velocidad directa debe estar entre -2 y +2 px/frame.")
        if not 0 <= extra_projectiles <= 4:
            raise ValueError("Los proyectiles adicionales deben estar entre 0 y 4.")
        if self.editing_id is None and len(self.existing) >= 32:
            raise ValueError("La mascara de guardado ya alcanzo su limite de 32 pasivos.")
        other_items = [item for item in self.existing if item[0] != self.editing_id]
        if identifier in {item[0] for item in other_items}:
            raise ValueError("Ya existe un pasivo con ese ID.")
        if display_name in {item[1] for item in other_items}:
            raise ValueError("Ya existe un pasivo con ese nombre.")
        return dict(identifier=identifier, display_name=display_name, sprite_id=sprite_id,
                    price=price, multipliers=multipliers, direct_speed=direct_speed,
                    extra_projectiles=extra_projectiles, pattern=self.pattern.get())

    @staticmethod
    def _factor(value: float) -> int:
        return int(round(value * 1000))

    def _build_stat_case(self, values: dict[str, object]) -> str:
        identifier = str(values["identifier"])
        multipliers = values["multipliers"]
        assert isinstance(multipliers, dict)
        lines = [f"        case ItemId::{identifier}:"]
        mapping = (("speed", "speed_factor"), ("size", "size_factor"),
                   ("frequency", "frequency_factor"), ("reserve", "reserve_factor"))
        for key, variable in mapping:
            factor = self._factor(float(multipliers[key]))
            if factor != 1000:
                lines.append(f"            {variable} = multiply_milli({variable}, {factor});")
        direct_speed = int(round(float(values["direct_speed"]) * 1000))
        if direct_speed:
            lines.append(f"            direct_speed += {direct_speed};")
        extra = int(values["extra_projectiles"])
        if extra:
            lines.append(f"            direct_projectiles += {extra};")
        if values["pattern"] == "Gemela":
            lines.append("            twin = true;")
        elif values["pattern"] == "Trina":
            lines.append("            triple = true;")
        if len(lines) == 1:
            lines.append("            // Objeto reservado sin modificadores.")
        lines.append("            break;")
        return "\n".join(lines) + "\n"

    def _prepare_sources(self, values: dict[str, object]) -> tuple[str, str]:
        header = read_text(SHOP_HEADER)
        main = read_text(MAIN_CPP)
        old_count = len(self.existing)
        identifier = str(values["identifier"])
        display_name = str(values["display_name"])
        sprite_id = str(values["sprite_id"])
        price = int(values["price"])

        header = replace_once(header, f"constexpr int passive_count = {old_count};",
                              f"constexpr int passive_count = {old_count + 1};", "passive_count")
        if old_count + 1 == 32:
            header = replace_once(
                header,
                "constexpr uint32_t all_passives_mask = (uint32_t(1) << passive_count) - 1;",
                "constexpr uint32_t all_passives_mask = 0xFFFFFFFFu;",
                "mascara completa de pasivos")
        header = replace_once_in_block(
            header, "enum class ItemId : uint8_t\n{", "\n};",
            "    POTION,\n", f"    {identifier},\n    POTION,\n", "enum ItemId")
        header = replace_once(header, '    {"POCION", 1},\n',
                              f'    {{"{display_name}", {price}}},\n    {{"POCION", 1}},\n',
                              "tabla de nombres y precios")
        marker = "        default: break;\n        }\n    }\n\n    int base_projectiles"
        header = replace_once(header, marker,
                              self._build_stat_case(values) + marker,
                              "calculo de estadisticas")

        include_line = f'#include "bn_sprite_items_{sprite_id}.h"\n'
        if include_line not in main:
            main = replace_once(main, '#include "player_stats.h"\n',
                                include_line + '#include "player_stats.h"\n', "include del sprite")
        sprite_case = (f"        case ItemId::{identifier}: return "
                       f"bn::sprite_items::{sprite_id}.create_sprite(sprite_x, sprite_y);\n")
        main = replace_once(main, "        case ItemId::POTION: return ",
                            sprite_case + "        case ItemId::POTION: return ",
                            "sprite de tienda")
        return header, main

    def _prepare_edited_sources(self, values: dict[str, object]) -> tuple[str, str, str]:
        if self.editing_id is None:
            raise ValueError("No hay un pasivo seleccionado para editar.")
        original_id = self.editing_id
        original = next((item for item in self.existing if item[0] == original_id), None)
        if not original:
            raise ValueError("El pasivo seleccionado ya no existe.")

        header = read_text(SHOP_HEADER)
        main = read_text(MAIN_CPP)
        identifier = str(values["identifier"])
        display_name = str(values["display_name"])
        sprite_id = str(values["sprite_id"])
        price = int(values["price"])
        old_sprite_id = sprite_for(main, original_id)

        if identifier != original_id:
            header = replace_once_in_block(
                header, "enum class ItemId : uint8_t\n{", "\n};",
                f"    {original_id},\n", f"    {identifier},\n", "enum ItemId")
        header = replace_once(
            header, f'    {{"{original[1]}", {original[2]}}},\n',
            f'    {{"{display_name}", {price}}},\n', "nombre y precio del pasivo")
        header = replace_stat_case(header, original_id, self._build_stat_case(values))

        include_line = f'#include "bn_sprite_items_{sprite_id}.h"\n'
        if include_line not in main:
            main = replace_once(main, '#include "player_stats.h"\n',
                                include_line + '#include "player_stats.h"\n', "include del sprite")
        old_case_pattern = re.compile(
            rf"^        case ItemId::{re.escape(original_id)}:\s*return\s+"
            rf"bn::sprite_items::{re.escape(old_sprite_id)}\.create_sprite"
            r"\(sprite_x, sprite_y\);\n", re.M)
        match = old_case_pattern.search(main)
        if not match:
            raise ValueError(f"No se pudo actualizar el sprite de {original_id}.")
        new_case = (f"        case ItemId::{identifier}: return "
                    f"bn::sprite_items::{sprite_id}.create_sprite(sprite_x, sprite_y);\n")
        main = main[:match.start()] + new_case + main[match.end():]
        return header, main, old_sprite_id

    def save_passive(self) -> None:
        editing = self.editing_id is not None
        try:
            values = self._values()
            if editing:
                new_header, new_main, old_sprite_id = self._prepare_edited_sources(values)
            else:
                new_header, new_main = self._prepare_sources(values)
                old_sprite_id = ""
            assert self.sprite_source is not None
            _, height = validate_sprite_bmp(self.sprite_source)
            try:
                self.sprite_source.resolve().relative_to(GRAPHICS.resolve())
                source_is_graphic = self.sprite_source.stem.lower() == values["sprite_id"]
            except ValueError:
                source_is_graphic = False
            destination_bmp = (self.sprite_source if source_is_graphic else
                               GRAPHICS / f"{values['sprite_id']}.bmp")
            destination_json = destination_bmp.with_suffix(".json")
            same_existing_sprite = editing and values["sprite_id"] == old_sprite_id
            same_source_asset = destination_bmp.resolve() == self.sprite_source.resolve()
            if (destination_bmp.exists() and destination_bmp.resolve() != self.sprite_source.resolve()
                    and not same_existing_sprite):
                raise ValueError(f"Ya existe el sprite {destination_bmp.name}.")
            if destination_json.exists() and not (same_existing_sprite or same_source_asset):
                raise ValueError(f"Ya existe {destination_json.name}.")
        except (OSError, ValueError) as error:
            messagebox.showerror("No se puede guardar", str(error), parent=self)
            self.status.set("Corrige los campos marcados por el mensaje.")
            return

        action = "Guardar cambios" if editing else "Agregar objeto pasivo"
        summary = (f"Accion: {action}\nID: {values['identifier']}\nNombre: {values['display_name']}\n"
                   f"Precio: {values['price']} monedas\nSprite: {values['sprite_id']}.bmp\n\n"
                   "Se actualizaran passive_shop.h, main.cpp y graphics/.")
        if not messagebox.askokcancel(action, summary, parent=self):
            return

        original_header = read_text(SHOP_HEADER)
        original_main = read_text(MAIN_CPP)
        asset_backups: dict[Path, bytes | None] = {
            destination_bmp: destination_bmp.read_bytes() if destination_bmp.exists() else None,
            destination_json: destination_json.read_bytes() if destination_json.exists() else None,
        }
        try:
            SHOP_HEADER.write_text(new_header, encoding="utf-8", newline="\n")
            MAIN_CPP.write_text(new_main, encoding="utf-8", newline="\n")
            if destination_bmp.resolve() != self.sprite_source.resolve():
                shutil.copy2(self.sprite_source, destination_bmp)
            destination_json.write_text(
                '{\n    "type": "sprite",\n    "height": ' + str(height) + "\n}\n",
                encoding="utf-8", newline="\n")
        except Exception as error:
            SHOP_HEADER.write_text(original_header, encoding="utf-8", newline="\n")
            MAIN_CPP.write_text(original_main, encoding="utf-8", newline="\n")
            for path, backup in asset_backups.items():
                try:
                    if backup is None:
                        if path.exists():
                            path.unlink()
                    else:
                        path.write_bytes(backup)
                except OSError:
                    pass
            messagebox.showerror("Cambios restaurados", f"No se pudo escribir el objeto:\n{error}", parent=self)
            return

        if editing:
            message = "Los cambios del pasivo quedaron guardados."
        else:
            message = ("El objeto quedo registrado. Si una partida antigua ya habia agotado todos "
                       "los pasivos, conviene renovar su seleccion de tienda para evitar IDs de "
                       "consumibles desplazados.")
        messagebox.showinfo("Pasivo actualizado" if editing else "Pasivo agregado",
                            message, parent=self)
        self.reload_existing()
        self.clear_form()


def main() -> None:
    if not SHOP_HEADER.exists() or not MAIN_CPP.exists():
        raise SystemExit("Ejecuta este editor dentro del proyecto Another Dungeon.")
    app = PassiveEditor()
    app.mainloop()


if __name__ == "__main__":
    main()
