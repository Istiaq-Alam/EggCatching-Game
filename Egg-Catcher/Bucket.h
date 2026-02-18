#ifndef BUCKET_H
#define BUCKET_H

#include "Egg.h"

class Bucket {
public:
    float x, y;       // current position
    float width, height; // size of bucket
    float speed;      // movement speed

    Bucket(float startX, float startY);

    void draw();
    void moveLeft();
    void moveRight();
    bool checkCollision(Egg &egg);
};

#endif
