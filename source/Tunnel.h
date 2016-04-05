#ifndef H_TUNNEL__
#define H_TUNNEL__

#include "Effect.h"
#include "ImageHandler.h"
#include "DisplacementMapper.h"
#include "Animation.h"
#include "Fade.h"

class Tunnel : public Effect {
public:
	Tunnel(ImageHandler& imageHandler);
	
	void				render(SDL_Surface* dest, unsigned int tick);
	void				reset();
		
private:
	DisplacementMapper	mapper;
	Animation			anim;
	float				dir;
	Fade				fade;
};

#endif