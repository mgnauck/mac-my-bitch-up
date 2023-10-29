#include "SDLWrapper.h"
#include <iostream>
#include "GFXHelper.h"
#include "Defines.h"

SDLWrapper::SDLWrapper(std::string const& t, int w, int h, bool full) : title(t), width(w), height(h), fullscreen(full) {}

SDLWrapper::~SDLWrapper() {
	SDL_ShowCursor(SDL_ENABLE);
	SDL_Quit();
}

bool SDLWrapper::init() {
	
	// init sdl video
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "unable to init SDL: " << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return false;
	}
	
	// attributes    
	// context
	unsigned int flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	
	if(fullscreen)
		flags |= SDL_FULLSCREEN;
	
    surface = SDL_SetVideoMode (width, height, 0, flags);
	
    if(!surface) {
		std::cout << "unable to init video mode" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}
	
	setWindowTitle(title);
	SDL_ShowCursor(SDL_DISABLE);
	
#ifdef DEBUG_OUT
	std::cout << "demo device: " << title << std::endl;
	std::cout << "graphics device: " << surface->w << "x" << surface->h << ", " << (fullscreen ? "fullscreen" : "windowed") << std::endl;
#endif

	return true;
}

bool SDLWrapper::active() {

	SDL_Event	event;
	bool		res = true;
	
	keyhit = false;
	
	while(SDL_PollEvent(&event)) {
		
		switch(event.type) {

			/*
			case SDL_MOUSEMOTION:
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			*/
			case SDL_KEYDOWN:
				
				keyhit	= true;
				key		= event.key.keysym.sym;
				
				if(key == SDLK_ESCAPE)
					res = false;
				break;

			case SDL_QUIT:
				res = false;
				break;

			default:
				break;
		}
	}
	
	return res;
}

void SDLWrapper::swapBuffers() const {
	//SDL_UpdateRect(surface, 0, 0, width, height);
	SDL_Flip(surface);
}

SDL_Surface* SDLWrapper::getSurface() const {
	return surface;
}

int SDLWrapper::getWidth() const {
	return width;
}

int SDLWrapper::getHeight() const {
	return height;
}

bool SDLWrapper::getFullscreen() const {
	return fullscreen;
}

char* SDLWrapper::getError() const {
	return SDL_GetError();
}

unsigned int SDLWrapper::getTicks() const {
	return SDL_GetTicks();
}

float SDLWrapper::pollFPS() {
	
	frames++;
	
	unsigned int ticks = getTicks() - lastTicks;

	if(ticks > 1000) {
		fps			= frames * 1000.0f / (float)ticks;
		lastTicks	= getTicks();
		frames		= 0;
	}
	
	return fps;
}

bool SDLWrapper::getKeyHit() const {
	return keyhit;
}

unsigned int SDLWrapper::getKey() const {
	return key;
}