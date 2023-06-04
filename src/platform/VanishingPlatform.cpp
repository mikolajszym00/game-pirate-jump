#include "../../inc/platform/VanishingPlatform.h"

void VanishingPlatform::action(unsigned int delta) {
    if (y < 0) {
        return;
    }

    if (cooldown < COOLDOWN_VANISHING)
        cooldown += (int) delta;

    if (cooldown > COOLDOWN_VANISHING) {
        x = -100;
        right_side = -100;
    }
}
