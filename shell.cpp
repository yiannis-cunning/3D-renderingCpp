#include "windClass.h"

// -lstdc++
// gcc ShellWindow.cpp ChildWindow.cpp shell.cpp -ld2d1 -lgdi32 -lstdc++ -o run
// gcc *.cpp -ld2d1 -lgdi32 -lstdc++ -o run

// Windows initialzation
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){


	static TCHAR name[] = TEXT ("WindowThing");
	int size = 11;

	// Create shell window
	ShellWindow shell(hInstance, name, size);
	int h = shell.createWnd(hInstance, nCmdShow);

	// Create child window
	ChildWindow canvas(hInstance);
	canvas.registerWnd();
	canvas.createWnd(shell.getHwnd(), hInstance, nCmdShow);






	if (h == 0){return 0;}	
	// set up path of camera
	int i = 0;
	double theta = 0;
	float v[3] = {0,0,0};
	float r = sqrt(20*20 + 10*10);
	theta = 0.5;
	setVector(v, r*cos(theta),r*sin(theta),r*cos(theta));
	canvas.changelens(v);
	
	MSG msg = {};
	while(GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
		if(i == 10){
			i = 0;
			theta = theta += 0.1;
			setVector(v, r*cos(theta),r*sin(theta),r*cos(theta));
			canvas.changelens(v);
		}
		i++;
	}
	
    	return 0;
}


