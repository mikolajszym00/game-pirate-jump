#include "../../inc/enemy/Turret.h"

void Turret::action(std::vector<std::shared_ptr<TurretProjectile>> &projectiles, std::pair<int, int> hero_pos) {
    unsigned int tick_delta = getTickCount() - prev_tick;
    prev_tick = getTickCount();

    if (cooldown <= TURRET_COOLDOWN)
        cooldown += (int) tick_delta;

    if (cooldown > TURRET_COOLDOWN && hero_pos.second - 20 > bottom && y > 20) {
        projectiles.emplace_back(std::make_shared<TurretProjectile>(std::make_pair(x + sprite_width / 2, getCurrBottom()),
                                            hero_pos)
        );

        cooldown = 0;
    }
}
