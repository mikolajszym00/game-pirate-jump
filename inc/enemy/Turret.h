#ifndef PIRATE_JUMP_TURRET_H
#define PIRATE_JUMP_TURRET_H

#include "Enemy.h"
#include "../settings.h"

class Turret : public Enemy {
public:
    ~Turret() = default;

    Turret() = default;

    Turret(int x, int y) :
            Enemy(x, y),
            prev_tick(getTickCount()),
            cooldown(0) {
        sprite = createSprite("../data/turret.png");
        getSpriteSizes();

        updateSize();
    }

    void action(std::vector<std::shared_ptr<TurretProjectile>> &projectiles, std::pair<int, int> hero_pos) override;

private:
    unsigned int prev_tick;
    int cooldown;
};

#endif //PIRATE_JUMP_TURRET_H
