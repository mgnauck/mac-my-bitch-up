#ifndef H_SQUARED__
#define H_SQUARED__

#include "Effect.h"
#include "ImageHandler.h"
#include "DisplacementMapper.h"
#include "Animation.h"

class Squared : public Effect {
public:
	Squared(ImageHandler& imageHandler);
	
	void				render(SDL_Surface* dest, unsigned int tick);
	void				reset();
		
private:
	DisplacementMapper	mapper;
	Animation			anim;
};

#endif