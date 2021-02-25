/*
nub3 External, por @mishac0de
based on NullBase's SDK: https://github.com/NullTerminatorr/NullBase
*/

#include "Includes.h"

using namespace std;

bool bunnyHopStatus = FALSE;
bool noFlashStatus = FALSE;
bool glowStatus = FALSE;
bool radarStatus = FALSE;
bool recoilStatus = FALSE;
bool triggerStatus = FALSE;
bool aimbotStatus = FALSE;
bool rageStatus = FALSE;
int aimbotSmooth = 20;
bool chamStatus = FALSE;
bool fovStatus = FALSE;

int main() {

	printf("nub3 external: Inicializando...");
	printf("codigo por @mishac0de" "\n" "\n");

	//Inicialización de los valores base (el contenido esta en el final de "MemoriaTest.cpp").
	init();

	SetConsoleTitle("nub3 external (por @mishac0de)");

	printf("\n" "Bunnyhop -> [F1]" "\n");
	printf("NoFlash -> [F2]" "\n");
	printf("GlowESP -> [F3]" "\n");
	printf("Radar -> [F4]" "\n");
	printf("RCS -> [F6]" "\n");
	printf("Triggerbot -> [F7] " "\n");
	printf("Aimbot (BETA) (Legit) -> [F8] [HOTKEY: F] " "\n");
	printf("Aimbot (BETA) (Rage) -> [F9] [HOTKEY: F] " "\n");
	printf("CLRender Chams (BETA) -> [F11]" "\n");
	printf("FOVChanger (BETA) -> [INS]" "\n");

	printf("\n");
	//Loop
	while (true) {

		//Bhop con tiempo de 35ms.
		if (GetAsyncKeyState(VK_F1) & 1) {
			bunnyHopStatus = !bunnyHopStatus;
			if (bunnyHopStatus == TRUE) {
				printf("Bunnyhop: [ON]" "\n");
			}
			else {
				printf("Bunnyhop: [OFF]" "\n");
			}
		}
		if (bunnyHopStatus) {
			
			bunnyHop();
		}

		//NoFlash
		if (GetAsyncKeyState(VK_F2) & 1) {
			noFlashStatus = !noFlashStatus;
			if (noFlashStatus == TRUE) {
				printf("NoFlash: [ON]" "\n");
			}
			else {
				printf("NoFlash: [OFF]" "\n");
			}
		}
		if (noFlashStatus) {
			
			NoFlash();
		}

		//GlowESP
		if (GetAsyncKeyState(VK_F3) & 1) {
			glowStatus = !glowStatus;
			if (glowStatus == TRUE) {
				printf("GlowESP: [ON]" "\n");
			}
			else {
				printf("GlowESP: [OFF]" "\n");
			}
		}
		if (glowStatus) {				
				Glow();
			
		}

		//Radar
		if (GetAsyncKeyState(VK_F4) & 1) {
			radarStatus = !radarStatus;
			if (radarStatus == TRUE) {
				printf("Radar: [ON]" "\n");
			}
			else {
				printf("Radar: [OFF]" "\n");
			}
		}
		if (radarStatus) {
			radar();
		}

		//RCS
		if (GetAsyncKeyState(VK_F6) & 1) {
			recoilStatus = !recoilStatus;
			if (recoilStatus == TRUE) {
				printf("RCS: [ON]" "\n");
			}
			else {
				printf("RCS: [OFF]" "\n");
			}
		}
		if (recoilStatus) {
			rcs();
		}

		//Triggerbot
		if (GetAsyncKeyState(VK_F7) & 1) {
			triggerStatus = !triggerStatus;
			if (triggerStatus == TRUE) {
				printf("Triggerbot: [ON]" "\n");
			}
			else {
				printf("Triggerbot: [OFF]" "\n");
			}
		}
		if (triggerStatus) {
			trigger();
		}

		//Aimbot (Legit)
		if (GetAsyncKeyState(VK_F8) & 1) {
			aimbotStatus = !aimbotStatus;
			if (aimbotStatus == TRUE) {
				printf("Aimbot (Legit): [ON]" "\n");
			}
			else{
				printf("Aimbot (Legit): [OFF]" "\n");
			}
		}		
		if (aimbotStatus) {
			//delta / smooth (20)
			aimbot(findPlayer(), 20);
		}

		//Aimbot rage
		if (GetAsyncKeyState(VK_F9) & 1) {
			rageStatus = !rageStatus;
			if (rageStatus == TRUE) {
				printf("Aimbot (Rage): [ON]" "\n");
			}

			else{
				printf("Aimbot (Rage): [OFF]" "\n");
			}
		}
		if (rageStatus) {
			aimbot(findPlayer(), 1);
		}
		
		//Chams
		if (GetAsyncKeyState(VK_F11) & 1) {
			chamStatus = !chamStatus;
			if (chamStatus == TRUE) {
				printf("Chams: [ON]" "\n");
			}
			else {
				printf("Chams: [OFF]" "\n");
				chamsReset(1);
			}
		}
		if (chamStatus) {
			//r, g, b, brillo
			chams(7);
		}
		
		//FOVChanger
		if (GetAsyncKeyState(VK_INSERT) & 1) {
			fovStatus = !fovStatus;
			if (fovStatus == TRUE) {
				printf("FOVChanger: [ON]" "\n");
			}
			else {
				printf("FOVChanger: [OFF]" "\n");
				fovreset();
			}
		}
		if (fovStatus) {
			fovchange();
		}
		
	}

	return 0;
}



