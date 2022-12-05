//Author: Moises B. Fuentes
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include "mfuentes.h"
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif //USE_OPENAL_SOUND

using namespace std;
float red = 0.0f;
float green = 0.0f;
float blue = 0.0f;

ALuint alBufferDrip, alBufferTick, alBufferSET, alBufferGO, alBufferIDLE, alBufferCAR;
ALuint alSourceDrip, alSourceTick, alSourceSET, alSourceGO, alSourceIDLE, alSourceCAR;


void show_name(){
    cout << "Moises Fuentes:";
}
//Credits Screen
bool credits(bool pressed){
    pressed = true;
	return pressed;
}
//cred screen
bool rmcredits(bool pressed){
    pressed = false;
	return pressed;
}
//Initial Start Menu
bool startMenu(bool pressed){
    pressed = true;
    return pressed; 
}
//Switch Color Feature
void switchColor(){
    //glColor3f(red, green, blue);
    glColor3f(red, green, blue);
}
//=============================
//Sound
//=============================
void initSound()
{
        #ifdef USE_OPENAL_SOUND
        alutInit(0, NULL);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: alutInit()\n");
                return;
        }
        //Clear error state.
        alGetError();
        //g.background3 = &img[3];
        //Setup the listener.
        //Forward and up vectors are used.
        float vec[6] = {0.0f,0.0f,1.0f, 0.0f,1.0f,0.0f};
        alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
        alListenerfv(AL_ORIENTATION, vec);
        alListenerf(AL_GAIN, 1.0f);
        //
        //Buffer holds the sound information.
        alBufferDrip = alutCreateBufferFromFile("tokyo.wav");
        alBufferTick = alutCreateBufferFromFile("select.wav");
        alBufferSET = alutCreateBufferFromFile("SET.wav");
        alBufferGO = alutCreateBufferFromFile("GO.wav");
        alBufferIDLE = alutCreateBufferFromFile("idle.wav");
        alBufferCAR = alutCreateBufferFromFile("carstart.wav");

        //
        //Source refers to the sound.
        //Generate a source, and store it in a buffer.
        alGenSources(1, &alSourceDrip);
        alSourcei(alSourceDrip, AL_BUFFER, alBufferDrip);
        //Set volume and pitch to normal, no looping of sound.
        alSourcef(alSourceDrip, AL_GAIN, 1.0f);
        alSourcef(alSourceDrip, AL_PITCH, 1.0f);
        alSourcei(alSourceDrip, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: setting source\n");
                return;
        }
        //Generate a source, and store it in a buffer.
        alGenSources(1, &alSourceTick);
        alSourcei(alSourceTick, AL_BUFFER, alBufferTick);
        //Set volume and pitch to normal, no looping of sound.
        alSourcef(alSourceTick, AL_GAIN, 1.0f);
        alSourcef(alSourceTick, AL_PITCH, 1.0f);
        alSourcei(alSourceTick, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: setting source\n");
                return;
        }
	//SET setup
        alGenSources(1, &alSourceSET);
        alSourcei(alSourceSET, AL_BUFFER, alBufferSET);
        //Set volume and pitch to normal, no looping of sound.
        alSourcef(alSourceSET, AL_GAIN, 1.0f);
        alSourcef(alSourceSET, AL_PITCH, 1.0f);
        alSourcei(alSourceSET, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: setting source\n");
                return;
        }
	//GO setup
        alGenSources(1, &alSourceGO);
        alSourcei(alSourceGO, AL_BUFFER, alBufferGO);
        //Set volume and pitch to normal, no looping of sound.
        alSourcef(alSourceGO, AL_GAIN, 1.0f);
        alSourcef(alSourceGO, AL_PITCH, 1.0f);
        alSourcei(alSourceGO, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: setting source\n");
                return;
        }
	//IDLE SETUP
        alGenSources(1, &alSourceIDLE);
        alSourcei(alSourceIDLE, AL_BUFFER, alBufferIDLE);
        //Set volume and pitch to normal, no looping of sound.
        alSourcef(alSourceIDLE, AL_GAIN, 1.0f);
        alSourcef(alSourceIDLE, AL_PITCH, 1.0f);
        alSourcei(alSourceIDLE, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: setting source\n");
                return;
        }
	//Car start
        alGenSources(1, &alSourceCAR);
        alSourcei(alSourceCAR, AL_BUFFER, alBufferCAR);
        //Set volume and pitch to normal, no looping of sound.
        alSourcef(alSourceCAR, AL_GAIN, 1.0f);
        alSourcef(alSourceCAR, AL_PITCH, 1.0f);
        alSourcei(alSourceCAR, AL_LOOPING, AL_FALSE);
        if (alGetError() != AL_NO_ERROR) {
                printf("ERROR: setting source\n");
                return;
        }

        #endif //USE_OPENAL_SOUND
}

void cleanupSound()
{
        #ifdef USE_OPENAL_SOUND
        //First delete the source.
        alDeleteSources(1, &alSourceDrip);
        alDeleteSources(1, &alSourceTick);
        alDeleteSources(1, &alSourceSET);
        alDeleteSources(1, &alSourceGO);
        alDeleteSources(1, &alSourceIDLE);

        //Delete the buffer.
        alDeleteBuffers(1, &alBufferDrip);
        alDeleteBuffers(1, &alBufferTick);
        alDeleteBuffers(1, &alBufferSET);
        alDeleteBuffers(1, &alBufferGO);
        alDeleteBuffers(1, &alBufferIDLE);

        //Close out OpenAL itself.
        //Get active context.
        ALCcontext *Context = alcGetCurrentContext();
        //Get device for active context.
        ALCdevice *Device = alcGetContextsDevice(Context);
        //Disable context.
        alcMakeContextCurrent(NULL);
        //Release context(s).
        alcDestroyContext(Context);
        //Close device.
        alcCloseDevice(Device);
        #endif //USE_OPENAL_SOUND
}

void playSound(ALuint source)
{
        #ifdef USE_OPENAL_SOUND
        alSourcePlay(source);
        #endif
}


/*extern class MyImage myimage;

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
}
*/
