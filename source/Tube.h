#ifndef H_TUBE__
#define H_TUBE__

#include "Effect.h"
#include "ImageHandler.h"
#include "DisplacementMapper.h"
#include "Animation.h"
#include "Fade.h"

class Tube : public Effect {
public:
	Tube(ImageHandler& imageHandler);
	
	void				render(SDL_Surface* dest, unsigned int tick);
	void				reset();
	
private:
	DisplacementMapper	mapper;
	Animation			anim;
	float				dir;
	Fade				fade;
};

#endif