//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by app.rc


#define LENGTH 6 //16384
#define CANALS 2

//extern "C" __declspec(dllimport) void _cdecl read(char* name);
extern "C" __declspec(dllimport) void _cdecl read2(char* name);
extern "C" __declspec(dllimport) int mainEcho(int buffer[CANALS][LENGTH], float coefficient, bool flagOfFirstUse, int memoryBuffer[CANALS][LENGTH]);
extern "C" __declspec(dllimport) int mainDistortion(int highLimit, int lowLimit, int buffer[CANALS][LENGTH]);