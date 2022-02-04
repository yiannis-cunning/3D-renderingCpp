#include "medium.h"



medium::medium(int width_in, int height_in, bool stiff_in)
{
       width = width_in;
       height = height_in;
       stiff = stiff_in;

       plane = (struct node *)calloc(width_in * height_in, sizeof(struct node));


       m = 1;
       k = 2000;
       if(width == 1){lx = 0;}
       else{lx = 2000/(width*1.0-1);}
       if(height == 1){ly = 0;}
       else{ly = 2000/(height*1.0-1);}
}


// do timestep for induvidual node
void medium::timestep_node(float deltaT, int x, int y)
{
       float dp[3] = {0,0,0};
       float force1[3] = {0,0,0};
       float force2[3] = {0,0,0};
       float force3[3] = {0,0,0};
       float force4[3] = {0,0,0};


       // 1) calculate the forces
       if( x != 0 && x != width - 1)
       {
              // Left
              setVector(dp, -lx, 0, 0);
              addVec(dp, plane[(x-1)+y*width].position, dp);
              subVec(dp, plane[x+y*width].position, dp);
              cpyVec(dp, force1);
              normalize(force1);          // magnitude of force is (lx - mag(dp))*k, direction of dp
              constMult(k*(vecMag(dp) - lx), force1, force1);


              // Right
              setVector(dp, lx, 0, 0);
              addVec(dp, plane[(x+1)+y*width].position, dp);
              subVec(dp, plane[x +y*width].position, dp);
              cpyVec(dp, force2);
              normalize(force2);    // direction of force is same as dp
              constMult(k*(vecMag(dp) - lx), force2, force2);    // magnatude of force is k*(mag(dp) - lx)

       }
       if( y != 0 && y != height - 1)
       {
              // inScreen
              setVector(dp, 0, -ly, 0);
              addVec(dp, plane[x+(y-1)*width].position, dp);
              subVec(dp, plane[x+y*width].position, dp);
              cpyVec(dp, force3);
              normalize(force3);          // magnitude of force is (lx - mag(dp))*k, direction of dp
              constMult(k*(vecMag(dp) - ly), force3, force3);


              // outScreen
              setVector(dp, 0, ly, 0);
              addVec(dp, plane[x + (y+1)*width].position, dp);
              subVec(dp, plane[x + y*width].position, dp);
              cpyVec(dp, force4);
              normalize(force4);    // direction of force is same as dp
              constMult(k*(vecMag(dp) - lx), force4, force4);    // magnatude of force is k*(mag(dp) - lx)
       }

       addVec(force1, force2, force1);
       addVec(force1, force3, force1);
       addVec(force1, force4, force1);
       //f1 is net force
       // a = f/m
       // v(i+1) = vi + a*t
       // d(i+1) = di + v*t
       constMult(-0.9, plane[x + y*width].velociy, force2);
       constMult(deltaT/m, force2, force2);
       setVector(force3, 0, 0 ,-9.8);
       constMult(deltaT, force3, force3);

       constMult(deltaT/m, force1, force1);
       addVec(force1, force2, force1);
       addVec(force3, force1, force1);


       addVec(plane[x + y*width].velociy, force1, plane[x + y*width].velociy);
       
}

// do simulation timestep
void medium::timestep(float deltaT)
{
       float temp[3] = {0,0,0};

       for(int x = 0; x < width; x++)
       {
              for(int y = 0; y < height; y++)
              {
                     timestep_node(deltaT, x, y);
              }
       }

       for(int x = 0; x < width; x++)
       {
              for(int y = 0; y < height; y++)
              {
                     constMult(deltaT, plane[x + y*width].velociy, temp);
                     addVec(plane[x + y*width].position, temp, plane[x + y*width].position);
              }
       }


}


void medium::reset_pos()
{
       for(int x = 0; x < width; x++)
       {
              for(int y = 0; y < height; y++)
              {
                     setVector(plane[x + y*width].velociy, 0, 0, 0);
                     setVector(plane[x + y*width].position, 0, 0, 0);
              }
       }
}

void medium::start_pos()
{
       int r = 10;
       for(int x = -r; x <= r; x++){
              for(int y = -sqrt(r*r - x*x); y <= sqrt(r*r - x*x); y++){

                     setVector(plane[(int)(height/2) + x + ((int)(width/2) + y)*width].position, 0, 0, 1600 - 1600*(x*x + y*y)/(r*r) );
                     //setVector(plane[11 + x + (11 + y)*width].position, 0, 0, 800 - 800*(x*x + y*y)/(r*r) );
              }
       }


       
}


void medium::print_node(int x, int y)
{
       struct node temp = plane[x + y*width];
       printf("node (%d, %d): %f, %f, %f\n", x, y, temp.position[0], temp.position[1], temp.position[2]);
}



float medium::get_ly(){return ly;}
float medium::get_lx(){return lx;}

void medium::copy_node_pos(int x, int y, float *ans){
       if(x < 0 || x > width || y < 0 || y > height){
              return;
       }
       cpyVec(plane[x + y*width].position, ans);
}