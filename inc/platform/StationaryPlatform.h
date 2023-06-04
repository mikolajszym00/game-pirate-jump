#ifndef PIRATE_JUMP_STANDPLATFORM_H
#define PIRATE_JUMP_STANDPLATFORM_H

#include "Platform.h"

class StationaryPlatform : public Platform {
public:
    StationaryPlatform() = default;

    ~StationaryPlatform() = default;

    StationaryPlatform(int x, int y) :
            Platform(x, y) {
        sprite = createSprite("../data/basic-platform.png");
        getSpriteSizes();
    }

    void action(unsigned int delta) override {};

};

#endif //PIRATE_JUMP_STANDPLATFORM_H
