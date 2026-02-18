#ifndef BUCKET_H
#define BUCKET_H

class Bucket {
private:
    float x, y;
    float width, height;
    float speed;

public:
    Bucket();
    Bucket(float x, float y);

    void moveLeft();
    void moveRight();
    void draw();

    float getX();
    float getY();
    float getWidth();
    float getHeight();
};

#endif
