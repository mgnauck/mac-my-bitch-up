#include "Blocks.h"
#include "Defines.h"

Blocks::Blocks(ImageHandler& imageHandler) : mapper(), anim(), dir(1.0f) {

	mapper.init(RESX * 2, RESY * 2, imageHandler.loadImage(PATH_PREFIX "tex00.bmp"));
	mapper.generate(DistanceFunctionInverseSquare(), 16.0f, 2.0f, 1.0f, 0.0f, 0.0f, 1.0, 1.0f);
	
	noise.init(imageHandler, 10, RESX, RESY, 0x40, 700);
	
	anim.init(450);
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "darthvader1.bmp", PATH_PREFIX "darthvader1a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "empty.bmp", PATH_PREFIX "empty.bmp"));
}

void Blocks::render(SDL_Surface* dest, unsigned int tick) {

	int resx2 = dest->w >> 1;
	int resy2 = dest->h >> 1;

	float move = tick * 0.1096f;

	int x1 = (int)(cos(tick * 0.0004746) * resx2) + resx2;
	int y1 = (int)(cos(tick * 0.0005923) * resy2) + resy2;
								
	mapper.render(dest, x1, y1, (int)(dir * move * 256.0f), 0);
	noise.renderAlpha(dest, tick);
		
#ifndef NO_OVERLAYS
	if(tick > 11500 && tick < 22150)
		anim.renderAlphaWithTest(dest, tick);
#endif
}

void Blocks::reset() {
	anim.reset();
}