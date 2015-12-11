
#include <stdio.h>
#include "gfx4.h"
#include <math.h>

void fern(double, double, double, double);

int main() {

// polygon array
	XPoint xp = {300,450};
	XPoint barnRoof[8]={{625,450},{500,550},{750,550},{625,450}};
	int sizeRoof = sizeof(barnRoof)/sizeof(XPoint);

gfx_open(750,750,"The Farm");

// Green Objects
	gfx_color(0,204,0);
	gfx_fill_rectangle(0,0,750,750);
	gfx_flush();

// Red Objects
	gfx_color(255,0,0);
	gfx_fill_rectangle(500,550,250,200);
	gfx_fill_polygon(barnRoof,sizeRoof);

// White Objects
	gfx_color(255,255,255);
	gfx_rectangle(500,550,249,199);

	gfx_line(500,550,625,750);
	gfx_line(500,551,625,751);
	gfx_line(500,552,625,748);
	gfx_line(501,550,626,750);
	gfx_line(502,550,627,750);

	gfx_line(500,750,625,550);
	gfx_line(499,750,624,550);
	gfx_line(498,750,623,550);
	gfx_line(500,749,625,549);
	gfx_line(500,748,625,548);

	gfx_line(625,750,750,550);
	gfx_line(626,750,750,549);
	gfx_line(627,750,750,548);
	gfx_line(625,749,749,550);
	gfx_line(625,748,748,550);

	gfx_line(625,550,750,750);
	gfx_line(625,549,749,750);
	gfx_line(625,548,748,750);
	gfx_line(626,550,751,750);
	gfx_line(627,550,752,750);

	gfx_line(625,450,500,550);
	gfx_line(625,451,501,550);
	gfx_line(501,549,749,549);
	gfx_line(750,550,625,450);
	gfx_line(749,550,625,451);

// Dark Green Objects
	int n;
	gfx_color(76,153,0);
	for (n=50; n<500; n+=50) {
		fern(n,740,50, 3*M_PI/2);
	}
	for (n=75; n<550; n+=75) {
		fern(730,n,50, 3*M_PI/2);
	}

// Loop Picture
	char c;
	while(1) {
		if (gfx_event_waiting()) {
			c = gfx_wait();
			if (c=='q') {
				return 0;
			}
		}	
	}

}
void fern(double xi, double yi, double length, double theta) {

	// Base Case
		if (length < 1) return;

	// Draw Lines
		double xf = xi + length*cos(theta);
                double yf = yi + length*sin(theta);
                gfx_line(xi, yi, xf, yf);

	// Change Variables
		double x1 = xf - (length/4)*cos(theta);
                double y1 = yf - (length/4)*sin(theta);
                double x2 = xf - (length/2)*cos(theta);
                double y2 = yf - (length/2)*sin(theta);
                double x3 = xf - (3*length/4)*cos(theta);
                double y3 = yf - (3*length/4)*sin(theta);

	// Recursive Calls
		fern(xf, yf, length/3.5, theta-M_PI/6);
                fern(xf, yf, length/3.5, theta+M_PI/6);
                fern(x1, y1, length/3.5, theta-M_PI/6);
                fern(x1, y1, length/3.5, theta+M_PI/6);
                fern(x2, y2, length/3.5, theta-M_PI/6);
                fern(x2, y2, length/3.5, theta+M_PI/6);
                fern(x3, y3, length/3.5, theta-M_PI/6);
                fern(x3, y3, length/3.5, theta+M_PI/6);
}
