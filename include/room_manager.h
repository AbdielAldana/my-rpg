#ifndef ROOM_MANAGER_H
#define ROOM_MANAGER_H

namespace bn
{
class seed_random;
}

enum class RoomTemplateId
{
    FIELD,
    STONE,
    RUINS,
    FIELD_STONES_1,
    FIELD_STONES_2,
    FIELD_STONES_3,
    FIELD_STONES_4,
    FIELD_STONES_5,
    COMPOSITION_1,
    COMPOSITION_1_2,
    COMPOSITION_2,
    COMPOSITION_2_2,
    COMPOSITION_3,
    COMPOSITION_4,
    PLANT_GARDEN,
    PLANT_CENTER_ROOM,
    SPECIAL,
    TUTORIAL,
    STAIRS,
    STAIRS_2,
    REWARD,
    IMPORTED
};

enum class RoomBackgroundId
{
    LAND,
    CAMPFIRE,
    ROOM2,
    ROOM3,
    TUTORIAL,
    BOSS_ROOM,
    MENU_START,
    BOSS_1,
    BOSS_2,
    BOSS_RAT
};

enum class RoomDirection
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

enum class RoomItemType
{
    KEY,
    COIN,
    ENERGY_POTION,
    SPRINT_POTION,
    ABILITY_DASH,
    ABILITY_STOP_TIME,
    ABILITY_TRAPDOOR_BACK,
    ABILITY_VIEW_ALL_MAP,
    ABILITY_MASTER_KEY,
    ABILITY_BOMB,
    ABILITY_FAMILIAR
};

struct RoomItem
{
    RoomItemType type = RoomItemType::KEY;
    int x = 0;
    int y = 0;
    int level = 1;
    bool active = false;
};

class RoomManager
{
public:
    static constexpr int max_rooms = 16;
    static constexpr int max_items_per_room = 8;

    int add_room(RoomTemplateId template_id);
    void generate_menu_floor();
    bool is_menu_floor() const;
    bool saved_floor_valid() const;
    bool generate_random_floor(bn::seed_random& random, int room_count, bool tutorial_start = false);
    bool connect_rooms(int room_id, RoomDirection direction, int other_room_id);
    bool has_door(RoomDirection direction) const;
    bool has_door(int room_id, RoomDirection direction) const;
    bool touching_door(int player_x, int player_y, RoomDirection direction) const;
    bool door_is_open(RoomDirection direction) const;
    bool door_is_special(RoomDirection direction) const;
    bool door_is_special(int room_id, RoomDirection direction) const;
    bool door_is_visible(int room_id, RoomDirection direction) const;
    bool set_door_visible(int room_id, RoomDirection direction, bool visible);
    bool set_door_open(int room_id, RoomDirection direction, bool open);
    int current_room_id() const;
    bool set_current_room(int room_id);
    int room_count() const;
    int stairs_room_id() const;
    int reward_room_id() const;
    bool is_reward_room(int room_id) const;
    bool room_discovered(int room_id) const;
    int room_grid_x(int room_id) const;
    int room_grid_y(int room_id) const;
    int connected_room_id(int room_id, RoomDirection direction) const;
    RoomTemplateId current_template() const;
    RoomTemplateId room_template(int room_id) const;
    RoomBackgroundId room_background(int room_id) const;
    bool add_item(int room_id, RoomItemType type, int x, int y, int level = 1);
    const RoomItem* item_at(int room_id, int item_index) const;
    bool remove_item(int room_id, int item_index);

    // Actualiza la habitación actual y devuelve el punto de entrada al cuarto destino.
    bool try_transition(int player_x, int player_y, int& spawn_x, int& spawn_y);

private:
    struct RoomInstance
    {
        struct Door
        {
            int target_room_id = -1;
            bool open = false;
            bool special = false;
            bool visible = true;
        };

        RoomTemplateId template_id = RoomTemplateId::FIELD;
        RoomBackgroundId background_id = RoomBackgroundId::LAND;
        int grid_x = 0;
        int grid_y = 0;
        bool position_assigned = false;
        bool discovered = false;
        Door doors[4];
        RoomItem items[max_items_per_room];
    };

    static int direction_index(RoomDirection direction);
    static RoomDirection opposite_direction(RoomDirection direction);

    RoomInstance _rooms[max_rooms];
    bool _menu_floor = false;
    int _room_count = 0;
    int _current_room_id = -1;
};

#endif
