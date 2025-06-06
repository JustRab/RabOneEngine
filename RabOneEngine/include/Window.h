#pragma once
#include "Prerequisites.h"

class 
Window {
public:
	Window() = default;
	~Window() = default;

	// Initialize the window with the given instance and command show parameters
	HRESULT init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndproc);
  
  // Updates the window state and handles any necessary processing.
	void 
	update();

  // Renders the window content, typically called in the main loop.
	void
	render();

  // Destroys the window and cleans up resources.
	void
	destroy();

public:
	HWND m_hWnd = nullptr;
	unsigned int m_width;
	unsigned int m_height;

private:
	HINSTANCE m_hInst = nullptr;
	RECT m_rect;
	std::string m_windowName = "RabOneEngine";
};
