#ifndef PIRATE_JUMP_IMMUNITY_H
#define PIRATE_JUMP_IMMUNITY_H

#include "Ability.h"

class Immunity : public Ability {
public:
    Immunity() = default;

    ~Immunity() = default;

    Immunity(int x, int y, bool icon) :
            Ability(x, y) {
        sprite = createSprite("../data/immunity.png");
        getSpriteSizes();

        if (!icon) {
            this->y -= sprite_height;
            this->x += 10;
            bottom = y + sprite_height;
            right_side = x + sprite_width;
        }
    }
};

#endif //PIRATE_JUMP_IMMUNITY_H
