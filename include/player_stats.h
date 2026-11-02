#ifndef PLAYER_STATS_H
#define PLAYER_STATS_H

#include "bn_fixed.h"

// Stats base y recursos actuales del jugador. Energy y Spirit se expresan en
// puntos de juego; los acumuladores internos de frames viven fuera de esta
// estructura para mantener el movimiento y la regeneración suaves.
struct PlayerStats
{
    static constexpr int max_energy = 20;
    static constexpr int max_spirit = 20;

    int energy = max_energy;
    int spirit = max_spirit;
    bn::fixed walk_speed = bn::fixed(1);
};

#endif
