#include "ground.h"
#include "main.h"


Ground::Ground(float x, float y, float z, float l, float w, float h) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    GLfloat arr[200];
    create_cuboid(arr,l,h,w,0.0f,0.0f,0.0f);
    GLfloat color[200];
    for(int i=0;i<36;i+=3)
    {
        color[i]=98.0/256.0, color[i+1]=76.0/256.0, color[i+2]=171.0/256.0;
    }
    this->ob[0] = create3DObject(GL_TRIANGLES, 36, arr, color, GL_FILL);
}

void Ground::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    // glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ob[0]);
}

void Ground::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Ground::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

