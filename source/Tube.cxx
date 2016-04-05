#include "Tube.h"
#include "Defines.h"

Tube::Tube(ImageHandler& imageHandler) : mapper(), anim(), dir(-1.0f), fade() {

	mapper.init(RESX * 2, RESY * 2, imageHandler.loadImage(PATH_PREFIX "tex01.bmp"));
	mapper.generate(DistanceFunctionRound(), 80.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0, 1.0f);
	
	anim.init(500);
	anim.setLoopInterval(5, 6, 300, true);
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "macgyver1.bmp", PATH_PREFIX "macgyver1a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "macgyver2.bmp", PATH_PREFIX "macgyver2a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "macgyver3.bmp", PATH_PREFIX "macgyver3a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "macgyver4.bmp", PATH_PREFIX "macgyver4a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "macgyver5.bmp", PATH_PREFIX "macgyver5a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "macgyver6.bmp", PATH_PREFIX "macgyver6a.bmp"));
	
	fade.init(0x0, 300);
}

void Tube::render(SDL_Surface* dest, unsigned int tick) {

	int resx2 = dest->w >> 1;
	int resy2 = dest->h >> 1;

	float rotate = (float)tick * 0.045f;
	float move = (float)tick * 0.26f;

	int x1 = (int)(cos(tick * 0.0005353) * resx2) + resx2;
	int y1 = (int)(sin(10.0f + tick * 0.0006493) * resy2) + resy2;
	int x2 = (int)(cos(14.0f + tick * 0.0009864) * resx2) + resx2;
	int y2 = (int)(sin(tick * 0.0004567) * resy2) + resy2;
								
	mapper.renderDual(dest, x1, y1, x2, y2, (int)(dir * move * 256.0f), (int)(dir * rotate * 256.0f));

#ifndef NO_OVERLAYS
	anim.renderAlphaWithTest(dest, tick);
#endif

	if(tick > getEndTime() - getStartTime() - 550)
		fade.fadeFromDest(dest, tick);
}

void Tube::reset() {
	anim.reset();
}