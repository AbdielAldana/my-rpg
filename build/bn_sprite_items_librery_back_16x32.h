#ifndef BN_SPRITE_ITEMS_LIBRERY_BACK_16X32_H
#define BN_SPRITE_ITEMS_LIBRERY_BACK_16X32_H

#include "bn_sprite_item.h"

//{{BLOCK(librery_back_16x32_bn_gfx)

//======================================================================
//
//	librery_back_16x32_bn_gfx, 16x32@4, 
//	+ palette 16 entries, not compressed
//	+ 8 tiles Metatiled by 2x4 not compressed
//	Total size: 32 + 256 = 288
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_LIBRERY_BACK_16X32_BN_GFX_H
#define GRIT_LIBRERY_BACK_16X32_BN_GFX_H

#define librery_back_16x32_bn_gfxTilesLen 256
extern const bn::tile librery_back_16x32_bn_gfxTiles[8];

#define librery_back_16x32_bn_gfxPalLen 32
extern const bn::color librery_back_16x32_bn_gfxPal[16];

#endif // GRIT_LIBRERY_BACK_16X32_BN_GFX_H

//}}BLOCK(librery_back_16x32_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item librery_back_16x32(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(librery_back_16x32_bn_gfxTiles, 8), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(librery_back_16x32_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

