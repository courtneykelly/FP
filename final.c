//Final Project
//Sheep Game
//Katie Schermerhorn and Courtney Kelly


#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "gfx4.h"

typedef struct pig {
  int xcenter;
  int ycenter;
  double vx;
  double vy;
} pig_t;

void drawpig(int,int);
void animatepig(sheep_t sheep[], int, int, int);

int main(void){

  int height= 750;
  int width = 750;
  int i;
  int loop=1;
  double randomSpeeds[3]= {0,-1,1};
  sheep_t pig[5];
  gfx_open(width,height,"Save the Swine");

  //initial position and speed of pig 
  for(i=0;i<5;i++) {
    pig[i].xcenter=rand() % width;
    pig[i].ycenter=rand() % height;
    pig[i].vx= randomSpeeds[rand() % 2];
    pig[i].vy= randomSpeeds[rand() % 2];
  }

  // Animation Loop
    while(loop) {
      gfx_clear();
      for(i=0;i<4;i++) {
        animatepig(pig,i,width,height);
      }
    }

}

void drawpig(int xcenter, int ycenter){
  gfx_circle(xcenter,ycenter,20);
  gfx_circle(xcenter,ycenter,10);
  gfx_circle(xcenter+3,ycenter-2,2);
  gfx_circle(xcenter-3,ycenter-2,2);
  gfx_circle(xcenter+(5*sqrt(2))+4,ycenter-(5*sqrt(2)),4);
  gfx_circle(xcenter-(5*sqrt(2))-4,ycenter-(5*sqrt(2)),4);

  gfx_line(xcenter+(10*sqrt(2)),ycenter+(10*sqrt(2)),xcenter+(10*sqrt(2))+4,ycenter+(10*sqrt(2))+4);
  gfx_line(xcenter-(10*sqrt(2)),ycenter+(10*sqrt(2)),xcenter-(10*sqrt(2))-4,ycenter+(10*sqrt(2))+4);

}

void animatepig(pig_t pig[], int i, int width, int height){

  drawpig(pig[i].xcenter,pig[i].ycenter);
  gfx_flush();
  pig[i].xcenter=pig[i].xcenter + pig[i].vx * 0.1;
  pig[i].ycenter=pig[i].ycenter + pig[i].vy * 0.1;

  //wall collision detect
  if(pig[i].xcenter >= width)
    pig[i].vx = - pig[i].vx;
  else if( pig[i].xcenter <= 20)
    pig[i].vx = -pig[i].vx;
  else if(pig[i].ycenter >= height)
    pig[i].vy = -pig[i].vy;
  else if( pig[i].ycenter <= 20)
    pig[i].vy = -pig[i].vy;

   gfx_flush();
   usleep(2000);
                                                  
 }
