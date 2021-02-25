#include "Includes.h"

//Para el bunnyhop, define el valor de si nuestro jugador está en el piso.
#define FL_ON_GROUND 257

void bunnyHop() {
	if (GetAsyncKeyState(VK_SPACE) && LocalPlayer::getLocalFlags() == FL_ON_GROUND)
		LocalPlayer::fJump();
}