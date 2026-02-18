#include "Game.h"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <sstream>

std::vector<Chicken> chickens;

void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);
    for(char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void Game::init() {
    score = 0;
    lives = 3;
    eggSpeed = 2.0f;
    state = HOME;

    // Clear previous egg safely
    if (currentEgg != nullptr) {
        delete currentEgg;
        currentEgg = nullptr;
    }

    chickens.clear();
    bucket = Bucket(350, 50);

    float wireY = 500;

    for(int i = 0; i < 5; i++) {
        chickens.push_back(Chicken(100 + i*130, wireY));
    }

    srand(time(0));
}

void Game::spawnEgg() {

    int randomIndex = rand() % chickens.size();
    float startX = chickens[randomIndex].getX();
    float startY = chickens[randomIndex].getY();

    float speed = 2.0f + (score * 0.2f);

    if (speed > 8.0f)
        speed = 8.0f;

    currentEgg = new Egg(startX, startY, speed);
}

void Game::update() {

    if (state != PLAYING)
        return;

    if (currentEgg == nullptr) {
        spawnEgg();
    }

    if (currentEgg != nullptr) {

        currentEgg->update();

        // Catch
        if (bucket.checkCollision(*currentEgg)) {
            score++;
            delete currentEgg;
            currentEgg = nullptr;
        }

        // Hit ground
        else if (currentEgg->getY() <= 50) {
            lives--;
            delete currentEgg;
            currentEgg = nullptr;

            if (lives <= 0) {
                state = GAME_OVER;
            }
        }
    }
}

void Game::render() {

    if (state == HOME) {
        drawHomeScreen();
        return;
    }

    if (state == GAME_OVER) {
        drawGameOver();
        return;
    }

    //background.draw();
    bucket.draw();

    for (auto &chicken : chickens)
        chicken.draw();

    if (currentEgg != nullptr)
        currentEgg->draw();

    drawUI();
}

void Game::drawUI() {
    std::stringstream ss;
    ss << "Score: " << score;
    drawText(20, 570, ss.str());

    ss.str("");
    ss << "Lives: " << lives;
    drawText(700, 570, ss.str());
}


void Game::reset() {
    score = 0;
    lives = 3;
    state = PLAYING;

    if (currentEgg != nullptr) {
        delete currentEgg;
        currentEgg = nullptr;
    }
}

void Game::drawHomeScreen() {
    drawText(280, 350, "EGG CATCHER GAME");
    drawText(300, 300, "Press S to Start");
    drawText(290, 270, "Catch Eggs to Score");
    drawText(260, 240, "Missing Eggs Costs a Life");
    drawText(310, 200, "Press Q to Quit");
}

void Game::drawGameOver() {
    drawText(320, 350, "GAME OVER");

    std::stringstream ss;
    ss << "Final Score: " << score;
    drawText(310, 310, ss.str());

    drawText(280, 260, "Press R to Play Again");
    drawText(330, 230, "Press Q to Quit");
}

void Game::handleInput(unsigned char key) {

    if(state == HOME) {

        if(key == 's')
            state = PLAYING;

        if(key == 'q')
            exit(0);
    }

    else if(state == GAME_OVER) {

        if(key == 'r')
            init();

        if(key == 'q')
            exit(0);
    }

    else if(state == PLAYING) {

        if(key == 'a')
            bucket.moveLeft();

        if(key == 'd')
            bucket.moveRight();
    }
}
