//program: car.cpp
//author:  Gordon Griesel
//date:	summer 2017
//
//Framework for group attempting a 3D game.
//
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <time.h>
#include <iostream>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "log.h"
#include "fonts.h"
#include "mfuentes.h"
#include "jquinonez.h"
#include "sdenney.h"
#include "jr3image.h"
#include "irene.h"
#include <string>
//#include <unistd.h>
typedef float Flt;
typedef Flt Vec[3];
typedef Flt	Matrix[4][4];
//some defined macros
#define MakeVector(x, y, z, v) (v)[0]=(x),(v)[1]=(y),(v)[2]=(z)
#define VecNegate(a) (a)[0]=(-(a)[0]); (a)[1]=(-(a)[1]); (a)[2]=(-(a)[2]);
#define VecDot(a,b) ((a)[0]*(b)[0]+(a)[1]*(b)[1]+(a)[2]*(b)[2])
#define VecLen(a) ((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecLenSq(a) sqrtf((a)[0]*(a)[0]+(a)[1]*(a)[1]+(a)[2]*(a)[2])
#define VecCopy(a,b) (b)[0]=(a)[0];(b)[1]=(a)[1];(b)[2]=(a)[2];
#define VecAdd(a,b,c) \
	(c)[0]=(a)[0]+(b)[0];\
	(c)[1]=(a)[1]+(b)[1];\
	(c)[2]=(a)[2]+(b)[2]
#define VecSub(a,b,c) \
	(c)[0]=(a)[0]-(b)[0]; \
	(c)[1]=(a)[1]-(b)[1]; \
	(c)[2]=(a)[2]-(b)[2]
#define VecS(A,a,b) (b)[0]=(A)*(a)[0]; (b)[1]=(A)*(a)[1]; (b)[2]=(A)*(a)[2]
#define VecAddS(A,a,b,c) \
	(c)[0]=(A)*(a)[0]+(b)[0]; \
	(c)[1]=(A)*(a)[1]+(b)[1]; \
	(c)[2]=(A)*(a)[2]+(b)[2]
#define VecCross(a,b,c) \
	(c)[0]=(a)[1]*(b)[2]-(a)[2]*(b)[1]; \
	(c)[1]=(a)[2]*(b)[0]-(a)[0]*(b)[2]; \
	(c)[2]=(a)[0]*(b)[1]-(a)[1]*(b)[0]
#define VecZero(v) (v)[0]=0.0;(v)[1]=0.0;v[2]=0.0
#define ABS(a) (((a)<0)?(-(a)):(a))
#define SGN(a) (((a)<0)?(-1):(1))
#define SGND(a) (((a)<0.0)?(-1.0):(1.0))
#define rnd() (float)rand() / (float)RAND_MAX
#define PI 3.14159265358979323846264338327950
#define MY_INFINITY 1000.0
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

//using namespace std;
//
// TODO: Finalize WASD movement of the camera/car object
// uncomment all commented-out lines when finished
//
//
void init();
void init_opengl();
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void physics();
void pause_state();
void render();
void show_name();
void show_name_jr3(void);
void show_name_s();
void display_name();
void print_name();
void accelerate(float & velocity);
void decelerate(float & velocity);
bool startState(int count); 
bool helpState(bool);
void switchColor();
#ifdef USE_OPENAL_SOUND
void initSound();
void cleanupSound();
void playSound(ALuint source);
#endif

int frames = 0;
int startCounter = 4;
//MyImage img[1] = {"kachow.jpeg"};


//class MyImage myimage = {"kachow.jpeg"};

class Texture {
public:
	MyImage *backImage;
	GLuint backTexture;
	float xc[2];
	float yc[2];
};

