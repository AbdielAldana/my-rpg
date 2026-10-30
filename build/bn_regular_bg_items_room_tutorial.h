#ifndef BN_REGULAR_BG_ITEMS_ROOM_TUTORIAL_H
#define BN_REGULAR_BG_ITEMS_ROOM_TUTORIAL_H

#include "bn_regular_bg_item.h"

//{{BLOCK(room_tutorial_bn_gfx)

//======================================================================
//
//	room_tutorial_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 112 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 3584 + 2048 = 5664
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROOM_TUTORIAL_BN_GFX_H
#define GRIT_ROOM_TUTORIAL_BN_GFX_H

#define room_tutorial_bn_gfxTilesLen 3584
extern const bn::tile room_tutorial_bn_gfxTiles[112];

#define room_tutorial_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell room_tutorial_bn_gfxMap[1024];

#define room_tutorial_bn_gfxPalLen 32
extern const bn::color room_tutorial_bn_gfxPal[16];

#endif // GRIT_ROOM_TUTORIAL_BN_GFX_H

//}}BLOCK(room_tutorial_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item room_tutorial(
            regular_bg_tiles_item(span<const tile>(room_tutorial_bn_gfxTiles, 112), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(room_tutorial_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(room_tutorial_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

