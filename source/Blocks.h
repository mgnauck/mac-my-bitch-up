#ifndef H_BLOCKS__
#define H_BLOCKS__

#include "Effect.h"
#include "ImageHandler.h"
#include "DisplacementMapper.h"
#include "Noise.h"

class Blocks : public Effect {
public:
	Blocks(ImageHandler& imageHandler);
	
	void				render(SDL_Surface* dest, unsigned int tick);
	void				reset();
		
private:
	DisplacementMapper	mapper;
	Animation			anim;
	Noise				noise;
	float				dir;
};

#endif