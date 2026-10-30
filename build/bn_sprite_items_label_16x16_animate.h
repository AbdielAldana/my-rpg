#ifndef BN_SPRITE_ITEMS_LABEL_16X16_ANIMATE_H
#define BN_SPRITE_ITEMS_LABEL_16X16_ANIMATE_H

#include "bn_sprite_item.h"

//{{BLOCK(label_16x16_animate_bn_gfx)

//======================================================================
//
//	label_16x16_animate_bn_gfx, 16x48@4, 
//	+ palette 16 entries, not compressed
//	+ 12 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 384 = 416
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LABEL_16X16_ANIMATE_BN_GFX_H
#define GRIT_LABEL_16X16_ANIMATE_BN_GFX_H

#define label_16x16_animate_bn_gfxTilesLen 384
extern const bn::tile label_16x16_animate_bn_gfxTiles[12];

#define label_16x16_animate_bn_gfxPalLen 32
extern const bn::color label_16x16_animate_bn_gfxPal[16];

#endif // GRIT_LABEL_16X16_ANIMATE_BN_GFX_H

//}}BLOCK(label_16x16_animate_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item label_16x16_animate(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(label_16x16_animate_bn_gfxTiles, 12), bpp_mode::BPP_4, compression_type::NONE, 3), 
            sprite_palette_item(span<const color>(label_16x16_animate_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

