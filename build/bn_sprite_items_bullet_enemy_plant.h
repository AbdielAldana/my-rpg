#ifndef BN_SPRITE_ITEMS_BULLET_ENEMY_PLANT_H
#define BN_SPRITE_ITEMS_BULLET_ENEMY_PLANT_H

#include "bn_sprite_item.h"

//{{BLOCK(bullet_enemy_plant_bn_gfx)

//======================================================================
//
//	bullet_enemy_plant_bn_gfx, 8x8@4, 
//	+ palette 16 entries, not compressed
//	+ 1 tiles not compressed
//	Total size: 32 + 32 = 64
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BULLET_ENEMY_PLANT_BN_GFX_H
#define GRIT_BULLET_ENEMY_PLANT_BN_GFX_H

#define bullet_enemy_plant_bn_gfxTilesLen 32
extern const bn::tile bullet_enemy_plant_bn_gfxTiles[1];

#define bullet_enemy_plant_bn_gfxPalLen 32
extern const bn::color bullet_enemy_plant_bn_gfxPal[16];

#endif // GRIT_BULLET_ENEMY_PLANT_BN_GFX_H

//}}BLOCK(bullet_enemy_plant_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item bullet_enemy_plant(sprite_shape_size(sprite_shape::SQUARE, sprite_size::SMALL), 
            sprite_tiles_item(span<const tile>(bullet_enemy_plant_bn_gfxTiles, 1), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(bullet_enemy_plant_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

