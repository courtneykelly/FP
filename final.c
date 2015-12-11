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
void fern(double, double, double, double);
void colorFarm();

int main(void){

  double height= 700;
  double width = 750;
  int i;
  int loop=1;
  //double randomSpeeds[5]= {1,-1,1,0.5,-0.5};
  pig_t pig[5];
  gfx_open(width,height,"Save the Swine");
  void colorFarm();

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
void colorFarm() {
  // polygon array
    XPoint xp = {300,450};
    XPoint barnRoof[8]={{625,450},{500,550},{750,550},{625,450}};
    int sizeRoof = sizeof(barnRoof)/sizeof(XPoint);
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
