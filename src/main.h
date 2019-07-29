#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct color_t {
    int r;
    int g;
    int b;
};
const float plane_r=0.5f,plane_h=1.0f,min_rot_mov=1.0f,min_mov=1.0/20,sky_limit=30.0f,accn=1.0/900,max_speed=0.10,bot_limit=0.0f;
const int no_triang = 50,num_mount=1000,num_volcano=150,fuel_max=600,smoke_max=900,para_max=150,check_max=420;
extern int is_x,is_y,is_z,under_barrel;
extern float x_comp,y_comp,z_comp,plane_top_y,plane_top_z,plane_top_x,checkx,checkz;
extern glm::mat4 iden;
extern std::vector<std::string> vec;

// nonedit.cpp
GLFWwindow *initGLFW(int width, int height);
GLuint     LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat *color_buffer_data, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const GLfloat red, const GLfloat green, const GLfloat blue, GLenum fill_mode = GL_FILL);
struct VAO *create3DObject(GLenum primitive_mode, int numVertices, const GLfloat *vertex_buffer_data, const color_t color, GLenum fill_mode = GL_FILL);
void       draw3DObject(struct VAO *vao);

// input.cpp
void keyboard(GLFWwindow *window, int key, int scancode, int action, int mods);
void keyboardChar(GLFWwindow *window, unsigned int key);
void mouseButton(GLFWwindow *window, int button, int action, int mods);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

// other_handlers.cpp
void error_callback(int error, const char *description);
void quit(GLFWwindow *window);
void reshapeWindow(GLFWwindow *window, int width, int height);

// Types
struct VAO {
    GLuint VertexArrayID;
    GLuint VertexBuffer;
    GLuint ColorBuffer;

    GLenum PrimitiveMode;
    GLenum FillMode;
    int    NumVertices;
};
typedef struct VAO VAO;

struct GLMatrices {
    glm::mat4 projection;
    glm::mat4 model;
    glm::mat4 view;
    GLuint    MatrixID;
};

extern GLMatrices Matrices;

// ---- Logic ----

enum direction_t { DIR_UP, DIR_RIGHT, DIR_DOWN, DIR_LEFT };

struct bounding_box_t {
    float x;
    float y;
    float z;
    float width;
    float height;
    float length;
};

struct point{
    float x,y,z;
};

bool detect_collision(bounding_box_t a, bounding_box_t b);
void create_circle(GLfloat arr[],float radius,float x,float y,float z);
void create_rect(GLfloat [],float,float,float,float);
void create_cuboid(GLfloat arr[],float l,float w,float h,float x,float y,float z);
void create_cylinder(GLfloat arr1[],GLfloat arr2[],GLfloat arr3[],float r1,float r2,float h,float x,float y,float z);
void create_sphere(GLfloat [][900],GLfloat [][900],GLfloat [][1800],float,float,float,float);
void create_pyramid(GLfloat [],float,float,float,float,float);
void fill(GLfloat arr[],point p,int i);
float dot_product(float x1,float x2,float y1,float y2,float z1,float z2);

extern float screen_zoom, screen_center_x, screen_center_y;
void reset_screen();

// ---- Colors ----
extern const color_t COLOR_RED;
extern const color_t COLOR_GREEN;
extern const color_t COLOR_BLACK;
extern const color_t COLOR_BACKGROUND;

#endif
