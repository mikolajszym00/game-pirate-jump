#ifndef DRAGONS_LAKE_PROJECTILE_H
#define DRAGONS_LAKE_PROJECTILE_H

#include <utility>
#include <algorithm>
#include <cmath>
#include "../gameObject/GameObject.h"

class Projectile : public GameObject {
public:
    ~Projectile() = default;

    Projectile() = default;

    Projectile(std::pair<int, int> hero_pos) :
            GameObject(hero_pos.first, hero_pos.second) {}

protected:
    double increase_at_x;
    double increase_at_y;

    void updateMove(int move_atr1) {
        if (x + sprite_width / 2 < 0)
            x = move_atr1 - sprite_width / 2;

        if (x + sprite_width / 2 > move_atr1)
            x = -sprite_width / 2;

        UpdateRightSide();
        updateBottom();
    }
};

#endif //DRAGONS_LAKE_PROJECTILE_H
