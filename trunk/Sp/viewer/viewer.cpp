// This is the main DLL file.
#pragma once
#include "viewer.h"
//#include "..\test1\test1.cpp"
//#include "..\test1\Form1.h"
#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

//TODO:
extern "C" __declspec(dllexport) void view(Buffer* buf)
{
    //Application::Run(gcnew Form1(buf));
}


#ifdef _MANAGED
#pragma managed(pop)
#endif