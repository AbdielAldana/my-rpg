#ifndef BN_SPRITE_ITEMS_TOTEM_DE_REPETICION_H
#define BN_SPRITE_ITEMS_TOTEM_DE_REPETICION_H

#include "bn_sprite_item.h"

//{{BLOCK(totem_de_repeticion_bn_gfx)

//======================================================================
//
//	totem_de_repeticion_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_TOTEM_DE_REPETICION_BN_GFX_H
#define GRIT_TOTEM_DE_REPETICION_BN_GFX_H

#define totem_de_repeticion_bn_gfxTilesLen 128
extern const bn::tile totem_de_repeticion_bn_gfxTiles[4];

#define totem_de_repeticion_bn_gfxPalLen 32
extern const bn::color totem_de_repeticion_bn_gfxPal[16];

#endif // GRIT_TOTEM_DE_REPETICION_BN_GFX_H

//}}BLOCK(totem_de_repeticion_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item totem_de_repeticion(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(totem_de_repeticion_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(totem_de_repeticion_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

