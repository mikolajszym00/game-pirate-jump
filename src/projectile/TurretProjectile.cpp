#include "../../inc/projectile/TurretProjectile.h"

void TurretProjectile::move(unsigned int delta, int move_atr1) {
    x += (int) (increase_at_x * (int) delta / FAC2);
    y += (int) (increase_at_y * (int) delta / FAC2);

    updateMove(move_atr1);
}

void TurretProjectile::fallingMove(unsigned int delta, int dist) {
    if (dist < 5) {
        y += dist;
        return;
    }

    if (dist < delta) {
        y += dist / FAC;
        return;
    }

    y += (int) delta / FAC;

    updateBottom();
    UpdateRightSide();
}
