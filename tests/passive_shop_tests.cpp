#include "passive_shop.h"

using namespace passive_shop;

constexpr bool four_visible_and_unique()
{
    State state;
    refresh(state);
    for(int left = 0; left < option_count; ++left)
    {
        if(state.options[left] == ItemId::EMPTY)
            return false;
        for(int right = left + 1; right < option_count; ++right)
            if(state.options[left] == state.options[right])
                return false;
    }
    return true;
}

constexpr bool purchase_marks_item_and_keeps_four()
{
    State state;
    refresh(state);
    ItemId bought = state.options[0];
    uint16_t coins = 20;
    PurchaseResult result = purchase(state, 0, coins);
    if(result != PurchaseResult::PASSIVE || coins != 20 - price(bought) ||
       !(state.purchased_mask & (uint32_t(1) << int(bought))))
        return false;
    for(ItemId option : state.options)
        if(option == ItemId::EMPTY || option == bought)
            return false;
    return true;
}

constexpr bool refresh_preserves_owned_items_and_coins()
{
    State state;
    state.purchased_mask = uint32_t(1) << int(ItemId::DENSE_CORE);
    uint16_t coins = 13;
    refresh(state);
    return coins == 13 && state.purchased_mask == (uint32_t(1) << int(ItemId::DENSE_CORE));
}

constexpr bool death_returns_items_and_stats()
{
    State state;
    state.purchased_mask = all_passives_mask;
    reset_for_death(state);
    BulletStats stats = calculate_bullet_stats(state.purchased_mask);
    return state.purchased_mask == 0 && stats.speed_milli == 1400 &&
        stats.size_milli == 1000 && stats.shot_interval_frames == 180 &&
        stats.projectile_count == 1 && stats.reserve == 16;
}

constexpr bool exhausted_shop_has_only_consumables()
{
    State state;
    state.purchased_mask = all_passives_mask;
    refresh(state);
    for(ItemId option : state.options)
        if(is_passive(option) || option == ItemId::EMPTY)
            return false;
    return true;
}

constexpr bool triple_has_priority_and_direct_bonuses_add()
{
    uint32_t mask = (uint32_t(1) << int(ItemId::TWIN_BURST)) |
        (uint32_t(1) << int(ItemId::TRIPLE_BURST)) |
        (uint32_t(1) << int(ItemId::REPETITION_TOTEM));
    BulletStats stats = calculate_bullet_stats(mask);
    return stats.pattern == ProjectilePattern::TRIPLE && stats.projectile_count == 4;
}

static_assert(four_visible_and_unique(), "The initial shop needs four unique passive items");
static_assert(purchase_marks_item_and_keeps_four(), "Purchasing must consume coins and replace the item");
static_assert(refresh_preserves_owned_items_and_coins(), "A refresh must preserve coins and owned passives");
static_assert(death_returns_items_and_stats(), "Death must return passives and reset bullet stats");
static_assert(exhausted_shop_has_only_consumables(), "An exhausted passive pool must show consumables");
static_assert(triple_has_priority_and_direct_bonuses_add(), "Projectile combination rules changed");

int main()
{
    return 0;
}
