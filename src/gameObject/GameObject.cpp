#include "../../inc/gameObject/GameObject.h"

void GameObject::UpdateRightSide() {
    right_side = x + sprite_width;
}

Sprite* GameObject::getSprite() {
    return sprite;
}

int GameObject::getCurrX() const {
    return x;
}

int GameObject::getCurrY() const {
    return y;
}

int GameObject::getCurrBottom() const {
    return bottom;
}

int GameObject::getCurrRightSide() const {
    return right_side;
}

void GameObject::updateBottom() {
    bottom = y + sprite_height;
}
