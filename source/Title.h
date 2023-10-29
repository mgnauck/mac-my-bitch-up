#ifndef H_TITLE__
#define H_TITLE__

#include "Effect.h"
#include "ImageHandler.h"
#include "Animation.h"
#include "Noise.h"
#include "Fade.h"

class Title : public Effect {
public:
	Title(ImageHandler& imageHandler);	
	void render(SDL_Surface* dest, unsigned int tick);
	void reset();
	
private:
	SDL_Surface*	tex;
	Animation		anim;
	Noise			noise;
	Fade			fade;
};

#endif