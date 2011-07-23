#include "CAbstraktOptions.h"

CAbstraktOptions::CAbstraktOptions() {
	// Standardwerte
	setFullscreen(true);
}

enum CAbstraktOptions::E_Emulator CAbstraktOptions::getEmulator() {
	return prEmuType;
}

void CAbstraktOptions::setEmulator(enum CAbstraktOptions::E_Emulator Val) {
	prEmuType=Val;
	if(Val==GNUBOY) setEmuCommand("sdlgnuboy");
	else setEmuCommand("visualboyadvance");
}


bool CAbstraktOptions::getFullscreen() const {
	return prFullscreen;
}


void CAbstraktOptions::setFullscreen(const bool Val) {
	prFullscreen=Val;
}


QString CAbstraktOptions::getEmuCommand() {
	return prEmuCommand;
}

void CAbstraktOptions::setEmuCommand(const QString& Val) {
	prEmuCommand=Val;
}
