#include "Includes.h"

//estos chams son medio una mierda pero ahi estan

void chams(float brightness)
{

	for (int i = 1; i < 32; i++)
	{
		DWORD plr = Entidad::getEntityBase(i);
		if (Entidad::getEntTeam(plr) != LocalPlayer::getLocalTeam()) {
			//color del modelo (r, g, b) para enemigos
			writeMem<BYTE>(plr + 0x70, BYTE(255));
			writeMem<BYTE>(plr + 0x71, BYTE(0));
			writeMem<BYTE>(plr + 0x72, BYTE(0));
		}
		else {
			writeMem<BYTE>(plr + 0x70, BYTE(0));
			writeMem<BYTE>(plr + 0x71, BYTE(255));
			writeMem<BYTE>(plr + 0x72, BYTE(0));
		}
	}

	//brillo del modelo (se pasa con la funcion chams)
	DWORD thisPtr = (int)(engineModule + signatures::model_ambient_min - 0x2c);
	DWORD xored = *(DWORD*)&brightness ^ thisPtr;
	writeMem<int>(engineModule + signatures::model_ambient_min, xored);

}

//resetear chams a color normal
void chamsReset(float brightness)
{

	for (int i = 1; i < 32; i++)
	{
		DWORD plr = Entidad::getEntityBase(i);
		if (Entidad::getEntTeam(plr) != LocalPlayer::getLocalTeam()) {
			//Model Color
			writeMem<BYTE>(plr + 0x70, BYTE(130));
			writeMem<BYTE>(plr + 0x71, BYTE(130));
			writeMem<BYTE>(plr + 0x72, BYTE(130));
		}
		else {
			writeMem<BYTE>(plr + 0x70, BYTE(130));
			writeMem<BYTE>(plr + 0x71, BYTE(130));
			writeMem<BYTE>(plr + 0x72, BYTE(130));
		}
	}

	//Model Brightness
	DWORD thisPtr = (int)(engineModule + signatures::model_ambient_min - 0x2c);
	DWORD xored = *(DWORD*)&brightness ^ thisPtr;
	writeMem<int>(engineModule + signatures::model_ambient_min, xored);

}