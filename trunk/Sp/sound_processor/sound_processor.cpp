// sound_processor.cpp : main project file.

#include "SpForm.h"
//#include <commctrl.h>

using namespace sound_processor;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 
	//InitCommonControls();

	// Create the main window and run it
	Application::Run(gcnew SpForm());
	return 0;
}
