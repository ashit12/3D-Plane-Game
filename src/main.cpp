#include "main.h"
#include "timer.h"
#include "ground.h"
#include "plane.h"
#include "smoke.h"
#include "missile.h"
#include "volcano.h"
#include "mountains.h"
#include "alt_bar.h"
#include "checkpoint.h"
#include "life.h"
#include "compass.h"
#include "fuel_bar.h"
#include "speed_bar.h"
#include "fuel.h"
#include "score.h"
#include "parachute.h"

using namespace std;

GLMatrices Matrices,mati;
GLuint     programID;
GLFWwindow *window;


/* Remaining
- Special maneuvers




/**************************
* Customizable functions *
**************************/

Ground ground;
Plane plane;
Score score,sc;
FuelBar bar;
Alt abar;
SpeedBar sbar;
Life heart,hr;
Compass comp;
Waypoint plane_way;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0, checkx, checkz, main_dist = 4.0f;
float camera_rotation_angle = 0,height=2.0f,angle=0,radius=3.0f,x_comp=0,y_comp=0,z_comp=1.0,plane_top_y=1.0f,plane_top_x=0.0f,plane_top_z=0.0f,camera_dist=5.0f;
int flag=0,view_cd=0,release=0,under_barrel=0;
double x_pos,y_pos,z_pos;
int para_cd,ring_cd,fuel_cd,check_cd,check_status;
Timer t60(1.0 / 60);
std::vector<std::string> alpha, vec;
std::vector<Mountain> mount;
std::vector<Smoke> smoke;
std::vector<Volcano> volcano;
std::vector<Missile> missile;
std::vector<Parachute> para;
std::vector<Checkpoint> check;
std::vector<Fuel> fuel;
glm::mat4 iden = glm::mat4(1.0f);
float sq(float a)
{
    return a*a;
}
float dist(float x1,float y1,float z1,float x2,float y2,float z2)
{
    return sqrt(sq(x1-x2)+sq(y1-y2)+sq(z1-z2));
}
void fill_data()
{
    int sc = plane.score;
    char s[] = "1011011", c[] = "1001110", o[] = "1111110", r[] = "1000110", e[] = "1001111", hy[] = "0000001";
    vec.push_back(s), vec.push_back(c), vec.push_back(o), vec.push_back(r), vec.push_back(e), vec.push_back(hy);
    int g[5], co = 0;
    while (sc > 0)
        g[co++] = sc % 10, sc /= 10;
    int k = co - 1;
    co = 4 - co;
    while (co > 0)
    {
        vec.push_back(alpha[0]);
        co--;
    }
    while (k >= 0)
    {
        vec.push_back(alpha[g[k]]);
        k--;
    }
}
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    //Use for first person
    // Eye - Location of camera. Don't change unless you are sure!!


    glm::vec3 eye,target,up;
    up = glm::vec3(0,1,0);

    //First person
    if(flag==0)
    {
        eye    = glm::vec3(plane.position.x+2*x_comp,plane.position.y+2*y_comp,plane.position.z+2*z_comp);
        target = glm::vec3(plane.position.x+500*x_comp,plane.position.y+500*y_comp,plane.position.z+500*z_comp);
        up     = glm::vec3 (plane_top_x,plane_top_y,plane_top_z);    
    }
    
    //Tower view
    else if(flag==1)
    {
        eye    = glm::vec3(20.0f,20.0f,20.0f);
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
    }
    
    //Follow cam view
    else if(flag==2)
    {
        eye    = glm::vec3(plane.position.x-2*x_comp+ 2*plane_top_x,plane.position.y - 2*y_comp + 2*plane_top_y ,plane.position.z-2*z_comp+ 2*plane_top_z);
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
        up     = glm::vec3 (plane_top_x,plane_top_y,plane_top_z);
    }    

    //Top view
    else if(flag==3)
    {
        eye    = glm::vec3(plane.position.x,plane.position.y + 10,plane.position.z-2);
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
    }
    
    //Helicopter camera view
    else if(flag==4)
    {
        x_pos = (x_pos-540)/540;
        y_pos = (y_pos-540)/540;
        if(x_pos <= -1)
            x_pos = -1;
        if(x_pos > 1)
            x_pos = 1;
        if(y_pos <= -1)
            y_pos = -1;
        if(y_pos >= 1)
            y_pos = 1;
        float r = screen_zoom*camera_dist;
        float a1 = x_pos*M_PI/2;
        float a2 = y_pos*M_PI/2;
        float eyex = plane.position.x-plane.rotate[2][0]*r*(cos(a1)+cos(a2)) + plane.rotate[0][0]*r*sin(a1) + plane.rotate[1][0]*r*sin(a2);
        float eyey = plane.position.y-plane.rotate[2][1]*r*(cos(a1)+cos(a2)) + plane.rotate[0][1]*r*sin(a1) + plane.rotate[1][1]*r*sin(a2);
        float eyez = plane.position.z-plane.rotate[2][2]*r*(cos(a1)+cos(a2)) + plane.rotate[0][2]*r*sin(a1) + plane.rotate[1][2]*r*sin(a2);

        eye = glm::vec3(eyex,eyey,eyez); 
        target = glm::vec3(plane.position.x,plane.position.y,plane.position.z);
    }


    
    
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    glm::vec3 e1(0,0,1);
    glm::vec3 l1(0,0,0);
    glm::vec3 u1(1,0,0);
    mati.view = glm::lookAt(e1,l1,u1);
    glm::mat4 VP = Matrices.projection * Matrices.view;
    glm::mat4 MVP;  // MVP = Projection * View * Model
    glm::mat4 vp = mati.projection * mati.view;
    glm::mat4 mvp;
    ground.draw(VP);
    for(int i=0;i<mount.size();i++)
        mount[i].draw(VP);
    for(int i=0;i<smoke.size();i++)
        smoke[i].draw(VP);
    for(int i=0;i<volcano.size();i++)
        volcano[i].draw(VP); 
    for(int i=0;i<para.size();i++)
        para[i].draw(VP);
    for(int i=0;i<check.size();i++)
    {
        check[i].draw(VP);
        if(check[i].can.size()==0)
        {
            check.erase(check.begin()+i);
            continue;
        }
        check[i].way.draw(VP);
        for(int j=0;j<check[i].can.size();j++)
        {
            
            check[i].can[j].draw(VP);
            for(int k=0;k<check[i].can[j].miss.size();k++)
                check[i].can[j].miss[k].draw(VP);
        }
    }
    for(int i=0;i<fuel.size();i++)
        fuel[i].draw(VP);
    plane.draw(VP); 
    for(int i=0;i<plane.miss.size();i++)    
        plane.miss[i].draw(VP);
    for(int i=0;i<plane.bomb.size();i++)    
        plane.bomb[i].draw(VP);
    if(check_status==1)
        plane_way.draw(VP);
    score.draw(vp);
    sc.draw(vp);
    hr.draw(vp,plane.life);
    heart.draw(vp,plane.life);
    comp.draw(vp);
    abar.draw(vp,plane.position.y);
    bar.draw(vp,plane.fuel);
    sbar.draw(vp,plane.speed);

}

