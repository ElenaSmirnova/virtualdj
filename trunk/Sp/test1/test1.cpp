// test1.cpp : main project file.

#include "stdafx.h"
#include "Form1.h"
#define n 2

using namespace test1;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Form1(n));
	return 0;
	
}
