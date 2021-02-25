#include "Includes.h"
#include "MemoriaTest.h"
#include "Xor.h"
#include "LocalPlayer.h"
#include <stdlib.h>


//Variables para utilizar
DWORD gameModule = NULL;
DWORD engineModule = NULL;
DWORD clientState = NULL;

//Variables para la snapshot del proceso
HANDLE hProcSnap = NULL;
PROCESSENTRY32 procEntry32;

//Variables para la snapshot del módulo
HANDLE hModuleSnap = NULL;
MODULEENTRY32 modEntry32;

//ID del proceso que se usó
DWORD pID = NULL;

//Handle al proceso
HANDLE processHandle = NULL;

bool getProcess(char* procName)
{

	//Toma una snapshot de TODOS los procesos que están corriendo
	hProcSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hProcSnap == INVALID_HANDLE_VALUE)
	{
		std::cout << "no se pudieron encontrar los procesos" << std::endl;
		return false;
	}

	//Definimos el tamaño de la entrada.
	procEntry32.dwSize = sizeof(PROCESSENTRY32);


	//Siempre que haya un proceso siguiente
	while (Process32Next(hProcSnap, &procEntry32))
	{

		//Si el proceso que estamos buscando se encuentra en la snapshot
		if (!strcmp(procName, procEntry32.szExeFile))
		{
			//Mostrando ID del proceso para posteriormente crear un HANDLE y leer/escribir la memoria
			std::cout << "Nombre del proceso: " << procEntry32.szExeFile << " ID: " << procEntry32.th32ProcessID << std::endl;
			processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procEntry32.th32ProcessID);
			pID = procEntry32.th32ProcessID;
			if (processHandle == NULL)
			{
				system("Color 4");
				std::cout << "No se pudo crear un handle al proceso." << std::endl;
			}
			//Cerrar el handle y devolver "true"
			CloseHandle(hProcSnap);
			return true;
		}
	}
	std::cout << "No se pudo encontrar " << procName << " (proceso) en la snapshot de los procesos." << std::endl;
	CloseHandle(hProcSnap);
	return false;
}

DWORD getModule(LPSTR moduleName)
{
	//Tomamos snapshot de los módulos corriendo (procedimiento parecido al anterior)
	hModuleSnap = INVALID_HANDLE_VALUE;
	hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);

	if (hModuleSnap == INVALID_HANDLE_VALUE)
	{
		std::cout << "No se pudo tomar una snapshot de los procesos." << std::endl;
		CloseHandle(hModuleSnap);
		return 0;
	}

	//Definiendo el tamaño de la estructura
	modEntry32.dwSize = sizeof(MODULEENTRY32);

	//Tomando información del primer módulo en la snapshot
	if (Module32First(hModuleSnap, &modEntry32))
	{
		//Si el módulo que buscamos es ese
		if (!strcmp(moduleName, modEntry32.szModule))
		{
			//Cerrar el handle al proceso y devolver address
			CloseHandle(hModuleSnap);
			return (DWORD)modEntry32.modBaseAddr;
		}
	}

	//Lo mismo que antes pero para el siguiente módulo
	while (Module32Next(hModuleSnap, &modEntry32))
	{
		if (!strcmp(moduleName, modEntry32.szModule))
		{
			CloseHandle(hModuleSnap);
			return (DWORD)modEntry32.modBaseAddr;
		}
	}
	std::cout << "No se pudo encontrar " << moduleName << " (modulo) en la snapshot de los modulos." << std::endl;
	CloseHandle(hModuleSnap);
	return false;
}

std::uint32_t find(const char* proc)
{
	auto snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(pe);

	if (Process32First(snapshot, &pe)) {
		while (Process32Next(snapshot, &pe))
		{
			if (!strcmp(proc, pe.szExeFile)) {
				CloseHandle(snapshot);
				return pe.th32ProcessID;
			}
		}
	}
	CloseHandle(snapshot);
	return 0;
}

//inicialización para encontrar valores base y el proceso, se llama a esta función con init();
void init()
{
	if (getProcess(XOR(LPSTR("csgo.exe"))))
	{
		gameModule = getModule(XOR(LPSTR("client.dll")));
		engineModule = getModule(XOR(LPSTR("engine.dll")));

		LocalPlayer::initLocalPlayer();
		clientState = readMem<DWORD>(engineModule + signatures::dwClientState);

	}
}