void tick_input(GLFWwindow *window) {
    int clockwise = glfwGetKey(window, GLFW_KEY_E);
    int anti = glfwGetKey(window, GLFW_KEY_Q);
    int left = glfwGetKey(window, GLFW_KEY_D);
    int right = glfwGetKey(window, GLFW_KEY_A);
    int front = glfwGetKey(window, GLFW_KEY_W);
    int behind = glfwGetKey(window, GLFW_KEY_S);
    int view = glfwGetKey(window, GLFW_KEY_V);
    int up = glfwGetKey(window, GLFW_KEY_Z);
    int down = glfwGetKey(window, GLFW_KEY_C);
    int mis = glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT);
    int bomb = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    // int barrel = glfwGetKey(window, GLFW_KEY_B);
    glfwGetCursorPos(window,&x_pos,&y_pos);
    if(view && view_cd<=0)
        flag=(flag+1)%5,view_cd=60;
    if(mis && plane.mis_cd<=0)
    {
        plane.mis_cd = 30;
        Missile m = Missile(plane.position.x+2.0f*x_comp,plane.position.y+2.0f*y_comp,plane.position.z+2.0f*z_comp,1);        
        plane.miss.push_back(m);
    }
    if(bomb && plane.bomb_cd<=0)
    {
        plane.bomb_cd = 30;
        Missile m = Missile(plane.position.x-1.1f*plane_top_x,plane.position.y-1.1f*plane_top_y,plane.position.z-1.1f*plane_top_z,2);
        plane.bomb.push_back(m);
    }
    // if(barrel && under_barrel<=0)
    // {
    //     under_barrel = 240;
    //     plane.rot_x = plane.rot_z = 0.0f;
    //     return ;
    // }
    if(front)
        plane.speed = min(plane.speed+accn,max_speed*1.0);
    else if(behind)
        plane.speed = max(plane.speed-accn,-max_speed*1.0);
    else
    {
        if(plane.speed > 0)
            plane.speed -= accn;
        else if(plane.speed < 0)
            plane.speed += accn;
        if(abs(plane.speed) < 1e-6)
            plane.speed = 0.0;
    }           
    if(left)
        plane.rot_z += min_rot_mov;
    else if(right)
        plane.rot_z -= min_rot_mov;
    if(clockwise)
        plane.rot_y -= min_rot_mov;
    else if(anti)
        plane.rot_y += min_rot_mov;
    if(up)
        plane.rot_x -= min_rot_mov;
    else if(down)
        plane.rot_x += min_rot_mov;


}

