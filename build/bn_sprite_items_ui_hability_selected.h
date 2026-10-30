#ifndef BN_SPRITE_ITEMS_UI_HABILITY_SELECTED_H
#define BN_SPRITE_ITEMS_UI_HABILITY_SELECTED_H

#include "bn_sprite_item.h"

//{{BLOCK(ui_hability_selected_bn_gfx)

//======================================================================
//
//	ui_hability_selected_bn_gfx, 32x32@4, 
//	+ palette 16 entries, not compressed
//	+ 16 tiles Metatiled by 4x4 not compressed
//	Total size: 32 + 512 = 544
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_UI_HABILITY_SELECTED_BN_GFX_H
#define GRIT_UI_HABILITY_SELECTED_BN_GFX_H

#define ui_hability_selected_bn_gfxTilesLen 512
extern const bn::tile ui_hability_selected_bn_gfxTiles[16];

#define ui_hability_selected_bn_gfxPalLen 32
extern const bn::color ui_hability_selected_bn_gfxPal[16];

#endif // GRIT_UI_HABILITY_SELECTED_BN_GFX_H

//}}BLOCK(ui_hability_selected_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item ui_hability_selected(sprite_shape_size(sprite_shape::SQUARE, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(ui_hability_selected_bn_gfxTiles, 16), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(ui_hability_selected_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

