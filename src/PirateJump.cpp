#include "../inc/PirateJump.h"

void PirateJump::PreInit(int &width, int &height, bool &fullscreen) {
    BASE = this->height - 80;

    width = this->width;
    height = this->height;

    mouse_pos = {0, 0};

    score = 0;
    score_platform = 0;

    std::fill(used_number_of_numbers, used_number_of_numbers
                                      + 10, 0);

    fullscreen = false;
}

bool PirateJump::Init() {
    hero = Hero(STEP, width / 2, BASE - 100, width);

    platforms.
            emplace_back(std::make_shared<StationaryPlatform>(width / 2, BASE)
    );

    curr_chunk = Chunk(width, hero.getJumpSize());
    curr_chunk.
            generate(platforms, enemies, abilities, score_platform
    );

    curr_base_platform_idx = 0;
    prev_tick = getTickCount();

    cooldown = 0;

    immunityInfo = Immunity(10, 10, true);

    bg = createSprite("../data/bck.png");
    setSpriteSize(bg, width, height
    );

    return true;
}

void PirateJump::Close() {
    projectiles.

            clear();

    turret_projectiles.

            clear();

    platforms.

            clear();

    enemies.

            clear();

    abilities.

            clear();

}

bool PirateJump::Tick() {
    unsigned int tick_delta = getTickCount() - prev_tick;
    prev_tick = getTickCount();

    generate();

    if (

            checkCollision()

            ||
            move(tick_delta)
            ) {
        restartGame();

        return false;
    }

    hero.
            action(tick_delta);

    enemyAction();

    platformAction(tick_delta);

    clean();

    draw();

    return false;
}

void PirateJump::onMouseMove(int x, int y, int xrelative, int yrelative) {
    mouse_pos = {x, y};
}

void PirateJump::onMouseButtonClick(FRMouseButton button, bool isReleased) {
    unsigned int tick_delta = getTickCount() - prev_tick_cooldown;
    prev_tick_cooldown = getTickCount();

    if (cooldown <= PROJECTILE_COOLDOWN)
        cooldown += (int)
                tick_delta;

    if (cooldown > PROJECTILE_COOLDOWN && button == FRMouseButton::LEFT && !isReleased) {
        projectiles.
                emplace_back(std::make_shared<HeroProjectile>(std::make_pair(hero.getCenter(), hero.getCurrY()),
                                                              mouse_pos)
        );
        cooldown = 0;
    }
}

void PirateJump::onKeyPressed(FRKey k) {
    if (k == FRKey::LEFT) {
        hero.
                L = true;
    }

    if (k == FRKey::RIGHT) {
        hero.
                R = true;
    }
}

void PirateJump::onKeyReleased(FRKey k) {
    if (k == FRKey::LEFT) {
        hero.
                L = false;
    }

    if (k == FRKey::RIGHT) {
        hero.
                R = false;
    }
}

const char *PirateJump::GetTitle() {
    return "doodle jump";
}


void PirateJump::generate() {
    if (curr_chunk.lastOnScreen(platforms)) {
        curr_chunk = Chunk(width, hero.getJumpSize());
        curr_chunk.generate(platforms, enemies, abilities, score_platform);
    }
}

void PirateJump::restartGame() {
    projectiles.clear();
    turret_projectiles.clear();
    platforms.clear();
    enemies.clear();
    abilities.clear();

    score = 0;
    score_platform = 0;

    Chunk::clearChunkClass();
    Init();
}

void PirateJump::enemyAction() {
    for (std::shared_ptr<Enemy> &e: enemies) {
        e->action(turret_projectiles,
                  std::make_pair(hero.getCenter(), hero.getCurrY()));
    }
}

void PirateJump::platformAction(unsigned int tick_delta) {
    for (std::shared_ptr<Platform> &p: platforms) {
        p->action(tick_delta);
    }
}

