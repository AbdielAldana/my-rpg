# AnotherDungeon

## English

Temporary test site: [test.abdielaldana.com](https://test.abdielaldana.com).

AnotherDungeon is a dungeon exploration game for **Game Boy Advance**, written
in C++ with [Butano](https://github.com/GValiente/butano). Each run generates
floors and room connections from a seed. The player explores, finds items and
abilities, rescues adventurers, and advances through the stairs.

### Gameplay

The logo screen leads to a playable menu floor. Its upper door leads into the
dungeon. The menu lets you choose a seed, and the map displays it during a run.
The seed controls the floor layout and its random choices.

Each dungeon floor has one reward room selected from the available boss room
designs. Its entrance stays hidden until three levers are activated: one at
the campfire, one by the stairs, and the last in a seed-selected room. Rewards
in imported boss rooms come from their Q and & markers in the room JSON. The
stairs lead to the next floor.

Run progress is saved when changing floors and when returning to the main menu
from the pause menu. Dying clears that run and proposes a new seed. Records
track explored floors and rooms, deaths, rescued adventurers, discovered
abilities, and enemies seen.

#### Main controls

| Button | Action |
| --- | --- |
| D-pad | Move the player |
| B + D-pad | Run |
| A | Use the equipped ability |
| L | Open or close the map |
| R | Open the inventory |
| START | Open the pause menu |

Menus display their additional controls and options on screen.

### Building

The build environment needs **Butano, devkitPro, and Python**. The
[Makefile](Makefile) expects Butano at `../butano` and runs
`tools/import_room.py` before processing code and graphics. From the project
root, in a terminal configured for GBA development:

```bash
make
```

The JSON files in `rooms/` become constant ROM data during the build; the GBA
does not read JSON at runtime. Do not edit `include/imported_room.h` by hand:
the importer regenerates it.

### Project structure

| Path | Contents |
| --- | --- |
| `src/main.cpp` | Game loop, player, interface, and entities |
| `src/room_manager.cpp` | Floor generation and room connections |
| `src/game_save.cpp` | Run saves and records |
| `include/` | Declarations and the generated room catalog |
| `rooms/` | Room JSON files; [format and rules](rooms/README.md) |
| `graphics/` | Background and sprite BMP files with JSON settings |
| `audio/` and `dmg_audio/` | Sounds and music |
| `tools/` | Importer, converters, tests, and background registration |

The room editor is a separate project in `Pagina GBA`. It exports JSON files
that can be placed in `rooms/`. Additional rooms must follow the importer's
rules; `rooms/README.md` explains doors, markers, collisions, and boss rooms.
To check room import without building the ROM:

```bash
python -B tools/test_import_room.py
```

### Adding a background

Prepare an **uncompressed 256 × 256, 8-bit indexed BMP** and save it in
`graphics/`, for example `graphics/templo_1.bmp`. Then run this from the
project root:

```bash
python tools/register_background.py templo_1
```

You can also pass the full BMP path. In PowerShell, if `python` is unavailable
on `PATH`, this installation includes Python with Blender:

```powershell
& "C:\Program Files\Blender Foundation\Blender 4.5\4.5\python\bin\python.exe" .\tools\register_background.py templo_1
```

The script registers the background in the game and room editor, creates
`graphics/templo_1.json`, and copies the BMP into `Pagina GBA/assets_game/`.
Use `--dry-run` to preview changes or `--editor-dir PATH` if the editor is
elsewhere. Then set `"background": "templo_1"` in the room JSON and build the
game. Running the command again with the same name does not duplicate entries.

## Español

Sitio de prueba temporal: [test.abdielaldana.com](https://test.abdielaldana.com).

Juego de exploración de mazmorras para **Game Boy Advance**, desarrollado en C++
con [Butano](https://github.com/GValiente/butano). Cada partida genera pisos y
conexiones de cuartos a partir de una semilla. El jugador explora, encuentra
objetos y habilidades, rescata aventureros y avanza por las escaleras.

### Cómo se juega

La pantalla del logotipo lleva al piso menú. Desde su puerta superior se entra
a la mazmorra. Los pisos se generan con una semilla; el menú permite elegirla y
el mapa la muestra durante la partida. La semilla determina la distribución y
las elecciones aleatorias del piso.

Cada piso tiene una sala de recompensa elegida entre los diseños boss
disponibles. Su entrada permanece oculta hasta activar tres palancas: una en la
fogata, otra en las escaleras y la última en un cuarto elegido por la semilla.
Las recompensas de los boss importados dependen de los marcadores Q y & de su
JSON. Las escaleras llevan al siguiente piso.

El progreso de la partida se guarda al cambiar de piso y al volver al menú
principal desde la pausa. Al morir se borra esa partida y se propone otra
semilla. Los récords conservan pisos y cuartos explorados, muertes,
aventureros salvados, habilidades descubiertas y enemigos vistos.

#### Controles principales

| Botón | Acción |
| --- | --- |
| Cruceta | Mover al personaje |
| B + cruceta | Correr |
| A | Usar la habilidad equipada |
| L | Abrir o cerrar el mapa |
| R | Abrir el inventario |
| START | Abrir la pausa |

Los menús muestran sus controles y opciones adicionales en pantalla.

### Compilación

El proyecto requiere **Butano, devkitPro y Python** en el entorno de
compilación. El [Makefile](Makefile) busca Butano en `../butano` y ejecuta
`tools/import_room.py` antes de procesar el código y los gráficos. Desde la
raíz del proyecto, en la terminal configurada para GBA:

```bash
make
```

Los JSON de `rooms/` se convierten en datos constantes de ROM durante la
compilación; la consola no lee JSON en tiempo de ejecución. No edites
`include/imported_room.h` a mano porque se genera de nuevo.

### Estructura del proyecto

| Ruta | Contenido |
| --- | --- |
| `src/main.cpp` | Bucle del juego, jugador, interfaz y entidades |
| `src/room_manager.cpp` | Generación y conexiones de los pisos |
| `src/game_save.cpp` | Guardado de partidas y récords |
| `include/` | Declaraciones y catálogo de cuartos generado |
| `rooms/` | Diseños JSON de los cuartos; [formato y reglas](rooms/README.md) |
| `graphics/` | Fondos y sprites BMP con su configuración JSON |
| `audio/` y `dmg_audio/` | Efectos y música |
| `tools/` | Importador, conversores, pruebas y registro de fondos |

El editor de cuartos es un proyecto separado en `Pagina GBA`. Exporta JSON que
pueden colocarse en `rooms/`. Los cuartos adicionales deben respetar las reglas
del importador; el README de `rooms/` detalla puertas, marcadores, colisiones y
salas boss. Para verificar la importación sin compilar el ROM:

```bash
python -B tools/test_import_room.py
```

### Añadir un fondo

Prepara un BMP de **256 × 256 píxeles, 8 bits con paleta y sin compresión** y
guárdalo en `graphics/`, por ejemplo `graphics/templo_1.bmp`. Después ejecuta
desde la raíz del proyecto:

```bash
python tools/register_background.py templo_1
```

También puedes pasar la ruta completa del BMP. En PowerShell, si `python` no
está disponible en el `PATH`, esta instalación tiene Python con Blender:

```powershell
& "C:\Program Files\Blender Foundation\Blender 4.5\4.5\python\bin\python.exe" .\tools\register_background.py templo_1
```

El programa registra el fondo en el juego y en el editor, crea
`graphics/templo_1.json` y copia la imagen a `Pagina GBA/assets_game/`. Usa
`--dry-run` para revisar los cambios previstos o `--editor-dir RUTA` si el
editor está en otra ubicación. Luego establece `"background": "templo_1"` en
el JSON del cuarto y compila el juego. Repetir el comando con el mismo nombre
no duplica entradas.
