#ifndef H_FADE__
#define H_FADE__

#include "GFXHelper.h"

class Fade {
public:
	Fade();
	
	void			init(unsigned int col, unsigned int duration);
	void			fadeFromDest(SDL_Surface* dest, unsigned int tick);
	void			fadeToDest(SDL_Surface* dest, unsigned int tick);
	void			reset();
	
private:
	unsigned int	color;
	unsigned int	lastTick;
	bool			startIn;
	bool			startOut;
	float			alpha;
	float			inc;
};

#endif