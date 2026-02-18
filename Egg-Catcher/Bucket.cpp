#include "Bucket.h"
#include <GL/glut.h>



Bucket::Bucket(float startX, float startY) {
    x = startX;
    y = startY;
    width = 100;    // example width
    height = 30;    // example height
    speed = 10.0f;  // how many pixels bucket moves per key press
}

bool Bucket::checkCollision(Egg &egg) {
    // Simple AABB collision
    if (egg.getX() + egg.width >= x &&
        egg.getX() <= x + width &&
        egg.getY() + egg.height >= y &&
        egg.getY() <= y + height) {
        return true;
    }
    return false;
}


void Bucket::moveLeft() {
    x -= speed;
    if(x < 0) x = 0;  // keep in screen bounds
}

void Bucket::moveRight() {
    x += speed;
    if(x + width > 800) x = 800 - width;  // assuming screen width 800
}


void Bucket::draw() {
    glColor3f(0.6, 0.3, 0.1);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

//float Bucket::getX() { return x; }
//float Bucket::getY() { return y; }
//float Bucket::getWidth() { return width; }
//float Bucket::getHeight() { return height; }

