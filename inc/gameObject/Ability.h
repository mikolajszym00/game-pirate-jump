#ifndef PIRATE_JUMP_ABILITY_H
#define PIRATE_JUMP_ABILITY_H

#include "FallingObject.h"

class Ability : public FallingObject {
public:
    ~Ability() = default;

    Ability() = default;

    Ability(int x, int y) :
            FallingObject(x, y) {}
};

#endif //PIRATE_JUMP_ABILITY_H
