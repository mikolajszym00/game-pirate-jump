#include "../inc/Chunk.h"

int Chunk::counter = 0;

ChunkDifficulty Chunk::curr_difficulty = ChunkDifficulty::REALLY_EASY;

std::pair<int, int> Chunk::_drawStage(const std::pair<int, int> &prev_platform_y,
                                      const y_prob_stages_t &y_stages) const {
    int diff = jump_size / (int) y_stages.size();

    for (int i = 0; i < y_stages.size(); i++) {
        if (generate_true_with_prob(y_stages[i])) {
            return std::make_pair(prev_platform_y.first - (i + 1) * diff,
                                  prev_platform_y.first - (prev_platform_y.second - prev_platform_y.first) - i * diff
            );
        }
    }

    return std::make_pair(prev_platform_y.first - y_stages.size() * diff,
                          prev_platform_y.first -
                          (prev_platform_y.second - prev_platform_y.first) -
                          (y_stages.size() - 1) * diff
    );
}

int Chunk::enemy_spawner(std::vector<std::shared_ptr<Enemy>> &enemies,
                         const std::shared_ptr<Platform> &platform,
                         double prob_enemy, double prob_turret) {
    if (!generate_true_with_prob(prob_enemy)) {
        return 0;
    }

    if (generate_true_with_prob(prob_turret)) {
        enemies.push_back(std::make_shared<Turret>(platform->getCurrX(), platform->getCurrY()));
    } else {
        enemies.push_back(std::make_shared<BasicEnemy>(platform->getCurrX(), platform->getCurrY()));
    }

    return 1;
}

bool Chunk::platformSpawner(std::vector<std::shared_ptr<Platform>> &platforms,
                            int x, int y, double prob_vanishing) {
    if (generate_true_with_prob(prob_vanishing)) {
        platforms.emplace_back(std::make_shared<VanishingPlatform>(x, y));
        return true;
    } else {
        platforms.emplace_back(std::make_shared<StationaryPlatform>(x, y));
        return false;
    }
}

bool Chunk::ability_spawner(std::vector<std::shared_ptr<Ability>> &abilities,
                            const std::shared_ptr<Platform> &platform, double prob_immunity) {
    if (generate_true_with_prob(prob_immunity)) {
        abilities.emplace_back(std::make_shared<Immunity>(platform->getCurrX(),
                                                          platform->getCurrY(),
                                                          false));
        return true;
    }
    return false;
}

void Chunk::generate(std::vector<std::shared_ptr<Platform>> &platforms,
                     std::vector<std::shared_ptr<Enemy>> &enemies,
                     std::vector<std::shared_ptr<Ability>> &abilities,
                     int jumps) {
    rules_t rules = CHUNK_RULES[curr_difficulty];
    int spawned_enemies = 0;

    for (int i = 0; i < PLATFORMS_IN_CHUNK; i++) {
        std::pair<int, int> prev_platform_y = std::make_pair(platforms.back()->getCurrY(),
                                                             platforms.back()->getCurrBottom());

        int platform_length = platforms.back()->getCurrRightSide() - platforms.back()->getCurrX();
        int platform_middle = platforms.back()->getCurrX() + platform_length / 2;

        std::pair<int, int> range_y = _drawStage(prev_platform_y, std::get<2>(rules));

        int y = generate_int_from_interval(range_y);
        int x = generate_int_from_interval(std::make_pair(std::max(0, platform_middle - PLATFORM_MAX_DIST),
                                                          std::min(width - platform_length,
                                                              platform_middle + PLATFORM_MAX_DIST)));

        bool vanishing = platformSpawner(platforms, x, y, std::get<6>(rules));

        bool ability = false;
        if (jumps > 50 && !vanishing) {
            ability = ability_spawner(abilities, platforms.back(), std::get<7>(rules));
        }

        if ((int) PLATFORMS_IN_CHUNK * std::get<5>(rules) > spawned_enemies && !vanishing && !ability)
            spawned_enemies += enemy_spawner(enemies,
                                             platforms.back(),
                                             std::get<3>(rules),
                                             std::get<4>(rules));
    }
}

bool Chunk::lastOnScreen(std::vector<std::shared_ptr<Platform>> &platforms) {
    return platforms.back()->getCurrY() > 0;
}

void Chunk::clearChunkClass() {
    counter = 0;
    curr_difficulty = ChunkDifficulty::REALLY_EASY;
}