bool PirateJump::checkCollision() {
    // hero-enemy collision
    if (hero.check_enemies_collision(enemies) == -1) {
        return true;
    }

    // hero-platform collision
    int new_base_platform_idx = hero.check_platforms_collision(platforms);
    if (new_base_platform_idx != -1) {
        hero.FALLING = false;
        curr_base_platform_idx = new_base_platform_idx;
    }

    // enemy-projectiles collision
    for (auto e = enemies.begin(); e != enemies.end();) {
        bool enemy_deleted = false;

        if ((*e)->getCurrY() < 0) { // enemies are sorted by y coordinate
            break;
        }

        for (auto p = projectiles.begin(); p != projectiles.end();) {
            if ((*e)->collision<HeroProjectile>(*p)) {
                p = projectiles.erase(p);
                e = enemies.erase(e);

                enemy_deleted = true;
                break;
            } else {
                p++;
            }
        }

        if (!enemy_deleted) {
            e++;
        }
    }

    // turret projectiles-hero collision
    for (auto p = turret_projectiles.begin(); p != turret_projectiles.end();) {
        if (hero.collision<TurretProjectile>(*p)) {
            p = turret_projectiles.erase(p);

            if (!hero.resistant) {
                return true;
            }

        } else {
            p++;
        }
    }

    // hero-ability collision
    for (auto a = abilities.begin(); a != abilities.end();) {
        if (hero.collision<Ability>(*a)) {
            a = abilities.erase(a);
            hero.setResistance();
        } else {
            a++;
        }
    }

    return false;
}

bool PirateJump::move(unsigned int tick_delta) {
    std::shared_ptr<Platform> &curr_base_platform = platforms[curr_base_platform_idx];

    hero.move(tick_delta, curr_base_platform->getCurrY());

    if (hero.getCurrY() > height) {
        return true;
    }

    // moving objects down in order to mimic camera that follows hero
    if (curr_base_platform->getCurrY() < BASE) {
        moveObjects(tick_delta, BASE - curr_base_platform->getCurrY());
        score += (BASE - curr_base_platform->getCurrY()) / 20;
    }

    for (std::shared_ptr<HeroProjectile> &p: projectiles) {
        p->move(tick_delta, width);
    }

    for (std::shared_ptr<TurretProjectile> &tp: turret_projectiles) {
        tp->move(tick_delta, width);
    }

    return false;
}

void PirateJump::clean() {
    for (auto p = platforms.begin(); p != platforms.end();) {
        if ((*p)->getCurrY() > height) {
            p = platforms.erase(p);
            curr_base_platform_idx--;
            score_platform = (score_platform + 1) % INT_MAX;
        } else {
            break;
        }
    }

    for (auto e = enemies.begin(); e != enemies.end();) {
        if ((*e)->getCurrY() > height) {
            e = enemies.erase(e);
        } else {
            break;
        }
    }

    for (auto p = projectiles.begin(); p != projectiles.end();) {
        if (0 - 10 > (*p)->getCurrY() || (*p)->getCurrY() > height + 10) {
            p = projectiles.erase(p);
        } else {
            p++;
        }
    }

    for (auto tp = turret_projectiles.begin(); tp != turret_projectiles.end();) {
        if (0 - 10 > (*tp)->getCurrY() || (*tp)->getCurrY() > height + 10) {
            tp = turret_projectiles.erase(tp);
        } else {
            tp++;
        }
    }

    for (auto a = abilities.begin(); a != abilities.end();) {
        if ((*a)->getCurrY() > height) {
            a = abilities.erase(a);
        } else {
            break;
        }
    }

}

void PirateJump::drawScore(int s, int which) {
    int x = width - 13 * 2;
    int y = 10 + 20 * which;

    do {
        int v = s % 10;

        int num = used_number_of_numbers[v];

        if (numbers[v].size() >= num) {
            numbers[v].push_back(Number(x, y, v));
        }

        Number &num_to_draw = numbers[v][num];
        drawSprite(num_to_draw.getSprite(), x, y);

        used_number_of_numbers[v]++;

        s /= 10;
        x -= 13;
    } while (s);

    std::fill(used_number_of_numbers, used_number_of_numbers + 10, 0);
}

void PirateJump::draw() {
    drawSprite(bg, 0, 0);

    drawObjects(platforms);
    drawObjects(enemies);
    drawObjects(projectiles);
    drawObjects(turret_projectiles);
    drawObjects(abilities);

    drawSprite(hero.getSprite(), hero.getCurrX(), hero.getCurrY());

    drawScore(score, 0);
    drawScore(score_platform, 1);

    if (hero.resistant) {
        drawSprite(immunityInfo.getSprite(),
                   immunityInfo.getCurrX(),
                   immunityInfo.getCurrY());
    }
}

void PirateJump::moveObjects(unsigned int delta, int dist) {
    for (std::shared_ptr<Platform> &p: platforms) {
        p->move(delta, dist);
    }

    for (std::shared_ptr<Enemy> &e: enemies) {
        e->move(delta, dist);
    }

    for (std::shared_ptr<Ability> &a: abilities) {
        a->move(delta, dist);
    }

    for (std::shared_ptr<TurretProjectile> &tp: turret_projectiles) {
        tp->fallingMove(delta, dist);
    }
}
