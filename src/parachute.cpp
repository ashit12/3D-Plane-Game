#include "parachute.h"
#include "main.h"


Parachute::Parachute(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    speed = 1.0;
    GLfloat top_cir[9*no_triang],bot_cir[9*no_triang],rects[18*no_triang];
    
    GLfloat c1[18*no_triang];
    for(int i=0;i<18*no_triang;i+=9)
    {
        c1[i] = 255.0/255.0, c1[i+1]=94.0/255.0, c1[i+2]=91.0/255.0;
        c1[i+3] = 39.0/255.0, c1[i+4]=62.0/255.0, c1[i+5]=71.0/255.0;
        c1[i+6] = 204.0/255.0, c1[i+7]=74.0/255.0, c1[i+8]=195.0/255.0;
    }
    // This creates the cylinder
    float r = 1.0f,h=0.4f;

    create_cylinder(top_cir,bot_cir,rects,0.0f,r,0.4f,0.0f,0.4f,0.0f);
    this->ob[0] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, COLOR_RED, GL_FILL);
    this->ob[1] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, COLOR_RED, GL_FILL);
    this->ob[2] = create3DObject(GL_TRIANGLES, 6*no_triang, rects, c1, GL_FILL);
    
    for(int i=0;i<18*no_triang;i+=9)
    {
        c1[i] = 204.0/255.0, c1[i+1]=41.0/255.0, c1[i+2]=54.0/255.0;
        c1[i+3] = 244.0/255.0, c1[i+4]=152.0/255.0, c1[i+5]=156.0/255.0;
        c1[i+6] = 230.0/255.0, c1[i+7]=199.0/255.0, c1[i+8]=156.0/255.0;
    }
    create_cylinder(top_cir,bot_cir,rects,r,0.0f,0.4f,0.0f,0.4f,0.4f);
    this->ob[3] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, c1, GL_FILL);
    this->ob[4] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, c1, GL_FILL);
    this->ob[5] = create3DObject(GL_LINES,     6*no_triang, rects, {20,15,45}, GL_FILL);

    GLfloat arr[200];
    create_cuboid(arr,0.5f,0.5f,0.5f,0.0f,0.4f,0.8f);
    GLfloat cub[]={
        117.0/255.0,221.0/255.0,221.0/255.0,
        80.0/255.0,137.0/255.0,145.0/255.0,
        23.0/255.0,42.0/255.0,58.0/255.0,
        0.0/255.0,67.0/255.0,50.0/255.0,
        9.0/255.0,188.0/255.0,138.0/255.0,
        180.0/255.0,151.0/255.0,214.0/255.0,
        191.0/255.0,172.0/255.0,150.0/255.0,
        207.0/255.0,203.0/255.0,202.0/255.0,
    };
    this->ob[6] = create3DObject(GL_TRIANGLES, 36, arr, cub, GL_FILL);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<7;i++)
        draw3DObject(this->ob[i]);
}

void Parachute::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Parachute::tick() {
    this->position.y -= speed/60;
}

