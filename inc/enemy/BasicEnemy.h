#ifndef PIRATE_JUMP_BASICENEMY_H
#define PIRATE_JUMP_BASICENEMY_H

#include "Enemy.h"

class BasicEnemy : public Enemy {
public:
    ~BasicEnemy() = default;

    BasicEnemy() = default;

    BasicEnemy(int x, int y) :
            Enemy(x, y) {
        sprite = createSprite("../data/basic-enemy.png");
        getSpriteSizes();

        updateSize();
    }

    void action(std::vector<std::shared_ptr<TurretProjectile>> &projectiles, std::pair<int, int> hero_pos) override {}
};

#endif //PIRATE_JUMP_BASICENEMY_H
