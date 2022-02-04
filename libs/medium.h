#pragma once
#include <Windows.h>
#include <stdio.h>
#include <d2d1.h>
#include <math.h>
#include "linalg.h"



struct node{
       float velociy[3];
       float position[3];
};




class medium{
       struct node *plane;
       bool stiff;

       float k;
       float m;
       float lx;
       float ly;
       
public:

       int width;
       int height;


       medium(int width_in, int height_in, bool stiff_in);
       void timestep(float deltaT);
       void timestep_node(float deltaT, int x, int y);
       void reset_pos();

       void start_pos();
       void print_node(int x, int y);
       

       float get_ly();
       float get_lx();
       void copy_node_pos(int x, int y, float *ans);
};