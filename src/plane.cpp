#include "plane.h"
#include "main.h"


Plane::Plane(float x, float y, float z,float r1,float r2,float h) {
    this->position = glm::vec3(x, y, z);
    this->rot_y = 0;
    this->rot_z = 0;
    this->rot_x = 0;
    this->mis_cd=0;
    this->life=5;
    this->fuel_cd = 300;
    this->fuel = 10.0;
    this->rotate = glm::mat4(1.0f);
    this->score=0;
    this->bomb_cd=0;
    this->h=h;
    speed = 0;
    GLfloat top_cir[9*no_triang],bot_cir[9*no_triang],rects[18*no_triang];
    GLfloat c1[9*no_triang],c2[18*no_triang];
    for(int i=0;i<9*no_triang;i+=9)
    {
        c1[i] = 30.0/255.0, c1[i+1]=56.0/255.0, c1[i+2]=136.0/255.0;
        c1[i+3] = 71.0/255.0, c1[i+4]=168.0/255.0, c1[i+5]=189.0/255.0;
        c1[i+6] = 83.0/255.0, c1[i+7]=58.0/255.0, c1[i+8]=113.0/255.0;
    }
    for(int i=0;i<18*no_triang;i+=9)
    {
        c2[i] = 31.0/255.0, c2[i+1]=39.0/255.0, c2[i+2]=27.0/255.0;
        c2[i+3] = 95.0/255.0, c2[i+4]=96.0/255.0, c2[i+5]=98.0/255.0;
        c2[i+6] = 28.0/255.0, c2[i+7]=16.0/255.0, c2[i+8]=24.0/255.0;
    }

    // This creates the cylinder
    create_cylinder(top_cir,bot_cir,rects,r1,r2,h,0.0f,0.0f,0.0f);
    this->ob[0] = create3DObject(GL_TRIANGLES, 3*no_triang, top_cir, COLOR_BACKGROUND, GL_FILL);
    this->ob[1] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, c1, GL_FILL);
    this->ob[2] = create3DObject(GL_TRIANGLES, 6*no_triang, rects, c2, GL_FILL);
    for(int i=0;i<9*no_triang;i+=9)
    {
        c1[i] = 254.0/255.0, c1[i+1]=78.0/255.0, c1[i+2]=0.0/255.0;
        c1[i+3] = 255.0/255.0, c1[i+4]=174.0/255.0, c1[i+5]=3.0/255.0;
        c1[i+6] = 230.0/255.0, c1[i+7]=127.0/255.0, c1[i+8]=13.0/255.0;
    }
    this->ob[8] = create3DObject(GL_TRIANGLES, 3*no_triang, bot_cir, c1, GL_FILL);
    
    for(int i=0;i<18*no_triang;i+=9)
    {
        c2[i] = 212.0/255.0, c2[i+1]=242.0/255.0, c2[i+2]=219.0/255.0;
        c2[i+3] = 206.0/255.0, c2[i+4]=247.0/255.0, c2[i+5]=160.0/255.0;
        c2[i+6] = 185.0/255.0, c2[i+7]=151.0/255.0, c2[i+8]=144.0/255.0;
    }
    //This creates the cone
    float cone_h = 1.0f;
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
    },wing_col[]={
        114.0/255.0,14.0/255.0,7.0/255.0,
        197.0/255.0,40.0/255.0,61.0/255.0,
        153.0/255.0,93.0/255.0,129.0/255.0
    };

    this->ob[6] = create3DObject(GL_TRIANGLES, 3, wing1, wing_col, GL_FILL);
    this->ob[7] = create3DObject(GL_TRIANGLES, 3, wing2, wing_col, GL_FILL);

}

void Plane::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    rotate *= glm::rotate((float) (this->rot_z * M_PI / 180.0f), glm::vec3(0, 0, 1));
    rotate *= glm::rotate((float) (this->rot_x * M_PI / 180.0f), glm::vec3(1, 0, 0));    
    rotate *= glm::rotate((float) (this->rot_y * M_PI / 180.0f), glm::vec3(0, 1, 0));    
    x_comp = rotate[2][0], y_comp = rotate[2][1], z_comp = rotate[2][2]; plane_top_y = rotate[1][1];  //Direction vector
    plane_top_x = rotate[1][0], plane_top_z = rotate[1][2];
    this->rot_x = this->rot_y = this->rot_z = 0.0f;
    iden=rotate;
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    for(int i=0;i<8;i++)
        draw3DObject(this->ob[i]);
    if(abs(this->speed)>0)
        draw3DObject(this->ob[8]);
}

void Plane::set_position(float x, float y,float z) {
    this->position = glm::vec3(x, y, z);
}

void Plane::tick() {
    this->position.x += speed*x_comp;
    this->position.y += speed*y_comp;
    this->position.z += speed*z_comp;
    if(this->position.y + 0.1f>= sky_limit)
        this->position.y = sky_limit-0.1f;
    if(this->position.y -0.1f <= bot_limit)
        exit(0);
    this->mis_cd--;
    this->bomb_cd--;
    this->fuel -= 1.0/300;
    this->fuel_cd--;
    if(this->fuel_cd<=0)
        this->fuel_cd=300;
}

