#ifndef BN_REGULAR_BG_ITEMS_HABILIDAD_DATA_H
#define BN_REGULAR_BG_ITEMS_HABILIDAD_DATA_H

#include "bn_regular_bg_item.h"

//{{BLOCK(habilidad_data_bn_gfx)

//======================================================================
//
//	habilidad_data_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 134 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 4288 + 2048 = 6368
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_HABILIDAD_DATA_BN_GFX_H
#define GRIT_HABILIDAD_DATA_BN_GFX_H

#define habilidad_data_bn_gfxTilesLen 4288
extern const bn::tile habilidad_data_bn_gfxTiles[134];

#define habilidad_data_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell habilidad_data_bn_gfxMap[1024];

#define habilidad_data_bn_gfxPalLen 32
extern const bn::color habilidad_data_bn_gfxPal[16];

#endif // GRIT_HABILIDAD_DATA_BN_GFX_H

//}}BLOCK(habilidad_data_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item habilidad_data(
            regular_bg_tiles_item(span<const tile>(habilidad_data_bn_gfxTiles, 134), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(habilidad_data_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(habilidad_data_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

