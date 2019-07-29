#include "main.h"

#ifndef ALT_BAR_H
#define ALT_BAR_H


class Alt {
public:
    Alt() {}
    Alt(float x, float y,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP,float x);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO *ob[2000];
};

#endif // ALT_BAR_H
