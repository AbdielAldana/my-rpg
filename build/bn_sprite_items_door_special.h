#ifndef BN_SPRITE_ITEMS_DOOR_SPECIAL_H
#define BN_SPRITE_ITEMS_DOOR_SPECIAL_H

#include "bn_sprite_item.h"

//{{BLOCK(door_special_bn_gfx)

//======================================================================
//
//	door_special_bn_gfx, 16x32@4, 
//	+ palette 16 entries, not compressed
//	+ 8 tiles Metatiled by 2x4 not compressed
//	Total size: 32 + 256 = 288
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_DOOR_SPECIAL_BN_GFX_H
#define GRIT_DOOR_SPECIAL_BN_GFX_H

#define door_special_bn_gfxTilesLen 256
extern const bn::tile door_special_bn_gfxTiles[8];

#define door_special_bn_gfxPalLen 32
extern const bn::color door_special_bn_gfxPal[16];

#endif // GRIT_DOOR_SPECIAL_BN_GFX_H

//}}BLOCK(door_special_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item door_special(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(door_special_bn_gfxTiles, 8), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(door_special_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

