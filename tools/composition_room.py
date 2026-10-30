"""Schema v2 adapter for the fourteen existing composition behavior profiles."""
import json
from pathlib import Path
import re
import uuid

BINDINGS = {
    'inicio_menu': ('Inicio Menu', 'TUTORIAL', 'menu'),
    'inicio': ('Inicio', 'TUTORIAL', 'start'),
    'boss_1_ant': ('Boss 1 Ant', 'REWARD', 'reward'),
    'fogata': ('Fogata', 'SPECIAL', 'campfire'),
    'cuarto_final_escaleras': ('Cuarto Final Escaleras', 'STAIRS', 'stairs'),
    'cuarto_final_escaleras_2': ('Cuarto Final Escaleras 2', 'STAIRS_2', 'stairs'),
    'cuarto_1': ('Cuarto 1', 'COMPOSITION_1', 'normal'),
    'cuarto_1_2': ('Cuarto 1.2', 'COMPOSITION_1_2', 'normal'),
    'cuarto_2': ('Cuarto 2', 'COMPOSITION_2', 'normal'),
    'cuarto_2_2': ('Cuarto 2.2', 'COMPOSITION_2_2', 'normal'),
    'cuarto_3': ('Cuarto 3', 'COMPOSITION_3', 'normal'),
    'cuarto_4': ('Cuarto 4', 'COMPOSITION_4', 'normal'),
    'cuarto_5': ('Cuarto 5', 'PLANT_GARDEN', 'normal'),
    'cuarto_6': ('Cuarto 6', 'PLANT_CENTER_ROOM', 'normal'),
}
BACKGROUNDS = {1: 'land', 2: 'room_campfire', 3: 'room2', 4: 'room3',
               5: 'boss_1', 6: 'menu_inicio', 9: 'room_tutorial'}
BG_ENUM = dict(zip(BACKGROUNDS.values(), ('LAND', 'CAMPFIRE', 'ROOM2', 'ROOM3', 'BOSS_ROOM', 'MENU_START', 'TUTORIAL')))
# symbol: assetId, width, height, role, available frames
ASSETS = {
    'x': ('column', 16, 32, 'decoration', 1),
    'b': ('library_back', 16, 32, 'decoration', 1),
    'f': ('library_front', 16, 32, 'decoration', 1),
    'c': ('campfire', 16, 32, 'interactive', 4),
    'p': ('stone', 16, 16, 'decoration', 1),
    'o': ('box', 16, 16, 'decoration', 1),
    'm': ('bat', 16, 16, 'enemy', 16),
    's': ('skeleton', 16, 16, 'enemy', 16),
    'j': ('plant', 16, 16, 'enemy', 16),
    'h': ('mushy', 16, 16, 'enemy', 16),
    'e': ('stairs', 16, 16, 'interactive', 1),
    'l': ('lever', 16, 16, 'lever', 3),
    'v': ('vase', 16, 16, 'decoration', 1),
    't': ('sign', 16, 16, 'decoration', 1),
    'i': ('chair', 16, 16, 'decoration', 4),
    'n': ('table', 32, 16, 'decoration', 1),
    'w': ('weapon_table', 32, 16, 'decoration', 1),
    'g': ('chest', 16, 16, 'decoration', 3),
    'z': ('axe', 16, 16, 'decoration', 1),
    'd': ('spikes', 16, 16, 'hazard', 3),
}
BY_ASSET = {value[0]: (key, *value[1:]) for key, value in ASSETS.items()}
NAMESPACE = uuid.UUID('3a9437de-6f96-4640-a91a-a8b601a351b4')


def stable_id(value):
    return str(uuid.uuid5(NAMESPACE, value))


def point(row, col):
    return {'x': 16 + col * 16, 'y': 56 + row * 16}


