//Modified by: Moises B. Fuentes
/*
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
*/

#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

extern float red;
extern float green;
extern float blue;

extern ALuint alBufferDrip, alBufferTick, alBufferSET, alBufferGO, alBufferIDLE, alBufferCAR;
extern ALuint alSourceDrip, alSourceTick, alSourceSET, alSourceGO, alSourceIDLE, alSourceCAR;

extern bool credits(bool pressed);
extern bool rmcredits(bool pressed);
extern bool startMenu(bool pressed);
extern void switchColor();

extern void initSound();
extern void cleanupSound();
extern void playSound(ALuint source);
