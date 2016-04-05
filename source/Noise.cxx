#include "Noise.h"

Noise::Noise() : noiseAnim() {}

void Noise::init(ImageHandler& imageHandler, int count, int w, int h, unsigned char maxStrength, int ticks) {

	noiseAnim.init(20, true);

	for(int i=0; i<count; i++) {
	
		SDL_Surface* surf = imageHandler.createEmptyImage(w, h, false);

		lockSurface(surf);

		for(int j=0; j<surf->h; j++)
			for(int i=0; i<surf->w; i++) {
				unsigned char c = rand() % maxStrength;
				((unsigned int*)surf->pixels)[(surf->pitch >> 2) * j + i] = (c << 24) | (c << 16) | (c << 8) | c;
			}
			
		noiseAnim.addFrame(surf);
		unlockSurface(surf);
	}
}

void Noise::render(SDL_Surface* dest, unsigned int ticks) {
	noiseAnim.render(dest, ticks);
}

void Noise::renderAlpha(SDL_Surface* dest, unsigned int ticks) {
	noiseAnim.renderAlpha(dest, ticks);
}

void Noise::renderAdditive(SDL_Surface* dest, unsigned int ticks) {
	noiseAnim.renderAdditive(dest, ticks);
}