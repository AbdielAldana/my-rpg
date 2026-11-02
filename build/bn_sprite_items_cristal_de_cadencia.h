#ifndef BN_SPRITE_ITEMS_CRISTAL_DE_CADENCIA_H
#define BN_SPRITE_ITEMS_CRISTAL_DE_CADENCIA_H

#include "bn_sprite_item.h"

//{{BLOCK(cristal_de_cadencia_bn_gfx)

//======================================================================
//
//	cristal_de_cadencia_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CRISTAL_DE_CADENCIA_BN_GFX_H
#define GRIT_CRISTAL_DE_CADENCIA_BN_GFX_H

#define cristal_de_cadencia_bn_gfxTilesLen 128
extern const bn::tile cristal_de_cadencia_bn_gfxTiles[4];

#define cristal_de_cadencia_bn_gfxPalLen 32
extern const bn::color cristal_de_cadencia_bn_gfxPal[16];

#endif // GRIT_CRISTAL_DE_CADENCIA_BN_GFX_H

//}}BLOCK(cristal_de_cadencia_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item cristal_de_cadencia(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(cristal_de_cadencia_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(cristal_de_cadencia_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

