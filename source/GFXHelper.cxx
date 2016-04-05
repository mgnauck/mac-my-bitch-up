#include "GFXHelper.h"
#include "Defines.h"
#include <iostream>

void setWindowTitle(std::string const& name) {
	
	std::string iconName("");
	SDL_WM_SetCaption(name.c_str(), iconName.c_str());		// icon name ..
}

void lockSurface(SDL_Surface* s) {
	if(SDL_MUSTLOCK(s))
		if(SDL_LockSurface(s) < 0)
			return;
}

void unlockSurface(SDL_Surface* s) {
	if(SDL_MUSTLOCK(s))
		SDL_UnlockSurface(s);
}

void clearSurface(SDL_Surface* dest, unsigned int col) {
	lockSurface(dest);
	SDL_FillRect(dest, 0, col);
	unlockSurface(dest);
}

void setPixel(SDL_Surface* s, int x, int y, unsigned int c) {
	((unsigned int*)s->pixels)[(s->pitch >> 2) * y + x] = c;
}

unsigned int getPixel(SDL_Surface* s, int x, int y) {
	return ((unsigned int*)s->pixels)[(s->pitch >> 2) * y + x];
}

void blitSurface(SDL_Surface* dest, SDL_Surface* tex, int x, int y) {
	
	int pitchDest	= dest->pitch >> 2;
	int pitchTex	= tex->pitch >> 2;
	
	int ofsDest		= pitchDest * y + x;
	int ofsTex		= 0;
	
	lockSurface(tex);
	lockSurface(dest);
	
	for(int j=0; j<tex->h; j++) {
		
		if((y + j) < dest->h && (y + j) >= 0) {
			
			for(int i=0; i<tex->w; i++) {
				
				if((x + i) < dest->w && (x + i) >= 0)
					((unsigned int*)dest->pixels)[ofsDest + i] = ((unsigned int*)tex->pixels)[ofsTex + i];
				
			}
		}
		
		ofsDest += pitchDest;
		ofsTex += pitchTex;
	}
	
	unlockSurface(tex);
	unlockSurface(dest);
}

void blitSurfaceAlpha(SDL_Surface* dest, SDL_Surface* tex, int x, int y) {
	
	int pitchDest	= dest->pitch >> 2;
	int pitchTex	= tex->pitch >> 2;
	
	int ofsDest		= pitchDest * y + x;
	int ofsTex		= 0;
	
	lockSurface(tex);
	lockSurface(dest);

	for(int j=0; j<tex->h; j++) {
		
		if((y + j) < dest->h && (y + j) >= 0) {
			
			for(int i=0; i<tex->w; i++) {
				
				if((x + i) < dest->w && (x + i) >= 0)
					((unsigned int*)dest->pixels)[ofsDest + i] =
						Blending::alpha(
							((unsigned int*)tex->pixels)[ofsTex + i],
							((unsigned int*)dest->pixels)[ofsDest + i]
						);
				
			}
		}
		
		ofsDest += pitchDest;
		ofsTex += pitchTex;
	}
	
	unlockSurface(tex);
	unlockSurface(dest);
}

void blitSurfaceAlphaWithTest(SDL_Surface* dest, SDL_Surface* tex, int x, int y) {
	
	int pitchDest	= dest->pitch >> 2;
	int pitchTex	= tex->pitch >> 2;
	
	int ofsDest		= pitchDest * y + x;
	int ofsTex		= 0;
	
	lockSurface(tex);
	lockSurface(dest);

	for(int j=0; j<tex->h; j++) {
		
		if((y + j) < dest->h && (y + j) >= 0) {
			
			for(int i=0; i<tex->w; i++) {
				
				if((x + i) < dest->w && (x + i) >= 0)
					((unsigned int*)dest->pixels)[ofsDest + i] =
						Blending::alphaWithTest(
							((unsigned int*)tex->pixels)[ofsTex + i],
							((unsigned int*)dest->pixels)[ofsDest + i]
						);
				
			}
		}
		
		ofsDest += pitchDest;
		ofsTex += pitchTex;
	}
	
	unlockSurface(tex);
	unlockSurface(dest);
}

void blitSurfaceAverage(SDL_Surface* dest, SDL_Surface* tex, int x, int y) {
	
	int pitchDest	= dest->pitch >> 2;
	int pitchTex	= tex->pitch >> 2;
	
	int ofsDest		= pitchDest * y + x;
	int ofsTex		= 0;
	
	lockSurface(tex);
	lockSurface(dest);

	for(int j=0; j<tex->h; j++) {
		
		if((y + j) < dest->h && (y + j) >= 0) {
			
			for(int i=0; i<tex->w; i++) {
				
				if((x + i) < dest->w && (x + i) >= 0)
					((unsigned int*)dest->pixels)[ofsDest + i] =
						Blending::average(
							((unsigned int*)tex->pixels)[ofsTex + i],
							((unsigned int*)dest->pixels)[ofsDest + i]
						);
				
			}
		}
		
		ofsDest += pitchDest;
		ofsTex += pitchTex;
	}
	
	unlockSurface(tex);
	unlockSurface(dest);
}


void blitSurfaceAdditive(SDL_Surface* dest, SDL_Surface* tex, int x, int y) {
	
	int pitchDest	= dest->pitch >> 2;
	int pitchTex	= tex->pitch >> 2;
	
	int ofsDest		= pitchDest * y + x;
	int ofsTex		= 0;

	lockSurface(tex);
	lockSurface(dest);
	
	for(int j=0; j<tex->h; j++) {
		
		if((y + j) < dest->h && (y + j) >= 0) {
			
			for(int i=0; i<tex->w; i++) {
				
				if((x + i) < dest->w && (x + i) >= 0)
					((unsigned int*)dest->pixels)[ofsDest + i] =
						Blending::additive(
							((unsigned int*)tex->pixels)[ofsTex + i],
							((unsigned int*)dest->pixels)[ofsDest + i]
						);
				
			}
		}
		
		ofsDest += pitchDest;
		ofsTex += pitchTex;
	}
	
	unlockSurface(tex);
	unlockSurface(dest);
}