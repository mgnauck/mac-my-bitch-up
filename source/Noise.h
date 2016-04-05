#ifndef H_NOISE__
#define H_NOISE__

#include <vector>
#include "ImageHandler.h"
#include "Animation.h"

class Noise {
public:
	Noise();
	
	void		init(ImageHandler& imageHandler, int count, int w, int h, unsigned char maxStrength, int ticks);
	void		render(SDL_Surface* dest, unsigned int ticks);
	void		renderAlpha(SDL_Surface* dest, unsigned int ticks);
	void		renderAdditive(SDL_Surface* dest, unsigned int ticks);
	
private:
	Animation	noiseAnim;
};

#endif