//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by app.rc

#include <stdio.h>
#include <stdlib.h>
#include <vcclr.h>
#include "..\wav\structure.h"

#define CANALS 2
/*[DllImport("wav.dll")]
[DllImport("sound_effects.dll")]*/
extern "C" void _cdecl read2(SoundBuffer *buffer, char* name);
extern "C" void _cdecl write2(SoundBuffer *buffer, char* name);
extern "C" int _cdecl mainEcho(SoundBuffer *buffer, float coefficient, bool flagOfFirstUse, SoundBuffer *memoryBuffer);
extern "C" int _cdecl mainDistortion(int highLimit, int lowLimit, SoundBuffer *buffer);
extern "C" void _cdecl sound_effect(SoundBuffer *buffer);