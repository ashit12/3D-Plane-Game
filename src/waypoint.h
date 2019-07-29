#include "main.h"

#ifndef WAYPOINT_H
#define WAYPOINT_H


class Waypoint {
public:
    Waypoint() {}
    Waypoint(float x, float y, float z, int type);
    glm::vec3 position;
    float rotation,rot;
    int type;
    double speed;
    glm::vec3 checkpoint;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    GLfloat arr1[200],arr2[200];
    void tick();
private:
    VAO *ob[2000];
};

#endif // WAYPOINT_H
