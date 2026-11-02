#ifndef BN_SPRITE_ITEMS_CHISPA_LIGERA_H
#define BN_SPRITE_ITEMS_CHISPA_LIGERA_H

#include "bn_sprite_item.h"

//{{BLOCK(chispa_ligera_bn_gfx)

//======================================================================
//
//	chispa_ligera_bn_gfx, 16x16@4, 
//	+ palette 16 entries, not compressed
//	+ 4 tiles Metatiled by 2x2 not compressed
//	Total size: 32 + 128 = 160
//
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_CHISPA_LIGERA_BN_GFX_H
#define GRIT_CHISPA_LIGERA_BN_GFX_H

#define chispa_ligera_bn_gfxTilesLen 128
extern const bn::tile chispa_ligera_bn_gfxTiles[4];

#define chispa_ligera_bn_gfxPalLen 32
extern const bn::color chispa_ligera_bn_gfxPal[16];

#endif // GRIT_CHISPA_LIGERA_BN_GFX_H

//}}BLOCK(chispa_ligera_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item chispa_ligera(sprite_shape_size(sprite_shape::SQUARE, sprite_size::NORMAL), 
            sprite_tiles_item(span<const tile>(chispa_ligera_bn_gfxTiles, 4), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(chispa_ligera_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

