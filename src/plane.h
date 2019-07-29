#include "main.h"
#include "missile.h"
#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(float x, float y, float z,float r1,float r2,float h);
    glm::vec3 position;
    float rot_y,rot_z,rot_x,l,h,w,fuel;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
    double speed;
    int mis_cd,bomb_cd,fuel_cd,score,life;
    glm::mat4 rotate;
    std::vector<Missile> miss,bomb;
private:
    VAO *ob[2000];
};

#endif // PLANE_H
