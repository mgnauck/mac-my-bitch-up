#ifndef H_SDLGLWRAPPER__
#define H_SDLGLWRAPPER__

#include <string>
#include "Defines.h"
#ifdef OS_X
	#include "SDL.h"
#endif
#ifdef WIN32
	#include "sdl/include/SDL.h"
#endif

class SDLWrapper {
public:
	SDLWrapper(std::string const& t, int w, int h, bool full = false);
	~SDLWrapper();
	
	bool				init();
	bool				active();
	void				swapBuffers() const;
	
	SDL_Surface*		getSurface() const;
	int					getWidth() const;
	int					getHeight() const;
	bool				getFullscreen() const;
	
	char*				getError() const;
	unsigned int		getTicks() const;
	float				pollFPS();
	
	bool				getKeyHit() const;
	unsigned int		getKey() const;
	
private:
	SDL_Surface*		surface;
	int					width;
	int					height;
	bool				fullscreen;
	std::string			title;
	
	float				fps;
	unsigned int		lastTicks;
	unsigned int		frames;
	
	bool				keyhit;
	unsigned int		key;
};

#endif