#ifndef PIRATE_JUMP_VANISHINGPLATFORM_H
#define PIRATE_JUMP_VANISHINGPLATFORM_H

#include "Platform.h"
#include "../settings.h"

class VanishingPlatform : public Platform {
public:
    VanishingPlatform() = default;

    ~VanishingPlatform() = default;

    VanishingPlatform(int x, int y) :
            Platform(x, y),
            cooldown(0) {
        sprite = createSprite("../data/vanishing-platform.png");
        getSpriteSizes();
    }

    void action(unsigned int delta) override;

private:
    int cooldown;
};

#endif //PIRATE_JUMP_VANISHINGPLATFORM_H
