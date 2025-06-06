#pragma once
#include "Prerequisites.h"

class
	BaseApp {
public:
	BaseApp();
	~BaseApp();

	// Initializes the application by setting up the necessary resources.
	HRESULT 
	init();

	// Updates de application logic each frame.
	void 
	update();

  // Renders the application content to the screen.
	void 
	render();

  // Releases all resources and cleans up the application to free memory before exiting.
	void destroy();

	// Runs the application from the main entry point.
	int 
	run(HINSTANCE hInstance, 
			HINSTANCE hPrevInstance, 
			LPWSTR lpCmdLine, 
			int nCmdShow, 
			WNDPROC wndproc);

private:

};
