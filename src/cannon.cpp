#include "cannon.h"
#include "main.h"


Cannon::Cannon(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    this->cd = 300;
    GLfloat top_cir[9*no_triang],bot_cir[9*no_triang],rects[18*no_triang];
    GLfloat c1[18*no_triang],c2[9*no_triang];
    int p = rand()%2;
    if(!p)
    {
        for(int i=0;i<18*no_triang;i+=9)
        {
            c1[i] = 204.0/255.0, c1[i+1]=41.0/255.0, c1[i+2]=54.0/255.0;
            c1[i+3] = 244.0/255.0, c1[i+4]=152.0/255.0, c1[i+5]=156.0/255.0;
            c1[i+6] = 230.0/255.0, c1[i+7]=199.0/255.0, c1[i+8]=156.0/255.0;
        }
        for(int i=0;i<9*no_triang;i+=9)
        {
            c2[i] = 247.0/255.0, c2[i+1]=235.0/255.0, c2[i+2]=236.0/255.0;
            c2[i+3] = 239.0/255.0, c2[i+4]=247.0/255.0, c2[i+5]=207.0/255.0;
            c2[i+6] = 164.0/255.0, c2[i+7]=153.0/255.0, c2[i+8]=190.0/255.0;
        }
    }
    else
    {
        for(int i=0;i<18*no_triang;i+=9)
        {
            c1[i] = 0.0/255.0, c1[i+1]=21.0/255.0, c1[i+2]=20.0/255.0;
            c1[i+3] = 107.0/255.0, c1[i+4]=5.0/255.0, c1[i+5]=4.0/255.0;
            c1[i+6] = 163.0/255.0, c1[i+7]=50.0/255.0, c1[i+8]=11.0/255.0;
        }
        for(int i=0;i<9*no_triang;i+=9)
        {
            c2[i] = 255.0/255.0, c2[i+1]=103.0/255.0, c2[i+2]=0.0/255.0;
            c2[i+3] = 186.0/255.0, c2[i+4]=92.0/255.0, c2[i+5]=18.0/255.0;
            c2[i+6] = 225.0/255.0, c2[i+7]=55.0/255.0, c2[i+8]=0.0/255.0;
        }
    }
    float r1 = 1.0f, r2 = 0.5f, h = 0.5f;
    this->len = this->wid = 2.0f, this->hei = 0.5f;
    create_cylinder(top_cir,bot_cir,rects,r1,r2,h,0.0f,0.0f,0.0f);
    this->ob[0] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, COLOR_RED, GL_FILL);
    this->ob[1] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, COLOR_RED, GL_FILL);
    this->ob[2] = create3DObject(GL_TRIANGLES, 6*no_triang, rects, c1, GL_FILL);
    create_cylinder(top_cir,bot_cir,rects,r2,r2,h,0.0f,0.0f,h/2);
    this->ob[3] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, c2, GL_FILL);
    this->ob[4] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, COLOR_RED, GL_FILL);
    

    this->ob[5] = create3DObject(GL_TRIANGLES, 6*no_triang, rects, c1, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(-1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<6;i++)
        draw3DObject(this->ob[i]);
}

void Cannon::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Cannon::tick() {
    this->cd--;
}

