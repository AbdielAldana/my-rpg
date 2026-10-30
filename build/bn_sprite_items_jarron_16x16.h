#ifndef BN_SPRITE_ITEMS_JARRON_16X16_H
#define BN_SPRITE_ITEMS_JARRON_16X16_H

#include "bn_sprite_item.h"

//{{BLOCK(jarron_16x16_bn_gfx)

//======================================================================
//
//	jarron_16x16_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_JARRON_16X16_BN_GFX_H
#define GRIT_JARRON_16X16_BN_GFX_H

#define jarron_16x16_bn_gfxTilesLen 128
extern const bn::tile jarron_16x16_bn_gfxTiles[4];

#define jarron_16x16_bn_gfxPalLen 32
extern const bn::color jarron_16x16_bn_gfxPal[16];

#endif // GRIT_JARRON_16X16_BN_GFX_H

//}}BLOCK(jarron_16x16_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item jarron_16x16(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(jarron_16x16_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(jarron_16x16_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

