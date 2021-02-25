#include "Includes.h"

//este fov changer tambien, checkea por lo menos si estas scopeando porque sino es desagradable, recomiendo no activarlo

int FOVValue;
bool isScoped;
int weaponID;

void fovchange() {
	FOVValue = readMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_iDefaultFOV);
	isScoped = readMem<bool>(LocalPlayer::getLocalPlayer() + netvars::m_bIsScoped);
	if (!isScoped && weaponID != 9) {
		writeMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_iDefaultFOV, 110);
	} if (weaponID == 9 && isScoped) {
		writeMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_iDefaultFOV, 90);
	}

}

void getWeapon() {
	int weapon = readMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_hActiveWeapon);
	//between weaponchange it doesn't work
	int weaponEntity = readMem<int>(gameModule + signatures::dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);

	if (weaponEntity != NULL) {
		weaponID = readMem<int>(weaponEntity + netvars::m_iItemDefinitionIndex);

	}
}

void fovreset() {
	while (FOVValue == 110) {
		for (int i = 0; i < 1000; i++) {
			writeMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_iDefaultFOV, 90);
		}
		FOVValue = readMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_iDefaultFOV);
	}
}

