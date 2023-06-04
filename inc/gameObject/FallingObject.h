#ifndef PIRATE_JUMP_FALLINGOBJECT_H
#define PIRATE_JUMP_FALLINGOBJECT_H

#include "GameObject.h"
#include "../settings.h"

class FallingObject : public GameObject {
public:
    FallingObject() = default;

    ~FallingObject() = default;

    FallingObject(int x, int y) :
            GameObject(x, y) {}

    void move(unsigned int delta, int move_atr1) override;
    bool IS_HERO_ABOVE = false;
};

#endif //PIRATE_JUMP_FALLINGOBJECT_H
