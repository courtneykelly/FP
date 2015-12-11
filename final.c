//Final Project
//Sheep Game
//Katie Schermerhorn and Courtney Kelly


#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include "gfx4.h"

typedef struct pig {
  double xcenter;
  double ycenter;
  double vx;
  double vy;
} pig_t;

void drawpig(double,double);
void animatepig(pig_t pig[], int, double, double);
void mouseEffect(pig_t pig[]);

int main(void){

  double height= 700;
  double width = 750;
  int i;
  int loop=1;
  //double randomSpeeds[5]= {1,-1,1,0.5,-0.5};
  pig_t pig[5];
  gfx_open(width,height,"Save the Swine");

  //initial position and speed of pig 
  for(i=0;i<5;i++) {
    pig[i].xcenter=rand() % 750;
    pig[i].ycenter=rand() % 750;
    pig[i].vx= rand() % 10 -5;//randomSpeeds[rand() % 4];
    pig[i].vy= rand() % 10 -5;//randomSpeeds[rand() % 4];
  }

  // Animation Loop
    while(loop) {
      gfx_clear();
      for(i=0;i<4;i++) {
        animatepig(pig,i,width,height);
      }
    }

}

void drawpig(double xcenter, double ycenter){
  gfx_color(238,70,215);
  gfx_circle(xcenter,ycenter,20);
  gfx_circle(xcenter,ycenter,10);
  gfx_circle(xcenter+3,ycenter-2,2);
  gfx_circle(xcenter-3,ycenter-2,2);
  gfx_circle(xcenter+(5*sqrt(2))+4,ycenter-(5*sqrt(2)),4);
  gfx_circle(xcenter-(5*sqrt(2))-4,ycenter-(5*sqrt(2)),4);

  gfx_line(xcenter+(10*sqrt(2)),ycenter+(10*sqrt(2)),xcenter+(10*sqrt(2))+4,ycenter+(10*sqrt(2))+4);
  gfx_line(xcenter-(10*sqrt(2)),ycenter+(10*sqrt(2)),xcenter-(10*sqrt(2))-4,ycenter+(10*sqrt(2))+4);

}

void animatepig(pig_t pig[], int i, double width, double height){

  int x;
  double dt=.3;

  drawpig(pig[i].xcenter,pig[i].ycenter);
  gfx_flush();
  pig[i].xcenter=pig[i].xcenter + pig[i].vx*dt;
  pig[i].ycenter=pig[i].ycenter + pig[i].vy*dt;

  //wall collision detect
  if(pig[i].xcenter >= (width-20))
    pig[i].vx = - pig[i].vx;
  else if( pig[i].xcenter <= 20)
    pig[i].vx = -pig[i].vx;
  else if(pig[i].ycenter >= (height-20))
    pig[i].vy = -pig[i].vy;
  else if( pig[i].ycenter <= 20)
    pig[i].vy = -pig[i].vy;

  //pig collision detect
  for(x=(i+1);x<4;x++){
    if((abs(pig[i].xcenter - pig[x].xcenter) <= 50) && (abs(pig[i].ycenter - pig[x].ycenter) <= 50)){
      pig[i].vx = - pig[i].vx;
      pig[i].vy = - pig[i].vy;
      }
    }
  for(x=0;x<i;x++){
    if((abs(pig[i].xcenter - pig[x].xcenter) <= 50) && (abs(pig[i].ycenter - pig[x].ycenter) <= 50)){
      pig[i].vx = - pig[i].vx;
      pig[i].vy = - pig[i].vy;
      }
    }

   gfx_flush();
   usleep(1000);

   mouseEffect(pig);

                                                  
 }

void mouseEffect(pig_t pig[]){

  //get mouse position
  double xmouse;
  double ymouse;
  int event,x;

  if(gfx_event_waiting()) {
    event=gfx_wait();
    if(event==1){
      xmouse = gfx_xpos();
      ymouse = gfx_ypos();
      for(x=0;x<4;x++) {
	if((abs(xmouse - pig[x].xcenter) <= 100) && (abs(ymouse - pig[x].ycenter) <= 100)) {
	  pig[x].vx = (pig[x].xcenter - xmouse) * 0.1;
	  pig[x].vy = (ymouse - pig[x].ycenter) * 0.1;
	}
      }
    }
  }
}
