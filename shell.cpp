#include "windClass.h"
#include <sys\timeb.h> 

// -lstdc++
// gcc ShellWindow.cpp ChildWindow.cpp shell.cpp -ld2d1 -lgdi32 -lstdc++ -o run
// gcc *.cpp libs\*.cpp -ld2d1 -lgdi32 -lstdc++ -o run

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
	
	struct timeb start, end;
	int diff;
	float dt;
	float avg_sum;
	int samples;


	MSG msg = {};
	while(GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		

		ftime(&start);

		theta = theta += 0.1;
		setVector(v, r*cos(theta),r*sin(theta),r*cos(theta));
		canvas.changelens(v);

		ftime(&end);
		dt = (float) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
		avg_sum += (1000/((float)dt));
		samples += 1;
		printf("\r Frame per second: %f. Average: %f", (1000/((float)dt)), avg_sum/samples);
		
	}
	
    	return 0;
}


