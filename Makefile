all: car

car: car.cpp ichavez.cpp  mfuentes.cpp jramos3.cpp sdenney.cpp jquinonez.cpp jquinonez.h
	g++ car.cpp ichavez.cpp mfuentes.cpp jramos3.cpp sdenney.cpp jquinonez.cpp -Wall -lX11 -lGL -lGLU -lm ./libggfonts.a -ocar \
	-D USE_OPENAL_SOUND \
	/usr/lib/x86_64-linux-gnu/libopenal.so \
    /usr/lib/x86_64-linux-gnu/libalut.so


clean:
	rm -f car
	rm -f *.o

