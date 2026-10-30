#ifndef BN_SPRITE_ITEMS_ASIENTO_16X16_4STATE_DOWN_UP_LEFT_RIGHT_H
#define BN_SPRITE_ITEMS_ASIENTO_16X16_4STATE_DOWN_UP_LEFT_RIGHT_H

#include "bn_sprite_item.h"

//{{BLOCK(asiento_16x16_4state_down_up_left_right_bn_gfx)

//======================================================================
//
//	asiento_16x16_4state_down_up_left_right_bn_gfx, 16x64@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 512 = 544
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ASIENTO_16X16_4STATE_DOWN_UP_LEFT_RIGHT_BN_GFX_H
#define GRIT_ASIENTO_16X16_4STATE_DOWN_UP_LEFT_RIGHT_BN_GFX_H

#define asiento_16x16_4state_down_up_left_right_bn_gfxTilesLen 512
extern const bn::tile asiento_16x16_4state_down_up_left_right_bn_gfxTiles[16];

#define asiento_16x16_4state_down_up_left_right_bn_gfxPalLen 32
extern const bn::color asiento_16x16_4state_down_up_left_right_bn_gfxPal[16];

#endif // GRIT_ASIENTO_16X16_4STATE_DOWN_UP_LEFT_RIGHT_BN_GFX_H

//}}BLOCK(asiento_16x16_4state_down_up_left_right_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item asiento_16x16_4state_down_up_left_right(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(asiento_16x16_4state_down_up_left_right_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 4), 
            sprite_palette_item(span<const color>(asiento_16x16_4state_down_up_left_right_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