class Global {
public:
	int xres, yres;
	int iniPos;
	int iniPos2;
	int rmCountDown;
	int numFrames;
	float rails = 0.2;
	Flt aspectRatio;
	Vec cameraPosition;
	GLfloat lightPosition[4];
	unsigned int feature_mode; //race mode
	unsigned int rotation_test;
	unsigned int bounds_mode;
	unsigned int speed_mode;
	unsigned int finishMode;
	unsigned int yPressed;
	bool zPressed, jPressed, ePressed, pPressed, cPressed, wPressed, aPressed, sPressed, dPressed, oPressed;
	int hPressed;
	bool raceModeOn;
	bool rotationTestOn;
	bool didYouWin;
	bool rmFinished;
	bool second0, second1, second2, second3, second4, second5;
	float curTheta;
	float vel;
	float anchorPosition0;
	float anchorPosition2;
	//int xres, yres;
	Texture tex;
	Global() {
		//constructor
		xres=1920;
		yres=1080;

		rmCountDown = 5;
		numFrames = 0;
		aspectRatio = (GLfloat)xres / (GLfloat)yres;
		MakeVector(0.0, 1.0, 8.0, cameraPosition);
		//light is up high, right a little, toward a little
		MakeVector(100.0f, 240.0f, 40.0f, lightPosition);
		lightPosition[3] = 1.0f;
		vel = 0.0f;
		curTheta = 0.0f;
		ePressed = false;
		wPressed = false;
		aPressed = false;
		sPressed = false;
		dPressed = false;
		cPressed = false;
		jPressed = false;
		//pause
		pPressed = false;
		oPressed = false;
		//help screen
		hPressed = 0;
		raceModeOn = false;
		rotationTestOn = false;
		didYouWin = false;
		rmFinished = false;
		second0 = false;
		second1 = false;
		second2 = false;
		second3 = false;
		second4 = false;
		second5 = false;
		anchorPosition0 = cameraPosition[0];
		anchorPosition2 = (float)cameraPosition[2] - 13.0f;
		//restart mode
		bounds_mode = 0;
		speed_mode = 0;
		yPressed = 0;
		//restart mode
		//finish
		finishMode = 0;
	}

} g;


class X11_wrapper {
private:
	Display *dpy;
	Window win;
	GLXContext glc;
public:
	X11_wrapper() {
		//Look here for information on XVisualInfo parameters.
		//http://www.talisman.org/opengl-1.1/Reference/glXChooseVisual.html
		Window root;
		GLint att[] = { GLX_RGBA,
						GLX_STENCIL_SIZE, 2,
						GLX_DEPTH_SIZE, 24,
						GLX_DOUBLEBUFFER, None };
		//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
		//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
		//XVisualInfo *vi;
		Colormap cmap;
		XSetWindowAttributes swa;
		setup_screen_res(g.xres, g.yres);
		dpy = XOpenDisplay(NULL);
		if (dpy == NULL) {
			printf("\n\tcannot connect to X server\n\n");
			exit(EXIT_FAILURE);
		}
		root = DefaultRootWindow(dpy);
		XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
		if (vi == NULL) {
			printf("\n\tno appropriate visual found\n\n");
			exit(EXIT_FAILURE);
		} 
		cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
		swa.colormap = cmap;
		swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
							StructureNotifyMask | SubstructureNotifyMask;
		win = XCreateWindow(dpy, root, 0, 0, g.xres, g.yres, 0,
								vi->depth, InputOutput, vi->visual,
								CWColormap | CWEventMask, &swa);
		set_title();
		glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
		glXMakeCurrent(dpy, win, glc);
	}
	~X11_wrapper() {
		XDestroyWindow(dpy, win);
		XCloseDisplay(dpy);
	}
	void setup_screen_res(const int w, const int h) {
		g.xres = w;
		g.yres = h;
		g.aspectRatio = (GLfloat)g.xres / (GLfloat)g.yres;
	}
	void check_resize(XEvent *e) {
		//The ConfigureNotify is sent by the
		//server if the window is resized.
		if (e->type != ConfigureNotify)
			return;
		XConfigureEvent xce = e->xconfigure;
		if (xce.width != g.xres || xce.height != g.yres) {
			//Window size did change.
			reshape_window(xce.width, xce.height);
		}
	}
	void reshape_window(int width, int height) {
		//window has been resized.
		setup_screen_res(width, height);
		//
		glViewport(0, 0, (GLint)width, (GLint)height);
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		glMatrixMode(GL_MODELVIEW); glLoadIdentity();
		glOrtho(0, g.xres, 0, g.yres, -1, 1);
		set_title();
	}
	void set_title() {
		//Set the window title bar.
		XMapWindow(dpy, win);
		XStoreName(dpy, win, "car demo");
	}
	bool getXPending() {
		return XPending(dpy);
	}
	XEvent getXNextEvent() {
		XEvent e;
		XNextEvent(dpy, &e);
		return e;
	}
	void swapBuffers() {
		glXSwapBuffers(dpy, win);
	}
} x11;


