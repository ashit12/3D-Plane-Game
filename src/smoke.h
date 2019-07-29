#include "main.h"

#ifndef SMOKE_H
#define SMOKE_H


class Smoke {
public:
    Smoke() {}
    Smoke(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    int time;

private:
    VAO *ob[2000];
};

#endif // SMOKE_H
