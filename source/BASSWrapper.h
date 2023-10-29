#ifndef H_BASSWRAPPER__
#define H_BASSWRAPPER__

#include <string>
#include "Defines.h"
#ifdef OS_X
	#include "bass.h"
#endif
#ifdef WIN32
	#include "bass/bass.h"
#endif

class BASSWrapper {
public:
	BASSWrapper();
	~BASSWrapper();
	
	bool	init();

	bool	loadStream(std::string const& name);
	bool	loadModule(std::string const& name);
	
	void	playStream(bool restart = false);
	void	playModule(bool restart = false);
	void	pauseStream();
	void	pauseModule();
	
	int		getRow() const;
	int		getOrder() const;
	int		getPosition() const;	// stream
	
private:
	HSTREAM streamHandle;
	HMUSIC	moduleHandle;
};


#endif