#include "main.h"

#ifndef FUEL_BAR_H
#define FUEL_BAR_H


class FuelBar {
public:
    FuelBar() {}
    FuelBar(float x, float y,color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP,float);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
private:
    VAO *ob[2000];
};

#endif // FUEL_BAR_H
