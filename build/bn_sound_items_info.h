#ifndef BN_SOUND_ITEMS_INFO_H
#define BN_SOUND_ITEMS_INFO_H

#include "bn_span.h"
#include "bn_sound_item.h"
#include "bn_string_view.h"

namespace bn::sound_items_info
{
    constexpr inline pair<sound_item, string_view> array[] = {
        make_pair(sound_item(0), string_view("bat1")),
        make_pair(sound_item(1), string_view("bat2")),
        make_pair(sound_item(2), string_view("campfire")),
        make_pair(sound_item(3), string_view("dash")),
        make_pair(sound_item(4), string_view("enter_door")),
        make_pair(sound_item(5), string_view("hit")),
        make_pair(sound_item(6), string_view("move_ui")),
        make_pair(sound_item(7), string_view("open_door")),
        make_pair(sound_item(8), string_view("pickup_item")),
        make_pair(sound_item(9), string_view("skeleton")),
        make_pair(sound_item(10), string_view("stairs")),
        make_pair(sound_item(11), string_view("step")),
    };

    constexpr inline span<const pair<sound_item, string_view>> span(array);
}

#endif

