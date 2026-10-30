#ifndef BN_REGULAR_BG_ITEMS_BOSS_1_H
#define BN_REGULAR_BG_ITEMS_BOSS_1_H

#include "bn_regular_bg_item.h"

//{{BLOCK(boss_1_bn_gfx)

//======================================================================
//
//	boss_1_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 242 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 7744 + 2048 = 9824
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BOSS_1_BN_GFX_H
#define GRIT_BOSS_1_BN_GFX_H

#define boss_1_bn_gfxTilesLen 7744
extern const bn::tile boss_1_bn_gfxTiles[242];

#define boss_1_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell boss_1_bn_gfxMap[1024];

#define boss_1_bn_gfxPalLen 32
extern const bn::color boss_1_bn_gfxPal[16];

#endif // GRIT_BOSS_1_BN_GFX_H

//}}BLOCK(boss_1_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item boss_1(
            regular_bg_tiles_item(span<const tile>(boss_1_bn_gfxTiles, 242), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(boss_1_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(boss_1_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

