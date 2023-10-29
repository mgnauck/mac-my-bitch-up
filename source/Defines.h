#ifndef H_DEFINES__
#define H_DEFINES__

#ifndef OS_X
#define OS_X
#endif//*/
/*#ifndef WIN32
#define WIN32
#endif*/

#ifdef OS_X
//#define PATH_PREFIX		"data/"		// makefile
#define PATH_PREFIX		"macbitch.app/Contents/Resources/"		// xcode
#endif

#ifdef WIN32
#define PATH_PREFIX		"data/"
#endif

#define AUDIO
#define DEBUG_OUT
//#define NO_OVERLAYS
//#define FPS

#define RESX			640
#define RESY			400
#define RESX2			(RESX / 2)
#define RESY2			(RESY / 2)
#define WINDOW_TITLE	"mac my bitch up"
#define FULLSCREEN		true


#endif