def parse_composition(text):
    lines = text.splitlines()
    sections = []
    for index, line in enumerate(lines):
        if not line.startswith('Fondo '):
            continue
        title = lines[index - 1].strip()
        binding = next((key for key, value in BINDINGS.items() if value[0] == title), None)
        if binding is None:
            raise ValueError(f'Unknown composition: {title}')
        backgrounds = [BACKGROUNDS[int(number)] for number in re.findall(r'\d+', line)]
        rows = []
        for entry in lines[index + 1:]:
            match = re.match(r'^\s*(?:FILA\s*|↓\s*)?(\d{2})\s+(.+)$', entry)
            if match and len(match[2].split()) == 15:
                number = int(match[1])
                if number != len(rows):
                    raise ValueError(f'{title}: unexpected row {number}')
                rows.append(match[2].split())
                if len(rows) == 10:
                    break
        if len(rows) != 10:
            raise ValueError(f'{title}: expected 10 rows')
        sections.append((binding, backgrounds, rows))
    if {entry[0] for entry in sections} != set(BINDINGS) or len(sections) != 14:
        raise ValueError('Expected all fourteen compositions')
    return sections


def convert(binding, backgrounds, grid):
    name, template, kind = BINDINGS[binding]
    data = dict(format='anotherdungeon-room', schemaVersion=2,
                id=stable_id(binding), name=name, description='Convertido de Cuartos Composicion.txt',
                width=256, height=256, tileSize=16, coordinateSystem='top-left-pixels',
                background=backgrounds[0], backgroundOptions=backgrounds,
                spawn={'x': 128, 'y': 128}, tiles=[], collisions=[], objects=[], markers=[],
                runtimeBinding=binding, roomKind=kind, doorPolicy='declared-sides-only',
                source={'file': 'Cuartos Composicion.txt', 'grid': [''.join(row) for row in grid]})
    occupied = set()
    enemy_slots = {}
    for row in range(10):
        for col in range(15):
            symbol = grid[row][col]
            if (row, col) in occupied or symbol in ('·', '-'):
                continue
            identity = f'{binding}:{row}:{col}'
            center = point(row, col)
            if symbol == '%':
                data['collisions'].append(dict(id=stable_id(identity), x=8+col*16,
                                               y=48+row*16, width=16, height=16,
                                               sourceCell={'row': row, 'col': col}))
                continue
            if symbol in 'Q&$123':
                types = ['random', 'ability'] if symbol == '$' else [
                    'random' if symbol == 'Q' else ('ability' if symbol == '&' else 'npc_delivery')]
                for marker_type in types:
                    marker = dict(id=stable_id(identity + ':' + marker_type), type=marker_type,
                                  **center, required=kind == 'reward', sourceSymbol=symbol,
                                  sourceCell={'row': row, 'col': col})
                    if symbol in '123':
                        marker['slot'] = int(symbol) - 1
                    data['markers'].append(marker)
                continue
            if symbol in 'rR':
                if col in (0, 14):
                    if row != 4 or grid[5][col] != symbol:
                        raise ValueError(f'{name}: side door must occupy rows 4 and 5')
                    occupied.add((5, col))
                    side, rotation = ('left', 0) if col == 0 else ('right', 180)
                    x, y = 8 + col * 16, 112
                elif col == 7 and row in (0, 9):
                    side, rotation = ('up', 270) if row == 0 else ('down', 90)
                    x, y = 112, 48 + row * 16
                else:
                    raise ValueError(f'{name}: door not at a supported edge')
                data['objects'].append(dict(id=stable_id(identity), assetId='door', x=x, y=y,
                    frame=0, rotation=rotation, flipX=False, solid=False,
                    hitbox={'x': 0, 'y': 0, 'width': 16, 'height': 32}, role='door',
                    side=side, rule='required' if symbol == 'R' else 'possible', destination='',
                    access='three-levers' if kind == 'reward' else ('closed' if kind == 'menu' and side != 'up' else 'normal'),
                    hiddenUntil='three-levers' if kind == 'reward' else '',
                    sourceSymbol=symbol, sourceCell={'row': row, 'col': col}))
                continue
            key = symbol.lower()
            if key not in ASSETS:
                raise ValueError(f'{name}: unknown symbol {symbol}')
            asset, width, height, role, _ = ASSETS[key]
            x, y = 8 + col * 16, 48 + row * 16
            if key in 'xfb':
                if row == 9 or grid[row+1][col] != symbol:
                    raise ValueError(f'{name}: {symbol} missing second cell')
                occupied.add((row+1, col))
            elif key in 'nw':
                if col == 14 or grid[row][col+1] != symbol:
                    raise ValueError(f'{name}: {symbol} missing second cell')
                occupied.add((row, col+1))
            elif key == 'c':
                y -= 8  # Single c names the fire's center cell, not its top edge.
            frame = 0
            if key == 'i':
                frame = 0 if row == 2 else (1 if row == 4 else (3 if col == 2 else 2))
            hb = {'x': 3, 'y': 0, 'width': width-6, 'height': height-8}
            if height == 32:
                hb = {'x': 5, 'y': 16, 'width': 6, 'height': 8}
            obj = dict(id=stable_id(identity), assetId=asset, x=x, y=y, frame=frame,
                       rotation=0, flipX=kind == 'campfire' and key in 'fb' and col > 7,
                       solid=role in ('decoration', 'lever') and key != 'i', hitbox=hb,
                       role=role, destination='', sourceSymbol=symbol,
                       sourceCell={'row': row, 'col': col},
                       collisionProfile='legacy-base' if key in 'xfb' else 'explicit')
            if role == 'enemy':
                slot = enemy_slots.get(asset, 0)
                enemy_slots[asset] = slot + 1
                if binding == 'cuarto_3':
                    slot = {(3,3): 0, (6,3): 1, (3,11): 2, (6,11): 3}[(row,col)]
                obj['runtimeSlot'] = slot
                obj['spawnMode'] = 'seeded'
                obj['authoredAxis'] = 'horizontal' if symbol.islower() else 'vertical'
                obj['behavior'] = {'bat':'bounce', 'skeleton':'patrol', 'plant':'stationary-shooter', 'mushy':'wander'}[asset]
                if key == 's':
                    dr, dc = (0,1) if symbol.islower() else (1,0)
                    first_r, first_c, last_r, last_c = row, col, row, col
                    allowed = set('-sSQ')
                    while 0 <= first_r-dr < 10 and 0 <= first_c-dc < 15 and grid[first_r-dr][first_c-dc] in allowed:
                        first_r -= dr; first_c -= dc
                    while 0 <= last_r+dr < 10 and 0 <= last_c+dc < 15 and grid[last_r+dr][last_c+dc] in allowed:
                        last_r += dr; last_c += dc
                    obj['patrol'] = {'axis': obj['authoredAxis'], 'from': point(first_r,first_c),
                                     'to': point(last_r,last_c), 'mode': 'ping-pong'}
            elif role == 'lever':
                obj['behavior'] = 'reward-lever'
                obj['spawnMode'] = 'choose-one-per-room-by-seed'
            elif key == 'g':
                obj['behavior'] = 'proximity-chest'
                obj['animation'] = {'idleFrame':0, 'transitionFrame':1, 'nearFrame':2,
                                    'stepFrames':8, 'openRadius':32, 'closeRadius':40}
            elif key == 'd':
                obj['alwaysActive'] = symbol == 'D'
            data['objects'].append(obj)
    if kind == 'reward':
        data['placement'] = {'relativeToExistingRoom': 'left', 'entrySide': 'right'}
        data['access'] = {'type': 'three-levers', 'requiresKey': False}
    return data


