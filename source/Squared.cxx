#include "Squared.h"
#include "Defines.h"

Squared::Squared(ImageHandler& imageHandler) : mapper(), anim() {

	mapper.init(RESX * 2, RESY * 2, imageHandler.loadImage(PATH_PREFIX "tex03.bmp"));
	mapper.generate(DistanceFunctionDiamond(), 128.0f, 5.0f, 2.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	
	anim.init(200, false);
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "lofi1.bmp", PATH_PREFIX "lofi1a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "lofi2.bmp", PATH_PREFIX "lofi2a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "lofi3.bmp", PATH_PREFIX "lofi3a.bmp"));
}

void Squared::render(SDL_Surface* dest, unsigned int tick) {

	int resx2		= dest->w >> 1;
	int resy2		= dest->h >> 2;

	float move		= tick * 0.5f;
	float rotate	= tick * 0.01f;

	int x1 = (int)(cos(tick * 0.0006353) * sin(tick * 0.0002435) * resx2) + resx2;
	int y1 = (int)(cos(tick * 0.0007193) * sin(tick * 0.0005385) * resy2) + resy2;
								
	mapper.render(dest, x1, y1, (int)(-1.0f * move * 256.0f), (int)(rotate * 256.0f));
	
#ifndef NO_OVERLAYS

	if(tick > 11000)
		anim.renderAlphaWithTest(dest, tick);
		
#endif
}

void Squared::reset() {
	anim.reset();
}