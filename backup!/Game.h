#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Bucket.h"
#include "Egg.h"
#include "Chicken.h"


enum GameState {
    HOME,
    PLAYING,
    GAME_OVER
};

class Game {
private:
    int score;
    int lives;
    float eggSpeed;
    GameState state;

    Bucket bucket;
    std::vector<Egg> eggs;
    std::vector<Chicken> chickens;


public:
    void init();
    void update();
    void render();
    void handleInput(unsigned char key);

    void spawnEgg();
    void checkCollisions();
    void increaseDifficulty();
};

#endif