int main()
{
	init_opengl();
	initSound();
	int done = 0;
	// int curCountDown = g.rmCountDown;
	int initPosition = get_init_pos(g.cameraPosition[0]);
	int initPosition2 = get_init_pos(g.cameraPosition[2]);
	g.iniPos = initPosition;
	g.iniPos2 = initPosition2;
	//playSound(alSourceIDLE);
	while (!done) {
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			check_mouse(&e);
			done = check_keys(&e);
		}
		if (g.raceModeOn)
			race_mode(g.rmCountDown, g.numFrames, g.iniPos,
					g.cameraPosition[2], g.second0, g.second1,
					g.second2, g.second3, g.second4, g.second5, g.didYouWin,
					g.rmFinished, g.xres, g.yres);
		if (!g.pPressed)
			physics();
		render();
		x11.swapBuffers();
	}
	cleanup_fonts();
	cleanupSound();
	return 0;
}

void init()
{

}

void init_opengl()
{
	//OpenGL initialization
	glClearColor(0.0f, 0.4f, 0.5f, 0.0f);
	glClearDepth(1.0);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, g.aspectRatio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	//Enable this so material colors are the same as vert colors.
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	//Turn on a light
	glLightfv(GL_LIGHT0, GL_POSITION, g.lightPosition);
	glEnable(GL_LIGHT0);
	//Do this to allow fonts
	glEnable(GL_TEXTURE_2D);
	//g.tex.backImage = &img[0];
	//create opengl texture elements

	/*glGenTextures(1, &g.tex.backTexture);
	int w = g.tex.backImage->width;
	int h = g.tex.backImage->height;
	glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, g.tex.backImage->data);
	g.tex.xc[0] = 0.0;
	g.tex.xc[1] = 0.25;
	g.tex.yc[0] = 0.0;
	g.tex.yc[1] = 1.0;
	*/
	initialize_fonts();
	//init_textures();
}

Flt vecNormalize(Vec vec) {
	Flt len = vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
	if (len == 0.0) {
		MakeVector(0.0,0.0,1.0,vec);
		return 1.0;
	}
	len = sqrt(len);
	Flt tlen = 1.0 / len;
	vec[0] *= tlen;
	vec[1] *= tlen;
	vec[2] *= tlen;
	return len;
}

void check_mouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
		}
		if (e->xbutton.button==3) {
			//Right button is down
			
	g.cameraPosition[2] -= 0.1;
	g.cameraPosition[0] = 1.0 + sin(g.cameraPosition[2]*0.3);
		}
	}
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		savex = e->xbutton.x;
		savey = e->xbutton.y;
	}
}

int check_keys(XEvent *e)
{
	//Was there input from the keyboard?
	if (e->type == KeyPress) {
		int key = (XLookupKeysym(&e->xkey, 0) & 0x0000ffff);
		switch(key) {
			case XK_1:
				break;
			case XK_w:
				g.wPressed = startState(startCounter);
				break;
			case XK_a:
				g.aPressed = startState(startCounter);
				break;
			case XK_s:
				g.sPressed = startState(startCounter);
				break;
			case XK_d:
				g.dPressed = startState(startCounter);
				break;
			case XK_i:
				print_name();
				break;
			case XK_q:
				display_name();
				break;
			case XK_m:
				show_name();
				break;
			case XK_j:
				g.jPressed = true;


				if((red == 0.0f) && (green == 0.0f) && (blue == 0.0f)) {
					red = 1.0f;
				}
				else if(red == 1.0f) {
					red = 0.0f;
					green = 1.0f;
				}
				else if(green == 1.0f) {
					green = 0.0f;
					red = 0.0f;
					blue = 1.0f;
				}

				else if(blue == 1.0f) {
					blue = 0.0f;
					red = 1.0f;
				}

				
				break;
			case XK_b:
				//g.pPressed = false; //unpause
				//g.pPressed = unpaused(g.pPressed);
				g.cPressed = rmcredits(g.cPressed);
				break;
			case XK_p:
				show_name_s();
				g.pPressed = paused(g.pPressed); //pause
				break;
			case XK_z:
				g.rails = rails(g.rails);
				g.zPressed = car(g.zPressed);
				break;
			case XK_c:
				g.cPressed = credits(g.cPressed);
				break;
			case XK_h:
				g.hPressed ^= 1; 
				break;
			case XK_e:
				g.ePressed = startMenu(g.ePressed); 
				break;
			case XK_r:
				g.feature_mode ^= 1;
				if (g.feature_mode == 1)
					g.raceModeOn = true;
				break;
			case XK_t:
				g.bounds_mode ^= 1;
				break;
			case XK_x:
				g.speed_mode ^= 1;
				break;
			case XK_y:
				if(g.bounds_mode != 0) {
					g.yPressed ^= 1;
				}
				if(g.finishMode != 0){
					g.yPressed ^= 1;
				}
				break;
			case XK_o:
				g.oPressed = paused(g.oPressed);
				break;
			case XK_v:
			g.finishMode ^=1;
				break;
			case XK_f:
				g.rotation_test ^= 1;
				if (g.rotation_test == 1)
					g.rotationTestOn = true;
				break;
			case XK_Escape:
				return 1;
		}
	}
	return 0;
}

