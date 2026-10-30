#ifndef BN_SPRITE_ITEMS_COLUMN_16X32_H
#define BN_SPRITE_ITEMS_COLUMN_16X32_H

#include "bn_sprite_item.h"

//{{BLOCK(column_16x32_bn_gfx)

//======================================================================
//
//	column_16x32_bn_gfx, 16x32@4, 
//	+ palette 16 entries, not compressed
//	+ 8 tiles Metatiled by 2x4 not compressed
//	Total size: 32 + 256 = 288
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_COLUMN_16X32_BN_GFX_H
#define GRIT_COLUMN_16X32_BN_GFX_H

#define column_16x32_bn_gfxTilesLen 256
extern const bn::tile column_16x32_bn_gfxTiles[8];

#define column_16x32_bn_gfxPalLen 32
extern const bn::color column_16x32_bn_gfxPal[16];

#endif // GRIT_COLUMN_16X32_BN_GFX_H

//}}BLOCK(column_16x32_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item column_16x32(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(column_16x32_bn_gfxTiles, 8), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(column_16x32_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

