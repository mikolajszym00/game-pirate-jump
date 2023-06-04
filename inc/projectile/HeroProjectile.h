#ifndef DRAGONS_LAKE_HEROPROJECTILE_H
#define DRAGONS_LAKE_HEROPROJECTILE_H

#include "Projectile.h"

class HeroProjectile : public Projectile {
public:
    ~HeroProjectile() = default;

    HeroProjectile() = default;

    HeroProjectile(std::pair<int, int> hero_pos, std::pair<int, int> mouse_pos) :
            Projectile(hero_pos) {
        sprite = createSprite("../data/bomb-hero.png");
        getSpriteSizes();

        getIncreaseValues(hero_pos, mouse_pos);
    }

    void move(unsigned int delta, int move_atr1) override;

private:
    void getIncreaseValues(std::pair<int, int> hero_pos, std::pair<int, int> mouse_pos) {
        double delta_x = mouse_pos.first - hero_pos.first;
        double delta_y = mouse_pos.second - hero_pos.second;

        double delta_abs = fabs(delta_x) + fabs(delta_y);

        if (delta_y <= 0) { // clicked above the hero
            delta_y *= -1;
        } else {
            delta_x *= -1;
        }

        increase_at_x = delta_x / delta_abs;
        increase_at_y = delta_y / delta_abs;

        if (increase_at_y < 0.3) {
            increase_at_x = 0.7;
            increase_at_y = 0.3;
        }
    }
};

#endif //DRAGONS_LAKE_HEROPROJECTILE_H
