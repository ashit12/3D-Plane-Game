#include "waypoint.h"
#include "main.h"


Waypoint::Waypoint(float x, float y,float z, int type) {
    this->position = glm::vec3(x, y,z);
    this->rotation = 90;
    this->rot = 0.0f;
    this->type = type;
    speed= 0.0f;
    this->checkpoint = glm::vec3(1.0f);
    if(this->type==1)
        this->checkpoint = glm::vec3(checkx,0.0f,checkz);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    float len = 2.0f, wid = 1.0f;
    GLfloat arr[]={
        len,wid/2,0.0f,
        -len,wid/2,0.0f,
        len,-wid/2,0.0f,
        -len,wid/2,0.0f,
        len,-wid/2,0.0f,
        -len,-wid/2,0.0f
    },ar[]={
        -2*wid,len/2+0.5f,0.0f,
        -2*wid,-len/2-0.5f,0.0f,
        -2*wid-0.5f,0.0f,0.0f
    },c1[]={
        163.0/255.0,0.0/255.0,21.0/255.0,
        245.0/255.0,93.0/255.0,62.0/255.0,
        241.0/255.0,211.0/255.0,2.0/255.0,
        163.0/255.0,0.0/255.0,21.0/255.0,
        245.0/255.0,93.0/255.0,62.0/255.0,
        241.0/255.0,211.0/255.0,2.0/255.0,
    },c2[]={
        163.0/255.0,0.0/255.0,21.0/255.0,
        245.0/255.0,93.0/255.0,62.0/255.0,
        241.0/255.0,211.0/255.0,2.0/255.0,
    };
    this->ob[0] = create3DObject(GL_TRIANGLES, 6, arr, c1, GL_FILL);
    this->ob[1] = create3DObject(GL_TRIANGLES, 3, ar, c2, GL_FILL);
}

void Waypoint::draw(glm::mat4 VP) {
    if(this->type==0)
    {
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
        glm::mat4 ro = glm::rotate((float)(this->rot),glm::vec3(1,0,0));
        Matrices.model *= (translate * rotate * ro);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    }
    else
    {
        this->rotation = 0.0f;
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
        this->rotation = 90.0f;
        rotate    *= glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
        rotate    *= glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));

        glm::mat4 rota = glm::mat4(1.0f);
        glm::vec3 v = glm::normalize(this->checkpoint-this->position);
        rota[2][0] = v.x, rota[2][1] = v.y, rota[2][2] = v.z;
        rota[1][0] = 0.0f, rota[1][1] = 1.0f, rota[1][2] = 0.0f;
        glm::vec3 v1,v2,v3;
        v2 = glm::vec3(rota[1][0],rota[1][1],rota[1][2]);
        v3 = glm::vec3(rota[2][0],rota[2][1],rota[2][2]);
        v1 = glm::cross(v2,v3);
        v1 = glm::normalize(v1);
        rota[0][0] = v1.x, rota[0][1]=v1.y, rota[0][2]=v1.z;
        Matrices.model *= (translate * rota * rotate);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    }
    
    for(int i=0;i<2;i++)
        draw3DObject(this->ob[i]);
    this -> rot += (M_PI/120.0);
    
}

void Waypoint::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Waypoint::tick() {
    this->position.x += speed*x_comp;
    this->position.y += speed*y_comp;
    this->position.z += speed*z_comp;
}