void box(float w1, float h1, float d1)
{
	float w=w1*0.5;
	float d=d1*0.5;
	float h=h1*0.5;
	//notice the normals being set
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
}


void identity33(Matrix m)
{
	m[0][0] = m[1][1] = m[2][2] = 1.0f;
	m[0][1] = m[0][2] = m[1][0] = m[1][2] = m[2][0] = m[2][1] = 0.0f;
}

void yy_transform(const Vec rotate, Matrix a)
{
	//This function applies a rotation to a matrix.
	//Call this function first, then call trans_vector() to apply the
	//rotations to an object or vertex.
	//
	if (rotate[0] != 0.0f) {
		Flt ct = cos(rotate[0]), st = sin(rotate[0]);
		Flt t10 = ct*a[1][0] - st*a[2][0];
		Flt t11 = ct*a[1][1] - st*a[2][1];
		Flt t12 = ct*a[1][2] - st*a[2][2];
		Flt t20 = st*a[1][0] + ct*a[2][0];
		Flt t21 = st*a[1][1] + ct*a[2][1];
		Flt t22 = st*a[1][2] + ct*a[2][2];
		a[1][0] = t10;
		a[1][1] = t11;
		a[1][2] = t12;
		a[2][0] = t20;
		a[2][1] = t21;
		a[2][2] = t22;
		return;
	}
	if (rotate[1] != 0.0f) {
		Flt ct = cos(rotate[1]), st = sin(rotate[1]);
		Flt t00 = ct*a[0][0] - st*a[2][0];
		Flt t01 = ct*a[0][1] - st*a[2][1];
		Flt t02 = ct*a[0][2] - st*a[2][2];
		Flt t20 = st*a[0][0] + ct*a[2][0];
		Flt t21 = st*a[0][1] + ct*a[2][1];
		Flt t22 = st*a[0][2] + ct*a[2][2];
		a[0][0] = t00;
		a[0][1] = t01;
		a[0][2] = t02;
		a[2][0] = t20;
		a[2][1] = t21;
		a[2][2] = t22;
		return;
	}
	if (rotate[2] != 0.0f) {
		Flt ct = cos(rotate[2]), st = sin(rotate[2]);
		Flt t00 = ct*a[0][0] - st*a[1][0];
		Flt t01 = ct*a[0][1] - st*a[1][1];
		Flt t02 = ct*a[0][2] - st*a[1][2];
		Flt t10 = st*a[0][0] + ct*a[1][0];
		Flt t11 = st*a[0][1] + ct*a[1][1];
		Flt t12 = st*a[0][2] + ct*a[1][2];
		a[0][0] = t00;
		a[0][1] = t01;
		a[0][2] = t02;
		a[1][0] = t10;
		a[1][1] = t11;
		a[1][2] = t12;
		return;
	}
}

