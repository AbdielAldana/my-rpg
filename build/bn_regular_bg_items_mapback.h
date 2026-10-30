#ifndef BN_REGULAR_BG_ITEMS_MAPBACK_H
#define BN_REGULAR_BG_ITEMS_MAPBACK_H

#include "bn_regular_bg_item.h"

//{{BLOCK(mapback_bn_gfx)

//======================================================================
//
//	mapback_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 141 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 4512 + 2048 = 6592
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MAPBACK_BN_GFX_H
#define GRIT_MAPBACK_BN_GFX_H

#define mapback_bn_gfxTilesLen 4512
extern const bn::tile mapback_bn_gfxTiles[141];

#define mapback_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell mapback_bn_gfxMap[1024];

#define mapback_bn_gfxPalLen 32
extern const bn::color mapback_bn_gfxPal[16];

#endif // GRIT_MAPBACK_BN_GFX_H

//}}BLOCK(mapback_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item mapback(
            regular_bg_tiles_item(span<const tile>(mapback_bn_gfxTiles, 141), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(mapback_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(mapback_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

