#include "main.h"

#ifndef MOUNTAIN_H
#define MOUNTAIN_H


class Mountain {
public:
    Mountain() {}
    Mountain(float x, float y, float z);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO *ob[2000];
};

#endif // MOUNTAIN_H
