#include "main.h"
#include "missile.h"
#ifndef CANNON_H
#define CANNON_H


class Cannon {
public:
    Cannon() {}
    Cannon(float x, float y, float z);
    glm::vec3 position;
    float rotation,len,wid,hei;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    std::vector<Missile> miss;
    int cd;
private:
    VAO *ob[2000];
};

#endif // CANNON_H
