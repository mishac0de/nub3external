#pragma  once
#include <iostream>
#include <string>
#include <windows.h>
#include <tlhelp32.h>

//handle al proceso
extern HANDLE processHandle;

//variables
extern DWORD gameModule;
extern DWORD engineModule;
extern DWORD clientState;
extern bool processInit;
extern bool secondaryModuleInit;
extern bool initModule;


extern HANDLE hProcSnap;
extern PROCESSENTRY32 procEntry32;


extern HANDLE hModuleSnap;
extern MODULEENTRY32 modEntry32;


extern DWORD pID;



//Función para escribir memoria (actualizada). Ahora sólo se necesita escribir "writeMem" en vez de inicializar la clase.
template <class dataType>
void writeMem(DWORD addressToWrite, dataType valToWrite)
{
	WriteProcessMemory(processHandle, (PVOID)addressToWrite, &valToWrite, sizeof(dataType), 0);
}

//Función para leer memoria (actualizada). Ahora sólo se necesita escribir "readMem" en vez de inicializar la clase.
template <class dataType>
dataType readMem(DWORD addressToRead)
{
	//el valor de la address que se está leyendo
	dataType addValue;

	//RPM
	ReadProcessMemory(processHandle, (PVOID)addressToRead, &addValue, sizeof(dataType), 0);

	//Return the value that was read
	return addValue;
}

//inicialización
extern void init();

extern bool getProcess(char* procName);

extern DWORD getModule(char* moduleName);

extern uintptr_t patternScan(char* base, size_t size, char* pattern);


extern std::uint32_t find(const char* proc);