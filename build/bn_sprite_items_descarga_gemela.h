#ifndef BN_SPRITE_ITEMS_DESCARGA_GEMELA_H
#define BN_SPRITE_ITEMS_DESCARGA_GEMELA_H

#include "bn_sprite_item.h"

//{{BLOCK(descarga_gemela_bn_gfx)

//======================================================================
//
//	descarga_gemela_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_DESCARGA_GEMELA_BN_GFX_H
#define GRIT_DESCARGA_GEMELA_BN_GFX_H

#define descarga_gemela_bn_gfxTilesLen 128
extern const bn::tile descarga_gemela_bn_gfxTiles[4];

#define descarga_gemela_bn_gfxPalLen 32
extern const bn::color descarga_gemela_bn_gfxPal[16];

#endif // GRIT_DESCARGA_GEMELA_BN_GFX_H

//}}BLOCK(descarga_gemela_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item descarga_gemela(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(descarga_gemela_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(descarga_gemela_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

