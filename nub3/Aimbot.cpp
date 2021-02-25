#include "Includes.h"

//El aimbot del video practicamente

DWORD findPlayer() {
	D3DXVECTOR3 w2sHead;
	DWORD plrToAim = NULL;
	double lowestDist = 9999;

	for (int i = 1; i <= 32; i++) {
		auto base = Entidad::getEntityBase(i);
		if (Entidad::getEntTeam(base) != LocalPlayer::getLocalTeam() && Entidad::isValid(base) && !Entidad::getEntImmunity(base)) {
			WorldToScreen(Entidad::getEntBonePos(base, 8), w2sHead, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
			double dist = sqrt(pow((GetSystemMetrics(SM_CXSCREEN) / 2) - w2sHead.x, 2) + pow((GetSystemMetrics(SM_CYSCREEN) / 2) - w2sHead.y, 2));
			if (dist < lowestDist) {
				lowestDist = dist;
				plrToAim = base;
			}
		}
	}
	return plrToAim;
}

float normalizeAngle(float angle, float upper, float lower) {
	while (lower > angle || angle > upper) {
		if (angle < lower) angle += 360.0f;
		if (angle > upper) angle -= 360.0f;
	}
	return angle;
}

float clampAngle(float angle, float upper, float lower, float clamp) {
	if (lower > angle || angle > upper) {
		return clamp;
	}
	return angle;
}

void aimbot(DWORD plrToAimbot, int smooth) {
	if (plrToAimbot != NULL) {
		if (Entidad::getSpotted(plrToAimbot) == 1 && GetAsyncKeyState(0x46)) {
			D3DXVECTOR3 aimAngles = CalcAngle(LocalPlayer::getLocalPos(), Entidad::getEntPos(plrToAimbot));
			aimAngles -= LocalPlayer::getLocalPunchAngles() * 2.0;
			aimAngles.x = normalizeAngle(aimAngles.x, 180.0f, -180.0f);
			aimAngles.y = normalizeAngle(aimAngles.y, 180.0f, -180.0f);
			aimAngles.x = clampAngle(aimAngles.x, 89.0f, -89.0f, 89.0f);
			auto currAngles = LocalPlayer::getLocalViewAngles();
			auto delta = aimAngles - currAngles;
			LocalPlayer::setLocalViewAngles(currAngles + delta / smooth);
			Sleep(4);
		}
	}
}



