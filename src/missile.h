#include "main.h"

#ifndef MISSILE_H
#define MISSILE_H


class Missile {
public:
    Missile() {}
    Missile(float x, float y, float z,int t);
    glm::vec3 position;
    float rotation,xc,zc,yc,sx,sy,sz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    int type,stat;
    double speed;
    glm::mat4 rotate;
private:
    VAO *ob[20];
};

#endif // MISSILE_H
