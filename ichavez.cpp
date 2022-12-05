//Author: Irene Chavez
#include <iostream>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include "fonts.h"
#include "log.h"
#include "math.h"
typedef float Flt;
typedef Flt vec[3];
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)

using namespace std;

class Texture {
public:
    //MyImage *backImage;
    XImage *backImage;
    GLuint backTexture;
    float xc[2];
    float yc[2];
};

class Global {
public:
    int xres, yres;
    float vel;
    float rails = 0.2;
    Texture tex;
    vec camera;
    int col;
    Global() {
        //constructor
        xres=640;
        yres=480;
        vel = 0.0f;
        MakeVector(0.0, 1.0, 8.0, camera);
        col = 0; 
    }   
} gx; 

void box2(float w, float h, float d, float x, float y, float z) 
{
    //float w=w1*0.5;
    //float d=d1*0.5;
    //float h=h1*0.5;
    //notice the normals being set
    glPushMatrix();
    glTranslatef(x,y,z);
    glBegin(GL_QUADS);
        //top
        glNormal3f( 0.0f, 1.0f, 0.0f);
        glVertex3f( w, h,-d);
        glVertex3f(-w, h,-d);
        glVertex3f(-w, h, d); 
        glVertex3f( w, h, d); 
        // bottom
        glNormal3f( 0.0f, -1.0f, 0.0f);
        glVertex3f( w,-h, d); 
        glVertex3f(-w,-h, d);
        glVertex3f(-w,-h,-d);
        glVertex3f( w,-h,-d);
        // front
        glNormal3f( 0.0f, 0.0f, 1.0f);
        glVertex3f( w, h, d);
        glVertex3f(-w, h, d);
        glVertex3f(-w,-h, d);
        glVertex3f( w,-h, d);
        // back
        glNormal3f( 0.0f, 0.0f, -1.0f);
        glVertex3f( w,-h,-d);
        glVertex3f(-w,-h,-d);
        glVertex3f(-w, h,-d);
        glVertex3f( w, h,-d);
        // left side
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(-w, h, d);
        glVertex3f(-w, h,-d);
        glVertex3f(-w,-h,-d);
        glVertex3f(-w,-h, d);
        // Right side
        glNormal3f( 1.0f, 0.0f, 0.0f);
        glVertex3f( w, h,-d);
        glVertex3f( w, h, d);
        glVertex3f( w,-h, d);
        glVertex3f( w,-h,-d);
        glEnd();
    glEnd();
    glPopMatrix();
}

void backScreen(float w, float h, float d, float x, float y, float z) 
{
    glPushMatrix();
    glColor3f(0.82f, 0.82f, 0.82f);
    glTranslatef(x,y,z);
    glBegin(GL_QUADS);
        glVertex2f( -w, -h);
        glVertex2f(-w, h);
        glVertex2f(w, h); 
        glVertex2f( w, -h); 
    glEnd();
    glPopMatrix();
}

void print_name(){
	cout<< "irene a." << endl;

}
bool helpState(bool touch){
	touch = true; 
	return touch; 
}
void practice(){
    int w = 175;
    int h = 80;

    Rect s;
    s.bot = 800;
    s.left = 840;
    s.center = 0;
    ggprint16(&s, 16, 0x00ff01de, " Congratulations you won!!!");

    Rect r;
    r.bot = 780;
    r.left = 840;
    r.center = 0;
    ggprint16(&r, 16, 0x000b173b, " Want to practice again?");
    
    Rect t;
    t.bot = 760;
    t.left = 840;
    t.center = 0;
    ggprint16(&t, 16, 0x000b173b, " Press (Y) if yes & (V) to return");
    backScreen(w, h, 0.0f, 980.0f, 800.0f, 0.0f);
}

/*void dodge () {
    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, 3.0, 0.0, -25.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, -2.0, 0.0, -30.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, -3.0, 0.0, -40.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, -2.0, 0.0, -50.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, 2.0, 0.0, -60.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, 3.0, 0.0, -70.0);
}*/
void finish(float z, float x){
    //dodge();
    //these are my ops
    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, 3.0, 0.0, -25.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, 0.0, 0.0, -30.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, -3.0, 0.0, -40.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, -2.0, 0.0, -50.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, 2.0, 0.0, -60.0);

    glColor3f(1.0f, 0.5f, 0.0f);
    box2(0.3, 1.0, 0.1, 3.0, 0.0, -70.0);
    //this is collision for obj1
    if (z <= -22.0f && z >= -24.0f && x >= 2.8f && x <= 4.0f){
        cout<<"you hit a box / had a collision" << endl;
        gx.col++;
    }
    //this is collision for obj2
    if (z <= -27.0f && z >= -29.0f && x >= -1.5f && x <= -3.0f){
        cout<<"you hit a box / had a collision" << endl;
        gx.col++;
    }
    //this is collision for obj3
    if (z <= -37.0f && z >= -36.0f && x >= -2.3f && x <= -4.0f){
        cout<<"you hit a box / had a collision" << endl;
        gx.col++;
    }
    //this is collision for obj4
    if (z <= -47.0f && z >= -46.0f && x >= -1.5f && x <= -3.0f){
        cout<<"you hit a box / had a collision" << endl;
        gx.col++;
    }
    //this is collision for obj5
    if (z <= -57.0f && z >= -56.0f && x >= 1.4f && x <= 3.0f){
        cout<<"you hit a box / had a collision" << endl;
        gx.col++;
    }
    //this is collision for obj6
    if (z <= -68.0f && z >= -67.0f && x >= 2.0f && x <= 4.0f){
        cout<<"you hit a box / had a collision" << endl;
        gx.col++;
    }
    //this is goign to tell you if you won or lost
    cout << "You had " << gx.col << " collisions"<< endl;
    //this is the finish line
    
    glColor3f(240.0f, 230.0f, 140.0f);//sign
    box2(7.0, 2.0, 0.1, 0.0, 5.0, -74.0);

    
    glColor3f(255.0f, 160.0f, 122.0f);// left pole 
    box2(0.3, 7.0, 0.1, -7.0, 0.0, -74.0);
       
    glColor3f(255.0f, 160.0f, 122.0f);//rightpole
    box2(0.3, 7.0, 0.1, 7.0, 0.0, -74.0);
    if(gx.camera[2] <= -74.0f){
        practice();
    }  
}
void mainFinish(){
    //this is brown
    glColor3f(0.54f, 0.27f, 0.07f);// left pole 
    box2(0.3, 7.0, 0.1, -7.0, 0.0, -950.0);
       
    glColor3f(0.54f, 0.27f, 0.07f);//rightpole
    //glColor3f(150.0f, 200.0f, 120.0f);
    box2(0.3, 7.0, 0.1, 7.0, 0.0, -950.0);

    //this is baby green 
    glColor3f(0.45f, 0.70f, 0.22f);//sign
    box2(7.0, 2.0, 0.1, 0.0, 5.0, -950.0);

}

void finishText(){
    Rect r;
    r.bot = 1000;
    r.left = 800;
    r.center = 0;
    ggprint16(&r, 16, 0x000b173b, "You are now in practice mode");
    
    Rect s;
    s.bot = 980;
    s.left = 800;
    s.center = 0;
    ggprint16(&s, 16, 0x000b173b, "Try to avoid the objects");
    
    Rect t;
    t.bot = 960;
    t.left = 880;
    t.center = 0;
    ggprint16(&t, 16, 0x000b173b, "Go! Go! Go!");
    }
    
