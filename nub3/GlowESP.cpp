#include "Includes.h"

//glow comun

void Glow() {
	for (int i = 0; i <= 32; i++) {
		auto plr = Entidad::getEntityBase(i);
		if (Entidad::getEntTeam(plr) != LocalPlayer::getLocalTeam()) {
			auto gObj = Entidad::getGlowObj();
			auto gIdx = Entidad::getGlowIndex(plr);

			Entidad::glowEsp(gObj, gIdx, 255, 0, 0, 200);
			Sleep(1);
		}
	}
	
}

