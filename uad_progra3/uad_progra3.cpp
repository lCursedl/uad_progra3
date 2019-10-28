// uad_progra3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
using namespace std;

#include "Include/CApp.h"
#include "Include/CAppMyCube.h"
#include "Include/CAppCubeTest.h"
#include "Include/CAppObjLoader.h"
#include "Include/CAppGeometricFigures.h"
#include "Include/CAppHexGrid.h"
#include "Include/CAppEmpty.h"

int main()
{
	CApp *app = NULL;					// Pointer to BASE class CApp
	app = new CAppHexGrid(800, 600);		// Using pointer to base class, create a new object of DERIVED class
	app->run();							// Run the app
	delete app;							// Delete pointer
	app = NULL;							// Set pointer to NULL

	return 0;
}