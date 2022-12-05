//NAME: Spencer Denney
//FILE: sdenney.cpp
//individual source file

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "log.h"
#include "fonts.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <cmath>
#include <math.h>
#include <fcntl.h>
#include "sdenney.h"
#include <sys/stat.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

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
	
	float vel;
	float rails = 0.2;
	//int xres, yres;	
	Texture tex;
	Global() {
		//constructor
		xres=640;
		yres=480;

		vel = 0.0f;
		// curTheta = 0.0f;
	}
} gl;

void box1(float w1, float h1, float d1)
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

void show_name_s()
{
	printf("sdenney hi\n");
}

bool paused(bool pressed)
{
	if (pressed == false) {
		pressed = true;
	}
	else if (pressed == true) {
		pressed = false;
	}
	gl.rails = pressed;
	return pressed;
}
/*bool unpaused(bool pressed)
{
	pressed = false;
	return pressed;
}*/
double rails(double rails) {
	int a = 0.2;
	int b = 5.0;

	if (rails == a) {
		return b;
	}
	if (rails == b) {
		return a;
	}
	return 0;
}
bool car(bool z) {
	if (z == false)
		z = true;
	else
		z = false;
	return z;
}

// creates a tunnel at the midway point
// creates 4 different towers on each side of the road 
void tunnel() {
	/*double width = 9.0;
	double height = 6.0;
	unsigned int slices = 10;*/
	int k = 120;
	for (int i=0; i<400; i++) {
		if (i > 100 && i <= 200) {
			glPushMatrix();
			glTranslatef(4.5f, -0.5f, (float)-i*2.5);
			//3rd element was 0.2
			//2nd element was 5.0
			box1(0.2, 8.0, gl.rails);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-4.5f, -0.5f, (float)-i*2.5);
			//3rd element was 0.2
			//2nd element was 5.0
			box1(0.2, 8.0, gl.rails);
			glPopMatrix();
			//-------------------top of tunnel--------------------------
			glPushMatrix();
			//1st element(x-pos) was 0.0f
			//2nd element was -0.5f
			//3rd element was (float)-i*2.5
			glTranslatef(0.0f, 3.5f, (float)-i*2.5);
			//1st element (width) was 0.2
			//2nd element(height) was 5.0
			//3rd element (length) was 0.2
			//box1(width,height,length)
			box1(9.0, 0.2, 5.0);
			glPopMatrix();


//failed attempt at tunnel
//**********************************************************************
/*
			double width = 9.0;
			double height = 4.0;
			unsigned int slices = 10;
			glPushMatrix();
			GLfloat offset = 0.5f;
			glScalef(width/2,height/(1+offset),10.0f);
			glBegin(GL_QUADS);
			for( unsigned int j = 0; j < slices; ++j ) {
				float curAngle = ( ( j + 0 ) / (float)slices ) * 3.14159;
				float nxtAngle = ( ( j + 1 ) / (float)slices ) * 3.14159;
				glVertex2f( cos( curAngle ), sin( curAngle ) );
				glVertex2f( cos( curAngle ), 1.0f + offset );
				glVertex2f( cos( nxtAngle ), 1.0f + offset );
				glVertex2f( cos( nxtAngle ), sin( nxtAngle ) );
			}
			glEnd();
			glPopMatrix(); */
//*********************************************************************
		}
		// towers
		if (i == k && i < 350) {

			//RIGHT SIDE
			glPushMatrix();
			glTranslatef(30.5f, 4.5f, (float)-i*3.0);
			//3rd element was 0.2
			//2nd element was 5.0
			//box1(width,height,length)
			box1(15.0, 30.0, 12.0);
			glColor3f(0.66, 0.66, 0.66);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(40.5f, 4.5f, (float)-i*2.5);
			//3rd element was 0.2
			//2nd element was 5.0
			//box1(width,height,length)
			box1(28.0, 60.0, 12.0);
			glColor3f(0.66, 0.66, 0.66);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(25.5f, 4.5f, (float)-i*2.8);
			//3rd element was 0.2
			//2nd element was 5.0
			//box1(width,height,length)
			box1(20.0, 30.0, 12.0);
			glColor3f(0.66, 0.66, 0.66);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(32.5f, 4.5f, (float)-i*2.6);
			//3rd element was 0.2
			//2nd element was 5.0
			//box1(width,height,length)
			box1(20.0, 70.0, 12.0);
			glColor3f(0.66, 0.66, 0.66);
			glPopMatrix();

			//LEFT SIDE
			glPushMatrix();
			glTranslatef(-25.0f, 4.5f, (float)-i*2.5);
			//3rd element was 0.2
			//2nd element was 5.0
			//box1(width,height,length)
			box1(15.0, 20.0, 10.0);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-40.0f, 4.5f, (float)-i*2.8);
			//3rd element was 0.2
			//2nd element was 5.0
			//box1(width,height,length)
			box1(20.0, 50.0, 13.0);
			glColor3f(0.56, 0.56, 0.56);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-30.0f, 4.5f, (float)-i*3.0);
			//3rd element was 0.2
			//2nd element was 5.0
			//box1(width,height,length)
			box1(28.0, 40.0, 12.0);
			glPopMatrix();
			glPushMatrix();
			glTranslatef(-45.0f, 4.5f, (float)-i*3.0);
			//3rd element was 0.2
			//2nd element was 5.0
			//box1(width,height,length)
			box1(20.0, 65.0, 12.0);
			glColor3f(0.66, 0.66, 0.66);
			glPopMatrix();
			k += 20; 
		}
	}
} 
void pause_state() 
{
	Rect r;
		//Pause Title
		r.bot = gl.yres -230;
		r.left = 280;
		r.center = 0;
		ggprint8b(&r, 6, 0x00000000, "PAUSED");
		 //glClear(GL_COLOR_BUFFER_BIT);
		 glColor3f(1.0, 1.0, 0.5);
		 //main
		//glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
		glBegin(GL_QUADS);
			glTexCoord2f(gl.tex.xc[0], gl.tex.yc[1]); glVertex2i(10,	  10);
			glTexCoord2f(gl.tex.xc[0], gl.tex.yc[0]); glVertex2i(10,	gl.yres);
			glTexCoord2f(gl.tex.xc[1], gl.tex.yc[0]); glVertex2i(gl.xres,  gl.yres);
			glTexCoord2f(gl.tex.xc[1], gl.tex.yc[1]); glVertex2i(gl.xres,  10);
		glEnd();
		glPopMatrix();

}
void pause_game()
{
	float w = 175.0;
	float h = 70.0;
	float x = 915.0f;
	float y = 800.0f;
	float z = 0.0f;
	Rect r;
		//Pause Title
		r.bot = 790;
		r.left = 900;
		r.center = 0;
		ggprint8b(&r, 6, 0x00000000, "PAUSED");
		 //glClear(GL_COLOR_BUFFER_BIT);
		 glColor3f(1.0, 1.0, 0.5);
		 //main
		//glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
		glTranslatef(x,y,z);
		glBegin(GL_QUADS);
				glTexCoord2f(gl.tex.xc[0], gl.tex.yc[1]); glVertex2i(-w, -h);
				glTexCoord2f(gl.tex.xc[0], gl.tex.yc[0]); glVertex2i(-w, h);
				glTexCoord2f(gl.tex.xc[1], gl.tex.yc[0]); glVertex2i(w, h);
				glTexCoord2f(gl.tex.xc[1], gl.tex.yc[1]); glVertex2i(w, -h);
		glEnd();
		glPopMatrix();
}

/*
extern class MyImage myimage;

MyImage::~MyImage() { delete [] data; }

MyImage::MyImage(const char *fname) {
	if (fname[0] == '\0')
	return;
	char name[40];
	strcpy(name, fname);
	int slen = strlen(name);
	name[slen-4] = '\0';
	char ppmname[80];
	sprintf(ppmname,"%s.ppm", name);
	char ts[100];
	sprintf(ts, "convert %s %s", fname, ppmname);
	system(ts);
	FILE *fpi = fopen(ppmname, "r");
	if (fpi) {
		char line[200];
		fgets(line, 200, fpi);
		fgets(line, 200, fpi);
		//skip comments and blank lines
		while (line[0] == '#' || strlen(line) < 2)
			fgets(line, 200, fpi);
		sscanf(line, "%i %i", &width, &height);
		fgets(line, 200, fpi);
		//get pixel data
		int n = width * height * 3;
		data = new unsigned char[n];
		for (int i=0; i<n; i++)
			data[i] = fgetc(fpi);
		fclose(fpi);
	} else {
		printf("ERROR opening image: %s\n", ppmname);
		exit(0);
	}
	unlink(ppmname);
}*/
 
