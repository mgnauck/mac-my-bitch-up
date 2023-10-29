#include "EffectHandler.h"
#include "GFXHelper.h"

EffectHandler::EffectHandler() {
	effects.reserve(10);
}

EffectHandler::~EffectHandler() {
	effects.clear();
}

void EffectHandler::addEffect(Effect* effect, int startTime, int endTime) {
	effect->setActiveTimeInterval(startTime, endTime);
	effects.push_back(std::pair<Effect*, Range>(effect, Range(startTime, endTime)));
}

bool EffectHandler::render(SDL_Surface* dest, int tick) {

	bool running = false;

	// find actual effect
	for(EffectList::iterator it=effects.begin(); it!=effects.end(); ++it) {
		if((tick >= it->second.start) && (tick < it->second.end)) {
			it->first->render(dest, tick - it->second.start);
			running = true;
		}
	}
	
	return running;
}

void EffectHandler::resetEffects() {
	for(EffectList::iterator it=effects.begin(); it!=effects.end(); ++it)
		it->first->reset();
}