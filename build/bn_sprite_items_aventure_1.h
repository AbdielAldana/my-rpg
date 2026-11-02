#ifndef BN_SPRITE_ITEMS_AVENTURE_1_H
#define BN_SPRITE_ITEMS_AVENTURE_1_H

#include "bn_sprite_item.h"

//{{BLOCK(aventure_1_bn_gfx)

//======================================================================
//
//	aventure_1_bn_gfx, 16x256@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 2048 = 2080
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_AVENTURE_1_BN_GFX_H
#define GRIT_AVENTURE_1_BN_GFX_H

#define aventure_1_bn_gfxTilesLen 2048
extern const bn::tile aventure_1_bn_gfxTiles[64];

#define aventure_1_bn_gfxPalLen 32
extern const bn::color aventure_1_bn_gfxPal[16];

#endif // GRIT_AVENTURE_1_BN_GFX_H

//}}BLOCK(aventure_1_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item aventure_1(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(aventure_1_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 16), 
            sprite_palette_item(span<const color>(aventure_1_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

