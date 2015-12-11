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

char *num2str(int);
void displayStats(int,int);
void displayEndScreen(int, int, int);
void drawpig(double,double);
int animatepig(pig_t pig[], int, double, double,int,int,int);
void mouseEffect(pig_t pig[],int);
int checklocation(pig_t pig[],int ,int);
void fern(double, double, double, double);
void colorFarm();
void drawWolf(int, int);

int main(void){

  double height= 750;
  double width = 750;
  int i, pigsSaved = 0, pigsKilled = 0;
  int loop=1;
  int numPigs = 4;
  pig_t pig[numPigs];
  gfx_open(width,height,"Save the Swine");
  //colorFarm();

  //initial position and speed of pig 
  for(i=0;i<numPigs;i++) {
    pig[i].xcenter=rand() % 750;
    pig[i].ycenter=rand() % 750;
    pig[i].vx= rand() % 10 -5;
    pig[i].vy= rand() % 10 -5;
  }

  // Animation Loop
    while(loop) {
      gfx_clear();
      drawWolf(250,250);
      colorFarm();
      displayStats(pigsSaved, pigsKilled);
      for(i=0;i<numPigs;i++) {
        pigsSaved = animatepig(pig,i,width,height,pigsSaved,pigsKilled,numPigs);
      }
      /*if(pigsSaved == numPigs) {
	displayEndScreen(numPigs,pigsSaved,pigsKilled);
	numPigs+=3;
	pigsSaved=0;
	pigsKilled = 0;
    
	}*/
    }

}

char *num2str(int number)
{
  static char a[10], *string=a;
  snprintf(string,10,"%d",number);
  return string;
}

void displayStats(int pigsSaved, int pigsKilled) {
  gfx_color(255,0,0);
  char *saveStr, *killStr;

  saveStr = num2str(pigsSaved);
  gfx_text(10, 10, "Pigs Saved:");
  gfx_text(20, 30, saveStr);

  killStr = num2str(pigsKilled);
  gfx_text(650, 10, "Pigs Killed:");
  gfx_text(660, 30, killStr);
}

void displayEndScreen(int numPigs, int pigsSaved, int pigsKilled){
  if(numPigs == pigsSaved) {  
    gfx_text(375, 375, "Congratulations!! You passed the level!");
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

int animatepig(pig_t pig[], int i, double width, double height, int pigsSaved, int pigsKilled,int numPigs){

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
  for(x=(i+1);x<numPigs;x++){
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

   pigsSaved = checklocation(pig,i,pigsSaved);

   mouseEffect(pig,numPigs);

   return pigsSaved;
                                                  
 }

int checklocation(pig_t pig[],int i,int pigsSaved){

  if((pig[i].xcenter >= 500) && (pig[i].ycenter >= 550)) {
    pig[i].xcenter = 800;
    pig[i].ycenter = 0;
    pig[i].vx = 0;
    pig[i].vy = 0;
    pigsSaved++;
  }

  return pigsSaved;
}

void mouseEffect(pig_t pig[],int numPigs){

  //get mouse position
  double xmouse;
  double ymouse;
  int event,x;

  if(gfx_event_waiting()) {
    event=gfx_wait();
    if(event==1){
      xmouse = gfx_xpos();
      ymouse = gfx_ypos();
      for(x=0;x<numPigs;x++) {
	if((abs(xmouse - pig[x].xcenter) <= 100) && (abs(ymouse - pig[x].ycenter) <= 100)) {
	  if(pig[x].ycenter != ymouse){
	    pig[x].vy = - ((ymouse - pig[x].ycenter) / (xmouse - pig[x].xcenter));
	    pig[x].vx = 1; 
	  }
	  else if((pig[x].ycenter == ymouse) && (xmouse > pig[x].xcenter)) {
	    pig[x].vy = 0;
	    pig[x].vx = -1;
	  }
	  else if((pig[x].ycenter == ymouse) &&(xmouse < pig[x].xcenter)) {
            pig[x].vy = 0;
            pig[x].vx = 1;
          }
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

  gfx_flush();

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
