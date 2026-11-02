#ifndef BN_SPRITE_ITEMS_RESERVA_DE_MANA_H
#define BN_SPRITE_ITEMS_RESERVA_DE_MANA_H

#include "bn_sprite_item.h"

//{{BLOCK(reserva_de_mana_bn_gfx)

//======================================================================
//
//	reserva_de_mana_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_RESERVA_DE_MANA_BN_GFX_H
#define GRIT_RESERVA_DE_MANA_BN_GFX_H

#define reserva_de_mana_bn_gfxTilesLen 128
extern const bn::tile reserva_de_mana_bn_gfxTiles[4];

#define reserva_de_mana_bn_gfxPalLen 32
extern const bn::color reserva_de_mana_bn_gfxPal[16];

#endif // GRIT_RESERVA_DE_MANA_BN_GFX_H

//}}BLOCK(reserva_de_mana_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item reserva_de_mana(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(reserva_de_mana_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(reserva_de_mana_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

