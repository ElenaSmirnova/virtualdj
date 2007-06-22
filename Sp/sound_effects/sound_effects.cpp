// This is the main DLL file.

#include "sound_effects.h"


#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

//TODO:
extern "C" __declspec(dllexport) void sound_effect(eff_parameters* parameters)
{
    printf("Hello world!\n");
}


#ifdef _MANAGED
#pragma managed(pop)
#endif


