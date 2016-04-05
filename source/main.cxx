#include "SDLWrapper.h"
#include "BASSWrapper.h"
#include "Defines.h"
#include "ImageHandler.h"
#include "EffectHandler.h"

// effects
#include "Tunnel.h"
#include "Blocks.h"
#include "Tube.h"
#include "Squared.h"
#include "Greets.h"
#include "Concentrical.h"
#include "Title.h"
#include "Break.h"
#include "Last.h"

int main(int argc, char* argv[]) {

	bool fullscreen = true;

	// commandline windowed?
	if((argc > 1) && (strcmp(argv[1], "windowed") == 0))
		fullscreen = false;

	// init grphics
	SDLWrapper graphics(WINDOW_TITLE, RESX, RESY, fullscreen & FULLSCREEN);
	if(!graphics.init())
		return 1;

	// init image handler
	ImageHandler imageHandler(graphics.getSurface());
	
	// init effects
	Tunnel			tunnel(imageHandler);
	Blocks			blocks(imageHandler);
	Tube			tube(imageHandler);
	Squared			squared(imageHandler);
	Greets			greets(imageHandler);
	Concentrical	concentrical(imageHandler, graphics.getSurface());
	Title			title(imageHandler);
	Last			last(imageHandler);
	Break			breakme(imageHandler);

	EffectHandler	effectHandler;
	effectHandler.addEffect(&title, 0, 23250);						// title stuff
	effectHandler.addEffect(&squared, 23250, 46100);				// squared tunnel
	effectHandler.addEffect(&tube, 46100, 68100);					// dual tunnel
	effectHandler.addEffect(&breakme, 68100, 69800);				// kurzer break
	effectHandler.addEffect(&concentrical, 69800, 105750);			// cc catch
	effectHandler.addEffect(&greets, 104750, 128000);				// chill part (greetings)
	effectHandler.addEffect(&blocks, 128000, 150400);				// knatter part ende 1
	effectHandler.addEffect(&tunnel, 150400, 174100);				// knatter part ende 2
	effectHandler.addEffect(&last, 174100, 178050);					// letzten paar sekunden

	// init audio
#ifdef AUDIO
	BASSWrapper audio;
	
	if(!audio.init())
		return 1;
	
	if(!audio.loadStream(PATH_PREFIX "muhmac.mp3"))
		return 1;
#endif
	

#ifdef AUDIO
	audio.playStream();
#endif

	// stuff
	bool	active		= true;
	int		startTick	= SDL_GetTicks();

	// kick it
	while(graphics.active() && active) {

		active = effectHandler.render(graphics.getSurface(), graphics.getTicks() - startTick);
		graphics.swapBuffers();

#ifdef FPS
		char str[512];
		sprintf(str, "fps: %f", graphics.pollFPS());
		setWindowTitle(str);
#endif
	}

	return 0;
}