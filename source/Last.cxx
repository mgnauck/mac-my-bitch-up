#include "Last.h"
#include "Defines.h"

Last::Last(ImageHandler& imageHandler) : anim(), noise(), fade() {
	
	anim.init(500, false);
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "bruce.bmp", PATH_PREFIX "brucea.bmp"));
	
	noise.init(imageHandler, 10, RESX, RESY, 0x40, 700);
	
	fade.init(0xffffff, 500);
}

void Last::render(SDL_Surface* dest, unsigned int tick) {

	clearSurface(dest, 0xff111111);
	noise.renderAlpha(dest, tick);
	
#ifndef NO_OVERLAYS	
		anim.renderAlphaWithTest(dest, tick);
#endif

	if(tick < 4000)
		fade.fadeToDest(dest, tick);
}

void Last::reset() {
	anim.reset();
	fade.reset();
}