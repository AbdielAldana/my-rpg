#ifndef GAME_REGULAR_FONT_H
#define GAME_REGULAR_FONT_H

#include "common_variable_8x16_sprite_font.h"
#include "bn_sprite_items_common_variable_regular_8x16_font.h"

namespace game
{

constexpr bn::sprite_font regular_variable_8x16_font(
    bn::sprite_items::common_variable_regular_8x16_font,
    common::variable_8x16_sprite_font.utf8_characters_ref(),
    common::variable_8x16_sprite_font.character_widths_ref());

}

#endif
