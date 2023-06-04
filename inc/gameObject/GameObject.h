#ifndef PIRATE_JUMP_GAMEOBJECT_H
#define PIRATE_JUMP_GAMEOBJECT_H

#include "../Framework.h"
#include "../func.h"
#include <memory>

class GameObject {
public:
    GameObject() = default;

    GameObject(int x, int y) :
        x(x),
        y(y)
        {}

    Sprite* getSprite();

    void UpdateRightSide();

    int getCurrX() const;

    int getCurrY() const;

    int getCurrRightSide() const;

    int getCurrBottom() const;

    virtual void move(unsigned int delta, int move_atr1) = 0;

    void updateBottom();

    template <typename T> bool collision(const std::shared_ptr<T> &go) const {
        static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from GameObject");

        return intersect(std::make_pair(go->getCurrX(),
                                        go->getCurrRightSide()),
                         std::make_pair(x, right_side)) &&
               intersect(std::make_pair(go->getCurrY(),
                                        go->getCurrBottom()),
                         std::make_pair(y, bottom));
    }
protected:
    Sprite* sprite;
    int x;
    int y;

    int sprite_height;
    int sprite_width;

    int bottom;
    int right_side;

    void getSpriteSizes() {
        getSpriteSize(sprite, sprite_width, sprite_height);
        bottom = y + sprite_height;
        right_side = x + sprite_width;
    }
};

#endif //PIRATE_JUMP_GAMEOBJECT_H
