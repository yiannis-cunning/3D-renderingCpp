# 3D-renderingCpp

main file: shell
most window functionality: ChildWindow
rest of objects/classes used: libs folder


This project includes a cpp class named 'camera' that acts as a virtual camera to a 3d scene and renders what is going on.
The camera class is implemented through a window class using windows.h and is painted using directx2d graphics. I also made
a vector function class to make methods for things like vector addition, dot product, matrix multiplication ext, to be used
by the camera and cube class. There is also a 'medium' class I created to try and simulate waves in a medium.

The main motivation of this project was to see what I could make completely from scratch mixed in with interest in how all
modern 3-d rendering stuff worked. The main 'shell' file is set up to create a demo of the program which rotates in a 
circular orbit around the origin focused on the rubix cube. Right now this is very slow and laggy as the program is still
very unoptimized. I am still looking into the bottleneck coming from the window itself, the possibility of accessing more
graphics resources and also just improving the way the scene is rendered.

Other functionality that has been implemented into the camera class includes the ability to draw. stl images and bitmaps if
in the correct format. There is also a few different rendering functions that use slightly different techniques of projecting
the image to the screen.


The demo/exe file is in the repository, or the code can be downloaded and complied by itself.
