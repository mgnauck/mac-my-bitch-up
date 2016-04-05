#include "Tunnel.h"
#include "Defines.h"

Tunnel::Tunnel(ImageHandler& imageHandler) : mapper(), anim(), dir(-1.0f), fade() {

	mapper.init(RESX * 2, RESY * 2, imageHandler.loadImage(PATH_PREFIX "tex06.bmp"));
	mapper.generate(DistanceFunctionRound(), 80.0f, 7.0f, 7.0f, 3.0f, 10.0f, 1.0, 1.0f);
	
	anim.init(3200, false);
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "credits1.bmp", PATH_PREFIX "credits1a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "credits2.bmp", PATH_PREFIX "credits2a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "credits3.bmp", PATH_PREFIX "credits3a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "credits4.bmp", PATH_PREFIX "credits4a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "credits5.bmp", PATH_PREFIX "credits5a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "credits6.bmp", PATH_PREFIX "credits6a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "empty.bmp", PATH_PREFIX "empty.bmp"));
	
	fade.init(0xffffff, 300);
}

void Tunnel::render(SDL_Surface* dest, unsigned int tick) {

	int resx2 = dest->w >> 1;
	int resy2 = dest->h >> 1;

	float rotate = tick * 0.05f;
	float move = tick * 0.2f;

	int x1 = (int)(cos(tick * 0.0006353) * sin(tick * 0.0002435) * resx2) + resx2;
	int y1 = (int)(cos(tick * 0.0007193) * resy2) + resy2;
								
	mapper.render(dest, x1, y1, (int)(dir * move * 256.0f), (int)(dir * rotate * 256.0f));
	
#ifndef NO_OVERLAYS
	if(tick > 2000)
		anim.renderAlphaWithTest(dest, tick);
#endif

	if(tick > 23700)
		fade.fadeFromDest(dest, tick);
}

void Tunnel::reset() {
	anim.reset();
	fade.reset();
}