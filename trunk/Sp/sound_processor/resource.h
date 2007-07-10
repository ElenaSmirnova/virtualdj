//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by app.rc


#define LENGTH 6 //16384
#define CANALS 2
[DllImport("wav.dll")]
extern "C" void read2(char* name);

[DllImport("sound_effects.dll")]
extern "C" int mainEcho(int buffer[CANALS][LENGTH], float coefficient, bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]);
extern "C" int mainDistortion(int highLimit, int lowLimit, int buffer[CANALS][LENGTH]);