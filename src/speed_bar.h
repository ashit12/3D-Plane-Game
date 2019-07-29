#include "main.h"

#ifndef SPEED_BAR_H
#define SPEED_BAR_H


class SpeedBar {
public:
    SpeedBar() {}
    SpeedBar(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP, float sp);
    void set_position(float x, float y,float z);
    void tick();
private:
    VAO *ob[2000];
};

#endif // SPEED_BAR_H
