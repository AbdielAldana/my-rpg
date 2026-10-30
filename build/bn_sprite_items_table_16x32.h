#ifndef BN_SPRITE_ITEMS_TABLE_16X32_H
#define BN_SPRITE_ITEMS_TABLE_16X32_H

#include "bn_sprite_item.h"

//{{BLOCK(table_16x32_bn_gfx)

//======================================================================
//
//	table_16x32_bn_gfx, 32x16@4, 
//	+ palette 16 entries, not compressed
//	+ 8 tiles Metatiled by 4x2 not compressed
//	Total size: 32 + 256 = 288
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TABLE_16X32_BN_GFX_H
#define GRIT_TABLE_16X32_BN_GFX_H

#define table_16x32_bn_gfxTilesLen 256
extern const bn::tile table_16x32_bn_gfxTiles[8];

#define table_16x32_bn_gfxPalLen 32
extern const bn::color table_16x32_bn_gfxPal[16];

#endif // GRIT_TABLE_16X32_BN_GFX_H

//}}BLOCK(table_16x32_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item table_16x32(sprite_shape_size(sprite_shape::WIDE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(table_16x32_bn_gfxTiles, 8), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(table_16x32_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

