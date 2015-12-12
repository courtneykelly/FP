
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "finalfn.h"
#include "gfx4.h"
#include <X11/Xlib.h>

int main(void){

  // Initialize Variables and Window
    double height= 750;
    double width = 750;
    gfx_open(width,height,"Save the Swine");
    int i, n, loop1=1, loop2; 
    int pigsSaved=0, pigsKilled=0, numPigs = 4, numWolves = 2, level=1;
    double random[4] = {-1,1,-2,2};

    while(loop1){

      pig_t pig[numPigs];
      wolf_t wolf[numWolves];

      //initial position and speed of pig 
        for(i=0;i<numPigs;i++) {
          pig[i].xcenter=rand() % 680 +30;
          pig[i].ycenter=rand() % 420 +30;
          pig[i].vx= random[rand() % 1];
          pig[i].vy= random[rand() % 1];
        }

      // Initial Position and Speed of the Wolves
        for (n=0; n<numWolves; n++) {
          wolf[n].xcenter = rand() % 680 +30;
          wolf[n].ycenter = rand() % 420 +30;
          wolf[n].vx = random[rand() % 3];
          wolf[n].vy = random[rand() % 3];
        }

      // Animation Loop
        loop2=1;
        while(loop2) {
          gfx_clear();
          colorFarm();
          displayStats(pigsSaved,pigsKilled);
            for (i=0; i<numPigs; i++) {
              pigsSaved = animatepig(pig,i,width,height,pigsSaved,pigsKilled,numPigs);
            }
            for (n=0; n<numWolves; n++) {
              pigsKilled = animateWolf(wolf, n, width, height, numWolves, pig, numPigs, pigsKilled);
            }
            if (pigsKilled >= ((double)(.25 * numPigs))) {
	      gfx_clear();
              displayEndScreen(numPigs,pigsSaved,pigsKilled);
              return 0;
            }
            if (pigsSaved >= ((double)(.75 * numPigs))) {
	      gfx_clear();
	      level++;
              displayLevelUp(level);
              numPigs+=2;
              numWolves++;
              pigsSaved=0;
              pigsKilled=0;
              loop2=0;
            }
        }
    }

}