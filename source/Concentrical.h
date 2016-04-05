#ifndef H_CONCENTRICAL__
#define H_CONCENTRICAL__

#include "Effect.h"
#include "ImageHandler.h"
#include "Animation.h"
#include "Noise.h"
#include "Blitter.h"
#include "Fade.h"

class Concentrical : public Effect {
public:
	Concentrical(ImageHandler& imageHandler, SDL_Surface* dest);	
	void render(SDL_Surface* dest, unsigned int tick);
	
private:
	SDL_Surface*	tex;
	Animation		anim1;
	Animation		anim2;
	Animation		anim3;
	Blitter			blitter[6];
	SDL_Surface*	tempSurface;
	int				phase;
	int				ovlNum;
	Fade			fade;
};

#endif