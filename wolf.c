
#include <stdio.h>
#include "gfx4.h"

void drawWolf(int, int);

int main() {

	gfx_open(500,500, "Wolf");
	drawWolf(250,250);

	char c;
	while (1) {
		c = gfx_wait();
		if ( c == 'q') {
			return 0;
		}
	}
}
void drawWolf(int x, int y) {
	int n;
	// Blue
		gfx_color(0,255,255);
		gfx_fill_rectangle(0,0,500,500);
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
