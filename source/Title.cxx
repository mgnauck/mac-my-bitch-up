#include "Title.h"
#include "Blitter.h"
#include "Defines.h"
#include <cmath>

Title::Title(ImageHandler& imageHandler) : anim(), noise(), fade() {

	noise.init(imageHandler, 10, RESX, RESY, 0x40, 700);
	
	anim.init(250);
	anim.setLoopInterval(1, 2, 250, false);
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "title1.bmp", PATH_PREFIX "title1a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "title2.bmp", PATH_PREFIX "title2a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "title3.bmp", PATH_PREFIX "title3a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "title4.bmp", PATH_PREFIX "title4a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "title5.bmp", PATH_PREFIX "title5a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "title6.bmp", PATH_PREFIX "title6a.bmp"));
	
	fade.init(0x0, 2000);
}

void Title::render(SDL_Surface* dest, unsigned int tick) {

	clearSurface(dest, 0xff222222);
	noise.renderAlpha(dest, tick);
	
	if(tick < 4000)
		fade.fadeToDest(dest, tick);

#ifndef NO_OVERLAYS	

	if(tick > 11100 && tick < 17000)
		anim.setLoopInterval(3, 4, 250, false);

	if(tick > 17000)
		anim.setLoopInterval(5, 6, 250, false);

	if(tick > 5500)
		anim.renderAlphaWithTest(dest, tick);

#endif
}

void Title::reset() {
	anim.reset();
	fade.reset();
}