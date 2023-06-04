/*
 * A file containing all the macros and objects that balance the game
 */

#ifndef PIRATE_JUMP_SETTINGS_H
#define PIRATE_JUMP_SETTINGS_H

#include <vector>

#define PROJECTILE_COOLDOWN 500 // in milliseconds

#define TURRET_COOLDOWN 3000 // in milliseconds

#define STEP 3 // slowing down the speed of hero falling and moving
#define JUMP_SIZE 200 // in px

// I think the value is too low for the speed of the game. I recommended 6000 ms.
#define COOLDOWN_VANISHING 3000 // in milliseconds

enum class ChunkDifficulty {
    REALLY_EASY,
    EASY,
    MEDIUM,
    HARD,
    REALLY_HARD
};

using end_t = int;
using enemies_prob_t = double;
using turret_prob_t = double;

// The maximum enemy rate multiplied by PLATFORMS_IN_CHUNK
// equals the number of enemies
using max_enemies_rate_t = double;

using vanishing_prob_t = double;
using ability_prob_t = double;
using next_diff_t = ChunkDifficulty;

// Probability of creating platform at the lower level (closer to player)
using y_prob_stages_t = std::vector<double>;

using rules_t = std::tuple<end_t,
        next_diff_t,
        y_prob_stages_t,
        enemies_prob_t,
        turret_prob_t,
        max_enemies_rate_t,
        vanishing_prob_t,
        ability_prob_t>;

// The maximum distance at x between the current highest platform and the spawned platform
#define PLATFORM_MAX_DIST 250

// The number of platforms generated in one chunk
#define PLATFORMS_IN_CHUNK 20

// Option to activate testing mode: difficulties will change faster
#define TESTING_GAME_MODE

#if defined(TESTING_GAME_MODE)
#define CHUNK_RULES                          \
std::unordered_map<ChunkDifficulty, rules_t>   \
{                                            \
{ChunkDifficulty::REALLY_EASY, {2, ChunkDifficulty::EASY, {0.7, 1., 1., 1.}, 0.1, 0.0, 0.1, 0.0, 0.01}}, \
{ChunkDifficulty::EASY, {4, ChunkDifficulty::MEDIUM, {0.6, 0.8, 1., 1.}, 0.2, 0.2, 0.2, 0.1, 0.02}},       \
{ChunkDifficulty::MEDIUM, {6, ChunkDifficulty::HARD, {0.4, 0.5, 0.9, 1.}, 0.4, 0.3, 0.3, 0.1, 0.02}},    \
{ChunkDifficulty::HARD, {8, ChunkDifficulty::REALLY_HARD, {0.2, 0.3, 0.5, 1.}, 0.6, 0.3, 0.5, 0.2, 0.02}}, \
{ChunkDifficulty::REALLY_HARD, {10, ChunkDifficulty::REALLY_HARD, {0.0, 0.0, 0.1, 1.}, 0.8, 0.3, 0.6, 0.3, 0.02}}\
}
#else
#define CHUNK_RULES                          \
std::unordered_map<ChunkDifficulty, rules_t>   \
{                                            \
{ChunkDifficulty::REALLY_EASY, {10, ChunkDifficulty::EASY, {0.7, 1., 1., 1.}, 0.1, 0.0, 0.1, 0.0, 0.01}}, \
{ChunkDifficulty::EASY, {25, ChunkDifficulty::MEDIUM, {0.6, 0.8, 1., 1.}, 0.2, 0.2, 0.2, 0.1, 0.02}},       \
{ChunkDifficulty::MEDIUM, {60, ChunkDifficulty::HARD, {0.4, 0.5, 0.9, 1.}, 0.4, 0.3, 0.3, 0.1, 0.05}},    \
{ChunkDifficulty::HARD, {100, ChunkDifficulty::REALLY_HARD, {0.2, 0.3, 0.5, 1.}, 0.6, 0.3, 0.5, 0.2, 0.05}}, \
{ChunkDifficulty::REALLY_HARD, {150, ChunkDifficulty::REALLY_HARD, {0.0, 0.0, 0.1, 1.}, 0.8, 0.3, 0.6, 0.3, 0.07}}\
}
#endif

#define FAC 2 // slowing down the speed of falling (eg. platforms)

#define FAC2 4 // slowing down the speed of turret projectile

#define HERO_RESISTANCE 20000 // duration of the immunity in ms

#endif //PIRATE_JUMP_SETTINGS_H
