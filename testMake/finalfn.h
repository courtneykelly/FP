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