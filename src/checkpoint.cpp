#include "checkpoint.h"
#include "main.h"
#include "cannon.h"
#include "waypoint.h"


Checkpoint::Checkpoint(float x, float y, float z,int num_can) {
    this->position = glm::vec3(x, y+0.01, z);
    this->rotation = 90;
    this->num_cannon = num_can;
    GLfloat arr[9*no_triang];
    create_circle(arr,5.0f,0.0f,0.0f,0.0f);
    GLfloat c1[9*no_triang];
    for(int i=0;i<9*no_triang;i+=9)
    {
        c1[i] = 227.0/255.0, c1[i+1]=228.0/255.0, c1[i+2]=219.0/255.0;
        c1[i+3] = 205.0/255.0, c1[i+4]=205.0/255.0, c1[i+5]=205.0/255.0;
        c1[i+6] = 134.0/255.0, c1[i+7]=187.0/255.0, c1[i+8]=216.0/255.0;
    }
    this->ob[0]=create3DObject(GL_TRIANGLES, 3*no_triang, arr, c1, GL_FILL);
    this->way = Waypoint(x,y+7.0f,z,0);
    int sign[] = {-1,1};
    for(int i=0;i<num_can;i++)
    {
        Cannon c = Cannon(x+sign[rand()%2]*(rand()%4),y+0.2f,z+sign[rand()%2]*(rand()%4));
        this->can.push_back(c);
    } 
}

void Checkpoint::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->ob[0]);
}

void Checkpoint::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Checkpoint::tick() {
    //this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}


