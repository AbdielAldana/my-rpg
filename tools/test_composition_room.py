"""Composition conversion checks; does not compile or run a ROM."""
import copy
import json
from pathlib import Path
import tempfile
import unittest

import composition_room as composition
import import_room

ROOT = Path(__file__).resolve().parents[1]


class CompositionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.sections = composition.parse_composition((ROOT/'Cuartos Composicion.txt').read_text(encoding='utf-8-sig'))
        cls.converted = {key: composition.convert(key, backgrounds, grid) for key, backgrounds, grid in cls.sections}

    def test_all_fourteen_exported_files_match_source(self):
        self.assertEqual(set(self.converted), set(composition.BINDINGS))
        # Validate fresh conversion output, not editable game files: changing a
        # room name or layout after conversion is intentional and must be allowed.
        with tempfile.TemporaryDirectory() as temporary:
            output=Path(temporary)
            composition.convert_file(ROOT/'Cuartos Composicion.txt',output)
            for key, expected in self.converted.items():
                with self.subTest(room=key):
                    actual=json.loads((output/f'{key}.json').read_text(encoding='utf-8'))
                    self.assertEqual(actual,expected)
                    composition.validate(actual)

    def test_every_nonempty_cell_is_represented_once(self):
        for key, _, grid in self.sections:
            data = self.converted[key]
            covered = set()
            for obj in data['objects']:
                row, col = obj['sourceCell']['row'], obj['sourceCell']['col']
                cells = [(row,col)]
                if obj['assetId'] in ('column','library_back','library_front'):
                    cells += [(row+1,col)]
                elif obj['assetId'] in ('table','weapon_table'):
                    cells += [(row,col+1)]
                elif obj['assetId']=='door' and obj['side'] in ('left','right'):
                    cells += [(row+1,col)]
                for cell in cells:
                    self.assertNotIn(cell, covered, (key,cell))
                    covered.add(cell)
            for item in data['markers'] + data['collisions']:
                cell=(item['sourceCell']['row'],item['sourceCell']['col'])
                if item.get('sourceSymbol')=='$' and cell in covered:
                    continue  # Shared ability and random marker, intentionally one cell.
                self.assertNotIn(cell,covered,(key,cell))
                covered.add(cell)
            expected={(r,c) for r in range(10) for c in range(15) if grid[r][c] not in ('·','-')}
            self.assertEqual(expected,covered,key)
            self.assertEqual([''.join(row) for row in grid],data['source']['grid'])

    def test_coordinate_conversion_and_multi_cell_objects(self):
        menu=self.converted['inicio_menu']['objects']
        table=next(obj for obj in menu if obj['assetId']=='table')
        self.assertEqual((56,96),(table['x'],table['y']))
        columns=[obj for obj in menu if obj['assetId']=='column']
        self.assertEqual(4,len(columns))
        self.assertEqual((24,48),(columns[0]['x'],columns[0]['y']))
        self.assertEqual(26,len([obj for obj in menu if obj['role']=='decoration']))
        fire=next(obj for obj in self.converted['fogata']['objects'] if obj['assetId']=='campfire')
        self.assertEqual((120,104),(fire['x'],fire['y']))

    def test_top_hitboxes_chairs_and_chest_frames(self):
        for data in self.converted.values():
            for obj in data['objects']:
                if obj['assetId']=='door': continue
                _,w,h,_,_=composition.BY_ASSET[obj['assetId']]
                if (w,h)==(16,16):
                    self.assertEqual(dict(x=3,y=0,width=10,height=8),obj['hitbox'])
                if obj['assetId']=='chair': self.assertFalse(obj['solid'])
        chest=next(o for o in self.converted['inicio_menu']['objects'] if o['assetId']=='chest')
        self.assertEqual((0,1,2),tuple(chest['animation'][key] for key in ('idleFrame','transitionFrame','nearFrame')))
        seats=[o['frame'] for o in self.converted['inicio_menu']['objects'] if o['assetId']=='chair']
        self.assertEqual([0,0,3,2,1,1],seats)

    def test_door_rules_and_menu_closed_sides(self):
        boss=[o for o in self.converted['boss_1_ant']['objects'] if o['role']=='door']
        self.assertEqual([('right','required','three-levers')],[(o['side'],o['rule'],o['access']) for o in boss])
        stairs=[o for o in self.converted['cuarto_final_escaleras_2']['objects'] if o['role']=='door']
        self.assertEqual([('down','required')],[(o['side'],o['rule']) for o in stairs])
        menu=[o for o in self.converted['inicio_menu']['objects'] if o['role']=='door']
        self.assertEqual(4,len(menu))
        self.assertEqual({'up':'normal','left':'closed','right':'closed','down':'closed'},{o['side']:o['access'] for o in menu})

    def test_reward_markers_and_invisible_rows_four_and_five(self):
        data=self.converted['boss_1_ant']
        self.assertEqual(3,sum(m['type']=='random' and m['required'] for m in data['markers']))
        self.assertEqual(1,sum(m['type']=='ability' and m['required'] for m in data['markers']))
        self.assertEqual(set(range(1,9)),{r['sourceCell']['row'] for r in data['collisions']})
        self.assertTrue(all(r['sourceCell']['col']==5 for r in data['collisions']))
        self.assertEqual({'type':'three-levers','requiresKey':False},data['access'])

    def test_random_candidates_and_shared_campfire_reward(self):
        expected={'cuarto_1':4,'cuarto_1_2':4,'cuarto_2':2,'cuarto_2_2':2,'cuarto_3':2,'cuarto_4':4,'cuarto_5':4,'cuarto_6':2}
        for key,count in expected.items():
            self.assertEqual(count,sum(m['type']=='random' for m in self.converted[key]['markers']))
        for key in ('fogata','cuarto_final_escaleras','cuarto_final_escaleras_2'):
            self.assertEqual(2,sum(o['role']=='lever' for o in self.converted[key]['objects']))
        markers=[m for m in self.converted['fogata']['markers'] if m['sourceSymbol']=='$']
        self.assertEqual({'random','ability'},{m['type'] for m in markers})
        self.assertEqual(1,len({(m['x'],m['y']) for m in markers}))

    def test_skeleton_patrols_keep_original_slot_geometry(self):
        expected={'cuarto_3':[(64,104,64,152,0),(64,104,64,152,48),(192,104,192,152,0),(192,104,192,152,48)],
                  'cuarto_4':[(64,88,192,88,0),(192,88,192,168,0),(64,88,64,168,80),(64,168,192,168,128)]}
        for key,routes in expected.items():
            objects=sorted((o for o in self.converted[key]['objects'] if o['assetId']=='skeleton'),key=lambda o:o['runtimeSlot'])
            actual=[]
            for obj in objects:
                a,b=obj['patrol']['from'],obj['patrol']['to']
                offset=abs(obj['x']+8-a['x'])+abs(obj['y']+8-a['y'])
                actual.append((a['x'],a['y'],b['x'],b['y'],offset))
            self.assertEqual(routes,actual)

    def test_seeded_enemy_spawn_slots_preserved(self):
        expected={'cuarto_1':[(64,-24),(-64,24)],'cuarto_2':[(-16,-40),(-32,-8),(32,-8),(16,24)],
                  'cuarto_final_escaleras':[(-64,-40),(64,24)],
                  'cuarto_5':[(-80,-40),(80,-40),(-80,40),(80,40)],
                  'cuarto_6':[(0,-8)],'cuarto_final_escaleras_2':[(-96,-8),(96,-8)]}
        for key,positions in expected.items():
            enemies=sorted((o for o in self.converted[key]['objects'] if o['role']=='enemy'),key=lambda o:o['runtimeSlot'])
            self.assertEqual(positions,[(o['x']-120,o['y']-120) for o in enemies])

    def test_background_pools_and_profile_identity(self):
        for key,backgrounds,_ in self.sections:
            self.assertEqual(backgrounds,self.converted[key]['backgroundOptions'])
        header=import_room.load_catalog(ROOT/'rooms')
        extra_rooms=sum('runtimeBinding' not in json.loads(path.read_text(encoding='utf-8-sig')) for path in (ROOT/'rooms').glob('*.json'))
        self.assertIn(f'constexpr int room_count = {extra_rooms};',header)
        self.assertIn('namespace composition_rooms',header)
        self.assertIn('{RoomTemplateId::REWARD, false, false,',header)
        self.assertIn('{RoomTemplateId::TUTORIAL, true, false,',header)

    def test_invalid_native_rules_rejected_with_filename(self):
        variants=[]
        boss=copy.deepcopy(self.converted['boss_1_ant'])
        next(o for o in boss['objects'] if o['role']=='door')['side']='left'
        variants.append(boss)
        boss=copy.deepcopy(self.converted['boss_1_ant'])
        boss['markers'].pop()
        variants.append(boss)
        fire=copy.deepcopy(self.converted['fogata'])
        fire['objects']=[o for o in fire['objects'] if o['assetId']!='lever']
        variants.append(fire)
        for bad in variants:
            entries=[(key+'.json',bad if key==bad['runtimeBinding'] else data) for key,data in self.converted.items()]
            with self.assertRaisesRegex(ValueError,bad['runtimeBinding']+'.json:'):
                import_room.generate_catalog(entries)

    def test_conversion_repeatable_without_touching_source(self):
        source=ROOT/'Cuartos Composicion.txt'
        original=source.read_bytes()
        with tempfile.TemporaryDirectory() as temporary:
            output=Path(temporary)
            composition.convert_file(source,output)
            first={p.name:p.read_bytes() for p in output.glob('*.json')}
            composition.convert_file(source,output)
            self.assertEqual(first,{p.name:p.read_bytes() for p in output.glob('*.json')})
        self.assertEqual(original,source.read_bytes())


if __name__=='__main__':
    unittest.main()
