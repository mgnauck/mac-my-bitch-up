#include "Blitter.h"
#include <iostream>
#include "Constants.h"

Blitter::Blitter() : src(0) {}

void Blitter::init(SDL_Surface* texture) {
	src = texture;
}

void Blitter::render(SDL_Surface* dst, int dx, int dy, int sx, int sy) {

	lockSurface(dst);
	lockSurface(src);

	clearSurface(dst, 0xff);
	
	// drunk'n'stoned c stlyee!!1
	int sw = src->pitch >> 2;	
	int dw = dst->pitch >> 2;

	int sl = sx;
	int sr = src->w - sx;
	int st = sy;
	int sb = src->h - sy;
	
	int dl = dx;
	int dr = dst->w - dx;
	int dt = dy;
	int db = dst->h - dy;

	int l = sl < dl ? sl : dl; //std::min(sl, dl);			// sucky vc6 stl implementation
	int r = sr < dr ? sr : dr; //std::min(sr, dr);	
	int t = st < dt ? st : dt; //std::min(st, dt);
	int b = sb < db ? sb : db; //std::min(sb, db);

	int w = r + l;
	int h = b + t;

	for(int j=0; j<h; j++)
		for(int i=0; i<w; i++)
			((unsigned int*)dst->pixels)[dw * (dt + j - t) + (dl + i - l)] = ((unsigned int*)src->pixels)[sw * (st + j - t) + (sl + i - l)];

	unlockSurface(dst);
	unlockSurface(src);
}

int Blitter::getTextureWidth() const {
	return src->w;
}

int Blitter::getTextureHeight() const {
	return src->h;
}