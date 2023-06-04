#include "../../inc/gameObject/FallingObject.h"

void FallingObject::move(unsigned int delta, int move_atr1) {
if (move_atr1 < 5) {
        y += move_atr1;
        return;
    }

    if (move_atr1 < delta) {
        y += move_atr1 / FAC;
        return;
    }

    y += (int) delta / FAC;

    updateBottom();
    UpdateRightSide();
}
