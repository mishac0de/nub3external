#include "Includes.h"

//noflash comun

void NoFlash() {

	if (LocalPlayer::getLocalFlashDur() > 0) {
		writeMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_flFlashDuration, 0);
		
	}

}

