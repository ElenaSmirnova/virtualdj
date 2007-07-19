
// test1.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"

using namespace test1;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false); 

	int _array[5];
	int arraySize = 5;
	_array[0] = 35;
	_array[1] = 0;
	_array[2] = 15;
	_array[3] = -20;
	_array[4] = 5;
	// Create the main window and run it
	Application::Run(gcnew Form1(_array,arraySize));
	return 0;
	
}
