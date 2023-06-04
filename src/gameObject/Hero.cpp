#include "../../inc/gameObject/Hero.h"
#include <algorithm>

void Hero::move(unsigned int delta, int move_atr1) {
    if (L) {
        x -= (int) delta / step;

        if (x + sprite_width / 2 < 0)
            x = window_width - sprite_width / 2;
    }

    if (R) {
        x += (int) delta / step;

        if (x + sprite_width / 2 > window_width)
            x = -sprite_width / 2;
    }
    UpdateRightSide();

    if (FALLING) {
        y += (int) delta / step;
    } else {
        if (move_atr1 - jump_size < bottom) {
            y -= (int) delta / step;
        } else {
            FALLING = true;
            y += (int) delta / step;
        }
    }
    updateBottom();
}

int Hero::getBottom() const {
    return bottom;
}

template <typename T>
bool Hero::collisionFromAbove(std::shared_ptr<T> &fo) {
    static_assert(std::is_base_of<FallingObject, T>::value, "T must inherit from FallingObject");

    if (!intersect(std::make_pair(fo->getCurrX(),
                                  fo->getCurrRightSide()),
                   std::make_pair(x, right_side))) {
        if (bottom >= fo->getCurrY()) {
            fo->IS_HERO_ABOVE = false;
        } else {
            fo->IS_HERO_ABOVE = true;
        }

        return false;
    }

    if (bottom >= fo->getCurrY()) {
        if (fo->IS_HERO_ABOVE) {
            fo->IS_HERO_ABOVE = false;
            return true;
        }
        return false;
    }
    fo->IS_HERO_ABOVE = true;
    return false;
}

int Hero::check_platforms_collision(std::vector<std::shared_ptr<Platform>> &platforms) {
    int i = 0;
    for (std::shared_ptr<Platform> &pl: platforms) {
        if (collisionFromAbove<Platform>(pl)) {
            return i;
        }
        i++;
    }
    return -1;
}

int Hero::check_enemies_collision(std::vector<std::shared_ptr<Enemy>> &enemies) {
    for (auto e = enemies.begin(); e != enemies.end(); e++) {
        if (collisionFromAbove<Enemy>(*e)) {
            enemies.erase(e);
            return 0;
        }

        if (collision<Enemy>(*e)) {
            enemies.erase(e);

            if (resistant) {
                return 0;
            }
            return -1;
        }
    }

    return 0;
}

int Hero::getJumpSize() const {
    return jump_size;
}

int Hero::getCenter() const {
    return x + sprite_width / 2;
}

void Hero::action(unsigned int delta) {
    if (resistant) {
        if (resistant_timer <= HERO_RESISTANCE) {
            resistant_timer += delta;
        }
    }

    if (resistant_timer > HERO_RESISTANCE) {
        resistant_timer = 0;
        resistant = false;
    }
}

void Hero::setResistance() {
    resistant = true;
    resistant_timer = 0;
}
