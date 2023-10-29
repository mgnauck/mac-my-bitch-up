#ifndef H_IMAGEHANDLER__
#define H_IMAGEHANDLER__

#include <vector>
#include <string>
#include "GFXHelper.h"

class ImageHandler {
public:
	ImageHandler(SDL_Surface* destinationSurfaceFormat);
	~ImageHandler();
	
	SDL_Surface*				loadImage(std::string const& name, bool doNotStore = false);
	SDL_Surface*				loadImageWithAlpha(std::string const& texName, std::string const& alphaName);
	SDL_Surface*				createEmptyImage(int w, int h, bool fill = true, unsigned int c = 0xff000000);
	SDL_Surface*				createEmptyImage(SDL_Surface* dest, int w, int h, bool fill = true, unsigned int c = 0xff000000);
	
	SDL_Surface*				getImage(int n);
	
private:
	std::vector<SDL_Surface*>	images;
	SDL_Surface*				destination;
};

#endif