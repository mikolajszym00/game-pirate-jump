#ifndef PIRATE_JUMP_HERO_H
#define PIRATE_JUMP_HERO_H

#include <vector>
#include <memory>
#include "GameObject.h"
#include "../platform/Platform.h"
#include "../enemy/Enemy.h"
#include "../func.h"
#include "../settings.h"

class Hero : public GameObject {
public:
    ~Hero() = default;
    Hero() = default;

    Hero(int step, int x, int y, int window_width) :
    GameObject(x, y),
    step(step),
    jump_size(JUMP_SIZE),
    window_width(window_width),
    resistant(false),
    resistant_timer(0)
    {
        sprite = createSprite("../data/hero.png");
        getSpriteSizes();
    }

    void move(unsigned int delta, int move_atr1) override;

    int getBottom() const;

    bool L = false;
    bool R = false;

    bool FALLING = true;

    bool resistant;

    template <typename T>
    bool collisionFromAbove(std::shared_ptr<T> &fo);

    int check_platforms_collision(std::vector<std::shared_ptr<Platform>> &platforms);

    int check_enemies_collision(std::vector<std::shared_ptr<Enemy>> &enemies);

    int getJumpSize() const;

    int getCenter() const;

    void action(unsigned int delta);

    void setResistance();
private:
    int step;
    int jump_size;

    int window_width;

    unsigned int resistant_timer;
};


#endif //PIRATE_JUMP_HERO_H
