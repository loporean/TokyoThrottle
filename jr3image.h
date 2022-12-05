//==============================================================================
//NAME: Jarl Ramos
//ASGT: Group Project - Tokyo Throttle
//ORGN: CSUB - CMPS-3350
//FILE: jr3image.h
//DATE: 28 November 2022
//==============================================================================
#ifndef IMAGE_H
#define IMAGE_H
extern void accelerate(float & velocity);
extern void decelerate(float & velocity);
extern void go_forwards(float & vel, float & cp1, float & cp2, float theta);
void go_forwards_grass(float & vel, float & cp1, float & cp2, float theta);
extern void go_backwards(float & vel, float & cp1, float & cp2, float theta);
extern void pedal_off_slow_down(bool pressed1, bool pressed2, float & vel, float & cp1,
                                float & cp2, float theta);
extern void shift_left(float & theta);
extern void shift_right(float & theta);
extern float conv_rad(float deg);
extern bool isOver(float velocity);
//extern void text_rect(Rect & rec, int bot, int left, int center, const char string[]);
extern void render_the_game_over(bool won, bool done, int xr, int yr);
extern void render_game_mode_title(bool isModeOn, int xr, int yr);
extern float get_init_pos(float position);
extern void race_mode(int & ctdn, int & frames, float init_pos, float position,
                      bool & sec0, bool & sec1, bool & sec2, bool & sec3,
                      bool & sec4, bool & sec5, bool & won, bool & done,
                      int xr, int yr);
extern void display_rm_options(bool isModeOn, bool rTestOn);
extern void rotation_test_mode(bool rTestOn, float theta);
extern void rotation_test_mode(bool rTestOn, float cp0, float cp2,
						float & ap0, float & ap2, float theta);
extern void display_rotation_text(bool rTestOn);
extern void rot_instructions(bool rTestOn);
extern void display_theta(bool rTestOn, float theta);
extern void display_countdown(bool isModeOn, int ctdn);
extern void go_go_go(bool isModeOn, float init_pos, float position);
extern void you_win(bool won, int xr, int yr);
#endif