def convert_file(source, destination):
    rooms = [convert(*entry) for entry in parse_composition(source.read_text(encoding='utf-8-sig'))]
    destination.mkdir(parents=True, exist_ok=True)
    for data in rooms:
        target = destination / (data['runtimeBinding'] + '.json')
        target.write_text(json.dumps(data, ensure_ascii=False, indent=2) + '\n', encoding='utf-8', newline='\n')
    return rooms


def number(value, label, minimum=0, maximum=256):
    if type(value) is not int or not minimum <= value <= maximum:
        raise ValueError(f'{label}: expected integer {minimum}..{maximum}')
    return value


def validate(data):
    binding = data.get('runtimeBinding')
    if data.get('format') != 'anotherdungeon-room' or data.get('schemaVersion') != 2 or binding not in BINDINGS:
        raise ValueError('Schema v2 currently requires a known composition runtimeBinding')
    _, _, kind = BINDINGS[binding]
    if data.get('roomKind') != kind:
        raise ValueError('roomKind does not match the composition behavior profile')
    if (data.get('width'),data.get('height'),data.get('tileSize'),data.get('coordinateSystem')) != (256,256,16,'top-left-pixels'):
        raise ValueError('Expected 256x256, 16px tiles, top-left-pixels')
    if data.get('tiles') or data.get('doorPolicy') != 'declared-sides-only':
        raise ValueError('Unsupported tiles or door policy')
    options = data.get('backgroundOptions')
    if not isinstance(options,list) or not options or any(item not in BG_ENUM for item in options):
        raise ValueError('Invalid backgroundOptions')
    if data.get('background') not in options:
        raise ValueError('background must be included in backgroundOptions')
    ids, sides = set(), set()
    if not isinstance(data.get('objects'),list) or len(data['objects']) > 64:
        raise ValueError('Expected at most 64 objects')
    for obj in data['objects'] + data.get('markers',[]) + data.get('collisions',[]):
        identity = obj.get('id')
        if not isinstance(identity,str) or not identity or identity in ids:
            raise ValueError('All object, marker and collision IDs must be unique')
        ids.add(identity)
        number(obj.get('x'),'x'); number(obj.get('y'),'y')
    for obj in data['objects']:
        asset = obj.get('assetId')
        if asset == 'door':
            if obj.get('role') != 'door' or obj.get('side') not in ('left','right','up','down') or obj.get('side') in sides:
                raise ValueError('Invalid or duplicate door side')
            sides.add(obj['side'])
            if obj.get('rule') not in ('possible','required') or obj.get('destination',''):
                raise ValueError('Doors need possible/required rules and seeded destinations')
            if type(obj.get('rotation')) is not int or obj['rotation'] not in (0,90,180,270):
                raise ValueError('Door requires a quarter-turn rotation')
            continue
        if asset not in BY_ASSET:
            raise ValueError('Unsupported composition asset: ' + str(asset))
        symbol,width,height,role,frames = BY_ASSET[asset]
        if obj.get('role') != role:
            raise ValueError('Object role does not match its asset')
        number(obj.get('frame'),'frame',0,frames-1)
        if obj.get('rotation') != 0 or type(obj.get('flipX')) is not bool or type(obj.get('solid')) is not bool:
            raise ValueError('Composition objects require rotation 0 and boolean flipX/solid')
        if symbol == 'i' and obj['solid']:
            raise ValueError('Chairs must not be solid')
        hb = obj.get('hitbox',{})
        hx=number(hb.get('x'),'hitbox.x',0,width); hy=number(hb.get('y'),'hitbox.y',0,height)
        hw=number(hb.get('width'),'hitbox.width',1,width); hh=number(hb.get('height'),'hitbox.height',1,height)
        if hx+hw > width or hy+hh > height:
            raise ValueError('Hitbox exceeds sprite frame')
        if obj.get('collisionProfile','explicit') not in ('explicit','legacy-base'):
            raise ValueError('Unknown collisionProfile')
        if role == 'enemy':
            number(obj.get('runtimeSlot'),'runtimeSlot',0,3)
            if obj.get('spawnMode') != 'seeded' or obj.get('solid'):
                raise ValueError('Enemies require seeded appearance and solid=false')
            if hb != {'x':3,'y':0,'width':10,'height':8}:
                raise ValueError('Native 16x16 enemies use the agreed 10x8 top hitbox')
            if asset == 'skeleton':
                route = obj.get('patrol',{})
                if route.get('mode') != 'ping-pong' or route.get('axis') not in ('horizontal','vertical'):
                    raise ValueError('Skeleton requires an explicit ping-pong patrol')
                for key in ('from','to'):
                    number(route.get(key,{}).get('x'),'patrol.x'); number(route.get(key,{}).get('y'),'patrol.y')
                a,b=route['from'],route['to']
                if not ((route['axis']=='horizontal' and a['y']==b['y'] and a['x']<b['x']) or
                        (route['axis']=='vertical' and a['x']==b['x'] and a['y']<b['y'])):
                    raise ValueError('Patrol endpoints must follow the declared axis')
    for asset in ('bat','skeleton','plant','mushy'):
        enemies=[obj for obj in data['objects'] if obj.get('assetId')==asset]
        if len(enemies)>4 or sorted(obj['runtimeSlot'] for obj in enemies)!=list(range(len(enemies))):
            raise ValueError('Enemy slots must be consecutive, with at most four candidates')
    for marker in data.get('markers',[]):
        if marker.get('type') not in ('random','ability','npc_delivery') or type(marker.get('required')) is not bool:
            raise ValueError('Invalid marker type or required flag')
    for rect in data.get('collisions',[]):
        number(rect.get('width'),'collision.width',1); number(rect.get('height'),'collision.height',1)
        if rect['x']+rect['width']>256 or rect['y']+rect['height']>256:
            raise ValueError('Collision rectangle exceeds canvas')
    expected_enemies = {'cuarto_1':('bat',2),'cuarto_1_2':('mushy',2),'cuarto_2':('bat',4),
                        'cuarto_2_2':('mushy',4),'cuarto_3':('skeleton',4),'cuarto_4':('skeleton',4),
                        'cuarto_5':('plant',4),'cuarto_6':('plant',1),
                        'cuarto_final_escaleras':('bat',2),'cuarto_final_escaleras_2':('plant',2)}
    enemy_objects=[obj for obj in data['objects'] if obj['role']=='enemy']
    expected = expected_enemies.get(binding)
    if expected and (len(enemy_objects)!=expected[1] or any(obj['assetId']!=expected[0] for obj in enemy_objects)):
        raise ValueError('This behavior profile requires its original enemy candidate count/type')
    if not expected and enemy_objects:
        raise ValueError('This behavior profile does not spawn enemies')
    if not sides:
        raise ValueError('Composition requires at least one door')
    if sum(obj['assetId']=='stone' for obj in data['objects']) > 26:
        raise ValueError('Current runtime supports at most 26 stones per room')
    if sum(obj['assetId']=='spikes' for obj in data['objects']) > 12:
        raise ValueError('Current runtime supports at most 12 spikes per room')
    if binding in ('fogata','cuarto_final_escaleras','cuarto_final_escaleras_2') and sum(obj['assetId']=='lever' for obj in data['objects'])!=2:
        raise ValueError('Campfire/stairs profiles require two candidate lever positions')
    if binding=='cuarto_final_escaleras_2' and (sides!={'down'} or next(obj for obj in data['objects'] if obj['role']=='door')['rule']!='required'):
        raise ValueError('Stairs 2 requires only its bottom door')
    if kind=='normal' and not any(m['type']=='random' for m in data['markers']):
        raise ValueError('Normal composition rooms require Q spawn markers')
    if binding=='fogata':
        if sum(obj['assetId']=='campfire' for obj in data['objects'])!=1 or sum(m['type']=='ability' for m in data['markers'])!=1:
            raise ValueError('Campfire requires its fire and shared Q/ability reward marker')
        slots=sorted(m.get('slot',-1) for m in data['markers'] if m['type']=='npc_delivery')
        if slots!=[0,1,2]:
            raise ValueError('Campfire requires its three NPC delivery positions')
    if kind=='stairs' and sum(obj['assetId']=='stairs' for obj in data['objects'])!=1:
        raise ValueError('Stairs profile requires one stair object')
    if sum(obj['assetId']=='chest' for obj in data['objects']) > (1 if kind=='menu' else 0):
        raise ValueError('Animated decorative chest currently belongs to the menu profile')
    if binding=='boss_1_ant':
        if sides!={'right'} or next(obj for obj in data['objects'] if obj['role']=='door')['rule']!='required':
            raise ValueError('Boss 1 must have only its required right door')
        markers=data['markers']
        if sum(item['type']=='random' and item['required'] for item in markers)!=3 or sum(item['type']=='ability' and item['required'] for item in markers)!=1:
            raise ValueError('Boss 1 requires three Q rewards and one ability reward')
        if data.get('access')!={'type':'three-levers','requiresKey':False}:
            raise ValueError('Boss 1 requires three levers and no key')
    return data