//Spawns rings,fuel and checkpoints depending on the game status
void spawns()
{
    float x = plane.position.x, y = plane.position.y, z = plane.position.z;
    int sign[]={-1,1};
    //Spawn parachute
    if(para_cd<=0)
    {
        para_cd = para_max;
        Parachute p = Parachute(x+sign[rand()%2]*(rand()%8),5+rand()%7, z+sign[rand()%2]*(rand()%8));
        para.push_back(p);
    }
    
    //Spawn smoke ring
    if(ring_cd<=0)
    {
        ring_cd = smoke_max;
        Smoke s = Smoke(x+1+sign[rand()%2]*(rand()%7),3+rand()%5, z+1+sign[rand()%2]*(rand()%7));
        smoke.push_back(s);
    }

    //Spawn fuel powerup
    if(fuel_cd<=0)
    {
        fuel_cd = fuel_max;
        Fuel f = Fuel(x+2+sign[rand()%2]*(rand()%5),4+rand()%5, z+2+sign[rand()%2]*(rand()%5));
        fuel.push_back(f);
    }

    //Create checkpoints
    if(check_status==0 && check_cd<=0)
    {
        check_status = 1;
        check_cd = check_max;
        checkx = x+5+rand()%20, checkz = z+5+rand()%20;
        plane_way = Waypoint(plane.position.x,plane.position.y,plane.position.z+main_dist,1);
        Checkpoint c = Checkpoint(checkx,0.0f,checkz,1+rand()%5);
        check.push_back(c);
    }
}

