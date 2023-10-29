#ifndef H_GFXHELPER__
#define H_GFXHELPER__

#include <string>
#include "SDLWrapper.h"
#include "Blending.h"

void			setWindowTitle(std::string const& name);
	
void			lockSurface(SDL_Surface* surface);
void			unlockSurface(SDL_Surface* surface);
	
void			clearSurface(SDL_Surface* dest, unsigned int col = 0xff000000);

void			setPixel(SDL_Surface* s, int x, int y, unsigned int c);
unsigned int	getPixel(SDL_Surface* s, int x, int y);

void			blitSurface(SDL_Surface* dest, SDL_Surface* tex, int x = 0, int y = 0);
void			blitSurfaceAverage(SDL_Surface* dest, SDL_Surface* tex, int x = 0, int y = 0);
void			blitSurfaceAdditive(SDL_Surface* dest, SDL_Surface* tex, int x = 0, int y = 0);
void			blitSurfaceAlpha(SDL_Surface* dest, SDL_Surface* tex, int x = 0, int y = 0);
void			blitSurfaceAlphaWithTest(SDL_Surface* dest, SDL_Surface* tex, int x = 0, int y = 0);

#endif