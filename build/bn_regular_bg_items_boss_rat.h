#ifndef BN_REGULAR_BG_ITEMS_BOSS_RAT_H
#define BN_REGULAR_BG_ITEMS_BOSS_RAT_H

#include "bn_regular_bg_item.h"

//{{BLOCK(boss_rat_bn_gfx)

//======================================================================
//
//	boss_rat_bn_gfx, 256x256@4, 
//	+ palette 16 entries, not compressed
//	+ 244 tiles (t|f|p reduced) not compressed
//	+ regular map (flat), not compressed, 32x32 
//	Total size: 32 + 7808 + 2048 = 9888
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BOSS_RAT_BN_GFX_H
#define GRIT_BOSS_RAT_BN_GFX_H

#define boss_rat_bn_gfxTilesLen 7808
extern const bn::tile boss_rat_bn_gfxTiles[244];

#define boss_rat_bn_gfxMapLen 2048
extern const bn::regular_bg_map_cell boss_rat_bn_gfxMap[1024];

#define boss_rat_bn_gfxPalLen 32
extern const bn::color boss_rat_bn_gfxPal[16];

#endif // GRIT_BOSS_RAT_BN_GFX_H

//}}BLOCK(boss_rat_bn_gfx)

namespace bn::regular_bg_items
{
    constexpr inline regular_bg_item boss_rat(
            regular_bg_tiles_item(span<const tile>(boss_rat_bn_gfxTiles, 244), bpp_mode::BPP_4, compression_type::NONE), 
            bg_palette_item(span<const color>(boss_rat_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE),
            regular_bg_map_item(boss_rat_bn_gfxMap[0], size(32, 32), compression_type::NONE, 1, false));
}

#endif

