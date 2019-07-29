#include "missile.h"
#include "main.h"


Missile::Missile(float x, float y, float z,int t) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    this->sx = x, this->sy=y, this->sz = z;
    this->type=t;
    this->stat=1;
    speed = 0.2;
    if(t==1 || t==3)
    {
        if(t==1)
            this->rotate=iden;
        else
            this->rotate = glm::mat4(1.0f),speed = 0.01f;

    GLfloat top_cir[9*no_triang],bot_cir[9*no_triang],rects[18*no_triang],c2[18*no_triang],c1[18*no_triang];
    
    // This creates the cylinder
    float r1 = plane_r/5, r2=plane_r/5,h=plane_h/5;
    create_cylinder(top_cir,bot_cir,rects,r1,r2,h,0.0f,0.0f,0.0f);
    this->ob[0] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, COLOR_RED, GL_FILL);
    
    for(int i=0;i<9*no_triang;i+=9)
    {
        c1[i] = 254.0/255.0, c1[i+1]=78.0/255.0, c1[i+2]=0.0/255.0;
        c1[i+3] = 255.0/255.0, c1[i+4]=174.0/255.0, c1[i+5]=3.0/255.0;
        c1[i+6] = 230.0/255.0, c1[i+7]=127.0/255.0, c1[i+8]=13.0/255.0;
    }
    this->ob[1] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, c1, GL_FILL);
    for(int i=0;i<18*no_triang;i+=9)
    {
        c1[i] = 193.0/255.0, c1[i+1]=154.0/255.0, c1[i+2]=183.0/255.0;
        c1[i+3] = 255.0/255.0, c1[i+4]=186.0/255.0, c1[i+5]=8.0/255.0;
        c1[i+6] = 3.0/255.0, c1[i+7]=43.0/255.0, c1[i+8]=67.0/255.0;
    }
    this->ob[2] = create3DObject(GL_TRIANGLES, 6*no_triang, rects, c1 , GL_FILL);
    for(int i=0;i<18*no_triang;i+=9)
    {
        c2[i] = 251.0/255.0, c2[i+1]=80.0/255.0, c2[i+2]=18.0/255.0;
        c2[i+3] = 244.0/255.0, c2[i+4]=96.0/255.0, c2[i+5]=54.0/255.0;
        c2[i+6] = 255.0/255.0, c2[i+7]=180.0/255.0, c2[i+8]=0.0/255.0;
    }
    //This creates the cone
    float cone_h = 0.2f;
    float cone_x=0, cone_y = 0, cone_z = h/2.0f+cone_h/2;
    create_cylinder(top_cir,bot_cir,rects,r1,0,cone_h,cone_x,cone_y,cone_z);
    this->ob[3] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, COLOR_RED, GL_FILL);
    this->ob[4] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, COLOR_RED, GL_FILL);
    this->ob[5] = create3DObject(GL_TRIANGLES, 6*no_triang, rects, c2, GL_FILL); 

    //This creates the wings
    GLfloat wing1[]={
        -r1,0.0f,h/3,
        -r1,0.0f,-h/3,
        -3*r1,0.0f,0.0f
    },wing2[]={
        r1,0.0f,h/3,
        r1,0.0f,-h/3,
        3*r1,0.0f,0.0f
    };
    this->ob[6] = create3DObject(GL_TRIANGLES, 3, wing1, {20,30,40}, GL_FILL);
    this->ob[7] = create3DObject(GL_TRIANGLES, 3, wing2, {20,30,40}, GL_FILL);
    }
    else if(t==2)
    {
        this->rotate=glm::mat4(1.0f);
        GLfloat arr[200];
        float dim = 0.4f;
        create_cuboid(arr,dim,dim,dim,0.0f,0.0f,0.0f);
        GLfloat col[]={
            227.0/255.0,23.0/255.0,10.0/255.0,
            225.0/255.0,96.0/255.0,54.0/255.0,
            239.0/255.0,160.0/255.0,11.0/255.0,
            214.0/255.0,81.0/255.0,.0/255.0,
            90.0/255.0,24.0/255.0,7.0/255.0,
            108.0/255.0,235.0/255.0,204.0/255.0,
            140.0/255.0,72.0/255.0,67.0/255.0,
            158.0/255.0,100.0/255.0,60.0/255.0,
        };
        this->ob[0] = create3DObject(GL_TRIANGLES, 36, arr, col, GL_FILL);
    }

    
}

void Missile::draw(glm::mat4 VP) {
    
    if(this->type==1||this->type==2)
    {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate_x    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate * rotate_x);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]); 
    }
    else
    {
        glm::vec3 v1,v2,v3;
        v2 = glm::vec3(this->xc,this->yc,this->zc);
        v2 = glm::normalize(v2);
        v3 = glm::vec3(0,1,0);
        v1 = glm::cross(v2,v3);
        v1 = glm::normalize(v1);
        rotate[1][0] = 0.0f, rotate[1][1] = 1.0f, rotate[1][2] = 0.0f;
        rotate[2][0] = v2.x, rotate[2][1] = v2.y, rotate[2][2] = v2.z;
        rotate[0][0] = v1.x, rotate[0][1] = v1.y, rotate[0][2] = v1.z;
        Matrices.model = glm::mat4(1.0f);
        glm::mat4 translate = glm::translate (this->position);    // glTranslatef
        glm::mat4 rotate_x    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(-1, 0, 0));
        Matrices.model *= (translate * rotate * rotate_x);
        glm::mat4 MVP = VP * Matrices.model;
        glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]); 
    }
    
    int num=1;  
    if(this->type==1 || this->type==3)
        num=8;
    for(int i=0;i<num;i++)
        draw3DObject(this->ob[i]);
}

void Missile::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Missile::tick() {
    if(this->type==1)
    {
        this->position.x += speed*rotate[2][0];
        this->position.y += speed*rotate[2][1];
        this->position.z += speed*rotate[2][2];
    }
    else if(this->type==2)
    {
        this->position.y -= speed*0.65f;
    }
    else 
    {
        this->position.x += speed*this->xc;
        this->position.y += speed*this->yc;
        this->position.z += speed*this->zc;
    }
}

