#include "main.h"

#ifndef GROUND_H
#define GROUND_H


class Ground {
public:
    Ground() {}
    Ground(float x, float y, float z,float l,float w,float h);
    glm::vec3 position;
    float rotation,l,h,w;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO *ob[2000];
};

#endif // GROUND_H
