
#include <stdio.h>
#include "gfx4.h"

/*typedef struct barn {
	double x;
	double y;
} XPoint;
*/
int main() {

// polygon array
	int barnRoof[8]={650,500,500,550,750,550,650,500};
	int n,p=0;
/*	XPoint barn[3];
	for (n=0; n<4; n++) {
		barn[n].x=barnRoof[p];
		barn[n].y=barnRoof[p+1];
		p+=2;
	}
*/

gfx_open(750,750,"The Farm");
gfx_color(0,204,0);
gfx_fill_rectangle(0,0,750,750);
gfx_flush();
gfx_color(255,0,0);
gfx_fill_rectangle(500,550,250,200);
//gfx_fill_polygon(XPoint,8);
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
