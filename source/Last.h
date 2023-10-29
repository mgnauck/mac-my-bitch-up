#ifndef H_LAST__
#define H_LAST__

#include "Effect.h"
#include "ImageHandler.h"
#include "Animation.h"
#include "Noise.h"
#include "Fade.h"

class Last : public Effect {
public:
	Last(ImageHandler& imageHandler);	
	void render(SDL_Surface* dest, unsigned int tick);
	void reset();
	
private:
	SDL_Surface*	tex;
	Animation		anim;
	Noise			noise;
	Fade			fade;
};

#endif