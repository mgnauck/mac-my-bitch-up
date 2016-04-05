#ifndef H_GREETS__
#define H_GREETS__

#include "Effect.h"
#include "ImageHandler.h"
#include "Animation.h"
#include "Blitter.h"
#include "Fade.h"

class Greets : public Effect {
public:
	Greets(ImageHandler& imageHandler);	
	void render(SDL_Surface* dest, unsigned int tick);
	void reset();
	
private:
	SDL_Surface*	tex;
	Animation		anim;
	Blitter			blitter;
	Fade			fade;
};

#endif