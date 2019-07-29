#include "compass.h"
#include "main.h"


Compass::Compass(float x, float y, float z,color_t color) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    GLfloat top[9*no_triang],bot[9*no_triang],mid[9*no_triang];
    create_circle(top,1.5f,0.0f,0.0f,0.0f);
    create_circle(bot,1.4f,0.0f,0.0f,0.0f);
    create_circle(mid,0.1f,0.0f,0.0f,0.0f);
    GLfloat a1[]={
        0.0f,0.1f,0.0f,
        0.0f,-0.1f,0.0f,
        1.4f,0.0f,0.0f,
    },a2[]={
        0.0f,0.1f,0.0f,
        0.0f,-0.1f,0.0f,
        -1.4f,0.0f,0.0f
    };
    GLfloat c1[9*no_triang];
    for(int i=0;i<9*no_triang;i+=9)
    {
        c1[i] = 155.0/255.0, c1[i+1]=3.0/255.0, c1[i+2]=30.0/255.0;
        c1[i+3] = 243.0/255.0, c1[i+4]=66.0/255.0, c1[i+5]=19.0/255.0;
        c1[i+6] = 244.0/255.0, c1[i+7]=116.0/255.0, c1[i+8]=59.0/255.0;
    }
    this->ob[0] = create3DObject(GL_TRIANGLES, 3*no_triang, top, c1, GL_FILL);
    for(int i=0;i<9*no_triang;i+=9)
    {
        c1[i] = 248.0/255.0, c1[i+1]=119.0/255.0, c1[i+2]=204.0/255.0;
        c1[i+3] = 199.0/255.0, c1[i+4]=130.0/255.0, c1[i+5]=131.0/255.0;
        c1[i+6] = 215.0/255.0, c1[i+7]=190.0/255.0, c1[i+8]=168.0/255.0;
    }
    GLfloat c[]={
        129.0/255.0, 244.0/255.0, 153.0/255.0,
        129.0/255.0, 166.0/255.0, 132.0/255.0,
        87.0/255.0, 136.0/255.0, 108.0/255.0
    },d[]={
        107.0/255.0,15.0/255.0,26.0/255.0,
        185.0/255.0,19.0/255.0,114.0/255.0,
        236.0/255.0,5.0/255.0,142.0/255.0,
    };
    this->ob[1] = create3DObject(GL_TRIANGLES, 3*no_triang, bot, c1, GL_FILL);
    this->ob[2] = create3DObject(GL_TRIANGLES, 3*no_triang, mid, {45,213,123}, GL_FILL);
    this->ob[3] = create3DObject(GL_TRIANGLES, 3, a1, c, GL_FILL); // Actual z-axis
    this->ob[4] = create3DObject(GL_TRIANGLES, 3, a2, d, GL_FILL);

}

void Compass::draw(glm::mat4 VP) {
    this->rotation = atan2(x_comp,z_comp);
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, -1));
    glm::mat4 scale     = glm::scale(glm::vec3(0.4,0.4,1.0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<5;i++)
        draw3DObject(this->ob[i]);
}

void Compass::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Compass::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

