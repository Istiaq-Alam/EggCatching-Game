#include "Game.h"
#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <math.h>

void Game::drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text++);
}

void Game::init() {
    score = 0;
    lives = 3;
    state = HOME;

    bucket = Bucket(350, 50);
    currentEgg = nullptr;

    chickens.clear();
    float wireY = 500;
    for (int i = 0; i < 5; i++)
        chickens.push_back(Chicken(100 + i * 130, wireY));

    srand(time(0));
}

void Game::spawnEgg() {
    int index = rand() % chickens.size();
    float x = chickens[index].getX();
    float y = chickens[index].getY() - 20;

    float speed = 2.0f + (score * 0.2f);
    if (speed > 8.0f) speed = 8.0f;

    currentEgg = new Egg(x, y, speed);
}

void Game::checkCollisions() {
    if (currentEgg == nullptr) return;

    // Check collision with bucket
    if (bucket.checkCollision(*currentEgg)) {
        score++;
        delete currentEgg;
        currentEgg = nullptr;
    }
    // Check collision with ground
    else if (currentEgg->y <= 50) {
        lives--;
        delete currentEgg;
        currentEgg = nullptr;
        if (lives <= 0) state = GAME_OVER;
    }
}

void Game::update() {
    if (state != PLAYING) return;

    if (currentEgg == nullptr)
        spawnEgg();

    if (currentEgg != nullptr)
        currentEgg->update();

    checkCollisions();
}

// change the life as red heart shapes
void drawHeart(float x, float y, float size) {
    glColor3f(1.0f, 0.0f, 0.0f); // Red color

    // Draw two circles for top of heart
    int numSegments = 50;
    float radius = size / 2.0f;

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 3.14159f * i / numSegments; // Half circle
        glVertex2f(x - radius + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x + radius, y);
    for (int i = 0; i <= numSegments; i++) {
        float angle = 3.14159f * i / numSegments; // Half circle
        glVertex2f(x + radius + cos(angle) * radius, y + sin(angle) * radius);
    }
    glEnd();

    // Draw bottom triangle
    glBegin(GL_TRIANGLES);
    glVertex2f(x - size, y);
    glVertex2f(x + size * 1, y);
    glVertex2f(x + size / -20.0f, y - size * 1.5f);
    glEnd();
}


void Game::render() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (state == HOME) {
        drawText(280, 350, "Egg Drop Saga");
        drawText(280, 300, "Press S to Start");
        drawText(280, 270, "Use A/D to Move Bucket");
        drawText(280, 240, "Catch Eggs Before They Hit Ground");
        drawText(280, 200, "Press Q to Quit");
    }
    else if (state == PLAYING) {
        // Draw wire
        glColor3f(0.2, 0.2, 0.2);
        glLineWidth(3);
        glBegin(GL_LINES);
        glVertex2f(50, 500);
        glVertex2f(750, 500);
        glEnd();

        // Draw chickens
        for (auto& c : chickens)
            c.draw();

        // Draw bucket
        bucket.draw();

        // Draw current egg
        if (currentEgg != nullptr)
            currentEgg->draw();

        // Draw UI
        std::stringstream ss;
        ss << "Score: " << score;
        drawText(20, 570, ss.str().c_str());

        // Old numeric display
        // ss.str("");
        // ss << "Lives: " << lives;
        // drawText(700, 570, ss.str().c_str());
        float startX = 700;
        float startY = 570;
        float heartSize = 10.0f; // Adjust for size

        for (int i = 0; i < lives; i++) {
            drawHeart(startX + i * 25, startY, heartSize);
        }


    }
    else if (state == GAME_OVER) {
        drawText(320, 350, "GAME OVER");
        std::stringstream ss;
        ss << "Final Score: " << score;
        drawText(310, 310, ss.str().c_str());
        drawText(280, 260, "Press R to Play Again");
        drawText(330, 230, "Press Q to Quit");
    }

    glutSwapBuffers();
}

void Game::handleInput(unsigned char key) {
    if (state == HOME) {
        if (key == 's') state = PLAYING;
        if (key == 'q') exit(0);
    }
    else if (state == GAME_OVER) {
        if (key == 'r') init();
        if (key == 'q') exit(0);
    }
    else if (state == PLAYING) {
        if (key == 'a') bucket.moveLeft();
        if (key == 'd') bucket.moveRight();
    }
}

