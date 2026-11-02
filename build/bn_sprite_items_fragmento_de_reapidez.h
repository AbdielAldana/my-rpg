#ifndef BN_SPRITE_ITEMS_FRAGMENTO_DE_REAPIDEZ_H
#define BN_SPRITE_ITEMS_FRAGMENTO_DE_REAPIDEZ_H

#include "bn_sprite_item.h"

//{{BLOCK(fragmento_de_reapidez_bn_gfx)

//======================================================================
//
//	fragmento_de_reapidez_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FRAGMENTO_DE_REAPIDEZ_BN_GFX_H
#define GRIT_FRAGMENTO_DE_REAPIDEZ_BN_GFX_H

#define fragmento_de_reapidez_bn_gfxTilesLen 128
extern const bn::tile fragmento_de_reapidez_bn_gfxTiles[4];

#define fragmento_de_reapidez_bn_gfxPalLen 32
extern const bn::color fragmento_de_reapidez_bn_gfxPal[16];

#endif // GRIT_FRAGMENTO_DE_REAPIDEZ_BN_GFX_H

//}}BLOCK(fragmento_de_reapidez_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item fragmento_de_reapidez(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(fragmento_de_reapidez_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(fragmento_de_reapidez_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

