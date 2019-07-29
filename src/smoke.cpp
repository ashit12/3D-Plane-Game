#include "smoke.h"
#include "main.h"


Smoke::Smoke(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    speed = 1;
    this->time = smoke_max;
    int n = 100;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat top_cir[9*no_triang],bot_cir[9*no_triang],rects[18*no_triang];
    float r1 = 1.0f, r2 = 1.0f, h = 0.1f;
    GLfloat c2[18*no_triang];
    for(int i=0;i<18*no_triang;i+=9)
    {
        c2[i] = 255.0/255.0, c2[i+1]=159.0/255.0, c2[i+2]=28.0/255.0;
        c2[i+3] = 248.0/255.0, c2[i+4]=249.0/255.0, c2[i+5]=145.0/255.0;
        c2[i+6] = 160.0/255.0, c2[i+7]=107.0/255.0, c2[i+8]=154.0/255.0;
    }
    // This creates the cylinder
    create_cylinder(top_cir,bot_cir,rects,r1,r2,h,0.0f,0.0f,0.0f);
    this->ob[0] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, c2, GL_FILL);
    this->ob[1] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, c2, GL_FILL);
    this->ob[2] = create3DObject(GL_TRIANGLES, 6*no_triang, rects, c2, GL_FILL);
    create_cylinder(top_cir,bot_cir,rects,r1-0.1,r2-0.1,h,0.0f,0.0f,0.0f);
    for(int i=0;i<18*no_triang;i+=9)
    {
        c2[i] = 130.0/255.0, c2[i+1]=142.0/255.0, c2[i+2]=130.0/255.0;
        c2[i+3] = 170.0/255.0, c2[i+4]=174.0/255.0, c2[i+5]=142.0/255.0;
        c2[i+6] = 218.0/255.0, c2[i+7]=227.0/255.0, c2[i+8]=229.0/255.0;
    }
    this->ob[3] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, c2, GL_FILL);
    this->ob[4] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, c2, GL_FILL);
    this->ob[5] = create3DObject(GL_TRIANGLES, 6*no_triang, rects, c2, GL_FILL);

}

void Smoke::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<6;i++)
        draw3DObject(this->ob[i]);
}

void Smoke::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Smoke::tick() {
    this->time--;
}

