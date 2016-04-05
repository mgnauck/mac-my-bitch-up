#include "Animation.h"

Animation::Animation() : actFrame(0), ping(true), resetAnim(true), noInterval(true), pingPong(false), loopStart(0), looping(false), paused(false) {}

void Animation::init(int ticksPerFrame, bool loopAnim) {
							
	frameTimeBeforeLoop	= ticksPerFrame;
	frameTimeWhileLoop	= ticksPerFrame;
	loop				= loopAnim;
	
	frames.reserve(10);
}

Animation::~Animation() {
	frames.clear();
}

void Animation::addFrame(SDL_Surface* pic) {

	frames.push_back(pic);
	
	if(noInterval) {
		loopEnd	= (int)frames.size() - 1;
		if(!loop)
			loopStart = loopEnd;
	}
}

void Animation::setLoopInterval(int start, int end, int ticksPerFrameWhileLoop, bool pingPongLoop) {
	loopStart			= start - 1;
	loopEnd				= end - 1;
	frameTimeWhileLoop	= ticksPerFrameWhileLoop;
	noInterval			= false;
	pingPong			= pingPongLoop;
}

void Animation::play(unsigned int tick) {

	if(frames.size() == 0)
		return;

	// safety net
	loopStart	= (loopStart < 0) ? 0 : loopStart;
	loopEnd		= (loopEnd < 0) ? 0 : loopEnd;
	loopEnd		= (loopEnd > ((unsigned int)frames.size() - 1)) ? ((unsigned int)frames.size() - 1) : loopEnd;
	loopStart	= (loopStart > loopEnd) ? loopEnd : loopStart;

	// reset
	if(resetAnim) {
		actFrame	= 0;
		lastTick	= tick;
		resetAnim	= false;
		ping		= true;
	}
	
	if(paused)
		return;
	
	// maybe different ticks..
	unsigned int frameTime = frameTimeBeforeLoop;
	if(looping)
		frameTime = frameTimeWhileLoop;
	
	// decide which frame
	if(tick - lastTick > frameTime) {
		
		lastTick = tick;
		
		if(!pingPong) {
			
			actFrame++;
			if(actFrame > loopEnd) {
				actFrame = loopStart;
				looping = true;
			}
							
		} else {

			if(!((loopStart == loopEnd) && (actFrame == loopEnd))) {
			
				if(ping) {
			
					if(actFrame == loopEnd) {
						looping = true;
						ping = false;
						actFrame--;
					} else
						actFrame++;
					
				} else {					// pong \o/
			
					if(actFrame == loopStart) {
						ping = true;
						actFrame++;
					} else
						actFrame--;
				}
			}
		}
	}
}

void Animation::render(SDL_Surface* dest, unsigned int tick) {

	play(tick);
	blitSurface(dest, frames[actFrame]);
}

void Animation::renderAlpha(SDL_Surface* dest, unsigned int tick) {

	play(tick);
	blitSurfaceAlpha(dest, frames[actFrame]);
}

void Animation::renderAlphaWithTest(SDL_Surface* dest, unsigned int tick) {

	play(tick);
	blitSurfaceAlphaWithTest(dest, frames[actFrame]);
}

void Animation::renderAdditive(SDL_Surface* dest, unsigned int tick) {

	play(tick);
	blitSurfaceAdditive(dest, frames[actFrame]);
}

void Animation::reset() {
	resetAnim = true;
}

void Animation::pause() {
	paused = true;
}

void Animation::resume() {
	paused = false;
}