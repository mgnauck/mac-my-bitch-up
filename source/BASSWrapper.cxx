#include "BASSWrapper.h"
#include "Defines.h"
#include <iostream>

BASSWrapper::BASSWrapper() : streamHandle(0), moduleHandle(0) {
}

BASSWrapper::~BASSWrapper() {
#ifdef DEBUG_OUT
	std::cout << "trying to kill audio ressources" << std::endl;
#endif
	BASS_Free();
}

bool BASSWrapper::init() {
	
	if(HIWORD(BASS_GetVersion()) != BASSVERSION) {
		std::cout << "wrong bass version" << std::endl;
		return false;
	}
	
	if(!BASS_Init(-1, 44100, 0, 0, 0)) {

		std::cout << "can't init proper sound device! trying no-sound.." << std::endl;
		
		if(!BASS_Init(0, 44100, 0, 0, 0)) {			// wtf!?! can not fail..
			std::cout << "dude, wtf? no no-sound!?!" << std::cout;
			return false;
		}
	}
	
#ifdef DEBUG_OUT
	std::cout << "audio device: " << BASS_GetDeviceDescription(BASS_GetDevice()) << std::endl;	
#endif

	return true;
}

bool BASSWrapper::loadStream(std::string const& name) {

#ifdef DEBUG_OUT
	std::cout << "trying to load: " << name << " ";
#endif
	
	streamHandle = BASS_StreamCreateFile(FALSE, name.c_str(), 0, 0, 0);
	
	if(!streamHandle) {
		std::cout << "- failed!" << std::endl;
		return false;
	}
	
#ifdef DEBUG_OUT
	std::cout << "- ok!" << std::endl;
#endif

	return true;
}

bool BASSWrapper::loadModule(std::string const& name) {

#ifdef DEBUG_OUT
	std::cout << "trying to load: " << name << " ";
#endif
	
	moduleHandle = BASS_MusicLoad(FALSE, name.c_str(), 0, 0, BASS_MUSIC_RAMP, 0);
	
	if(!moduleHandle) {
		std::cout << "- failed!" << std::endl;
		return false;
	}

#ifdef DEBUG_OUT
	std::cout << "- ok!" << std::endl;
#endif

	return true;
}

void BASSWrapper::playStream(bool restart) {
	
	BASS_Start();	
	BASS_ChannelPlay(streamHandle, restart);
}

void BASSWrapper::playModule(bool restart) {
	
	BASS_Start();
	BASS_ChannelPlay(moduleHandle, restart);
}

void BASSWrapper::pauseStream() {
	BASS_ChannelPause(streamHandle);
}

void BASSWrapper::pauseModule() {
	BASS_ChannelPause(moduleHandle);
}

int BASSWrapper::getRow() const {
	DWORD dw = BASS_MusicGetOrderPosition(moduleHandle);
	return HIWORD(dw);
}

int BASSWrapper::getOrder() const {
	DWORD dw = BASS_MusicGetOrderPosition(moduleHandle);
	return LOWORD(dw);
}

int BASSWrapper::getPosition() const {
	return BASS_StreamGetFilePosition(streamHandle, BASS_FILEPOS_CURRENT);
}
