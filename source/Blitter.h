#ifndef H_BLITTER__
#define H_BLITTER__

#include "GFXHelper.h"

class Blitter {
public:
	Blitter();
	
	void			init(SDL_Surface* texture);
	void			render(SDL_Surface* dest, int dx, int dy, int sx, int sy);
	
	int				getTextureWidth() const;
	int				getTextureHeight() const;
		
private:
	SDL_Surface*	src;
};

#endif