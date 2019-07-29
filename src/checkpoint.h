#include "main.h"
#include "cannon.h"
#include "waypoint.h"

#ifndef CHECKPOINT_H
#define CHECKPOINT_H


class Checkpoint {
public:
    Checkpoint() {}
    Checkpoint(float x, float y, float z,int num_can);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    std::vector<Cannon> can;
    Waypoint way;
    int num_cannon;
private:
    VAO *ob[20];
};

#endif // CHECKPOINT_H
