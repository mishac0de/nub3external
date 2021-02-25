#include "Includes.h"

D3DXVECTOR3 NewViewAngles;
D3DXVECTOR3 OldAimPunch;

//esto es el recoil control todas las balas van derechitas

void rcs() {
	if (LocalPlayer::getShotsFired() > 1) {
		NewViewAngles.x = ((LocalPlayer::getLocalViewAngles().x + OldAimPunch.x) - (LocalPlayer::getLocalPunchAngles().x * 2.f));        //agarra el aimpunch comparado con el anterior
		NewViewAngles.y = ((LocalPlayer::getLocalViewAngles().y + OldAimPunch.y) - (LocalPlayer::getLocalPunchAngles().y * 2.f));


		while (NewViewAngles.y > 180)
			NewViewAngles.y -= 360;

		while (NewViewAngles.y < -180)
			NewViewAngles.y += 360;

		if (NewViewAngles.x > 89.0f)
			NewViewAngles.x = 89.0f;

		if (NewViewAngles.x < -89.0f)
			NewViewAngles.x = -89.0f;

		OldAimPunch.x = LocalPlayer::getLocalPunchAngles().x * 2.f; //corrige y escribe el aimpunch anterior al del momento
		OldAimPunch.y = LocalPlayer::getLocalPunchAngles().y * 2.f;

		LocalPlayer::setLocalViewAngles(NewViewAngles);
	}
	else
	{
		OldAimPunch.x = OldAimPunch.y = 0; //si no disparas no hay punch
	}
}
