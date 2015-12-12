//Final Project
//Save the swine
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

typedef struct wolf {
  double xcenter;
    double ycenter;
    double vx;
    double vy;
} wolf_t;

char *num2str(int);
void displayStats(int,int);
void displayEndScreen(int, int, int);
void drawpig(double,double);
int animatepig(pig_t pig[], int, double, double,int,int,int);
void mouseEffect(pig_t pig[],int);
int checklocation(pig_t pig[],int ,int);
void fern(double, double, double, double);
void colorFarm();
void drawWolf(double, double);
int animateWolf(wolf_t wolf[], int, double, double, int, pig_t pig[], int, int);
int checkWolfLocation(pig_t pig[], wolf_t wolf[], int,int, int);
void displayLevelUp(int);

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

char *num2str(int number)
{
  static char a[10], *string=a;
  snprintf(string,10,"%d",number);
  return string;
}
void displayLevelUp( int level) {
  gfx_color(255,255,255);
  char* levelString = num2str(level);
    gfx_text(250,375, "Congratulations! You Passed the Level!");
    gfx_text(270,390, "Moving on to Level:");
    gfx_text(280,405, levelString);
    gfx_flush();
    usleep(5000000);
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
  gfx_color(255,255,255);
  gfx_text(250,375, "Game over. You failed to save your swine.");
  gfx_flush();
  usleep(5000000);
}

void drawpig(double xcenter, double ycenter){
  gfx_color(238,70,215);
  gfx_fill_circle(xcenter,ycenter,20);
  gfx_color(0,0,0);
  gfx_circle(xcenter,ycenter,10);
  gfx_circle(xcenter+3,ycenter-2,2);
  gfx_circle(xcenter-3,ycenter-2,2);
  gfx_circle(xcenter+(5*sqrt(2))+4,ycenter-(5*sqrt(2)),4);
  gfx_circle(xcenter-(5*sqrt(2))-4,ycenter-(5*sqrt(2)),4);

  gfx_color(238,70,215);
  gfx_line(xcenter+(10*sqrt(2)),ycenter+(10*sqrt(2)),xcenter+(10*sqrt(2))+4,ycenter+(10*sqrt(2))+4);
  gfx_line(xcenter-(10*sqrt(2)),ycenter+(10*sqrt(2)),xcenter-(10*sqrt(2))-4,ycenter+(10*sqrt(2))+4);

}

int animatepig(pig_t pig[], int i, double width, double height, int pigsSaved, int pigsKilled,int numPigs){

  int x;
  double dt=3;

  drawpig(pig[i].xcenter,pig[i].ycenter);
  gfx_flush();
  pig[i].xcenter=pig[i].xcenter + pig[i].vx*dt;
  pig[i].ycenter=pig[i].ycenter + pig[i].vy*dt;

  //pig collision detect                                                                                             
    for(x=(i+1);x<numPigs;x++){
      if((abs(pig[i].xcenter - pig[x].xcenter) <= 50) && (abs(pig[i].ycenter - pig[x].ycenter) <= 50)){
        pig[i].vy= rand() % 2 -1;
        pig[i].vx = rand() % 2 -1;
      } 
    }
    for(x=0;x<i;x++){
      if((abs(pig[i].xcenter - pig[x].xcenter) <= 50) && (abs(pig[i].ycenter - pig[x].ycenter) <= 50)){
        pig[i].vy= rand() % 2 -1;
        pig[i].vx = rand() % 2 -1;
      } 

    }

  //wall collision detect
    if(pig[i].xcenter >= (width-30))
      pig[i].vx = - pig[i].vx;
    else if( pig[i].xcenter <= 30)
      pig[i].vx = -pig[i].vx;
    else if(pig[i].ycenter >= (height-30))
      pig[i].vy = -pig[i].vy;
    else if( pig[i].ycenter <= 30)
      pig[i].vy = -pig[i].vy;


   gfx_flush();
   usleep(10000);

   pigsSaved = checklocation(pig,i,pigsSaved);

   mouseEffect(pig,numPigs);

   return pigsSaved;                                              
 }

