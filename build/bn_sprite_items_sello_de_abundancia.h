#ifndef BN_SPRITE_ITEMS_SELLO_DE_ABUNDANCIA_H
#define BN_SPRITE_ITEMS_SELLO_DE_ABUNDANCIA_H

#include "bn_sprite_item.h"

//{{BLOCK(sello_de_abundancia_bn_gfx)

//======================================================================
//
//	sello_de_abundancia_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_SELLO_DE_ABUNDANCIA_BN_GFX_H
#define GRIT_SELLO_DE_ABUNDANCIA_BN_GFX_H

#define sello_de_abundancia_bn_gfxTilesLen 128
extern const bn::tile sello_de_abundancia_bn_gfxTiles[4];

#define sello_de_abundancia_bn_gfxPalLen 32
extern const bn::color sello_de_abundancia_bn_gfxPal[16];

#endif // GRIT_SELLO_DE_ABUNDANCIA_BN_GFX_H

//}}BLOCK(sello_de_abundancia_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item sello_de_abundancia(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(sello_de_abundancia_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(sello_de_abundancia_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

