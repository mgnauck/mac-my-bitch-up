#include "ImageHandler.h"
#include "Defines.h"
#include <iostream>

//namespace

	ImageHandler::ImageHandler(SDL_Surface* destinationSurfaceFormat) : destination(destinationSurfaceFormat) {
		images.reserve(100);
	}

	ImageHandler::~ImageHandler() {

	#ifdef DEBUG_OUT
		std::cout << "trying to kill image resources" << std::endl;
	#endif

		for(std::vector<SDL_Surface*>::iterator it=images.begin(); it!=images.end(); ++it)
			SDL_FreeSurface(*it);
		images.clear();
	}

	SDL_Surface* ImageHandler::loadImage(std::string const& name, bool doNotStore) {
	
	#ifdef DEBUG_OUT
		std::cout << "trying to load: " << name << " - ";
	#endif

		SDL_Surface* temp		= SDL_LoadBMP(name.c_str());
	
		if(!temp) {
	#ifdef DEBUG_OUT		
			std::cout << "failed!";
	#endif
			return 0;
		}
	
		SDL_Surface* texture	= SDL_ConvertSurface(temp, destination->format, SDL_SWSURFACE);		
		SDL_FreeSurface(temp);
	
		if(!doNotStore)
			// add to imagehandler for deletion later on.. thats why we got it :)
			images.push_back(texture);
		
	#ifdef DEBUG_OUT	
		std::cout << "ok! res: " << texture->w << "x" << texture->h << std::endl;
	#endif
	
		return texture;
	}

	SDL_Surface* ImageHandler::loadImageWithAlpha(std::string const& texName, std::string const& alphaName) {
	
		SDL_Surface* texture	= loadImage(texName);
		SDL_Surface* alpha		= loadImage(alphaName, true);
	
		lockSurface(texture);
		lockSurface(alpha);
	
		for(int j=0; j<texture->h; j++)
			for(int i=0; i<texture->w; i++)
				((unsigned int*)texture->pixels)[(texture->pitch >> 2) * j + i] |= 
					(((unsigned int*)alpha->pixels)[(alpha->pitch >> 2) * j + i] & 0xff) << 24;

		unlockSurface(texture);
		unlockSurface(alpha);

		SDL_FreeSurface(alpha);
	
		return texture;
	}
	

	SDL_Surface* ImageHandler::createEmptyImage(int w, int h, bool fill, unsigned int c) {
	
		SDL_Surface* im = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
	
		if(im)
			clearSurface(im, c);
			
		images.push_back(im);
	
		return im;
	}

	SDL_Surface* ImageHandler::createEmptyImage(SDL_Surface* dest, int w, int h, bool fill, unsigned int c) {
	
		SDL_Surface* temp	= SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_Surface* im		= SDL_ConvertSurface(temp, dest->format, SDL_SWSURFACE);		
	
		SDL_FreeSurface(temp);
		
		if(im)
			clearSurface(im, c);
			
		images.push_back(im);
	
		return im;
	}


	SDL_Surface* ImageHandler::getImage(int n) {
		return images[n];
	}