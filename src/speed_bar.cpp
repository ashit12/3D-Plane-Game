#include "speed_bar.h"
#include "main.h"


SpeedBar::SpeedBar(float x, float y,color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 90;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat top[9*no_triang],bot[9*no_triang];
    create_circle(top,1.0f,0.0f,0.0f,0.0f);
    create_circle(bot,0.8f,0.0f,0.0f,0.0f);
    GLfloat needle[]={
        -0.1f,0.0f,0.0f,
        0.1f,0.0f,0.0f,
        0.0f,1.0f,0.0f
    },c[]={
        241.0/255.0,143.0/255.0,1.0/255.0,
        162.0/255.0,59.0/255.0,144.0/255.0,
        178.0/255.0,239.0/255.0,255.0/255.0,
    };
    GLfloat c1[9*no_triang];
    for(int i=0;i<9*no_triang;i+=9)
    {
        c1[i] = 209.0/255.0, c1[i+1]=213.0/255.0, c1[i+2]=222.0/255.0;
        c1[i+3] = 183.0/255.0, c1[i+4]=192.0/255.0, c1[i+5]=194.0/255.0;
        c1[i+6] = 131.0/255.0, c1[i+7]=117.0/255.0, c1[i+8]=105.0/255.0;
    }
    this->ob[0] = create3DObject(GL_TRIANGLES, 3*no_triang/2, top, c1, GL_FILL);
    for(int i=0;i<9*no_triang;i+=9)
    {
        c1[i] = 86.0/255.0, c1[i+1]=77.0/255.0, c1[i+2]=101.0/255.0;
        c1[i+3] = 46.0/255.0, c1[i+4]=47.0/255.0, c1[i+5]=47.0/255.0;
        c1[i+6] = 5.0/255.0, c1[i+7]=16.0/255.0, c1[i+8]=20.0/255.0;
    }
    this->ob[1] = create3DObject(GL_TRIANGLES, 3*no_triang/2, bot, c1, GL_FILL);
    this->ob[2] = create3DObject(GL_TRIANGLES, 3, needle, c, GL_FILL);

}

void SpeedBar::draw(glm::mat4 VP, float sp) {
    //Rotating and drawing the needle
    sp = abs(sp);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) ((this->rotation) * M_PI / 180.0f), glm::vec3(0, 0, -1));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ob[0]);
    draw3DObject(this->ob[1]);
    
    //Rotating and drawing the remaining bar
    rotate    *= glm::rotate((float) ((this->rotation-270) * M_PI / 180.0f), glm::vec3(0, 0, -1));
    rotate *= glm::rotate((float)(sp*M_PI/max_speed),glm::vec3(0,0,-1));
    Matrices.model *= (rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ob[2]);

}

void SpeedBar::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void SpeedBar::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

