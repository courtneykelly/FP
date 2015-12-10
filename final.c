//Final Project
//Sheep Game
//Katie Schermerhorn and Courtney Kelly


#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "gfx4.h"

typedef struct sheep {
  int xcenter;
  int ycenter;
  double vx;
  double vy;
} sheep_t;

void drawsheep(int,int);
void animatesheep(sheep_t sheep[], int, int, int);

int main(void){

  int height= 750;
  int width = 750;
  int i;
  int loop=1;
  int randomSpeeds[3]= {0,-1,1};
  sheep_t sheep[5];
  gfx_open(width,height,"Sheep Game");



  //initial position and speed
  for(i=0;i<5;i++) {
    sheep[i].xcenter=rand() % width;
    sheep[i].ycenter=rand() % height;
    sheep[i].vx= randomSpeeds[rand() % 2];
    sheep[i].vy= randomSpeeds[rand() % 2];
  }

 


  while(loop) {

    gfx_clear();

    for(i=0;i<4;i++) {
      animatesheep(sheep,i,width,height);
    }
  }

}


void drawsheep(int xcenter, int ycenter){
  gfx_circle(xcenter,ycenter,20);
  gfx_circle(xcenter,ycenter,10);
  gfx_circle(xcenter+3,ycenter-2,2);
  gfx_circle(xcenter-3,ycenter-2,2);
  gfx_circle(xcenter+(5*sqrt(2))+4,ycenter-(5*sqrt(2)),4);
  gfx_circle(xcenter-(5*sqrt(2))-4,ycenter-(5*sqrt(2)),4);

  gfx_line(xcenter+(10*sqrt(2)),ycenter+(10*sqrt(2)),xcenter+(10*sqrt(2))+4,ycenter+(10*sqrt(2))+4);
  gfx_line(xcenter-(10*sqrt(2)),ycenter+(10*sqrt(2)),xcenter-(10*sqrt(2))-4,ycenter+(10*sqrt(2))+4);

}

void animatesheep(sheep_t sheep[],int i, int width, int height){

  drawsheep(sheep[i].xcenter,sheep[i].ycenter);
  gfx_flush();
  sheep[i].xcenter=sheep[i].xcenter + sheep[i].vx * 0.1;
  sheep[i].ycenter=sheep[i].ycenter + sheep[i].vy * 0.1;

  //wall collision detect
  if(sheep[i].xcenter >= width)
    sheep[i].vx = - sheep[i].vx;
  else if( sheep[i].xcenter <= 20)
    sheep[i].vx = -sheep[i].vx;
  else if(sheep[i].ycenter >= height)
    sheep[i].vy = -sheep[i].vy;
  else if( sheep[i].ycenter <= 20)
     sheep[i].vy = -sheep[i].vy;

   gfx_flush();
   usleep(2000);
                                                  
 }
