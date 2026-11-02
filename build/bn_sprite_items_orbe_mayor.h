#ifndef BN_SPRITE_ITEMS_ORBE_MAYOR_H
#define BN_SPRITE_ITEMS_ORBE_MAYOR_H

#include "bn_sprite_item.h"

//{{BLOCK(orbe_mayor_bn_gfx)

//======================================================================
//
//	orbe_mayor_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ORBE_MAYOR_BN_GFX_H
#define GRIT_ORBE_MAYOR_BN_GFX_H

#define orbe_mayor_bn_gfxTilesLen 128
extern const bn::tile orbe_mayor_bn_gfxTiles[4];

#define orbe_mayor_bn_gfxPalLen 32
extern const bn::color orbe_mayor_bn_gfxPal[16];

#endif // GRIT_ORBE_MAYOR_BN_GFX_H

//}}BLOCK(orbe_mayor_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item orbe_mayor(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(orbe_mayor_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(orbe_mayor_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