void check_collisions()
{
    //Plane and ring
    bounding_box_t b1,b2;
    b1.x = plane.position.x, b1.y = plane.position.y, b1.z = plane.position.z;
    b1.width = 1.0f, b1.height = 1.0f, b1.length = 2.0f;
    for(int i=0;i<smoke.size();i++)
    {
        b2.x = smoke[i].position.x,b2.y = smoke[i].position.y,b2.z = smoke[i].position.z;
        b2.height = b2.width = 2.0f, b2.length=0.2f;
        if(detect_collision(b1,b2))
        {
            smoke.erase(smoke.begin()+i);
            plane.score += 20;
        }
    }

    //Plane and volcano
    for(int i=0;i<volcano.size();i++)
    {
        if(sqrt(sq(plane.position.x-volcano[i].position.x)+sq(plane.position.y-volcano[i].position.y)+sq(plane.position.z-volcano[i].position.z)<=3.0f))
            exit(0);
    } 

    //Plane and cannon missile
    for(int i=0;i<check.size();i++)
    {
        for(int j=0;j<check[i].can.size();j++)
        {
            for(int k=0;k<check[i].can[j].miss.size();k++)
            {
                b2.x = check[i].can[j].miss[k].position.x;
                b2.y = check[i].can[j].miss[k].position.y;
                b2.z = check[i].can[j].miss[k].position.z;
                b2.length = 0.4f, b2.height = b2.width = 0.2f;
                if(detect_collision(b1,b2))
                {
                    check[i].can[j].miss.erase(check[i].can[j].miss.begin()+k);
                    plane.life--;
                    if(plane.life == 0)
                        exit(0);
                }
            }
        }
    }

    //Plane bomb and cannon
    for(int k=0;k<check.size();k++)
    {
        int flag=0;
        for(int j=0;j<check[k].can.size();j++)
        {
            for(int i=0;i<plane.bomb.size();i++)
            {   
                bounding_box_t b1,b2;
                b1.x = plane.bomb[i].position.x,b1.y = plane.bomb[i].position.y,b1.z = plane.bomb[i].position.z;
                b1.height=b1.width=b1.height=0.4f; 
                b2.x = check[k].can[j].position.x, b2.y = check[k].can[j].position.y, b2.z = check[k].can[j].position.z;
                b2.height = check[k].can[j].hei, b2.width = check[k].can[j].wid, b2.length = check[k].can[j].len;
                if(detect_collision(b1,b2))
                {
                    check[k].can.erase(check[k].can.begin()+j);
                    plane.bomb.erase(plane.bomb.begin()+i);
                    check[k].num_cannon--;
                    if(check[k].num_cannon==0)
                    {
                        check_status=0;
                        plane.score += 50;
                        flag=1;
                        break;
                    }   
                    continue;
                }
            }
        }
        if(flag)
        {
            check.erase(check.begin()+k);
            break;
        }
    }

    //Plane missile and parachute - Very wrong
    for(int i=(int)(plane.miss.size())-1; i>=0;i--)
    {
        b1.x = plane.miss[i].position.x;
        b1.y = plane.miss[i].position.y;
        b1.z = plane.miss[i].position.z;
        b1.length = 0.4f, b1.height = b1.width = 0.2f;
        for(int j=(int)(para.size())-1;j>=0;j--)
        {
            b2.x = para[j].position.x;
            b2.y = para[j].position.y;
            b2.z = para[j].position.z;
            b2.height = b2.length = 2.0f, b2.width = 1.3f;
            if(detect_collision(b1,b2))
            {
                para.erase(para.begin()+j);
                plane.miss.erase(plane.miss.begin()+i);
                plane.score += 5;
                break;
            }
        }
    }

    //Plane and fuel tank
    for(int i=0;i<fuel.size();i++)
    {
        b2.x = fuel[i].position.x, b2.y = fuel[i].position.y, b2.z = fuel[i].position.z;
        b2.height = b2.length = b2.width = 0.2f;
        if(detect_collision(b1,b2))
        {
            fuel.erase(fuel.begin()+i);
            plane.fuel = 10.0f;
        }
    }

}
void tick_elements() {
    view_cd--;
    para_cd--;
    fuel_cd--;
    ring_cd--;
    if(check_status==0)
        check_cd--;
    score.tick();
    sc.tick();
    bar.tick();
    ground.tick();
    plane.tick();
    if(plane.fuel<=0)
        plane.position.y -= 0.05f;
    float dis=0;
    if(flag==0)
        dis = 2.0;
    if(check_status)
        plane_way.set_position(plane.position.x + x_comp*main_dist+dis*plane_top_x,plane.position.y + y_comp*main_dist+dis*plane_top_y,plane.position.z + z_comp*main_dist+dis*plane_top_z);
    for(int i=0;i<plane.miss.size();i++)
    {
        if(dist(plane.position.x,plane.position.y,plane.position.z,plane.miss[i].position.x,plane.miss[i].position.y,plane.miss[i].position.z)>=25.0f)
            plane.miss.erase(plane.miss.begin()+i);
        else
            plane.miss[i].tick();
    }
    for(int i=0;i<plane.bomb.size();i++)
    {
        // if(dist(plane.position.x,plane.position.y,plane.position.z,plane.bomb[i].position.x,plane.bomb[i].position.y,plane.bomb[i].position.z)>=12.0f)
            // plane.bomb.erase(plane.miss.begin()+i); 
        // else
            plane.bomb[i].tick();
    }
    for(int i=0;i<fuel.size();i++)
    {
        if(fuel[i].time<=0)
            fuel.erase(fuel.begin()+i);
        else
            fuel[i].tick();        
    }
    for(int i=0;i<smoke.size();i++)
    {
        if(smoke[i].time<=0)
            smoke.erase(smoke.begin()+i);
        else
            smoke[i].tick();
    }
    for(int i=0;i<mount.size();i++)
        mount[i].tick();
    for(int i=0;i<volcano.size();i++)
        volcano[i].tick();
    for(int i=0;i<missile.size();i++)
        missile[i].tick();
    for(int i=0;i<para.size();i++)
    {
        if(para[i].position.y<=bot_limit-2.0f)
            para.erase(para.begin()+i);
        else
            para[i].tick();
    }
    for(int i=0;i<check.size();i++)
    {
        check[i].tick();
        check[i].way.tick();
        for(int j=0;j<check[i].can.size();j++)
        {
            
            check[i].can[j].tick();
            if(check[i].can[j].cd<=0)
            {
                check[i].can[j].cd=300;
                Missile m = Missile(check[i].can[j].position.x,check[i].can[j].position.y,check[i].can[j].position.z,3);
                m.xc = plane.position.x - check[i].can[j].position.x;
                m.yc = plane.position.y - check[i].can[j].position.y;
                m.zc = plane.position.z - check[i].can[j].position.z;
                check[i].can[j].miss.push_back(m);
            }
            for(int k=0;k<check[i].can[j].miss.size();k++)
                check[i].can[j].miss[k].tick();
        }
    }
}


