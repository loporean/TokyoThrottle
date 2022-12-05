//NAME: Spencer Denney
//FILE: sdenney.h
//sdenney individual header file
//


extern void show_name_s();
extern bool paused(bool);
//extern bool unpaused(bool);
extern double rails(double);
extern bool car(bool);
extern void pause_state();
extern void pause_game();
extern void tunnel();
//extern void m_music(int, char* []);


#ifndef _MYIMAGE_H_
#define _MYIMAGE_H_
class MyImage {
public:
	int width, height;
	unsigned char *data;
	~MyImage(); //destructor
	MyImage(const char *fname);
};
#endif
