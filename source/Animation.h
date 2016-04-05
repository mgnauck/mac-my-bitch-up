#ifndef H_ANIMATION__
#define H_ANIMATION__

#include <vector>
#include "GFXHelper.h"

class Animation {
public:
	Animation();
	~Animation();
	
	void						init(int ticksPerFrameBeforeLoop, bool loopAnim = true);
	void						addFrame(SDL_Surface* pic);
	void						setLoopInterval(int start, int end, int ticksPerFrameWhileLoop, bool pingPongLoop = false);

	void						render(SDL_Surface* dest, unsigned int tick);
	void						renderAlpha(SDL_Surface* dest, unsigned int tick);
	void						renderAlphaWithTest(SDL_Surface* dest, unsigned int tick);
	void						renderAdditive(SDL_Surface* dest, unsigned int tick);

	void						reset();
	void						pause();
	void						resume();
	
private:
	void						play(unsigned int tick);
	
	unsigned int				frameTimeBeforeLoop;
	unsigned int				frameTimeWhileLoop;
	unsigned int				loopStart;
	unsigned int				loopEnd;
	bool						pingPong;
	
	std::vector<SDL_Surface*>	frames;
	
	unsigned int				actFrame;
	unsigned int				lastTick;
	bool						loop;
	bool						ping;
	bool						resetAnim;
	bool						noInterval;
	bool						looping;
	bool						paused;
};

#endif