/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    color_t c1 = {18,17,19};
    color_t c2 = {74,82,90};
    ground = Ground(0.0,-1.0,0.0,1000.0,2.0,1000.0);
    plane  = Plane(0.0,2.0,-5.0,plane_r,plane_r,plane_h);
    score = Score(0.0, 3.8, c1);
    sc = Score(-0.01,3.795,c2);
    bar = FuelBar(-3.5, 1.9, COLOR_GREEN);
    sbar = SpeedBar(-3.9,-2.9, COLOR_GREEN);
    abar = Alt(-0.5,-3.5,COLOR_RED);
    color_t c = {205, 16, 93};
    color_t d = {7,7,10};
    heart = Life(3.5, -2.5,c);
    hr = Life(3.4,-2.6,d);
    comp = Compass(-3.3,0.0,0.0,COLOR_RED);

    int sign[]={-1,1},eff=500;
    para_cd = para_max, fuel_cd = fuel_max, ring_cd = smoke_max, check_status = 0, check_cd = check_max;
    for(int i=0;i<num_mount;i++)
    {
        Mountain m = Mountain(sign[rand()%2]*(rand()%eff),0.0f,sign[rand()%2]*(rand()%eff));
        mount.push_back(m);
    }
    for(int i=0;i<num_volcano;i++)
    {
        Volcano vo = Volcano(sign[rand()%2]*(rand()%eff),1.0f,1+sign[rand()%2]*(rand()%eff));
        volcano.push_back(vo);
    }

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");
    mati.MatrixID = glGetUniformLocation(programID, "mvp");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 1080;
    int height = 1080;
    alpha.push_back("1111110"); //0
    alpha.push_back("0110000"); //1
    alpha.push_back("1101101"); //2
    alpha.push_back("1111001"); //3
    alpha.push_back("0110011"); //4
    alpha.push_back("1011011"); //5
    alpha.push_back("1011111"); //6
    alpha.push_back("1110000"); //7
    alpha.push_back("1111111"); //8
    alpha.push_back("1111011"); //9
    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            vec.clear();
            fill_data();
            draw();
            spawns();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);
            check_collisions();
            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height)) &&
           (abs(a.z - b.z) * 2 < (a.length + b.length));
}
void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::perspective(3.14f/2, 4.0f/3.0f, 0.1f, 500.0f);
    mati.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}

