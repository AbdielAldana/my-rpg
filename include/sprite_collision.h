#ifndef SPRITE_COLLISION_H
#define SPRITE_COLLISION_H

namespace game
{

struct Hitbox
{
    int left;
    int right;
    int top;
    int bottom;
};

// Coordenadas locales respecto al centro del dibujo. En pixels de la imagen:
// objeto 16x16: x [3, 13), y [0, 8), ancho 10 y alto 8.
constexpr Hitbox sprite16_hitbox = {-5, 5, -8, 0};
constexpr Hitbox player_hitbox = {-8, 8, -8, 8};

template<typename Coordinate>
constexpr bool hitboxes_overlap(Coordinate delta_x, Coordinate delta_y, Hitbox first, Hitbox second)
{
    return delta_x > Coordinate(second.left - first.right) &&
           delta_x < Coordinate(second.right - first.left) &&
           delta_y > Coordinate(second.top - first.bottom) &&
           delta_y < Coordinate(second.bottom - first.top);
}

template<typename Coordinate>
constexpr bool sprite16_overlaps_player(Coordinate delta_x, Coordinate delta_y)
{
    return hitboxes_overlap(delta_x, delta_y, player_hitbox, sprite16_hitbox);
}

template<typename Coordinate>
constexpr bool sprites16_overlap(Coordinate delta_x, Coordinate delta_y)
{
    return hitboxes_overlap(delta_x, delta_y, sprite16_hitbox, sprite16_hitbox);
}

constexpr int sprite_collision_side_trim = 3;
constexpr int sprite_collision_bottom_trim = 8;

// Regla anterior para las otras dimensiones; las imagenes de 16x16 usan la caja exacta de arriba.
// Coordinate mantiene la precision de los proyectiles que usan bn::fixed.
template<typename Coordinate>
constexpr bool sprite_collision_overlaps(Coordinate delta_x, Coordinate delta_y,
                                         int half_width, int top, int bottom)
{
    return delta_x > Coordinate(-half_width + sprite_collision_side_trim) &&
           delta_x < Coordinate(half_width - sprite_collision_side_trim) &&
           delta_y > Coordinate(top) &&
           delta_y < Coordinate(bottom - sprite_collision_bottom_trim);
}

}

#endif
