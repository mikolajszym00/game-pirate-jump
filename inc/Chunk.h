#ifndef PIRATE_JUMP_CHUNK_H
#define PIRATE_JUMP_CHUNK_H

#include <vector>
#include <tuple>
#include <unordered_map>
#include <iostream>
#include <utility>
#include <random>
#include <chrono>
#include <memory>

#include "platform/Platform.h"
#include "platform/VanishingPlatform.h"
#include "platform/StationaryPlatform.h"
#include "enemy/Enemy.h"
#include "enemy/Turret.h"
#include "enemy/BasicEnemy.h"
#include "func.h"
#include "settings.h"
#include "gameObject/Ability.h"
#include "gameObject/Immunity.h"

class Chunk {

public:
    ~Chunk() = default;

    Chunk() = default;

    Chunk(int width, int jump_size) :
            width(width),
            jump_size(jump_size) {
        setDifficulty();
    }

    static int enemy_spawner(std::vector<std::shared_ptr<Enemy>> &enemies,
                      const std::shared_ptr<Platform> &platform,
                      double prob_enemy, double prob_turret);

    static bool platformSpawner(std::vector<std::shared_ptr<Platform>> &platforms,
                         int x, int y, double prob_vanishing);

    static bool ability_spawner(std::vector<std::shared_ptr<Ability>> &abilities,
                         const std::shared_ptr<Platform> &platform, double prob_immunity);

    void generate(std::vector<std::shared_ptr<Platform>> &platforms,
                  std::vector<std::shared_ptr<Enemy>> &enemies,
                  std::vector<std::shared_ptr<Ability>> &abilities,
                  int jumps);

    bool lastOnScreen(std::vector<std::shared_ptr<Platform>> &platforms);

    static void clearChunkClass();

private:
    static int counter;
    static ChunkDifficulty curr_difficulty;
    int width;
    int jump_size;

    void setDifficulty() {
        if (curr_difficulty != ChunkDifficulty::REALLY_HARD) {
            if (std::get<0>(CHUNK_RULES[curr_difficulty]) == counter) {
                curr_difficulty = std::get<1>(CHUNK_RULES[curr_difficulty]);
            }
            counter++;
        }
    }

    std::pair<int, int> _drawStage(const std::pair<int, int> &prev_platform_y,
                                   const y_prob_stages_t &y_stages) const;

};

#endif //PIRATE_JUMP_CHUNK_H
