
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "gfx4.h"

typedef struct wolf {
	double xcenter;
  	double ycenter;
  	double vx;
  	double vy;
} wolf_t;

void drawWolf(double, double);
void animateWolf(wolf_t wolf[], int, double, double, int);

int main() {
	double height = 750;
	double width = 750;
	gfx_open(width,height, "Wolf");
	
	int numWolves = 2,n;
	wolf_t wolf[numWolves];
	double random[3] = {1,1,-1};

	// Initial Position and Speed of the Wolves
		for (n=0; n<numWolves; n++) {
			wolf[n].xcenter = rand() % 750;
			wolf[n].ycenter = rand() % 750;
			wolf[n].vx = .5*random[rand() % 2];
			wolf[n].vy = .5*random[rand() % 2];
		}

	while (1) {
		gfx_clear();
		for (n=0; n<numWolves; n++) {
			animateWolf(wolf,n,width,height,numWolves);
		}
	}
}
void animateWolf( wolf_t wolf[], int i, double width, double height, int numWolves) {
	int x;
	double dt = 3;
	
	drawWolf(wolf[i].xcenter, wolf[i].ycenter);
	gfx_flush();
	wolf[i].xcenter = wolf[i].xcenter + wolf[i].vx*dt;
	wolf[i].ycenter = wolf[i].ycenter + wolf[i].vy*dt;

	double random[3] = {1,1,-1};

	// Wolf Collision Detect
		for (x=(i+1); x<numWolves; x++) {
			if ((abs(wolf[i].xcenter - wolf[x].xcenter) <= 50) && (abs(wolf[i].ycenter - wolf[x].ycenter) <= 50)){
      				wolf[i].vx = random[rand() % 2];
      				wolf[i].vy = random[rand() % 2];
      			}
    		}
		for (x=0; x<i; x++) {
			if ((abs(wolf[i].xcenter - wolf[x].xcenter) <= 50) && (abs(wolf[i].ycenter - wolf[x].ycenter) <= 50)){
                                wolf[i].vx = random[rand() % 2];
                                wolf[i].vy = random[rand() % 2];
                        }
		}

	// Wall Collision Detect
		if (wolf[i].xcenter >= (width-20))
                        wolf[i].vx = -wolf[i].vx;
                else if( wolf[i].xcenter <= 20)
                        wolf[i].vx = -wolf[i].vx;
                else if(wolf[i].ycenter >= (height-20))
                        wolf[i].vy = -wolf[i].vy;
                else if( wolf[i].ycenter <= 20)
                        wolf[i].vy = -wolf[i].vy;
	gfx_flush();
	usleep(10000);

}
void drawWolf(double x, double y) {
	int n;
	// Grey
		gfx_color(192,192,192);
		for (n=0; n<5; n++) {
			gfx_point(x-n,y-n);
		}
		gfx_point(x,y+2);
		gfx_point(x,y+4);
		gfx_point(x,y+5);
		gfx_point(x,y-1);
		gfx_point(x,y-2);
		gfx_point(x,y-3);
		gfx_point(x,y-4);
		gfx_point(x-1,y);
		gfx_point(x-1,y-1);
		gfx_point(x-1,y-2);
		gfx_point(x-1,y-3);
		gfx_point(x-1,y-5);
		gfx_point(x-1,y+1);
		gfx_point(x-1,y+3);
		gfx_point(x-1,y+4);
		gfx_point(x-1,y+5);
		gfx_point(x-2,y-1);
		gfx_point(x-2,y-2);
		gfx_point(x-2,y-3);
		gfx_point(x-2,y-5);
		gfx_point(x-2,y-6);
		gfx_point(x-2,y+1);
		gfx_point(x-2,y+3);
		gfx_point(x-2,y+4);
		gfx_point(x-3,y-2);
		gfx_point(x-3,y-3);
		gfx_point(x-3,y-4);
		gfx_point(x-3,y-5);
		gfx_point(x-3,y-6);
		gfx_point(x-3,y-7);
		gfx_point(x-3,y+1);
		gfx_point(x-3,y+2);
		gfx_point(x-3,y+3);
		gfx_point(x-3,y+4);
		gfx_point(x-4,y-2);
		gfx_point(x-4,y-3);
		gfx_point(x-4,y+2);
		gfx_point(x-4,y+3);
		gfx_point(x-5,y);
		gfx_point(x-5,y-1);
		gfx_point(x-5,y+1);
		gfx_point(x-5,y+2);
		gfx_point(x-5,y+3);
		gfx_point(x-6,y);
		gfx_point(x-6,y+1);
		gfx_point(x-6,y+2);
		gfx_point(x-6,y+3);
		gfx_point(x-7,y+1);
		gfx_point(x-7,y+2);
		gfx_point(x+1,y);
		gfx_point(x+1,y-1);
		gfx_point(x+1,y-2);
		gfx_point(x+1,y-5);
		gfx_point(x+1,y-6);
		gfx_point(x+1,y+1);
		gfx_point(x+1,y+2);
		gfx_point(x+1,y+3);
		gfx_point(x+1,y+4);
		gfx_point(x+1,y+5);
		gfx_point(x+2,y);
		gfx_point(x+2,y-1);
		gfx_point(x+2,y-7);
		gfx_point(x+2,y-8);
		gfx_point(x+2,y+1);
		gfx_point(x+2,y+3);
		gfx_point(x+2,y+4);
		gfx_point(x+2,y+5);
		gfx_point(x+3,y);
		gfx_point(x+3,y-1);
		gfx_point(x+3,y+1);
		gfx_point(x+3,y+2);
		gfx_point(x+3,y+3);
		gfx_point(x+4,y);
		gfx_point(x+4,y-1);
		gfx_point(x+4,y+3);
		gfx_point(x+4,y+4);
		gfx_point(x+4,y+5);
		gfx_point(x+5,y);
		gfx_point(x+5,y-1);
		gfx_point(x+5,y+1);
		gfx_point(x+6,y);
		gfx_point(x+6,y+1);
		gfx_point(x+6,y+2);
	// Black
		gfx_color(0,0,0);
		gfx_point(x-8,y);
		gfx_point(x-8,y-1);
		gfx_point(x-8,y+1);
		gfx_point(x-8,y+2);
		gfx_point(x-7,y);
		gfx_point(x-7,y-1);
		gfx_point(x-7,y+3);
		gfx_point(x-6,y-1);
		gfx_point(x-6,y+4);
		gfx_point(x-6,y+5);
		gfx_point(x-5,y-2);
		gfx_point(x-5,y-3);
		gfx_point(x-5,y+6);
		gfx_point(x-4,y);
		gfx_point(x-4,y-1);
		gfx_point(x-4,y-4);
		gfx_point(x-4,y-5);
		gfx_point(x-4,y-6);
		gfx_point(x-4,y-7);
		gfx_point(x-4,y-8);
		gfx_point(x-4,y+1);
		gfx_point(x-4,y+4);
		gfx_point(x-4,y+5);
		gfx_point(x-4,y+6);
		gfx_point(x-3,y-1);
		gfx_point(x-3,y-8);
		gfx_point(x-3,y+5);
		gfx_point(x-2,y);
		gfx_point(x-2,y-4);
		gfx_point(x-2,y-7);
		gfx_point(x-2,y+2);
		gfx_point(x-2,y+5);
		gfx_point(x-1,y-4);
		gfx_point(x-1,y-6);
		gfx_point(x-1,y+2);
		gfx_point(x-1,y+6);
		gfx_point(x,y-5);
		gfx_point(x,y-6);
		gfx_point(x,y+1);
		gfx_point(x,y+3);
		gfx_point(x,y+6);
		gfx_point(x+1,y+1);
		gfx_point(x+1,y-3);
		gfx_point(x+1,y-4);
		gfx_point(x+1,y-7);
		gfx_point(x+1,y-8);
		gfx_point(x+2,y-2);
		gfx_point(x+2,y-5);
		gfx_point(x+2,y-6);
		gfx_point(x+2,y-9);
		gfx_point(x+2,y+2);
		gfx_point(x+2,y+6);
		gfx_point(x+3,y-8);
		gfx_point(x+3,y+4);
		gfx_point(x+3,y+5);
		gfx_point(x+4,y-6);
		gfx_point(x+4,y-7);
		gfx_point(x+4,y+1);
		gfx_point(x+4,y+2);
		gfx_point(x+4,y+6);
		gfx_point(x+5,y-2);
		gfx_point(x+5,y-3);
		gfx_point(x+5,y-4);
		gfx_point(x+5,y-5);
		gfx_point(x+5,y+2);
		gfx_point(x+5,y+3);
		gfx_point(x+5,y+4);
		gfx_point(x+5,y+5);
		gfx_point(x+6,y-1);
		gfx_point(x+6,y+3);
		gfx_point(x+7,y);
		gfx_point(x+7,y+1);
		gfx_point(x+7,y+2);
	// White
		gfx_color(255,255,255);
		gfx_point(x-5,y+4);
		gfx_point(x-5,y+5);
		gfx_point(x-3,y);
		gfx_point(x+2,y-3);
		gfx_point(x+2,y-4);
		gfx_point(x+3,y-2);
		gfx_point(x+3,y-3);
		gfx_point(x+3,y-4);
		gfx_point(x+3,y-5);
		gfx_point(x+3,y-6);
		gfx_point(x+3,y-7);
		gfx_point(x+4,y-2);
		gfx_point(x+4,y-3);
		gfx_point(x+4,y-4);
		gfx_point(x+4,y-5);
}
