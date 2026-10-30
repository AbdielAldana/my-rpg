#ifndef BN_SPRITE_ITEMS_PLANT_ENEMY_H
#define BN_SPRITE_ITEMS_PLANT_ENEMY_H

#include "bn_sprite_item.h"

//{{BLOCK(plant_enemy_bn_gfx)

//======================================================================
//
//	plant_enemy_bn_gfx, 16x256@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 2048 = 2080
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PLANT_ENEMY_BN_GFX_H
#define GRIT_PLANT_ENEMY_BN_GFX_H

#define plant_enemy_bn_gfxTilesLen 2048
extern const bn::tile plant_enemy_bn_gfxTiles[64];

#define plant_enemy_bn_gfxPalLen 32
extern const bn::color plant_enemy_bn_gfxPal[16];

#endif // GRIT_PLANT_ENEMY_BN_GFX_H

//}}BLOCK(plant_enemy_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item plant_enemy(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(plant_enemy_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 16), 
            sprite_palette_item(span<const color>(plant_enemy_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

