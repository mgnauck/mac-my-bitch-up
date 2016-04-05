#include "Greets.h"
#include "Blitter.h"
#include <cmath>

Greets::Greets(ImageHandler& imageHandler) : anim(), blitter(), fade() {

	blitter.init(imageHandler.loadImage(PATH_PREFIX "scrolly.bmp"));
	
	fade.init(0x0, 2000);
	
	anim.init(1630);
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz1.bmp", PATH_PREFIX "greetz1a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz2.bmp", PATH_PREFIX "greetz2a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz3.bmp", PATH_PREFIX "greetz3a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz4.bmp", PATH_PREFIX "greetz4a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz5.bmp", PATH_PREFIX "greetz5a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz6.bmp", PATH_PREFIX "greetz6a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz7.bmp", PATH_PREFIX "greetz7a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz8.bmp", PATH_PREFIX "greetz8a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz9.bmp", PATH_PREFIX "greetz9a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz10.bmp", PATH_PREFIX "greetz10a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz11.bmp", PATH_PREFIX "greetz11a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz12.bmp", PATH_PREFIX "greetz12a.bmp"));
	anim.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "greetz13.bmp", PATH_PREFIX "greetz13a.bmp"));
}

void Greets::render(SDL_Surface* dest, unsigned int tick) {

	int w		= dest->w >> 1;	
	int h		= dest->h >> 1;	
	int xoff	= abs(dest->w - blitter.getTextureWidth()) >> 1;
	int yoff	= abs(dest->h - blitter.getTextureHeight()) >> 1;
	int x = dest->w - ((int)(cos(tick * 0.00018) * (float)xoff * 1.0f) + w);
	int y = (int)(sin(tick * 0.000342) * (float)yoff * 0.7f) + h;
		
	blitter.render(dest, x, y, blitter.getTextureWidth() >> 1, blitter.getTextureHeight() >> 1);
	
	if(tick < 6000)
		fade.fadeToDest(dest, tick);
		
	if(tick > 2000)
		anim.renderAlphaWithTest(dest, tick);
}

void Greets::reset() {
	anim.reset();
	fade.reset();
}