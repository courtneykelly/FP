//Final Project
//Sheep Game
//Katie Schermerhorn and Courtney Kelly

#include <stdio.h>
#include <math.h>
#include "gfx4.h"

typedef struct sheep {
  int xcenter;
  int ycenter;
  double vx;
  double vy;
} sheep_t;

void drawsheep(int,int);
void animatesheep(double,double,int,int,int,int);

int main(void){

  int height= 750;
  int width = 750;
  int i;
  gfx_open(width,height,"Sheep Game");

  for(i=0;i<5;i++) {
    sheep[i].xcenter=rand() % width;
    sheep[i].ycenter=rand() % height;
    drawsheep(sheep[i].xcenter , sheep[i].ycenter);
  }



  while(1) {



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

void animatesheep(double vx, double vy, int xcenter, int ycenter, int width, int height){

  gfx_flush();                                                                                          
  xcenter = xcenter + vx*.01;                                                                          
  ycenter = ycenter + vy*.01;

  drawsheep(xcenter,ycenter);                                                                           

  //wall collision detection                                                                             
  if(xcenter >= width)                                                                                  
  vx = -vx;                                                                                            
  else if(ycenter >= height)                                                                            
  vy = -vy;                                                                                                                                                                                         

  gfx_flush();                                                                                          
  usleep(2000);  

}
