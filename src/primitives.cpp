#include "primitives.h"
#include "main.h"

void fill(GLfloat arr[],point p,int i)
{
    arr[i]=p.x,arr[i+1]=p.y,arr[i+2]=p.z;
}
void create_rect(GLfloat arr[],float l,float w,float x,float y)
{
    arr[0] = x, arr[1]=y, arr[2]=0.0f;
    arr[3] = x+l, arr[4]=y, arr[5]=0.0f;
    arr[6] = x+l, arr[7]=y+w, arr[8]=0.0f;
    arr[9] = x, arr[10]=y, arr[11]=0.0f;
    arr[12] = x+l, arr[13]=y+w, arr[14]=0.0f;
    arr[15] = x, arr[16]=y+w, arr[17] = 0.0f;
}
void create_circle(GLfloat arr[],float radius,float x,float y,float z)
{
    float angle = (2*M_PI);
    int n = no_triang;
    for(int j=0,i=0;i<9*n;i+=9,j++)
    {
    	arr[i]=x,arr[i+1]=y,arr[i+2]=z;
        arr[i+3]=x+radius*cos(angle*j/n),arr[i+4]=y+radius*sin(angle*j/n),arr[i+5]=z;
        arr[i+6]=x+radius*cos(angle*(j+1)/n),arr[i+7]=y+radius*sin(angle*(j+1)/n),arr[i+8]=z;
    }
}
void create_cuboid(GLfloat arr[],float l,float w,float h,float x,float y,float z)
{
    point p1 = {x-l/2,y-h/2,z-w/2};
    point p2 = {x-l/2,y-h/2,z+w/2};
    point p3 = {x+l/2,y-h/2,z+w/2};
    point p4 = {x+l/2,y-h/2,z-w/2};
    point p5 = {x-l/2,y+h/2,z-w/2};
    point p6 = {x-l/2,y+h/2,z+w/2};
    point p7 = {x+l/2,y+h/2,z+w/2};
    point p8 = {x+l/2,y+h/2,z-w/2};
    int counter = 0;
    
    fill(arr,p1,counter); counter += 3; fill(arr,p2,counter); counter+=3; fill(arr,p3,counter); counter+=3;
    fill(arr,p1,counter); counter += 3; fill(arr,p3,counter); counter+=3; fill(arr,p4,counter); counter+=3;
    
    fill(arr,p5,counter); counter += 3; fill(arr,p6,counter); counter+=3; fill(arr,p7,counter); counter+=3;
    fill(arr,p5,counter); counter += 3; fill(arr,p7,counter); counter+=3; fill(arr,p8,counter); counter+=3;
    
    fill(arr,p1,counter); counter += 3; fill(arr,p2,counter); counter+=3; fill(arr,p5,counter); counter+=3;
    fill(arr,p2,counter); counter += 3; fill(arr,p5,counter); counter+=3; fill(arr,p6,counter); counter+=3;
    
    fill(arr,p3,counter); counter += 3; fill(arr,p4,counter); counter+=3; fill(arr,p7,counter); counter+=3;
    fill(arr,p4,counter); counter += 3; fill(arr,p7,counter); counter+=3; fill(arr,p8,counter); counter+=3;
    
    fill(arr,p2,counter); counter += 3; fill(arr,p3,counter); counter+=3; fill(arr,p6,counter); counter+=3;
    fill(arr,p3,counter); counter += 3; fill(arr,p6,counter); counter+=3; fill(arr,p7,counter); counter+=3;
    
    fill(arr,p1,counter); counter += 3; fill(arr,p4,counter); counter+=3; fill(arr,p5,counter); counter+=3;
    fill(arr,p4,counter); counter += 3; fill(arr,p5,counter); counter+=3; fill(arr,p8,counter); counter+=3;
}
void create_cylinder(GLfloat arr1[],GLfloat arr2[],GLfloat arr3[],float r1,float r2,float h,float x,float y,float z)
{
    create_circle(arr2,r1,x,y,z-h/2);
    create_circle(arr1,r2,x,y,z+h/2);
    int n=no_triang;
    int counter = 0; 
    for(int i=0,j=0;i<9*n;i+=9,j++)
    {
        point p1 = {arr1[i+3],arr1[i+4],arr1[i+5]};
        point p2 = {arr1[i+6],arr1[i+7],arr1[i+8]};
        point p3 = {arr2[i+3],arr2[i+4],arr2[i+5]};
        point p4 = {arr2[i+6],arr2[i+7],arr2[i+8]};
        fill(arr3,p1,counter); counter += 3; fill(arr3,p2,counter); counter+=3; fill(arr3,p3,counter); counter+=3;
        fill(arr3,p2,counter); counter += 3; fill(arr3,p4,counter); counter+=3; fill(arr3,p3,counter); counter+=3;
    }
}
void create_pyramid(GLfloat arr[],float x,float y,float z,float b,float h)
{
    point p1 = {x,y+h/2,z}, p2 = {x+b/2,y-h/2,z-h/2}, p3 = {x+b/2,y-h/2,z+h/2}, p4 = {x-b/2,y-h/2,z-h/2}, p5={x-b/2,y-h/2,z+h/2};
    int c = 0;
    fill(arr,p1,c); c+=3; fill(arr,p2,c); c+=3; fill(arr,p3,c); c+=3;
    fill(arr,p1,c); c+=3; fill(arr,p4,c); c+=3; fill(arr,p5,c); c+=3;    
    fill(arr,p1,c); c+=3; fill(arr,p2,c); c+=3; fill(arr,p4,c); c+=3;    
    fill(arr,p1,c); c+=3; fill(arr,p3,c); c+=3; fill(arr,p5,c); c+=3;    
    fill(arr,p4,c); c+=3; fill(arr,p2,c); c+=3; fill(arr,p3,c); c+=3;    
    fill(arr,p4,c); c+=3; fill(arr,p5,c); c+=3; fill(arr,p3,c); c+=3;    
}

float dot_product(float x1,float x2,float y1,float y2,float z1,float z2)
{
    return x1*x2+y1*y2+z1*z2;
}
