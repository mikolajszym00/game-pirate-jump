#ifndef DRAGONS_LAKE_TURRETPROJECTILE_H
#define DRAGONS_LAKE_TURRETPROJECTILE_H

#include "Projectile.h"
#include "../settings.h"

class TurretProjectile : public Projectile {
public:
    ~TurretProjectile() = default;

    TurretProjectile() = default;

    TurretProjectile(std::pair<int, int> hero_pos, std::pair<int, int> mouse_pos) :
            Projectile(hero_pos) {
        sprite = createSprite("../data/bomb-enemy.png");
        getSpriteSizes();

        getIncreaseValues(hero_pos, mouse_pos);
    }

    void move(unsigned int delta, int move_atr1) override;

    void fallingMove(unsigned int delta, int dist);

private:
    void getIncreaseValues(std::pair<int, int> enemy_pos, std::pair<int, int> hero_pos) {
        double delta_x = hero_pos.first - enemy_pos.first;
        double delta_y = hero_pos.second - enemy_pos.second;

        double delta_abs = fabs(delta_x) + fabs(delta_y);

        increase_at_x = delta_x / delta_abs;
        increase_at_y = delta_y / delta_abs;
    }
};

#endif //DRAGONS_LAKE_TURRETPROJECTILE_H
