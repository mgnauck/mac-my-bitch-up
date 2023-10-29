#ifndef H_EFFECTHANDLER__
#define H_EFFECTHANDLER__

#include "Effect.h"
#include "GFXHelper.h"
#include <vector>

class Range {
public:
	Range(int s, int e) : start(s), end(e) {}
	int	getDuration() { return end - start; }
	
	int	start;
	int	end;
};

class EffectHandler {
public:
	EffectHandler();
	~EffectHandler();
		
	void addEffect(Effect* effect, int startTime, int endTime);
	bool render(SDL_Surface* dest, int tick);
	
	void resetEffects();
	
private:
	std::vector<std::pair<Effect*, Range> > effects;
};

typedef std::vector<std::pair<Effect*, Range> > EffectList;

#endif