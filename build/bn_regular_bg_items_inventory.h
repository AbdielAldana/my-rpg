#ifndef BN_REGULAR_BG_ITEMS_INVENTORY_H
#define BN_REGULAR_BG_ITEMS_INVENTORY_H

#include "bn_regular_bg_item.h"

//{{BLOCK(inventory_bn_gfx)

//======================================================================
//
//	inventory_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 38 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 1216 + 2048 = 3296
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_INVENTORY_BN_GFX_H
#define GRIT_INVENTORY_BN_GFX_H

#define inventory_bn_gfxTilesLen 1216
extern const bn::tile inventory_bn_gfxTiles[38];

#define inventory_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell inventory_bn_gfxMap[1024];

#define inventory_bn_gfxPalLen 32
extern const bn::color inventory_bn_gfxPal[16];

#endif // GRIT_INVENTORY_BN_GFX_H

//}}BLOCK(inventory_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item inventory(
            regular_bg_tiles_item(span<const tile>(inventory_bn_gfxTiles, 38), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(inventory_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(inventory_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

