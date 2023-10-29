#include "Concentrical.h"
#include "Defines.h"
#include <cmath>

Concentrical::Concentrical(ImageHandler& imageHandler, SDL_Surface* dest)
	: anim1(), anim2(), anim3(), phase(0), ovlNum(0), fade() {
	
	blitter[0].init(imageHandler.loadImage(PATH_PREFIX "cccatch11.bmp"));
	blitter[1].init(imageHandler.loadImage(PATH_PREFIX "cccatch12.bmp"));
	blitter[2].init(imageHandler.loadImage(PATH_PREFIX "cccatch21.bmp"));
	blitter[3].init(imageHandler.loadImage(PATH_PREFIX "cccatch22.bmp"));
	blitter[4].init(imageHandler.loadImage(PATH_PREFIX "cccatch31.bmp"));
	blitter[5].init(imageHandler.loadImage(PATH_PREFIX "cccatch32.bmp"));

	tempSurface = imageHandler.createEmptyImage(dest->w, dest->h, false);

	anim1.init(200);
	anim1.setLoopInterval(1, 7, 200, true);
	anim1.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim1_1.bmp", PATH_PREFIX "anim1_1a.bmp"));
	anim1.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim1_2.bmp", PATH_PREFIX "anim1_2a.bmp"));
	anim1.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim1_3.bmp", PATH_PREFIX "anim1_3a.bmp"));	
	anim1.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim1_4.bmp", PATH_PREFIX "anim1_4a.bmp"));	
	anim1.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim1_5.bmp", PATH_PREFIX "anim1_5a.bmp"));
	anim1.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim1_6.bmp", PATH_PREFIX "anim1_6a.bmp"));
	anim1.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim1_7.bmp", PATH_PREFIX "anim1_7a.bmp"));
				
	anim2.init(170);
	anim2.setLoopInterval(1, 8, 170, true);
	anim2.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim2_1.bmp", PATH_PREFIX "anim2_1a.bmp"));
	anim2.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim2_2.bmp", PATH_PREFIX "anim2_2a.bmp"));
	anim2.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim2_3.bmp", PATH_PREFIX "anim2_3a.bmp"));
	anim2.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim2_4.bmp", PATH_PREFIX "anim2_4a.bmp"));
	anim2.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim2_5.bmp", PATH_PREFIX "anim2_5a.bmp"));
	anim2.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim2_6.bmp", PATH_PREFIX "anim2_6a.bmp"));
	anim2.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim2_7.bmp", PATH_PREFIX "anim2_7a.bmp"));
	anim2.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim2_8.bmp", PATH_PREFIX "anim2_8a.bmp"));
	
	anim3.init(150);
	anim3.setLoopInterval(1, 8, 150, true);
	anim3.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim3_1.bmp", PATH_PREFIX "anim3_1a.bmp"));
	anim3.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim3_2.bmp", PATH_PREFIX "anim3_2a.bmp"));
	anim3.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim3_3.bmp", PATH_PREFIX "anim3_3a.bmp"));
	anim3.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim3_4.bmp", PATH_PREFIX "anim3_4a.bmp"));
	anim3.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim3_5.bmp", PATH_PREFIX "anim3_5a.bmp"));
	anim3.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim3_6.bmp", PATH_PREFIX "anim3_6a.bmp"));
	anim3.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim3_7.bmp", PATH_PREFIX "anim3_7a.bmp"));
	anim3.addFrame(imageHandler.loadImageWithAlpha(PATH_PREFIX "anim3_8.bmp", PATH_PREFIX "anim3_8a.bmp"));
	
	fade.init(0xffffff, 1250);
}

void Concentrical::render(SDL_Surface* dest, unsigned int tick) {

	int w		= dest->w >> 1;
	int h		= dest->h >> 1;
	
	int xoff	= abs(dest->w - blitter[0].getTextureWidth()) >> 1;
	int yoff	= abs(dest->h - blitter[0].getTextureHeight()) >> 1;
		
	int x1 = (int)(sin(tick * 0.001442) * (float)xoff) + w;
	int y1 = (int)(cos(tick * 0.002627) * (float)yoff) + h;

	int x2 = (int)(sin(tick * 0.002135) * (float)xoff) + w;
	int y2 = (int)(cos(tick * 0.001789) * (float)yoff) + h;
	
	if(tick > 11000 && tick < 17000) {
		phase = 1;
		ovlNum = 1;
	}

	if(tick > 17000 && tick < 23000) {
		phase = 2;
		ovlNum = 2;
	}
		
	if(tick > 23000 && tick < 29000) {
		phase = 1;
		ovlNum = 0;
	}

	if(tick > 29000) {
		phase = 0;
		ovlNum = 1;
	}
		
	blitter[(phase * 2) + 0].render(dest, x1, y1, blitter[0].getTextureWidth() >> 1, blitter[0].getTextureHeight() >> 1);	
	blitter[(phase * 2) + 1].render(tempSurface, x2, y2, blitter[0].getTextureWidth() >> 1, blitter[0].getTextureHeight() >> 1);
	
	blitSurfaceAdditive(dest, tempSurface);

#ifndef NO_OVERLAYS
	if(ovlNum == 0)
		anim1.renderAlphaWithTest(dest, tick);
	if(ovlNum == 1)
		anim2.renderAlphaWithTest(dest, tick);
	if(ovlNum == 2)
		anim3.renderAlphaWithTest(dest, tick);
#endif

	if(tick < 2000)
		fade.fadeToDest(dest, tick);
}