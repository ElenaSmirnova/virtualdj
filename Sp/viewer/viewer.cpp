// This is the main DLL file.
#pragma once

#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include "viewer.h"
#include "..\test1\test1.cpp"

#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}


extern "C" __declspec(dllexport) void view(SoundBuffer* buf)
{
	//  Application::Run(gcnew Form1(buf));
}


#ifdef _MANAGED
#pragma managed(pop)
#endif