#ifndef H_EFFECT__
#define H_EFFECT__

#include "GFXHelper.h"

class Effect {
public:
	virtual ~Effect() {}
	
	virtual void	render(SDL_Surface* dest, unsigned int time) { clearSurface(dest, 0xffff0000); }
	virtual void	reset() {}
	
	void			setActiveTimeInterval(unsigned int start, unsigned int end) { startTime = start; endTime = end; }
	unsigned int	getStartTime() const { return startTime; }
	unsigned int	getEndTime() const { return endTime; }
	unsigned int	getDuration() const { return endTime - startTime; }
	
private:
	unsigned int	startTime;
	unsigned int	endTime;
};

#endif