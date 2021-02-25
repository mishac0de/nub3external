#pragma once

#include <windows.h>

//Just for vector and matrix shit (im lazy)
#include <d3d9.h>
#include <d3dx9.h>

namespace LocalPlayer
{
	//Funciones de return del archivo "LocalPlayer.cpp"
	extern DWORD			localPlayerAddress;
	extern void				initLocalPlayer();
	extern DWORD			getLocalPlayer();		
	extern int				getLocalFlags();
	extern void				fJump(int tiempoEspera = 35);
	extern int				getLocalTeam();
	extern int				getLocalFlashDur();
	extern D3DXVECTOR3		getLocalViewAngles();											//Set the local player base address
	extern void				setLocalViewAngles(D3DXVECTOR3 angles);
	extern D3DXVECTOR3		getLocalPunchAngles();
	extern D3DXMATRIX		getLocalViewMatrix();
	extern int				getShotsFired();
	extern int				getLocalCrosshair();
	extern D3DXVECTOR3		getLocalPos();
	extern int				getLocalCrossID();
	extern bool				isScoped();
}

extern DWORD						localPlayer;
