#ifndef PIRATE_JUMP_ENEMY_H
#define PIRATE_JUMP_ENEMY_H

#include <memory>
#include "../gameObject/FallingObject.h"
#include "../projectile/Projectile.h"
#include "../projectile/TurretProjectile.h"

class Enemy : public FallingObject {
public:
    ~Enemy() = default;

    Enemy() = default;

    Enemy(int x, int y) :
            FallingObject(x, y) {}

    virtual void action(std::vector<std::shared_ptr<TurretProjectile>> &projectiles, std::pair<int, int> hero_pos) = 0;

    void updateSize() {
        this->y -= sprite_height;
        bottom = y + sprite_height;
        right_side = x + sprite_width;
    }
};

#endif //PIRATE_JUMP_ENEMY_H