int animateWolf( wolf_t wolf[], int i, double width, double height, int numWolves, pig_t pig[], int numPigs, int pigsKilled) {
  int x;
  double dt = 3;
  double random[4] = {-2,-1,1,2};
  
  drawWolf(wolf[i].xcenter, wolf[i].ycenter);
  gfx_flush();
  wolf[i].xcenter = wolf[i].xcenter + wolf[i].vx*dt;
  wolf[i].ycenter = wolf[i].ycenter + wolf[i].vy*dt;


  // Wolf Collision Detect
    for (x=(i+1); x<numWolves; x++) {
      if ((abs(wolf[i].xcenter - wolf[x].xcenter) <= 50) && (abs(wolf[i].ycenter - wolf[x].ycenter) <= 50)){
	wolf[i].vx = random[rand() % 3];
	wolf[i].vy = random[rand() % 3];
      }
    }
    for (x=0; x<i; x++) {
      if ((abs(wolf[i].xcenter - wolf[x].xcenter) <= 50) && (abs(wolf[i].ycenter - wolf[x].ycenter) <= 50)){
	wolf[i].vx = random[rand() % 3];
	wolf[i].vy = random[rand() % 3];
      }
    }

  // Wall Collision Detect
    if (wolf[i].xcenter >= (width-20)){
      wolf[i].vx = -wolf[i].vx;
    }
    else if( wolf[i].xcenter <= 20){
      wolf[i].vx = -wolf[i].vx;
    }
    else if(wolf[i].ycenter >= (height-20)) {
      wolf[i].vy = -wolf[i].vy;
    }
    else if( wolf[i].ycenter <= 20){
      wolf[i].vy = -wolf[i].vy;
    }
    else if((wolf[i].xcenter >= 500) && (wolf[i].ycenter >= 450)) {
      wolf[i].vy = -wolf[i].vy; 
      wolf[i].vx = -wolf[i].vx;
    }

  // Pig Collision Detect
    int p;
    for (p=0; p<numPigs; p++) {
      pigsKilled = checkWolfLocation(pig, wolf, i, p, pigsKilled);
      }

  gfx_flush();
  usleep(10000);

  return pigsKilled;
}
int checkWolfLocation(pig_t pig[], wolf_t wolf[], int i, int p, int pigsKilled) {

  if ((abs(pig[p].xcenter - wolf[i].xcenter) <= 30) && (abs(pig[p].ycenter - wolf[i].ycenter) <= 30)) {
    pig[p].xcenter = 800;
    pig[p].ycenter = 0;
    pig[p].vx = 0;
    pig[p].vy = 0;
    pigsKilled++;
  }
  return pigsKilled;
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
	  if((pig[x].ycenter < ymouse) && (pig[x].xcenter < xmouse)) {
	      pig[x].vx = -1;
	      pig[x].vy = -1;
	    }
	  else if((pig[x].ycenter > ymouse) && (pig[x].xcenter < xmouse)) {
		pig[x].vx = -1;
		pig[x].vy = 1;
	    }
	  else if((pig[x].ycenter > ymouse) && (pig[x].xcenter > xmouse)) {
	    pig[x].vx = 1;
	    pig[x].vy = 1;
	  }
	  else if((pig[x].ycenter < ymouse) && (pig[x].xcenter > xmouse)) {
	    pig[x].vx = 1;
	    pig[x].vy = -1;
	  }
	  else if((pig[x].ycenter < ymouse) && (pig[x].xcenter == xmouse)) {
	    pig[x].vx = 0;
	    pig[x].vy = -1;
	  }
	  else if((pig[x].ycenter > ymouse) && (pig[x].xcenter == xmouse)) {
            pig[x].vx = 0;
            pig[x].vy = 1;
          }
	  else if((pig[x].xcenter < xmouse) && (pig[x].ycenter == ymouse)) {
            pig[x].vx = -1;
            pig[x].vy = 0;
          }
	  else if((pig[x].xcenter > xmouse) && (pig[x].ycenter == ymouse)) {
            pig[x].vx = 1;
            pig[x].vy = 0;
          }
	  else if((pig[x].xcenter == xmouse) && (pig[x].ycenter == ymouse)) {
            pig[x].vx = 0;
            pig[x].vy = 0;
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
void drawWolf(double x, double y) {
  int n;
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
