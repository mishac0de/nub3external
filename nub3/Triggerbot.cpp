#include "Includes.h"

//triggerbot con delay para cada arma, me rompi la cabeza escribiendo cada tiempo para que funcione bien

struct Tbvars {
	int tbDelay;
	int myWeaponID;
	bool isScoped;
}tbval;

struct vector {
	float x, y, z;
};

void setTBDelay(float distance) {
	float delay;
	switch (tbval.myWeaponID) {
	case 1:
		delay = 0.1; //DESERT EAGLE
		break;
	case 2:
		delay = 1.5; //BERRETAS
		break;
	case 3:
		delay = 1; //FIVE-SEVEN
		break;
	case 4:
		delay = 1;
		break;
	case 8:
		delay = 3;
		break;
	case 10:
		delay = 3;
		break;
	case 11:
		delay = 0.5;
		break;
	case 13:
		delay = 3.6;
		break;
	case 14:
		delay = 5;
		break;
	case 16:
		delay = 3.3;
		break;
	case 17:
		delay = 1.5;
		break;
	case 19:
		delay = 1.5;
		break;
	case 23:
		delay = 1.5;
		break;
	case 24:
		delay = 1.5;
		break;
	case 25:
		delay = 0.2;
		break;
	case 26:
		delay = 1.5;
		break;
	case 27:
		delay = 0.2;
		break;
	case 28:
		delay = 1.5;
		break;
	case 29:
		delay = 0.2;
		break;
	case 30:
		delay = 1;
		break;
	case 31:
		delay = 0.1;
		break;
	case 32:
		delay = 1;
		break;
	case 33:
		delay = 1.5;
		break;
	case 34:
		delay = 1.5;
		break;
	case 35:
		delay = 0.2;
		break;
	case 36:
		delay = 2;
		break;
	case 38:
		delay = 0.4;
		break;
	case 39:
		delay = 3;
		break;
	case 61:
		delay = 2;
		break;
	case 63:
		delay = 2;
		break;
	case 60:
		delay = 3; //M4A1S
		break;
	case 7:
		delay = 3.3; //AK-47
		break;
	case 40:
		delay = 0.1; //SCOUT
		break;
	case 9:
		delay = 0.1; //AWP
		break;

	default: delay = 0;
	}
	tbval.tbDelay = delay * distance;
}

bool checkIfScoped() {
	tbval.isScoped = readMem<bool>(LocalPlayer::getLocalPlayer() + netvars::m_bIsScoped);
	return 0;
}

void getMyWeapon() {
	int weapon = readMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_hActiveWeapon);
	//between weaponchange it doesn't work
	int weaponEntity = readMem<int>(gameModule + signatures::dwEntityList + ((weapon & 0xFFF) - 1) * 0x10);

	if (weaponEntity != NULL) {
		tbval.myWeaponID = readMem<int>(weaponEntity + netvars::m_iItemDefinitionIndex);

	}
}

float getDistance(DWORD inCross) {
	vector myLocation = readMem<vector>(LocalPlayer::getLocalPlayer() + netvars::m_vecOrigin);
	vector entLocation = readMem<vector>(inCross + netvars::m_vecOrigin);

	return sqrt(pow(myLocation.x - entLocation.x, 2) + pow(myLocation.y - entLocation.y, 2) + pow(myLocation.z - entLocation.z, 2)) * 0.0254;


}

void trigger()
{
	auto xhair = LocalPlayer::getLocalCrossID();
	if (xhair > -1) {
		auto inCross = Entidad::getEntityBase(xhair - 1);

		if (Entidad::getEntTeam(inCross) != LocalPlayer::getLocalTeam()) {
			float distance = getDistance(inCross);
			getMyWeapon();
			setTBDelay(distance);
			checkIfScoped();
			if (tbval.myWeaponID == 40 || tbval.myWeaponID == 9 || tbval.myWeaponID == 11 || tbval.myWeaponID == 38) {
				if (tbval.isScoped) {
					Sleep(tbval.tbDelay);
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Sleep(25);
					mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
				}
				else {

				}

			}
			if (tbval.myWeaponID != 40 && tbval.myWeaponID != 9 && tbval.myWeaponID != 11 && tbval.myWeaponID != 38) {
				Sleep(tbval.tbDelay);
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
				Sleep(25);
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			}
		}
	}
}

