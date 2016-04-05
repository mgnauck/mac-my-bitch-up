
'mac my bitch up' sourcecode release notes - yey!

this is the source release for bypass 'mac my bitch up' demo. nothing fancy. all the data and some osx xcode 2.4 project files are included.

under osx you can compile the demo via xcode or the classic makefile (included in source directory) way. you will need some sdl distribution installed (either sdl framework from libsdl.org when using xcode or some sdl port like fink). in defines.h you need to set the appropriate data path (points to the bundles /Resource directory right now).

if you want to compile it under windows you have to add adequate sdl and bass distributions yourself and change some defines again.

for the linux lane you'll need to change the audio lib (maybe fmod) as there is afaik no bass distribution available (shouldn't be too hard to accomplish).

i'm not responsible for any damage or whatsoever. take care!

www.unik.de
markus at unik de
