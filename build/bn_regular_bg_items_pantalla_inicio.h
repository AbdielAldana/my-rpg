#ifndef BN_REGULAR_BG_ITEMS_PANTALLA_INICIO_H
#define BN_REGULAR_BG_ITEMS_PANTALLA_INICIO_H

#include "bn_regular_bg_item.h"

//{{BLOCK(pantalla_inicio_bn_gfx)

//======================================================================
//
//	pantalla_inicio_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 224 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 7168 + 2048 = 9248
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_PANTALLA_INICIO_BN_GFX_H
#define GRIT_PANTALLA_INICIO_BN_GFX_H

#define pantalla_inicio_bn_gfxTilesLen 7168
extern const bn::tile pantalla_inicio_bn_gfxTiles[224];

#define pantalla_inicio_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell pantalla_inicio_bn_gfxMap[1024];

#define pantalla_inicio_bn_gfxPalLen 32
extern const bn::color pantalla_inicio_bn_gfxPal[16];

#endif // GRIT_PANTALLA_INICIO_BN_GFX_H

//}}BLOCK(pantalla_inicio_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item pantalla_inicio(
            regular_bg_tiles_item(span<const tile>(pantalla_inicio_bn_gfxTiles, 224), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(pantalla_inicio_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(pantalla_inicio_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

