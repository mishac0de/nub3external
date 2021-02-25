#include "Includes.h"

DWORD LocalPlayer::localPlayerAddress = 0;

//Localizar el jugador local ej: (LocalPlayer::getLocalPlayer() + netvars::m_fFlags) para conocer las flags, getLocalPlayer() corresponde al valor del jugador local.
DWORD LocalPlayer::getLocalPlayer() {

	return LocalPlayer::localPlayerAddress;

}

//Inicialización del jugador local, para encontrar el valor al iniciar el cheat
void LocalPlayer::initLocalPlayer() {
	
	LocalPlayer::localPlayerAddress = readMem<DWORD>(gameModule + signatures::dwLocalPlayer);
}

//Para encontrar las flags de nuestro jugador
int LocalPlayer::getLocalFlags() {

	return readMem<int>(LocalPlayer::localPlayerAddress + netvars::m_fFlags);

}

//Para saltar con tiempo de espera (el tiempo de espera está definido en "LocalPlayer.h" pero no es necesario modificarlo)
void LocalPlayer::fJump(int tiempoEspera) {

	writeMem<int>(gameModule + signatures::dwForceJump, 1);
	Sleep(tiempoEspera);
	writeMem<int>(gameModule + signatures::dwForceJump, 0);

}

//Encontrar el equipo del jugador local
int LocalPlayer::getLocalTeam() {

	return readMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_iTeamNum);

}

//Encontrar la duración de flash del jugador local
int LocalPlayer::getLocalFlashDur() {
	return readMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_flFlashDuration);
}

void LocalPlayer::setLocalViewAngles(D3DXVECTOR3 angles)
{
	writeMem<D3DXVECTOR3>(clientState + signatures::dwClientState_ViewAngles, angles);
}

D3DXVECTOR3 LocalPlayer::getLocalPunchAngles()
{
	return readMem<D3DXVECTOR3>(LocalPlayer::getLocalPlayer() + netvars::m_aimPunchAngle);
}

D3DXMATRIX	LocalPlayer::getLocalViewMatrix()
{
	return readMem<D3DXMATRIX>(gameModule + signatures::dwViewMatrix);
}

int LocalPlayer::getShotsFired() {
	return readMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_iShotsFired);
}

D3DXVECTOR3 LocalPlayer::getLocalViewAngles()
{
	return readMem<D3DXVECTOR3>(clientState + signatures::dwClientState_ViewAngles);
}

int LocalPlayer::getLocalCrosshair()
{
	auto temp = readMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_iCrosshairId);
	if (temp <= 0 || temp > 32)
		return -1;
	return temp;
}

D3DXVECTOR3 LocalPlayer::getLocalPos()
{
	return readMem<D3DXVECTOR3>(LocalPlayer::getLocalPlayer() + netvars::m_vecOrigin);
}

int LocalPlayer::getLocalCrossID()
{
	auto temp = readMem<int>(LocalPlayer::getLocalPlayer() + netvars::m_iCrosshairId);
	if (temp <= 0 || temp > 32)
		return -1;
	return temp;
}
