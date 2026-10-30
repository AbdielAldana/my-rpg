"""One-off conversion; never changes the composition text or runs a compiler."""
from pathlib import Path
import sys
from composition_room import convert_file

if __name__ == '__main__':
    if len(sys.argv) != 3:
        raise SystemExit('Usage: convert_composition.py source.txt output_directory')
    rooms = convert_file(Path(sys.argv[1]), Path(sys.argv[2]))
    print(f'Converted {len(rooms)} rooms.')
