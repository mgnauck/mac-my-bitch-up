#include "DisplacementMapper.h"
#include "GFXHelper.h"

DisplacementMapper::DisplacementMapper() : texture(0) {
	// could do something here
}

DisplacementMapper::~DisplacementMapper() {
	displacement.clear();
	gradient.clear();
}

void DisplacementMapper::init(int lw, int lh, SDL_Surface* tex) {

	lutWidth = lw;
	lutHeight = lh;
	texture = tex;

	displacement.reserve(lutWidth * lutHeight);
	gradient.reserve(lutWidth * lutHeight);
}

void DisplacementMapper::render(SDL_Surface* dest, int lutx, int luty, int step, int rot) {
	
	lockSurface(dest);
	lockSurface(texture);
	
	unsigned int destWidth	= dest->pitch >> 2;
	unsigned int texWidth	= texture->pitch >> 2;
	unsigned int posOfs		= lutWidth * luty + lutx;
	
	// blockwise
	for(int y=0; y<dest->h / BLOCK_SIZE_Y; y++) {
		for(int x=0; x<dest->w / BLOCK_SIZE_X; x++) {
			
			// calc some ofsets
			unsigned int lutOfs		= lutWidth * (y * BLOCK_SIZE_Y) + x * BLOCK_SIZE_X;
			unsigned int ofs		= destWidth * (y * BLOCK_SIZE_Y) + x * BLOCK_SIZE_X;
			unsigned int lutLine	= 0;
			unsigned int line		= 0;
			
			// loop through all pixels in block
			for(int j=0; j<BLOCK_SIZE_Y; j++) {
				for(int i=0; i<BLOCK_SIZE_X; i++) {
					
					// look up displacement + luminance
					unsigned int	ofs2	= posOfs + lutOfs + lutLine + i;
					unsigned int	d		= displacement[ofs2];
					unsigned char	illum	= Blending::multiplicativeByte(gradient[ofs2], gradient[ofs2]);		// quadr falloff :)
					
					// displacement -> y = distance (word 1), x = angle (word 0)
					// blend value from texture with luminance value
					((unsigned int*)dest->pixels)[ofs + line + i] =
						Blending::multiplicativeByteInt(
							illum,
							((unsigned int*)texture->pixels)[texWidth * ((((d >> 16) + step) & 0xffff) >> 8) + (((rot + (d & 0xffff)) >> 8) & 0xff)]

						);
				}
				lutLine += lutWidth;
				line += destWidth;
			}
		}
	}
	
	unlockSurface(texture);
	unlockSurface(dest);
}

void DisplacementMapper::renderDual(SDL_Surface* dest, int lutx1, int luty1, int lutx2, int luty2, int step, int rot) {
	
	lockSurface(dest);
	lockSurface(texture);
	
	unsigned int destWidth	= dest->pitch >> 2;
	unsigned int texWidth	= texture->pitch >> 2;
	unsigned int posOfs1	= lutWidth * luty1 + lutx1;
	unsigned int posOfs2	= lutWidth * luty2 + lutx2;
	
	// blockwise
	for(int y=0; y<dest->h / BLOCK_SIZE_Y; y++) {
		for(int x=0; x<dest->w / BLOCK_SIZE_X; x++) {
			
			// calc some ofsets
			unsigned int lutOfs		= lutWidth * (y * BLOCK_SIZE_Y) + x * BLOCK_SIZE_X;
			unsigned int ofs		= destWidth * (y * BLOCK_SIZE_Y) + x * BLOCK_SIZE_X;
			unsigned int lutLine	= 0;
			unsigned int line		= 0;
			
			// loop through all pixels in block
			for(int j=0; j<BLOCK_SIZE_Y; j++) {
				for(int i=0; i<BLOCK_SIZE_X; i++) {
					
					// look up displacement + luminance
					unsigned int	ofs21	= posOfs1 + lutOfs + lutLine + i;
					unsigned int	ofs22	= posOfs2 + lutOfs + lutLine + i;
					unsigned int	d		= displacement[ofs21] - displacement[ofs22];
					unsigned char	illum	= Blending::multiplicativeByte(gradient[ofs21], gradient[ofs22]);
					
					illum = Blending::multiplicativeByte(illum, illum);
															
					// displacement -> y = distance (word 1), x = angle (word 0)
					// blend value from texture with luminance value
					((unsigned int*)dest->pixels)[ofs + line + i] =
					Blending::multiplicativeByteInt(
							illum,
							((unsigned int*)texture->pixels)[texWidth * ((((d >> 16) + step) & 0xffff) >> 8) + (((rot + (d & 0xffff)) >> 8) & 0xff)]
					);
				}
				lutLine += lutWidth;
				line += destWidth;
			}
		}
	}
	
	unlockSurface(texture);
	unlockSurface(dest);
}