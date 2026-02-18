#ifndef EGG_H
#define EGG_H

#include "Bucket.h"

class Egg {
public:
    float x, y;
    float width, height;
    float speed;

    Egg(float startX, float startY, float speed);

    void update();
    void draw();

    float getX();  // add these
    float getY();
};
#endif

