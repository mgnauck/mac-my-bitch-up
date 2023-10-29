#include "Fade.h"
#include "Blending.h"

#define STEP_TIME	20

Fade::Fade() : startIn(false), startOut(false) {}

void Fade::init(unsigned int col, unsigned int duration) {
	color		= col;
	inc			= (256.0f * STEP_TIME) / (float)duration;
}

void Fade::fadeFromDest(SDL_Surface* dest, unsigned int tick) {

	lockSurface(dest);

	if(!startOut) {
		alpha = 0.0f;
		startOut = true;
	}
		
	if(tick - lastTick >= STEP_TIME) {
		alpha += inc;
		if(alpha > 255.0f)
			alpha = 255.0f;
		lastTick = tick;
	}
		
	int w = dest->pitch >> 2;

	for(int j=0; j<dest->h; j++)
		for(int i=0; i<dest->w; i++)
			((unsigned int*)dest->pixels)[w * j + i] = Blending::alpha(color | (((int)alpha) << 24), ((unsigned int*)dest->pixels)[w * j + i]);

	unlockSurface(dest);
}

void Fade::fadeToDest(SDL_Surface* dest, unsigned int tick) {

	lockSurface(dest);

	if(!startIn) {
		alpha = 256.0f;
		startIn = true;
	}
		
	if(tick - lastTick >= STEP_TIME) {
		alpha -= inc;
		if(alpha < 0.0f)
			alpha = 0.0f;
		lastTick = tick;
	}
		
	int w = dest->pitch >> 2;

	for(int j=0; j<dest->h; j++)
		for(int i=0; i<dest->w; i++)
			((unsigned int*)dest->pixels)[w * j + i] = Blending::alpha(color | (((int)alpha) << 24), ((unsigned int*)dest->pixels)[w * j + i]);
			
	unlockSurface(dest);
}

void Fade::reset() {
	startIn = false;
	startOut = false;
}

/*
void Fade::fadeFromDest(SDL_Surface* dest, unsigned int tick) {

	lockSurface(dest);

	if(!startOut) {
		alpha = 0x0;
		startOut = true;
	}
		
	if(tick - lastTick > timeDelta) {
		if(alpha < 0xff)
		 alpha++;
		lastTick = tick;
	}
		
	int w = dest->pitch >> 2;

	for(int j=0; j<dest->h; j++)
		for(int i=0; i<dest->w; i++)
			((unsigned int*)dest->pixels)[w * j + i] = Blending::alpha(color | (alpha << 24), ((unsigned int*)dest->pixels)[w * j + i]);

	unlockSurface(dest);
}

void Fade::fadeToDest(SDL_Surface* dest, unsigned int tick) {

	lockSurface(dest);

	if(!startIn) {
		alpha = 0xff;
		startIn = true;
	}
		
	if(tick - lastTick > timeDelta) {
		if(alpha > 0x0)
		 alpha--;
		lastTick = tick;
	}
		
	int w = dest->pitch >> 2;

	for(int j=0; j<dest->h; j++)
		for(int i=0; i<dest->w; i++)
			((unsigned int*)dest->pixels)[w * j + i] = Blending::alpha(color | (alpha << 24), ((unsigned int*)dest->pixels)[w * j + i]);

	unlockSurface(dest);
}
*/