void trans_vector(Matrix mat, const Vec in, Vec out)
{
	Flt f0 = mat[0][0] * in[0] + mat[1][0] * in[1] + mat[2][0] * in[2];
	Flt f1 = mat[0][1] * in[0] + mat[1][1] * in[1] + mat[2][1] * in[2];
	Flt f2 = mat[0][2] * in[0] + mat[1][2] * in[1] + mat[2][2] * in[2];
	out[0] = f0;
	out[1] = f1;
	out[2] = f2;
}
/*
void show_kachow()
{
		 //glClear(GL_COLOR_BUFFER_BIT);
		 glColor3f(1.0, 1.0, 1.0);
		 //main
		glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
		glBegin(GL_QUADS);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(10,	  10);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(10,	  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres,  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres,  10);
		glEnd();
}
*/
void credits() 
{
	Rect r;
	Rect s;
	Rect p;
	Rect l;
	Rect m;
		//credits location 
		r.bot = g.yres -230;	
		r.left = 300;
		r.center = 0;
		s.bot = g.yres -240;
		s.left = 300;
		s.center = 0;
		p.bot = g.yres -250;
		p.left = 300;
		p.center = 0;
		l.bot = g.yres -260;
		l.left = 300;
		l.center = 0;
		m.bot = g.yres -270;
		m.left = 300;
		m.center = 0;
		ggprint8b(&r, 6, 0x00000000, "Moises Fuentes");
		ggprint8b(&s, 6, 0x00000000, "Jarls Ramos");
		ggprint8b(&p, 6, 0x00000000, "Spencer Denney");
		ggprint8b(&l, 6, 0x00000000, "Irene Chavez");
		ggprint8b(&m, 6, 0x00000000, "Jesus Quinonez");
		 //glClear(GL_COLOR_BUFFER_BIT);
		 glColor3f(1.0, 1.0, 1.0);
		 //main
		//glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
		glBegin(GL_QUADS);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(10,	  10);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(10,	  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres,  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres,  10);
		glEnd();

}

//Pause screen pops up 
/*void pause()
{
	Rect r;
		//Pause Title
		r.bot = g.yres -230;
		r.left = 300;
		r.center = 0;
		ggprint8b(&r, 6, 0x00000000, "PAUSED");
		 //glClear(GL_COLOR_BUFFER_BIT);
		 glColor3f(1.0, 1.0, 0.5);
		 //main
		//glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
		glBegin(GL_QUADS);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(10,	  10);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(10,	  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres,  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres,  10);
		glEnd();

}*/
//Help screen 
void help()
{
	 Rect r, d;
		//help title
		r.bot = g.yres -230;
		r.left = 300;
		r.center = 0;
		ggprint16(&r, 6, 0x00cd00cd, "HELP");
		d.bot = g.yres -250;
		d.left = 300;
		d.center = 0;
		ggprint16(&d, 6, 0x00cd00cd, "Spencer's Feature Mode: press 'o'");
		r.bot = g.yres -270;
		ggprint16(&r, 6, 0x00cd00cd, "Jesus Feature Mode: Press t key for out of bounds mode");
		r.bot = g.yres -290;
		ggprint16(&r, 6, 0x00cd00cd, "Moises Feature Mode: Press j key for out of box change color mode");
		r.bot = g.yres -310;
		ggprint16(&r, 6, 0x00cd00cd, "Irenes Feature Mode: Press v key for finish line mode");
		r.bot = g.yres -330;
		ggprint16(&r, 6, 0x00cd00cd, "Jarls Feature Mode: Press r key for race mode and f key for test rotation mode");
		 //glClear(GL_COLOR_BUFFER_BIT);
		 glColor3f(0.0, 0.0, 1.0);
		 //main
		//glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
		glBegin(GL_QUADS);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(10,	  10);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(10,	  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres,  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres,  10);
		glEnd();
}
void startMenu()
{
		 Rect r;
		 Rect s;
		//start menu
		r.bot = g.yres -700;
		r.left = 1150;
		r.center = 0;
		s.bot = g.yres -750;
		s.left = 1160;
		s.center = 0;
		ggprint16(&r, 6, 0x00cd00cd, "TOKYO THROTTLE!");

		ggprint16(&s, 6, 0x00cd00cd, "Press E to Start!");
		ggprint16(&s, 6, 0x00000000, "Press E to Start!");

		 //glClear(GL_COLOR_BUFFER_BIT);
		 glColor3f(0.0, 0.0, 0.0);
		 //main
		//glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
		glBegin(GL_QUADS);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(0,	  0);
				glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(0,	  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres,  g.yres);
				glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres,  0);
				glEnd();
}

void build_billboard(float p1, float p2, float p3, 
					 float red, float green, float blue)
{
	// first param: left/right
	// last param: push forward 
	glPushMatrix();
	glColor3f(red, green, blue);
		//1st element was 6.0f
		//2nd element was -0.5f
	glTranslatef(p1, p2, p3);
		//3rd element was 0.2
		//2nd element was 5.0
		//1st element was 0.2
	box(0.5, 10.0, 0.5);
	glPopMatrix();
   
	glPushMatrix();
	glColor3f(red, green, blue);
		//1st element was 6.0f
		//2nd element was -0.5f
	glTranslatef(p1, p2 + 5.5f, p3);
		//3rd element was 0.2
		//2nd element was 5.0
		//1st element was 0.2
	box(6.0f, 3.0f, 0.5f);
	glPopMatrix();
}

