#ifndef PIRATE_JUMP_PLATFORM_H
#define PIRATE_JUMP_PLATFORM_H

#include "../gameObject/FallingObject.h"

class Platform : public FallingObject {
public:
    Platform() = default;

    ~Platform() = default;

    Platform(int x, int y) :
            FallingObject(x, y) {
        sprite = createSprite("../data/basic-platform.png");
        getSpriteSizes();
    }

    virtual void action(unsigned int delta) = 0;

};

#endif //PIRATE_JUMP_PLATFORM_H
