#ifndef PASSIVE_SHOP_H
#define PASSIVE_SHOP_H

#include <stdint.h>

namespace passive_shop
{

constexpr int passive_count = 21;
constexpr int option_count = 4;
constexpr uint32_t all_passives_mask = (uint32_t(1) << passive_count) - 1;

enum class ItemId : uint8_t
{
    LIGHT_SPARK,
    DENSE_CORE,
    CONCENTRATED_ESSENCE,
    CADENCE_CRYSTAL,
    ABUNDANCE_SEAL,
    TWIN_BURST,
    TRIPLE_BURST,
    ARCANE_HEART,
    ENCHANTED_WIND,
    QUICK_CHANNELER,
    GREATER_ORB,
    LESSER_ORB,
    MANA_RESERVE,
    REPETITION_TOTEM,
    LIGHT_STAFF,
    HEAVY_STAFF,
    SWIFTNESS_FRAGMENT,
    MULTIPLICATION_FRAGMENT,
    POWER_SEAL,
    GREAT_ARCANE_CORE,
    CRUZ_DIVINA,
    POTION,
    KEY,
    MEDIKIT,
    EMPTY = 255
};

enum class ProjectilePattern : uint8_t
{
    SINGLE,
    TWIN,
    TRIPLE
};

struct ItemDefinition
{
    const char* name;
    uint8_t price;
};

constexpr ItemDefinition definitions[] =
{
    {"CHISPA LIGERA", 5},
    {"NUCLEO DENSO", 6},
    {"ESENCIA CONCENTRADA", 5},
    {"CRISTAL DE CADENCIA", 8},
    {"SELLO DE ABUNDANCIA", 4},
    {"DESCARGA GEMELA", 10},
    {"DESCARGA TRINA", 16},
    {"CORAZON ARCANO", 6},
    {"VIENTO ENCANTADO", 5},
    {"CANALIZADOR RAPIDO", 10},
    {"ORBE MAYOR", 8},
    {"ORBE MENOR", 7},
    {"RESERVA DE MANA", 5},
    {"TOTEM DE REPETICION", 11},
    {"BASTON LIVIANO", 7},
    {"BASTON PESADO", 6},
    {"FRAGMENTO DE RAPIDEZ", 4},
    {"FRAGMENTO MULTIPLE", 9},
    {"SELLO DE POTENCIA", 12},
    {"GRAN NUCLEO ARCANO", 20},
    {"CRUZ DIVINA", 30},
    {"POCION", 1},
    {"LLAVE", 1},
    {"MEDIKIT", 1}
};

struct State
{
    uint32_t purchased_mask = 0;
    uint32_t random_state = 0;
    ItemId options[option_count] = {};
    bool initialized = false;
};

struct BulletStats
{
    // Milésimas: 1400 = 1.4 px/cuadro; 1000 = escala original.
    int speed_milli = 1400;
    int size_milli = 1000;
    int shot_interval_frames = 180;
    int projectile_count = 1;
    int reserve = 16;
    ProjectilePattern pattern = ProjectilePattern::SINGLE;
};

enum class PurchaseResult : uint8_t
{
    INVALID,
    NOT_ENOUGH_COINS,
    PASSIVE,
    POTION,
    KEY,
    MEDIKIT
};

constexpr bool is_passive(ItemId item)
{
    return int(item) < passive_count;
}

constexpr int price(ItemId item)
{
    return int(item) < int(sizeof(definitions) / sizeof(definitions[0])) ?
        definitions[int(item)].price : 0;
}

constexpr const char* name(ItemId item)
{
    return int(item) < int(sizeof(definitions) / sizeof(definitions[0])) ?
        definitions[int(item)].name : "AGOTADO";
}

constexpr int clamp(int value, int minimum, int maximum)
{
    return value < minimum ? minimum : (value > maximum ? maximum : value);
}

constexpr int multiply_milli(int value, int factor)
{
    return (value * factor + 500) / 1000;
}

constexpr BulletStats calculate_bullet_stats(uint32_t mask)
{
    BulletStats result;
    int speed_factor = 1000;
    int size_factor = 1000;
    int frequency_factor = 1000;
    int reserve_factor = 1000;
    int direct_speed = 0;
    int direct_projectiles = 0;
    bool twin = false;
    bool triple = false;

    for(int id = 0; id < passive_count; ++id)
    {
        if(!(mask & (uint32_t(1) << id)))
            continue;
        switch(ItemId(id))
        {
        case ItemId::LIGHT_SPARK: speed_factor = multiply_milli(speed_factor, 1290); break;
        case ItemId::DENSE_CORE:
            size_factor = multiply_milli(size_factor, 1400);
            speed_factor = multiply_milli(speed_factor, 790);
            break;
        case ItemId::CONCENTRATED_ESSENCE:
            size_factor = multiply_milli(size_factor, 700);
            speed_factor = multiply_milli(speed_factor, 1210);
            break;
        case ItemId::CADENCE_CRYSTAL: frequency_factor = multiply_milli(frequency_factor, 830); break;
        case ItemId::ABUNDANCE_SEAL: reserve_factor = multiply_milli(reserve_factor, 1250); break;
        case ItemId::TWIN_BURST: twin = true; break;
        case ItemId::TRIPLE_BURST: triple = true; break;
        case ItemId::ARCANE_HEART: size_factor = multiply_milli(size_factor, 1150); break;
        case ItemId::ENCHANTED_WIND: speed_factor = multiply_milli(speed_factor, 1210); break;
        case ItemId::QUICK_CHANNELER: frequency_factor = multiply_milli(frequency_factor, 750); break;
        case ItemId::GREATER_ORB: size_factor = multiply_milli(size_factor, 1700); break;
        case ItemId::LESSER_ORB:
            size_factor = multiply_milli(size_factor, 650);
            frequency_factor = multiply_milli(frequency_factor, 750);
            break;
        case ItemId::MANA_RESERVE: reserve_factor = multiply_milli(reserve_factor, 1500); break;
        case ItemId::REPETITION_TOTEM: ++direct_projectiles; break;
        case ItemId::LIGHT_STAFF: frequency_factor = multiply_milli(frequency_factor, 830); break;
        case ItemId::HEAVY_STAFF:
            size_factor = multiply_milli(size_factor, 1400);
            frequency_factor = multiply_milli(frequency_factor, 1330);
            break;
        case ItemId::SWIFTNESS_FRAGMENT: direct_speed += 200; break;
        case ItemId::MULTIPLICATION_FRAGMENT: ++direct_projectiles; break;
        case ItemId::POWER_SEAL:
            size_factor = multiply_milli(size_factor, 1250);
            speed_factor = multiply_milli(speed_factor, 1140);
            break;
        case ItemId::GREAT_ARCANE_CORE:
            size_factor = multiply_milli(size_factor, 1400);
            speed_factor = multiply_milli(speed_factor, 1210);
            frequency_factor = multiply_milli(frequency_factor, 1330);
            twin = true;
            break;
        case ItemId::CRUZ_DIVINA:
            speed_factor = multiply_milli(speed_factor, 3500);
            size_factor = multiply_milli(size_factor, 900);
            frequency_factor = multiply_milli(frequency_factor, 2000);
            reserve_factor = multiply_milli(reserve_factor, 3000);
            direct_speed += 1000;
            direct_projectiles += 4;
            triple = true;
            break;
        default: break;
        }
    }

    int base_projectiles = triple ? 3 : (twin ? 2 : 1);
    result.speed_milli = clamp(multiply_milli(1400, speed_factor) + direct_speed, 500, 4000);
    result.size_milli = clamp(size_factor, 500, 3000);
    result.shot_interval_frames = clamp(multiply_milli(180, frequency_factor), 30, 360);
    result.projectile_count = clamp(base_projectiles + direct_projectiles, 1, 5);
    result.reserve = clamp(multiply_milli(16, reserve_factor), 1, 32);
    result.pattern = triple ? ProjectilePattern::TRIPLE :
        (twin ? ProjectilePattern::TWIN : ProjectilePattern::SINGLE);
    return result;
}

constexpr uint32_t next_random(uint32_t& state)
{
    if(!state)
        state = 0x51A7E123u;
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

constexpr bool option_contains(const State& state, ItemId item, int ignored_slot = -1)
{
    for(int index = 0; index < option_count; ++index)
        if(index != ignored_slot && state.options[index] == item)
            return true;
    return false;
}

constexpr ItemId choose_option(State& state, int slot)
{
    ItemId candidates[passive_count] = {};
    int candidate_count = 0;
    for(int id = 0; id < passive_count; ++id)
    {
        ItemId item = ItemId(id);
        if(!(state.purchased_mask & (uint32_t(1) << id)) && !option_contains(state, item, slot))
            candidates[candidate_count++] = item;
    }
    if(candidate_count > 0)
        return candidates[next_random(state.random_state) % unsigned(candidate_count)];
    return ItemId(int(ItemId::POTION) + int(next_random(state.random_state) % 3));
}

constexpr void refresh(State& state)
{
    for(ItemId& option : state.options)
        option = ItemId::EMPTY;
    for(int slot = 0; slot < option_count; ++slot)
        state.options[slot] = choose_option(state, slot);
    state.initialized = true;
}

constexpr void ensure_initialized(State& state)
{
    if(!state.initialized)
        refresh(state);
}

constexpr void reset_for_death(State& state)
{
    state.purchased_mask = 0;
    refresh(state);
}

constexpr PurchaseResult purchase(State& state, int slot, uint16_t& coins)
{
    if(slot < 0 || slot >= option_count)
        return PurchaseResult::INVALID;
    ItemId item = state.options[slot];
    int item_price = price(item);
    if(item_price <= 0)
        return PurchaseResult::INVALID;
    if(coins < item_price)
        return PurchaseResult::NOT_ENOUGH_COINS;
    coins = uint16_t(coins - item_price);
    PurchaseResult result = PurchaseResult::INVALID;
    if(is_passive(item))
    {
        state.purchased_mask |= uint32_t(1) << int(item);
        result = PurchaseResult::PASSIVE;
    }
    else if(item == ItemId::POTION)
        result = PurchaseResult::POTION;
    else if(item == ItemId::KEY)
        result = PurchaseResult::KEY;
    else if(item == ItemId::MEDIKIT)
        result = PurchaseResult::MEDIKIT;
    state.options[slot] = choose_option(state, slot);
    return result;
}

}

#endif