def generate_cpp(entries, cpp_string):
    rooms={}
    for source,data in entries:
        try:
            validate(data)
            binding=data['runtimeBinding']
            if binding in rooms:
                raise ValueError('Duplicate runtimeBinding: '+binding)
            rooms[binding]=data
        except (ValueError,KeyError,TypeError,AttributeError) as error:
            raise ValueError(f'{source}: {error}') from error
    if set(rooms)!=set(BINDINGS):
        raise ValueError('Missing composition JSON files: '+', '.join(sorted(set(BINDINGS)-set(rooms))))
    out=['namespace composition_rooms','{',
         'struct Point { int x; int y; };',
         'struct Object { char type; int x; int y; int width; int height; int frame; bool flip_x; bool solid; bool legacy_base; game::Hitbox hitbox; };',
         'struct Rect { int x; int y; int width; int height; };',
         'struct Spike { int x; int y; bool always_active; };',
         'struct Route { int x; int y; int end_x; int end_y; int initial_offset; };',
         'struct Door { int x; int y; int rotation; int rule; };',
         'template<class T> struct Range { const T* data; int size;',
         '    constexpr const T* begin() const { return data; }',
         '    constexpr const T* end() const { return data + size; }',
         '    constexpr const T& operator[](int index) const { return data[index]; } };',
         'struct Room { RoomTemplateId template_id; bool menu; bool ordinary; const char* name;',
         '    Range<Object> objects; Range<Point> stones; Range<Point> q_points; Range<Point> ability_points;',
         '    Range<Point> levers; Range<Point> bats; Range<Point> mushies; Range<Point> plants;',
         '    Range<Point> npc_positions; Range<Route> skeletons; Range<Spike> spikes;',
         '    Range<Rect> collisions; Range<RoomBackgroundId> backgrounds; Door doors[4];',
         "    constexpr Point position(char type) const { for(const Object& o : objects) if(o.type == type) return {o.x,o.y}; return {0,0}; }",'};','']
    maxima={'decorations':1,'stones':1}
    def array(type_name,name,rows):
        out.append(f'constexpr {type_name} {name}[] = {{')
        out.extend('    '+row+',' for row in (rows or ['{}']))
        out.append('};')
        return f'{{{name}, {len(rows)}}}'
    records=[]
    for binding in BINDINGS:
        data=rooms[binding]
        objects=data['objects']
        ranges={}
        deco=[]
        for obj in objects:
            if obj['role'] not in ('decoration','interactive'):
                continue
            symbol,w,h,_,_=BY_ASSET[obj['assetId']]
            hb=obj['hitbox']
            deco.append("{'%s', %d, %d, %d, %d, %d, %s, %s, %s, {%d, %d, %d, %d}}" % (
                symbol,obj['x']+w//2-128,obj['y']+h//2-128,w,h,obj['frame'],
                str(obj['flipX']).lower(),str(obj['solid']).lower(),str(obj.get('collisionProfile')=='legacy-base').lower(),
                hb['x']-w//2,hb['x']+hb['width']-w//2,hb['y']-h//2,hb['y']+hb['height']-h//2))
        ranges['objects']=array('Object',binding+'_objects',deco)
        maxima['decorations']=max(maxima['decorations'],len(deco))
        for key,asset in [('stones','stone'),('levers','lever'),('bats','bat'),('mushies','mushy'),('plants','plant')]:
            candidates=[obj for obj in objects if obj['assetId']==asset]
            if key in ('bats','mushies','plants'):
                candidates.sort(key=lambda obj:obj['runtimeSlot'])
            rows=['{%d, %d}'%(obj['x']-120,obj['y']-120) for obj in candidates]
            ranges[key]=array('Point',binding+'_'+key,rows)
            if key=='stones': maxima['stones']=max(maxima['stones'],len(rows))
        for key,marker_type in [('q_points','random'),('ability_points','ability'),('npc_positions','npc_delivery')]:
            candidates=[marker for marker in data['markers'] if marker['type']==marker_type]
            if key=='npc_positions': candidates.sort(key=lambda marker:marker['slot'])
            ranges[key]=array('Point',binding+'_'+key,['{%d, %d}'%(m['x']-128,m['y']-128) for m in candidates])
        candidates=sorted((obj for obj in objects if obj['assetId']=='skeleton'),key=lambda obj:obj['runtimeSlot'])
        routes=[]
        for obj in candidates:
            a,b=obj['patrol']['from'],obj['patrol']['to']
            offset=abs(obj['x']+8-a['x'])+abs(obj['y']+8-a['y'])
            routes.append('{%d, %d, %d, %d, %d}'%(a['x']-128,a['y']-128,b['x']-128,b['y']-128,offset))
        ranges['skeletons']=array('Route',binding+'_skeletons',routes)
        ranges['spikes']=array('Spike',binding+'_spikes',['{%d, %d, %s}'%(obj['x']-120,obj['y']-120,str(obj['alwaysActive']).lower()) for obj in objects if obj['assetId']=='spikes'])
        ranges['collisions']=array('Rect',binding+'_collisions',['{%d, %d, %d, %d}'%(r['x']-128,r['y']-128,r['width'],r['height']) for r in data['collisions']])
        ranges['backgrounds']=array('RoomBackgroundId',binding+'_backgrounds',['RoomBackgroundId::'+BG_ENUM[item] for item in data['backgroundOptions']])
        doors=[]
        for side in ('left','right','up','down'):
            obj=next((obj for obj in objects if obj['role']=='door' and obj['side']==side),None)
            if not obj: doors.append('{0,0,0,0}'); continue
            w,h=(32,16) if obj['rotation']%180 else (16,32)
            doors.append('{%d, %d, %d, %d}'%(obj['x']+w//2-128,obj['y']+h//2-128,obj['rotation'],2 if obj['rule']=='required' else 1))
        _,template,kind=BINDINGS[binding]
        order=('objects','stones','q_points','ability_points','levers','bats','mushies','plants','npc_positions','skeletons','spikes','collisions','backgrounds')
        records.append('    {RoomTemplateId::%s, %s, %s, %s,\n        %s,\n        {%s}},'%(template,str(kind=='menu').lower(),str(kind=='normal').lower(),cpp_string(data['name']),', '.join(ranges[key] for key in order),', '.join(doors)))
    out+=['constexpr Room rooms[] = {',*records,'};',
          f"constexpr int max_decoration_count = {maxima['decorations']};",
          f"constexpr int max_stones = {maxima['stones']};",
          'constexpr const Room* find(RoomTemplateId template_id, bool menu = false) {',
          '    for(const Room& room : rooms) if(room.template_id == template_id && room.menu == menu) return &room;',
          '    return nullptr; }',
          'constexpr bool allows(RoomTemplateId template_id, RoomDirection direction, bool menu = false) {',
          '    const Room* room = find(template_id, menu); return !room || room->doors[int(direction)].rule != 0; }',
          'constexpr Point campfire_position = find(RoomTemplateId::SPECIAL)->position(\'c\');',
          'constexpr Point campfire_reward_position = fogata_ability_points[0];',
          'constexpr int delivered_npc_offsets[][2] = {']
    fire=next(obj for obj in rooms['fogata']['objects'] if obj['assetId']=='campfire')
    fx,fy=fire['x']+8,fire['y']+16
    markers=sorted((m for m in rooms['fogata']['markers'] if m['type']=='npc_delivery'),key=lambda m:m['slot'])
    out+=['    {%d,%d},'%(m['x']-fx,m['y']-fy) for m in markers]
    out+=['};','constexpr int plant_positions[][2] = {']
    for binding,count in [('cuarto_5',4),('cuarto_6',1),('cuarto_final_escaleras_2',2)]:
        objs=sorted((o for o in rooms[binding]['objects'] if o['assetId']=='plant'),key=lambda o:o['runtimeSlot'])
        if len(objs)!=count: raise ValueError('Plant profile slot count changed')
        out+=['    {%d,%d},'%(o['x']-120,o['y']-120) for o in objs]
    out+=['};','}', '']
    return '\n'.join(out)
