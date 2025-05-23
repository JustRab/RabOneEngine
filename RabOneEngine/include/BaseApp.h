#pragma once
#include "Prerequisites.h"

class BaseApp
{
public:
	BaseApp();
	~BaseApp();

	HRESULT init();

	void update();

	void render();

	void destroy();

	int run(HINSTANCE hInstance, 
			HINSTANCE hPrevInstance, 
			LPWSTR lpCmdLine, 
			int nCmdShow, 
			WNDPROC wndproc);

private:

};
