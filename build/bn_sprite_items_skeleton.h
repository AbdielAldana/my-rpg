#ifndef BN_SPRITE_ITEMS_SKELETON_H
#define BN_SPRITE_ITEMS_SKELETON_H

#include "bn_sprite_item.h"

//{{BLOCK(skeleton_bn_gfx)

//======================================================================
//
//	skeleton_bn_gfx, 16x256@4, 
//	+ palette 16 entries, not compressed
//	+ 64 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 2048 = 2080
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SKELETON_BN_GFX_H
#define GRIT_SKELETON_BN_GFX_H

#define skeleton_bn_gfxTilesLen 2048
extern const bn::tile skeleton_bn_gfxTiles[64];

#define skeleton_bn_gfxPalLen 32
extern const bn::color skeleton_bn_gfxPal[16];

#endif // GRIT_SKELETON_BN_GFX_H

//}}BLOCK(skeleton_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item skeleton(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(skeleton_bn_gfxTiles, 64), bpp_mode::BPP_4, compression_type::NONE, 16), 
            sprite_palette_item(span<const color>(skeleton_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