void drawStreet()
{
	glPushMatrix();
	glColor3f(0.2f, 0.2f, 0.2f);
	float w = 5.0;
	//d = 100.0 -> changed
	float d = 1000.0;
	float h = 0.0;
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		//top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( w, h,-d);
		glVertex3f(-w, h,-d);
		glVertex3f(-w, h, d);
		glVertex3f( w, h, d);
	glEnd();
	glPopMatrix();

	grass(frames); //spawns grass, black/white squares, and light post
	mainFinish();
	if(g.finishMode != 0){
		finish(g.cameraPosition[2], g.cameraPosition[0]);
		if(g.yPressed != 0){
			g.cameraPosition[0] = g.iniPos;
		}
	}

	//double yellow line
	glColor3f(0.8f, 0.8f, 0.2f);
	w = 0.1;
	//d = 100.0 -> changed
	d = 1000.0;
	h = 0.01;
	glPushMatrix();
	glTranslatef(-0.15f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		//top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( w, h,-d);
		glVertex3f(-w, h,-d);
		glVertex3f(-w, h, d);
		glVertex3f( w, h, d);
	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0.15f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		//top
		glNormal3f( 0.0f, 1.0f, 0.0f);
		glVertex3f( w, h,-d);
		glVertex3f(-w, h,-d);
		glVertex3f(-w, h, d);
		glVertex3f( w, h, d);
	glEnd();
	glPopMatrix();
	//guard rails
	glColor3f(1.0f, 1.0f, 1.0f);
	//double k = 2.0;
	if (g.oPressed) {
		tunnel();
	}
	//i<40 -> changed
	/*for (int i=0; i<400; i++) {
		if (i <= 200){
			k = k + 0.05;
			glPushMatrix();
			glTranslatef(6.0f, -0.5f, (float)-i*2.5);
			//3rd element was 0.2
			//2nd element was 5.0
			box(0.2, k, g.rails);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-6.0f, -0.5f, (float)-i*2.5);
			//3rd element was 0.2
			//2nd element was 5.0
			box(0.2, k, g.rails);
			glPopMatrix();
		}
		else {
			k = k - 0.05;
			glPushMatrix();
			glTranslatef(6.0f, -0.5f, (float)-i*2.5);
			//3rd element was 0.2
			//2nd element was 5.0
			box(0.2, k, g.rails);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-6.0f, -0.5f, (float)-i*2.5);
			//3rd element was 0.2
			//2nd element was 5.0
			box(0.2, k, g.rails);
			glPopMatrix();
		}
	}*/
				//box car -- WORK IN PROGRESS
				glPushMatrix();
				glColor3f(0.0f, 0.0f, 0.0f);
						if(g.jPressed) {
							switchColor();
						}
				//1st element was 6.0f
				//2nd element was -0.5f
				glTranslatef(g.cameraPosition[0], -0.5f, (float)g.cameraPosition[2] - 3.0);
				glRotatef(g.curTheta, 0, -1, 0);
				glMatrixMode(GL_MODELVIEW);
				//3rd element was 0.2
				//2nd element was 5.0
				//1st element was 0.2
				box(0.5, 2.0, 0.5);
				glPopMatrix();

				//finish mode
				/*
				if(g.finishMode != 0){
				glEnable(GL_DEPTH_TEST);
				glDepthFunc(GL_ALWAYS);
				glPushMatrix();
				glColor3ub(150.0f, 200.0f, 120.0f);
				glTranslatef(0.0f, 1.5f, -70.0f);
				box(5.0, 2.0, 5.0);
				glPopMatrix();
				}*/
				
				if (g.rotationTestOn) {
					
					glPushMatrix();
					glColor3f(0.0f, 0.0f, 0.0f);
					//1st element was 6.0f
					//2nd element was -0.5f
					glTranslatef(g.anchorPosition0, -0.5f, g.anchorPosition2);
					//3rd element was 0.2
					//2nd element was 5.0
					//1st element was 0.2
					box(0.5, 2.0, 0.5);
					rotation_test_mode(g.rotationTestOn, g.cameraPosition[0], g.cameraPosition[2], 
					g.anchorPosition0, g.anchorPosition2, g.curTheta);
						
					glPopMatrix();
				}
				// first param: left/right
				// last param: push forward 

				glPushMatrix();
				build_billboard(-8.0f, -0.5f, -20.0f, 0.0f, 1.0f, 0.0f);  
				build_billboard(8.0f, -0.5f, -100.0f, 0.0f, 0.0f, 1.0f);
				build_billboard(-8.0f, -0.5f, -200.0f, 0.0f, 1.0f, 0.0f);
				build_billboard(8.0f, -0.5f, -300.0f, 1.0f, 0.0f, 0.0f);
				build_billboard(-8.0f, -0.5f, -400.0f, 0.0f, 1.0f, 0.0f);
				build_billboard(8.0f, -0.5f, -500.0f, 0.0f, 0.0f, 1.0f);
				build_billboard(-8.0f, -0.5f, -600.0f, 1.0f, 0.0f, 0.0f);
				build_billboard(8.0f, -0.5f, -700.0f, 0.0f, 1.0f, 0.0f);
				build_billboard(-8.0f, -0.5f, -800.0f, 0.0f, 0.0f, 1.0f);
				build_billboard(8.0f, -0.5f, -900.0f, 1.0f, 0.0f, 0.0f);
				build_billboard(-8.0f, -0.5f, -1000.0f, 0.0f, 1.0f, 0.0f);
				glPopMatrix();
}

void physics()
{
	if (g.wPressed) {
		if(g.cameraPosition[0] > 5 || g.cameraPosition[0] < -5){
			grassAccelerate(g.vel);
			go_forwards_grass(g.vel, g.cameraPosition[2], g.cameraPosition[0], g.curTheta);
			//g.cameraPosition[2] -= g.vel;
			g.wPressed = false;
		} else {
			//accelerate(g.vel);
			go_forwards(g.vel, g.cameraPosition[2], g.cameraPosition[0], g.curTheta);
			//g.cameraPosition[2] -= g.vel;
			g.wPressed = false;
		}
		
	}
	if (g.aPressed) {
		//accelerate(g.vel);
		go_forwards(g.vel, g.cameraPosition[2], g.cameraPosition[0], g.curTheta);
		shift_left(g.curTheta);
		//g.cameraPosition[2] -= g.vel;
		//g.cameraPosition[0] -= 0.1;
		g.aPressed = false;
	}	
	if (g.sPressed) {
		//decelerate(g.vel);
		go_backwards(g.vel, g.cameraPosition[2], g.cameraPosition[0], g.curTheta);
		//g.cameraPosition[2] -= g.vel;
		g.sPressed = false;
		 cout << g.vel << endl;
	}
	if (g.dPressed) {
		//accelerate(g.vel);
		go_forwards(g.vel, g.cameraPosition[2], g.cameraPosition[0], g.curTheta);
		shift_right(g.curTheta);
		//g.cameraPosition[2] -= g.vel;
		//g.cameraPosition[0] += 0.1;
		g.dPressed = false;
	}
	pedal_off_slow_down(g.wPressed, g.sPressed, g.vel, g.cameraPosition[2],
						g.cameraPosition[0], g.curTheta);	
}

void render()
{
	Rect r;
	if(!g.pPressed) {
		
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//
		//3D mode
		glMatrixMode(GL_PROJECTION); glLoadIdentity();
		gluPerspective(45.0f, g.aspectRatio, 0.1f, 100.0f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		//for documentation...
		//
		if(g.cameraPosition[0] > 5 || g.cameraPosition[0] < -5){
			Vec up = {static_cast<float>((rnd()*.2)-0.1), 1, static_cast<float>((rnd()*.2)-0.1)};

		gluLookAt(
			g.cameraPosition[0], g.cameraPosition[1], g.cameraPosition[2],
			g.cameraPosition[0], g.cameraPosition[1], g.cameraPosition[2]-1.0,
			up[0], up[1], up[2]);
		}
		else{	

		Vec up = {0,1,0};
		gluLookAt(
			g.cameraPosition[0], g.cameraPosition[1], g.cameraPosition[2],
			g.cameraPosition[0], g.cameraPosition[1], g.cameraPosition[2]-1.0,
			up[0], up[1], up[2]);
		}
		glLightfv(GL_LIGHT0, GL_POSITION, g.lightPosition);
		//
		drawStreet();
		//
		//
		//
		//switch to 2D mode
		//
		glViewport(0, 0, g.xres, g.yres);
		glMatrixMode(GL_MODELVIEW);   glLoadIdentity();
		glMatrixMode (GL_PROJECTION); glLoadIdentity();
		gluOrtho2D(0, g.xres, 0, g.yres);
		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_LIGHTING);
		//glDisable(GL_DEPTH_TEST);
		//glDisable(GL_CULL_FACE);
	}
	else {
		pause_game();
	}


	if(!g.ePressed) {
		startMenu();
	}
	else
	{
		//Start state 
		if(frames < 480) {
		frames++;
		}   
		startPrint(frames);
		startCounter = startCount(frames);
		//Start state
		
		//out of bounds mode
		/*if(g.bounds_mode != 0) {
				boundModePrint();
			}*/

			if((g.cameraPosition[0] > 13 || g.cameraPosition[0] < -13)) {
				boundsPrint(frames);
				if(frames > 720) {
					g.cameraPosition[0] = g.iniPos;
					g.bounds_mode = 0;
					frames = 480;
				}
				frames++;
			}
			
		if(g.cameraPosition[2] < -1000) {
			g.cameraPosition[0] = g.iniPos;
			g.cameraPosition[2] = 8;
		}
		if(g.speed_mode) {
			speedHud(g.vel);
		}
		
		if(frames == 60){
			playSound(alSourceSET);
			playSound(alSourceIDLE);
		}
		if(frames == 120)
		playSound(alSourceSET);
		if(frames == 180)
		playSound(alSourceGO);
		if(g.vel == 0 && frames == 190)
		for(int i = 0; i <4; i++){
			playSound(alSourceCAR);
		}
		
		//finish line mode 
		if(g.finishMode !=0) {
			finishText();
		}
			/*
			//draw a border using a triangle strip
			glPushMatrix();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_BLEND);
			//exit(0);
			glColor3f(255, 20, 147);
			glColor4f(1.0, 0.0, 1.0, 0.9);

			int w = 40;
			glBegin(GL_TRIANGLE_STRIP);
			//glVertex2i(0, 0);
		// glVertex2i(0+w ,w);

			glVertex2i(0, g.yres);
			//glVertex2i(0+w ,g.yres-w);
			//trying to fix the boader
			glVertex2i(0,g.yres-w);

			glVertex2i(g.xres, g.yres);
			glVertex2i(g.xres ,g.yres-w);
			//glVertex2i(g.xres-w ,g.yres);

			//glVertex2i(g.xres, 0);
			//glVertex2i(g.xres-w ,w);

			//glVertex2i(0,0);
			//glVertex2i(0+w, w);
			glEnd();
			glDisable(GL_BLEND);
			glPopMatrix();
		}*/
		if(g.finishMode != 0 && g.cameraPosition[2] <= -74.0f) {
			practice();
		}

		render_the_game_over(g.didYouWin, g.rmFinished, g.xres, g.yres);
		render_game_mode_title(g.raceModeOn, g.xres, g.yres);
		display_rm_options(g.raceModeOn, g.rotationTestOn);
		rot_instructions(g.rotationTestOn);
		display_rotation_text(g.rotationTestOn);
		display_countdown(g.raceModeOn, g.rmCountDown);
		go_go_go(g.raceModeOn, g.iniPos, g.cameraPosition[2]);
		you_win(g.didYouWin, g.xres, g.yres);

		r.bot = g.yres - 40;
		r.left = 20;
		r.center = 0;
		ggprint16(&r, 16, 0x00ff0000, ">PRESS H FOR SPECIFIC KEYS FOR FEATURES<");
		//if p is pressed then pause
		if(g.pPressed) {
		pause_game();
		}

		if(g.cPressed) {
		credits();
		}
		if(g.hPressed) {
		help();
		}
		if(g.jPressed) {

				Rect r;
				Rect s;
				r.bot = 480 - 230;
				r.left = 230;
				r.center = 0;
				s.bot = 480 - 270;
				s.center = 0;
				ggprint16(&r, 6, 0x005f0202, "Color Select!");
						if(red == 1.0f)
								ggprint16(&s, 6, 0x00ff0000, "Red");
						else if(green == 1.0f)
								ggprint16(&s, 6, 0x0000ff00, "Green");
						else if(blue == 1.0f)
								ggprint16(&s, 6, 0x000000ff, "Blue");
		}

	}
	glPopAttrib();
  
}





