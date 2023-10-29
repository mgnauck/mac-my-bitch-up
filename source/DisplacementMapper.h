#ifndef H_DISPLACEMENTMAPPER__
#define H_DISPLACEMENTMAPPER__

#include <vector>
#include "SDLWrapper.h"
#include "Constants.h"

#define BLOCK_SIZE_X 20			// depends on resolution!
#define BLOCK_SIZE_Y 20

struct DistanceFunctionRound {
	float operator()(float x, float y) {
		return (float)sqrt(x * x + y * y);
	}
};

struct DistanceFunctionPlanes {
	float operator()(float x, float y) {
		return fabs(x + y);
	}
};

struct DistanceFunctionSquare {
	float operator()(float x, float y) {
		return (fabs(x) > fabs(y)) ? fabs(x) : fabs(y);
	}
};

struct DistanceFunctionInverseSquare {
	float operator()(float x, float y) {
		return (fabs(x) < fabs(y)) ? fabs(x) : fabs(y);
	}
};

struct DistanceFunctionDiamond {
	float operator()(float x, float y) {
		return (fabs(x) + fabs(y)) / 2.0f;
	}
};

class DisplacementMapper {
public:
	DisplacementMapper();
	~DisplacementMapper();
	
	template<typename T>
	void generate(T distanceFunction, float maxZ, float distortionFreq = 0.0f, float distortionAmp = 0.0f, float shapeFreq = 0.0f, float shapeAmp = 0.0f, float distScaleX = 1.0f, float distScaleY = 1.0f) {
	
		for(int j=0; j<lutHeight; j++) {
			for(int i=0; i<lutWidth; i++) {
			
				// x/y dist to center
				float xd	= (float)(i - (lutWidth >> 1)) * distScaleX;
				float yd	= (float)(j - (lutHeight >> 1)) * distScaleY;
			
				// eval distance function
				float dist = distanceFunction(xd, yd);
				
				// hack dist greater zero
				dist = (dist == 0.0f) ? 1.0f : dist;
			
				// distance based luminance [0..255] value
				unsigned char l = (dist > 255.0f) ? 0xff : (unsigned char)dist;
				gradient.push_back(l);
			
				// distort 
				dist = dist + sin(xd * distortionFreq) * distortionAmp + distortionAmp;
				dist = dist + sin(yd * distortionFreq) * distortionAmp + distortionAmp;
				dist = dist + sin(atan2(xd, yd) * shapeFreq) * shapeAmp;
			
				// perspective / z
				dist = maxZ / dist;
			
				// angle in [0..1]
				float angle = atan2(xd, yd) / (2.0f * PI) + 0.5f;
			
				// bring distance and angle to [0..255] and convert to fixed point
				int d = (int)(dist * 256.0f * 256.0f) & 0xffff;
				int a = (int)(angle * 256.0f * 256.0f) & 0xffff;
			
				// store (angle lower word, dist higher word)
				displacement.push_back((d << 16) | a);
			}
		}
	}
	
	void						init(int lw, int lh, SDL_Surface* tex);
	void						render(SDL_Surface* dest, int lutx, int luty, int step, int rot);
	void						renderDual(SDL_Surface* dest, int lutx1, int luty1, int lutx2, int luty2, int step, int rot);
	
protected:
	std::vector<unsigned int>	displacement;
	std::vector<unsigned char>	gradient;
	int							lutWidth;
	int							lutHeight;
	SDL_Surface*				texture;
};

#endif