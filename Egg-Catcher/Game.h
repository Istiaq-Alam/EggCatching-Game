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
    void drawHomeScreen();
    void drawGameOver();
    void drawUI();
    void reset();


};


#endif

