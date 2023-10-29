#include "Break.h"
#include "Defines.h"

#define FADE_TIME 350

Break::Break(ImageHandler& imageHandler) : anim(), noise(), fade() {
	
	anim.init(400, false);
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "breakremote1.bmp", PATH_PREFIX "breakremote1a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "breakremote2.bmp", PATH_PREFIX "breakremote2a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "breakremote3.bmp", PATH_PREFIX "breakremote3a.bmp"));
	
	noise.init(imageHandler, 10, RESX, RESY, 0x40, 700);
	fade.init(0xffffff, FADE_TIME);
}

void Break::render(SDL_Surface* dest, unsigned int tick) {

	clearSurface(dest, 0xff000000);

#ifndef NO_OVERLAYS	
	anim.renderAlphaWithTest(dest, tick);
#endif
	
	if(tick > getDuration() - FADE_TIME)
		fade.fadeFromDest(dest, tick);		// out
	else
		fade.fadeToDest(dest, tick);		// fadein
}

void Break::reset() {
	anim.reset();
}