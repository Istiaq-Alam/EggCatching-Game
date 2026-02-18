#include "Game.h"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <sstream>

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
    eggs.clear();
    chickens.clear();

    bucket = Bucket(350, 50);

    // Create chickens on wire
    float wireY = 500;

    for(int i = 0; i < 5; i++) {
        chickens.push_back(Chicken(100 + i*130, wireY));
    }

    srand(time(0));
}


void Game::spawnEgg() {

    if(rand() % 100 < 2) {

        int index = rand() % chickens.size();

        float x = chickens[index].getX();
        float y = chickens[index].getY() - 20;

        eggs.push_back(Egg(x, y, eggSpeed));
    }
}


void Game::increaseDifficulty() {
    if(score > 0 && score % 5 == 0)
        eggSpeed += 0.01f;
}

void Game::checkCollisions() {
    for(auto it = eggs.begin(); it != eggs.end();) {

        if(it->collides(bucket)) {
            score++;
            increaseDifficulty();
            it = eggs.erase(it);
        }
        else if(it->isOutOfBounds()) {
            lives--;
            it = eggs.erase(it);
            if(lives <= 0)
                state = GAME_OVER;
        }
        else {
            ++it;
        }
    }
}

void Game::update() {

    if(state != PLAYING)
        return;

    spawnEgg();

    for(auto &egg : eggs)
        egg.update();

    checkCollisions();
}

void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    if(state == HOME) {

        drawText(280, 350, "EGG CATCHER GAME");
        drawText(300, 300, "Press S to Start");
        drawText(290, 270, "Catch Eggs to Score");
        drawText(260, 240, "Missing Eggs Costs a Life");
        drawText(310, 200, "Press Q to Quit");
    }

    else if(state == PLAYING) {

        // Draw wire
        glColor3f(0.2, 0.2, 0.2);
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2f(50, 500);
        glVertex2f(750, 500);
        glEnd();

        // Draw chickens
        for(auto &chicken : chickens)
            chicken.draw();

        bucket.draw();

        for(auto &egg : eggs)
            egg.draw();

        std::stringstream ss;
        ss << "Score: " << score;
        drawText(20, 570, ss.str());

        ss.str("");
        ss << "Lives: " << lives;
        drawText(700, 570, ss.str());
    }

    else if(state == GAME_OVER) {

        drawText(320, 350, "GAME OVER");

        std::stringstream ss;
        ss << "Final Score: " << score;
        drawText(310, 310, ss.str());

        drawText(280, 260, "Press R to Play Again");
        drawText(330, 230, "Press Q to Quit");
    }

    glutSwapBuffers();
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
            init();  // Reset everything

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
