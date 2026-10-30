#ifndef BN_REGULAR_BG_ITEMS_MENU_INICIO_H
#define BN_REGULAR_BG_ITEMS_MENU_INICIO_H

#include "bn_regular_bg_item.h"

//{{BLOCK(menu_inicio_bn_gfx)

//======================================================================
//
//	menu_inicio_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 169 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 5408 + 2048 = 7488
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MENU_INICIO_BN_GFX_H
#define GRIT_MENU_INICIO_BN_GFX_H

#define menu_inicio_bn_gfxTilesLen 5408
extern const bn::tile menu_inicio_bn_gfxTiles[169];

#define menu_inicio_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell menu_inicio_bn_gfxMap[1024];

#define menu_inicio_bn_gfxPalLen 32
extern const bn::color menu_inicio_bn_gfxPal[16];

#endif // GRIT_MENU_INICIO_BN_GFX_H

//}}BLOCK(menu_inicio_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item menu_inicio(
            regular_bg_tiles_item(span<const tile>(menu_inicio_bn_gfxTiles, 169), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(menu_inicio_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(menu_inicio_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

