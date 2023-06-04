#ifndef PIRATE_JUMP_PIRATEJUMP_H
#define PIRATE_JUMP_PIRATEJUMP_H

#include <iostream>
#include <vector>
#include <climits>
#include <memory>

#include "settings.h"
#include "gameObject/Hero.h"
#include "Chunk.h"
#include "gameObject/Number.h"
#include "projectile/HeroProjectile.h"


class PirateJump {
public:
    ~PirateJump() = default;

    PirateJump() = default;

    PirateJump(int width, int height) :
            width(width),
            height(height) {}

    void PreInit(int &width, int &height, bool &fullscreen);

    bool Init();

    void Close();

    bool Tick();

    void onMouseMove(int x, int y, int xrelative, int yrelative);

    void onMouseButtonClick(FRMouseButton button, bool isReleased);

    void onKeyPressed(FRKey k);

    void onKeyReleased(FRKey k);

    const char *GetTitle();

private:
    int width;
    int height;

    int BASE;

    int score;
    int score_platform;

    int curr_base_platform_idx;
    std::vector<std::shared_ptr<Platform>> platforms;
    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<HeroProjectile>> projectiles;
    std::vector<std::shared_ptr<TurretProjectile>> turret_projectiles;
    std::vector<std::shared_ptr<Ability>> abilities;

    std::pair<int, int> mouse_pos;

    unsigned int prev_tick;
    unsigned int prev_tick_cooldown;
    int cooldown;

    Hero hero;
    Chunk curr_chunk;
    Immunity immunityInfo;
    Sprite *bg;

    int used_number_of_numbers[10];
    std::unordered_map<int, std::vector<Number>> numbers;

    void generate();

    void restartGame();

    void enemyAction();

    void platformAction(unsigned int tick_delta);

    bool checkCollision();

    bool move(unsigned int tick_delta);

    void clean();

    void drawScore(int s, int which);

    template<typename T>
    void drawObjects(std::vector<std::shared_ptr<T>> &game_objects) {
        static_assert(std::is_base_of<GameObject, T>::value, "T must inherit from GameObject");

        for (std::shared_ptr<T> &go: game_objects) {
            drawSprite(go->getSprite(),
                       go->getCurrX(),
                       go->getCurrY());
        }
    }

    void draw();

    void moveObjects(unsigned int delta, int dist);
};

#endif //PIRATE_JUMP_PIRATEJUMP_H
