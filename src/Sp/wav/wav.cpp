// This is the main DLL file.

#include "wav.h"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

//TODO:
extern "C" __declspec(dllexport) void read(read_parameters* parameters)
{
    printf("Hello world!\n");
}

//TODO:
extern "C" __declspec(dllexport) void write(write_parameters* parameters)
{}

#ifdef _MANAGED
#pragma managed(pop)
#endif


