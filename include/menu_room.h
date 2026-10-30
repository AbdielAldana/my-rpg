#ifndef MENU_ROOM_H
#define MENU_ROOM_H

#include "imported_room.h"

namespace menu_room
{
using Object = composition_rooms::Object;
constexpr const auto& objects = composition_rooms::inicio_menu_objects;
constexpr int object_count = sizeof(objects) / sizeof(objects[0]);
}

#endif
