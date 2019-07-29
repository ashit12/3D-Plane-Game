#include "fuel_bar.h"
#include "main.h"


FuelBar::FuelBar(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90;
    speed = 1;
    int n = 100;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat arr[20];
    GLfloat c[]={
        19.0/255.0,3.0/255.0,3.0/255.0,
        45.0/255.0,8.0/255.0,10.0/255.0,
        44.0/255.0,7.0/255.0,3.0/255.0,
        19.0/255.0,3.0/255.0,3.0/255.0,
        45.0/255.0,8.0/255.0,10.0/255.0,
        44.0/255.0,7.0/255.0,3.0/255.0
    },d[]={
        155.0/255.0,136.0/255.0,22.0/255.0,
        236.0/255.0,206.0/255.0,142.0/255.0,
        243.0/255.0,222.0/255.0,44.0/255.0,
        155.0/255.0,136.0/255.0,22.0/255.0,
        236.0/255.0,206.0/255.0,142.0/255.0,
        243.0/255.0,222.0/255.0,44.0/255.0, 
    };
    float a =1.8f;
    for(int i=0;i<10;i++,a-=0.2f)
    {
        create_rect(arr,0.2f,0.4f,a,0.0f);
        this->ob[i]=create3DObject(GL_TRIANGLES, 6, arr, d, GL_FILL);
    }
    a=0.0f;
    for(int i=0;i<10;i++,a+=0.2f)
    {
        create_rect(arr,0.3f,0.5f,a-0.05,-0.05);
        this->ob[i+10]=create3DObject(GL_TRIANGLES, 6, arr, c, GL_FILL);
    } 
}

void FuelBar::draw(glm::mat4 VP,float f) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<10;i++)
        draw3DObject(this->ob[i+10]);
    for(int i=0;i<f;i++)
        draw3DObject(this->ob[i]);
}

void FuelBar::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void FuelBar::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

