#ifndef BN_SPRITE_ITEMS_CAMPFIRE_H
#define BN_SPRITE_ITEMS_CAMPFIRE_H

#include "bn_sprite_item.h"

//{{BLOCK(campfire_bn_gfx)

//======================================================================
//
//	campfire_bn_gfx, 16x128@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles Metatiled by 2x4 not compressed
//	Total size: 32 + 1024 = 1056
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CAMPFIRE_BN_GFX_H
#define GRIT_CAMPFIRE_BN_GFX_H

#define campfire_bn_gfxTilesLen 1024
extern const bn::tile campfire_bn_gfxTiles[32];

#define campfire_bn_gfxPalLen 32
extern const bn::color campfire_bn_gfxPal[16];

#endif // GRIT_CAMPFIRE_BN_GFX_H

//}}BLOCK(campfire_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item campfire(sprite_shape_size(sprite_shape::TALL, sprite_size::BIG), 
            sprite_tiles_item(span<const tile>(campfire_bn_gfxTiles, 32), bpp_mode::BPP_4, compression_type::NONE, 4), 
            sprite_palette_item(span<const color>(campfire_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

