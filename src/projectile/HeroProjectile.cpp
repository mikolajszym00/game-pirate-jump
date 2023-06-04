#include "../../inc/projectile/HeroProjectile.h"

void HeroProjectile::move(unsigned int delta, int move_atr1) {
    x += (int) (increase_at_x * (int) delta);
    y -= (int) (increase_at_y * (int) delta);

    updateMove(move_atr1);
}
