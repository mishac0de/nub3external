#include "Includes.h"

//radar comun

void radar() {
	for (int i = 0; i <= 32; i++) {
		DWORD entBase = Entidad::getEntityBase(i);
		if (Entidad::getEntTeam(entBase) != LocalPlayer::getLocalTeam()) {
			if (Entidad::getSpotted(entBase) == 0) { //esto significa que tomamos a la entidad como si la estuvieramos viendo, x lo tanto se ve en el radar
				Entidad::setSpotted(entBase, 1);
			}
		}
	}
}