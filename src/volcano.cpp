#include "volcano.h"
#include "main.h"


Volcano::Volcano(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 90;
    speed = 1;
    GLfloat top_cir[9*no_triang],bot_cir[9*no_triang],rects[18*no_triang],base[9*no_triang];
    GLfloat top_col[9*no_triang],bot_col[9*no_triang],base_col[9*no_triang],rects_col[18*no_triang];
    for(int i=0;i<9*no_triang;i+=6)
    {
        base_col[i]=1.0/255.0,base_col[i+1]=142.0/255.0,base_col[i+2]=66.0/255.0;
        base_col[i+3]=95.0/255.0,base_col[i+4]=173.0/255.0,base_col[i+5]=65.0/255.0;
    }
    for(int i=0;i<18*no_triang;i+=6)
    {
        rects_col[i] = 255.0/255.0, rects_col[i+1] = 155.0/255.0, rects_col[i+2] = 20.0/255.0;
        rects_col[i+3]=216.0/255.0, rects_col[i+4] = 204.0/255.0, rects_col[i+5] = 52.0/255.0;
    }
    // This creates the cylinder
    float r1 = 1.0f, r2 = 0.5f, h = 2.0f;
    create_circle(base,1.5f,0.0f,0.0f,-h/2.1);
    create_cylinder(top_cir,bot_cir,rects,r1,r2,h,0.0f,0.0f,0.0f);
    this->ob[0] = create3DObject(GL_TRIANGLES, 3*no_triang, base, base_col, GL_FILL);    
    this->ob[1] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, {250,130,76}, GL_FILL);
    this->ob[2] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, COLOR_GREEN, GL_FILL);
    this->ob[3] = create3DObject(GL_TRIANGLES, 6*no_triang, rects, rects_col, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(-1, 0, 0));
    
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);   
    for(int i=0;i<4;i++)
        draw3DObject(this->ob[i]);
}

void Volcano::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Volcano::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

