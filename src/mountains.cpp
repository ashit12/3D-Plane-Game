#include "mountains.h"
#include "main.h"


Mountain::Mountain(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;

    float b = 1.0f,h = 1.0f;
    GLfloat tr1[]={
        0.0f,h/2,0.0f,
        b/2,-h/2,b/2,
        -b/2,-h/2,b/2,
    },tr2[]={
        0.0f,h/2,0.0f,
        -b/2,-h/2,b/2,
        -b/2,-h/2,-b/2,
    },tr3[]={
        0.0f,h/2,0.0f,
        -b/2,-h/2,-b/2,
        b/2,-h/2,-b/2,
    },tr4[]={
        0.0f,h/2,0.0f,
        b/2,-h/2,-b/2,
        b/2,-h/2,b/2,
    },c1[]={
        255.0/255.0,85.0/255.0,0.0,
        1.0,189.0/255.0,0.0,
        158.0/255.0,0.0,89.0/255.0
    },c2[]={
        252.0/255.0,68.0/255.0,15.0/255.0,
        180.0/255.0,227.0/255.0,61.0/255.0,
        244.0/255.0,162.0/255.0,89.0/255.0
    };
    this->ob[0] = create3DObject(GL_TRIANGLES, 3, tr1, c1, GL_FILL);
    this->ob[1] = create3DObject(GL_TRIANGLES, 3, tr2, c2, GL_FILL);
    this->ob[2] = create3DObject(GL_TRIANGLES, 3, tr3, c1, GL_FILL);
    this->ob[3] = create3DObject(GL_TRIANGLES, 3, tr4, c2, GL_FILL);

}

void Mountain::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    glm::mat4 scale = glm::scale(glm::vec3(2.0f,2.5f,1.3f));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<4;i++)
        draw3DObject(this->ob[i]);
}

void Mountain::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Mountain::tick() {
    ;
}

