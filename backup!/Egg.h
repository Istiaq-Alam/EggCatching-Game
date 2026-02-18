#ifndef EGG_H
#define EGG_H

#include "Bucket.h"

class Egg {
private:
    float x, y;
    float radius;
    float speed;

public:
    Egg(float x, float y, float speed);

    void update();
    void draw();

    bool collides(Bucket &bucket);
    bool isOutOfBounds();
};

#endif
