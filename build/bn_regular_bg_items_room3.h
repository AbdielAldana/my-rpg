#ifndef BN_REGULAR_BG_ITEMS_ROOM3_H
#define BN_REGULAR_BG_ITEMS_ROOM3_H

#include "bn_regular_bg_item.h"

//{{BLOCK(room3_bn_gfx)

//======================================================================
//
//	room3_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 81 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 2592 + 2048 = 4672
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROOM3_BN_GFX_H
#define GRIT_ROOM3_BN_GFX_H

#define room3_bn_gfxTilesLen 2592
extern const bn::tile room3_bn_gfxTiles[81];

#define room3_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell room3_bn_gfxMap[1024];

#define room3_bn_gfxPalLen 32
extern const bn::color room3_bn_gfxPal[16];

#endif // GRIT_ROOM3_BN_GFX_H

//}}BLOCK(room3_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item room3(
            regular_bg_tiles_item(span<const tile>(room3_bn_gfxTiles, 81), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(room3_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(room3_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

