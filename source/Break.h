#ifndef H_BREAK__
#define H_BREAK__

#include "Effect.h"
#include "ImageHandler.h"
#include "Animation.h"
#include "Noise.h"
#include "Fade.h"

class Break : public Effect {
public:
	Break(ImageHandler& imageHandler);	
	void render(SDL_Surface* dest, unsigned int tick);
	void reset();
	
private:
	SDL_Surface*	tex;
	Animation		anim;
	Noise			noise;
	Fade			fade;
};

#endif