#include "fuel.h"
#include "main.h"


Fuel::Fuel(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    speed = 1;
    this->time = fuel_max;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat arr[200];
    float l=0.2f,h=0.2f,w=0.2f;
    create_cuboid(arr,l,h,w,0.0f,0.0f,0.0f);
    GLfloat c[]={
        250.0/255.0,121.0/255.0,33.0/255.0,
        244.0/255.0,0,0,
        254.0/255.0,153.0/255.0,32.0/255.0,
        246.0/255.0,174.0/255.0,45.0/255.0,
        242.0/255.0,100.0/255.0,25.0/255.0,
        237.0/255.0,255.0/255.0,134.0/255.0,
        243.0/255.0,201.0/255.0,105.0/255.0,
        255.0/255.0,212.0/255.0,0
    };
    this->ob[0] = create3DObject(GL_TRIANGLES, 36, arr, c, GL_FILL);
    
}

void Fuel::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
        draw3DObject(this->ob[0]);
}

void Fuel::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Fuel::tick() {
    this->time--;
}

