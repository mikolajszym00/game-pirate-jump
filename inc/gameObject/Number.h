#ifndef PIRATE_JUMP_NUMBER_H
#define PIRATE_JUMP_NUMBER_H

#include <unordered_map>
#include <sstream>
#include "GameObject.h"

class Number : public GameObject {
public:
    Number() = default;

    ~Number() = default;

    Number(int x, int y, int v) :
            GameObject(x, y) {

        std::stringstream ss;

        ss << "../data/" << v << ".png";

        sprite = createSprite(ss.str().c_str());
        getSpriteSizes();
    }

    void move(unsigned int delta, int move_atr1) override {}
};

#endif //PIRATE_JUMP_NUMBER_H
