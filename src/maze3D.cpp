#include <math.h>
#include <stdio.h>
#include <vector>
#include "maze3D.h"
#include "maze.h"
#include "fssimplewindow.h"

////////// Camera Object /////////////
CameraObject::CameraObject()
{
    Initialize();
}

void CameraObject::Initialize(void)
{
    x=0;
    y=0;
    z=0;
    h=0;
    p=0;
    b=0;

    fov=myPi/6.0;  // 30 degree
    nearZ=0.1;
    farZ=1000;
}

void CameraObject::SetUpCameraProjection(void)
{
    int wid,hei;
    double aspect;

    FsGetWindowSize(wid,hei);
    aspect=(double)wid/(double)hei;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov*180.0/myPi,aspect,nearZ,farZ);
}

void CameraObject::SetUpCameraTransformation(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(-b*180.0/myPi,0.0,0.0,1.0);
    glRotated(-p*180.0/myPi,1.0,0.0,0.0);
    glRotated(-h*180.0/myPi,0.0,1.0,0.0);
    glTranslated(-x,-y,-z);
}

void CameraObject::GetForwardVector(double &vx,double &vy,double &vz)
{
    vx=-cos(p)*sin(h);
    vy= sin(p);
    vz=-cos(p)*cos(h);
}

////////// Orbit Viewer /////////////
OrbitingViewer::OrbitingViewer()
{
    Initialize();
}

void OrbitingViewer::Initialize(void)
{
    h=0;
    p=0;
    dist=500.0;
    focusX=0.0;
    focusY=0.0;
    focusZ=0.0;
}

void OrbitingViewer::SetUpCamera(CameraObject &camera)
{
    camera.h=h;
    camera.p=p;
    camera.b=0.0;

    double vx,vy,vz;
    camera.GetForwardVector(vx,vy,vz);
    camera.x=focusX-vx*dist;
    camera.y=focusY-vy*dist;
    camera.z=focusZ-vz*dist;
}

////////// Maze_3D /////////////

Maze_3D::Maze_3D(){
  maze = new int*[blockNumber];
  for(int i = 0;i < blockNumber;i++){
    maze[i] = new int [blockNumber];
  }
  curState = 0;
  for(int i = 0;i < blockNumber;i++){
    for(int j = 0;j < blockNumber;j++){
      maze[i][j] = 1;
    }
  }
}


Maze_3D::~Maze_3D(){
  for(int i = 0;i < blockNumber;i++){
    delete [] maze[i];
  }
  delete [] maze;
}

void Maze_3D::SetMaze(int i,int j,int input){
  maze[i][j] = input;
}

void Maze_3D::SetOrientation(char orient){
  orientation = orient;

  switch(orient){
    case 'T':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 2*blockNumber*blockSize_3D;
      origin.y = 0;

      // Giada's Edition
      origin3.x = -blockNumber*blockSize_3D*0.5;
      origin3.y =  blockNumber*blockSize_3D*0.5;
      origin3.z = -blockNumber*blockSize_3D*0.5;
      nextX.x   = 1;
      nextX.y   = 0;
      nextX.z   = 0;
      nextY.x   = 0;
      nextY.y   = 0;
      nextY.z   = 1;

      break;
    case 'B':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 2*blockNumber*blockSize_3D;
      origin.y = 2*blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x = -blockNumber*blockSize_3D*0.5;
      origin3.y = -blockNumber*blockSize_3D*0.5;
      origin3.z =  blockNumber*blockSize_3D*0.5;
      nextX.x   = 1;
      nextX.y   = 0;
      nextX.z   = 0;
      nextY.x   = 0;
      nextY.y   = 0;
      nextY.z   = -1;

      break;
    case 'N':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 0;
      origin.y = blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x =  (blockNumber  )*blockSize_3D*0.5;
      origin3.y =  (blockNumber  )*blockSize_3D*0.5;
      origin3.z = -(blockNumber)*blockSize_3D*0.5;
      nextX.x   = -1;
      nextX.y   = 0;
      nextX.z   = 0;
      nextY.x   = 0;
      nextY.y   = -1;
      nextY.z   = 0;

      break;
    case 'W':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = blockNumber*blockSize_3D;
      origin.y = blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x = -blockNumber*blockSize_3D*0.5;
      origin3.y =  blockNumber*blockSize_3D*0.5;
      origin3.z = -blockNumber*blockSize_3D*0.5;
      nextX.x   = 0;
      nextX.y   = 0;
      nextX.z   = 1;
      nextY.x   = 0;
      nextY.y   = -1;
      nextY.z   = 0;

      break;
    case 'S':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 2*blockNumber*blockSize_3D;
      origin.y = blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x = -(blockNumber)*blockSize_3D*0.5;
      origin3.y =  (blockNumber)*blockSize_3D*0.5;
      origin3.z =  (blockNumber)*blockSize_3D*0.5;
      nextX.x   = 1;
      nextX.y   = 0;
      nextX.z   = 0;
      nextY.x   = 0;
      nextY.y   = -1;
      nextY.z   = 0;

      break;
    case 'E':
      baseColor.r = 0;
      baseColor.g = 0;
      baseColor.b = 175;
      origin.x = 3*blockNumber*blockSize_3D;
      origin.y = blockNumber*blockSize_3D;

      // Giada's Edition
      origin3.x = (blockNumber)*blockSize_3D*0.5;
      origin3.y = (blockNumber)*blockSize_3D*0.5;
      origin3.z = (blockNumber)*blockSize_3D*0.5;
      nextX.x   = 0;
      nextX.y   = 0;
      nextX.z   = -1;
      nextY.x   = 0;
      nextY.y   = -1;
      nextY.z   = 0;
      break;

  }
}

const int Maze_3D::ReturnElement(int i,int j)const{
  return maze[i][j];
}

void Maze_3D::Print(){
  printf("Orientation = %c\n",orientation);
  for(int i = 0;i < blockNumber;i++){
    for(int j = 0;j < blockNumber;j++){
      printf("%d ",maze[i][j]);
    }
    printf("\n");
  }
}

void Maze_3D::Activate(Coord_3D cur,int state){
  cursor.x = cur.x;
  cursor.y = cur.y;
  cursor.xdir = cur.xdir;
  cursor.ydir = cur.ydir;
  curState = state;
  if(curState == 2){
    maze[cursor.x][cursor.y] = 0;
  }
  if(curState == 3){
    maze[cursor.x][cursor.y] = 1;
  }
}

void Maze_3D::Deactivate(){
  curState = 0;
}

void Maze_3D::Draw3D()
{
    double x,y,z;
    int surface,gx,gy;

    for(int i = 0;i < blockNumber;i++){
      for(int j = 0;j < blockNumber;j++){

        x = (double)(origin3.x + nextX.x*blockSize_3D*i + nextY.x*blockSize_3D*j);
        y = (double)(origin3.y + nextX.y*blockSize_3D*i + nextY.y*blockSize_3D*j);
        z = (double)(origin3.z + nextX.z*blockSize_3D*i + nextY.z*blockSize_3D*j);

        if (curState > 0 && cursor.x == i && cursor.y == j) DrawPacMan(x,y,z);

        else {
          if (maze[i][j] == 1) {
            glColor3ub(baseColor.r,baseColor.g,baseColor.b);
            glBegin(GL_QUADS);
            glVertex3d(origin3.x + nextX.x*blockSize_3D*i     + nextY.x*blockSize_3D*j,
                       origin3.y + nextX.y*blockSize_3D*i     + nextY.y*blockSize_3D*j,
                       origin3.z + nextX.z*blockSize_3D*i     + nextY.z*blockSize_3D*j    );
            glVertex3d(origin3.x + nextX.x*blockSize_3D*(i+1) + nextY.x*blockSize_3D*j,
                       origin3.y + nextX.y*blockSize_3D*(i+1) + nextY.y*blockSize_3D*j,
                       origin3.z + nextX.z*blockSize_3D*(i+1) + nextY.z*blockSize_3D*j    );
            glVertex3d(origin3.x + nextX.x*blockSize_3D*(i+1) + nextY.x*blockSize_3D*(j+1),
                       origin3.y + nextX.y*blockSize_3D*(i+1) + nextY.y*blockSize_3D*(j+1),
                       origin3.z + nextX.z*blockSize_3D*(i+1) + nextY.z*blockSize_3D*(j+1));
            glVertex3d(origin3.x + nextX.x*blockSize_3D*i     + nextY.x*blockSize_3D*(j+1),
                       origin3.y + nextX.y*blockSize_3D*i     + nextY.y*blockSize_3D*(j+1),
                       origin3.z + nextX.z*blockSize_3D*i     + nextY.z*blockSize_3D*(j+1));
            glEnd();
          }
          else if (maze[i][j] == 0) DrawPerl(x,y,z);
          else if (maze[i][j] == 3) DrawSuperPerl(x,y,z);
          else if (maze[i][j] == 2) DrawCherry(x,y,z);
          else if (maze[i][j] == -1) {
            glColor3ub(0,0,0);
            glBegin(GL_QUADS);
            glVertex3d(origin3.x + nextX.x*blockSize_3D*i     + nextY.x*blockSize_3D*j,
                       origin3.y + nextX.y*blockSize_3D*i     + nextY.y*blockSize_3D*j,
                       origin3.z + nextX.z*blockSize_3D*i     + nextY.z*blockSize_3D*j    );
            glVertex3d(origin3.x + nextX.x*blockSize_3D*(i+1) + nextY.x*blockSize_3D*j,
                       origin3.y + nextX.y*blockSize_3D*(i+1) + nextY.y*blockSize_3D*j,
                       origin3.z + nextX.z*blockSize_3D*(i+1) + nextY.z*blockSize_3D*j    );
            glVertex3d(origin3.x + nextX.x*blockSize_3D*(i+1) + nextY.x*blockSize_3D*(j+1),
                       origin3.y + nextX.y*blockSize_3D*(i+1) + nextY.y*blockSize_3D*(j+1),
                       origin3.z + nextX.z*blockSize_3D*(i+1) + nextY.z*blockSize_3D*(j+1));
            glVertex3d(origin3.x + nextX.x*blockSize_3D*i     + nextY.x*blockSize_3D*(j+1),
                       origin3.y + nextX.y*blockSize_3D*i     + nextY.y*blockSize_3D*(j+1),
                       origin3.z + nextX.z*blockSize_3D*i     + nextY.z*blockSize_3D*(j+1));
            glEnd();
          }
        }

        for(int n=0; n<ghost.size(); n++) {
          int i = ghost[n].x;
          int j = ghost[n].y;
          int xdir = ghost[n].xdir;
          int ydir = ghost[n].ydir;
          x = (double)(origin3.x + nextX.x*blockSize_3D*i + nextY.x*blockSize_3D*j);
          y = (double)(origin3.y + nextX.y*blockSize_3D*i + nextY.y*blockSize_3D*j);
          z = (double)(origin3.z + nextX.z*blockSize_3D*i + nextY.z*blockSize_3D*j);

          switch(orientation){
            case 'T':
              y += 0.75;
              break;
            case 'B':
              y -= 0.75;
              break;
            case 'N':
              z -= 0.75;
              break;
            case 'W':
              x -= 0.75;
              break;
            case 'S':
              z += 0.75;
              break;
            case 'E':
              x += 0.75;
              break;
          }
          DrawGhost(x,y,z,xdir,ydir);
        }
      }
    }
}

void Maze_3D::DrawPerl(double drawX, double drawY, double drawZ) {
	double x_2D, y_2D;
	char pattern[] =
	{
    "..."
    ".0."
    "..."
	};
  int i=0, j=0;
  double unit = 2.33334;
	for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=unit) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=unit) {
      int bit = (int)((x_2D/unit)+((y_2D/unit)*3));
			if (pattern[bit] == '0') glColor3ub(255,255,255);
      else glColor3ub(0,0,0);
      glBegin(GL_QUADS);
      glVertex3d( drawX + (x_2D  )*nextX.x + (y_2D  )*nextY.x,
                  drawY + (x_2D  )*nextX.y + (y_2D  )*nextY.y,
                  drawZ + (x_2D  )*nextX.z + (y_2D  )*nextY.z  );
      glVertex3d( drawX + (x_2D+unit)*nextX.x + (y_2D  )*nextY.x,
                  drawY + (x_2D+unit)*nextX.y + (y_2D  )*nextY.y,
                  drawZ + (x_2D+unit)*nextX.z + (y_2D  )*nextY.z  );
      glVertex3d( drawX + (x_2D+unit)*nextX.x + (y_2D+unit)*nextY.x,
                  drawY + (x_2D+unit)*nextX.y + (y_2D+unit)*nextY.y,
                  drawZ + (x_2D+unit)*nextX.z + (y_2D+unit)*nextY.z  );
      glVertex3d( drawX + (x_2D  )*nextX.x + (y_2D+unit)*nextY.x,
                  drawY + (x_2D  )*nextX.y + (y_2D+unit)*nextY.y,
                  drawZ + (x_2D  )*nextX.z + (y_2D+unit)*nextY.z  );
			glEnd();
		}
	}
}

void Maze_3D::DrawSuperPerl(double drawX, double drawY, double drawZ) {
	double x_2D, y_2D;
	char pattern[] =
	{
		".............."
		".............."
		".............."
		".....1000....."
		"....110000...."
		"...11000000..."
		"...11000000..."
		"...11000000..."
		"...11000000..."
		"....110000...."
		".....1000....."
		".............."
		".............."
	};
	for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=0.5) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=0.5) {
      int bit = (int)((x_2D*2)+((y_2D*2)*14));
			if      (pattern[bit] == '0') glColor3ub(255,255,50);
      else if (pattern[bit] == '1') glColor3ub(255,155,50);
      else glColor3ub(0,0,0);
      glBegin(GL_QUADS);
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D+0.5)*nextY.z  );
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D+0.5)*nextY.z  );
			glEnd();
		}
	}
}

void Maze_3D::DrawCherry(double drawX, double drawY, double drawZ) {
	double x_2D, y_2D;
	char pattern[] =
	{
		".............."
		"............22"
		"..........2222"
		"........22.2.."
		".......2...2.."
		"..11112...2..."
		".1111211.2...."
		".111111.1211.."
		".10111.112111."
		".11011.111111."
		"..1111.101111."
		".......110111."
		"........1111.."
	};
	for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=0.5) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=0.5) {
      int bit = (int)((x_2D*2)+((y_2D*2)*14));
			if      (pattern[bit] == '0') glColor3ub(255,255,255);
			else if (pattern[bit] == '1') glColor3ub(242,  0,  0);
			else if (pattern[bit] == '2') glColor3ub(170,138, 67);
      else glColor3ub(0,0,0);
      glBegin(GL_QUADS);
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D+0.5)*nextY.z  );
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D+0.5)*nextY.z  );
			glEnd();
		}
	}
}

void Maze_3D::DrawPacMan(double drawX, double drawY, double drawZ) {
	double x_2D, y_2D;
	char pattern[] =
	{
    ".....44444...."
		"...444444444.."
		"..44444444444."
		"..444444444444"
		".4444444444..."
		".44444444....."
		".444444......."
		".444444......."
		".44444444....."
		".4444444444..."
		"..444444444444"
		"..44444444444."
		"...444444444.."
		".....44444...."
	};

	for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=0.5) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=0.5) {

      double i=x_2D, j=y_2D;
      if (cursor.xdir == -1 && cursor.ydir == 0) { // left
        i = (blockSize_3D-0.5) - x_2D;
        j = y_2D;
      }
      else if (cursor.xdir == 0 && cursor.ydir == 1) { // up
        i = y_2D;
        j = (blockSize_3D-0.5) - x_2D;
      }
      else if (cursor.xdir == 0 && cursor.ydir == -1) { // down
        i = (blockSize_3D-0.5) - y_2D;
        j = (blockSize_3D-0.5) - x_2D;
      }

      int bit = (int)((i*2)+((j*2)*14));
			if (pattern[bit] == '4') glColor3ub(255,255,  0);
      else                                  glColor3ub(0,0,0);
      glBegin(GL_QUADS);
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D+0.5)*nextY.z  );
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D+0.5)*nextY.z  );
			glEnd();
		}
	}
}



void Maze_3D::DrawGhost(double drawX, double drawY, double drawZ, int xdir, int ydir) {
	double x_2D, y_2D;
  int i, j;
  char patternLeft[] =
  {
    ".....____....."
    "...________..."
    "..__________.."
    "._11____11___."
    ".2211__2211__."
    ".2211__2211__."
    "_2211__2211___"
    "__11____11____"
    "______________"
    "______________"
    "______________"
    "______________"
    "__.___..___.__"
    "_...__..__..._"
  };
  char patternRight[] =
  {
    ".....____....."
    "...________..."
    "..__________.."
    ".___11____11_."
    ".__1122__1122."
    ".__1122__1122."
    "___1122__1122_"
    "____11____11__"
    "______________"
    "______________"
    "______________"
    "______________"
    "__.___..___.__"
    "_...__..__..._"
  };
  char patternUp[] =
  {
    ".....____....."
    "...________..."
    ".._22____22_.."
    "._1221__1221_."
    "._1221__1221_."
    "__1111__1111__"
    "___11____11___"
    "______________"
    "______________"
    "______________"
    "______________"
    "______________"
    "__.___..___.__"
    "_...__..__..._"
  };
  char patternDown[] =
  {
    ".....____....."
    "...________..."
    "..__________.."
    "._11____11___."
    ".1111__1111__."
    ".1221__1221__."
    "_1221__1221___"
    "__22____22____"
    "______________"
    "______________"
    "______________"
    "______________"
    "__.___..___.__"
    "_...__..__..._"
  };
  char patternVulnerable[] =
  {
    ".....____....."
    "...________..."
    "..__________.."
    ".__11____11__."
    "._1111__1111_."
    ".__11____11__."
    "______________"
    "______________"
    "__111____111__"
    "_111111111111_"
    "_1___1111___1_"
    "______________"
    "__.___..___.__"
    "_...__..__..._"
  };

  for (y_2D = 0.0; y_2D < blockSize_3D; y_2D+=0.5) {
		for (x_2D = 0.0; x_2D < blockSize_3D; x_2D+=0.5) {
      int bit = (int)((x_2D*2)+((y_2D*2)*14));
      if (cursor.powerState) {
        if      (patternVulnerable[bit] == '_') glColor3ub(150,  0,255);
        else if (patternVulnerable[bit] == '1') glColor3ub(  0,  0,  0);
        else glColor3ub(0,0,0);
      }
      else {
        if      ((xdir == -1 && ydir ==  0 && patternLeft[bit]  == '_') ||
                 (xdir ==  1 && ydir ==  0 && patternRight[bit] == '_') ||
                 (xdir ==  0 && ydir == -1 && patternUp[bit]    == '_') ||
                 (xdir ==  0 && ydir ==  1 && patternDown[bit]  == '_') ||
                 (xdir ==  0 && ydir ==  0 && patternRight[bit] == '_')) {
                    glColor3ub(255,  0,  0);
                  }
        else if ((xdir == -1 && ydir ==  0 && patternLeft[bit]  == '1') ||
                 (xdir ==  1 && ydir ==  0 && patternRight[bit] == '1') ||
                 (xdir ==  0 && ydir == -1 && patternUp[bit]    == '1') ||
                 (xdir ==  0 && ydir ==  1 && patternDown[bit]  == '1') ||
                 (xdir ==  0 && ydir ==  0 && patternRight[bit] == '1')) {
                    glColor3ub(255,255,255);
                  }
        else if ((xdir == -1 && ydir ==  0 && patternLeft[bit]  == '2') ||
                 (xdir ==  1 && ydir ==  0 && patternRight[bit] == '2') ||
                 (xdir ==  0 && ydir == -1 && patternUp[bit]    == '2') ||
                 (xdir ==  0 && ydir ==  1 && patternDown[bit]  == '2') ||
                 (xdir ==  0 && ydir ==  0 && patternRight[bit] == '2')) {
                    glColor3ub(  0,  0,255);
                  }
        else glColor3ub(0,0,0);
      }

      glBegin(GL_QUADS);
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D    )*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D    )*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D    )*nextY.z  );
      glVertex3d( drawX + (x_2D+0.5)*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D+0.5)*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D+0.5)*nextX.z + (y_2D+0.5)*nextY.z  );
      glVertex3d( drawX + (x_2D    )*nextX.x + (y_2D+0.5)*nextY.x,
                  drawY + (x_2D    )*nextX.y + (y_2D+0.5)*nextY.y,
                  drawZ + (x_2D    )*nextX.z + (y_2D+0.5)*nextY.z  );
			glEnd();
    }
  }
}


////////// Full Maze 3D /////////////

FullMaze_3D::FullMaze_3D(){
  maze[0].SetOrientation('T');
  maze[1].SetOrientation('N');
  maze[2].SetOrientation('W');
  maze[3].SetOrientation('S');
  maze[4].SetOrientation('E');
  maze[5].SetOrientation('B');
  curSurface = 'S';
  curState = 1;
  cursor.x = rand()%blockNumber;
  cursor.y = rand()%blockNumber;
  maze[3].Activate(cursor,curState);
};

void FullMaze_3D::PrintGhost(){
  for(int i = 0;i < 6;i++){
    printf("%ld,",maze[i].ghost.size());
  }
  printf("\n");
}

void FullMaze_3D::SetGhost(std::vector<Ghost> *ghostInfo){
  int n = ghostInfo->size();
  for(int i = 0;i < 6;i++){
    maze[i].ghost.clear();
  }
  for(int i = 0;i < n;i++){
    int surface = ghostInfo->at(i).surface;
    maze[surface].ghost.push_back(ghostInfo->at(i));
  }
}

void FullMaze_3D::SetCursor(PacMan pacman){
  switch(pacman.surface){
    case 0:
      curSurface = 'T';
      break;
    case 1:
      curSurface = 'N';
      break;
    case 2:
      curSurface = 'W';
      break;
    case 3:
      curSurface = 'S';
      break;
    case 4:
      curSurface = 'E';
      break;
    case 5:
      curSurface = 'B';
      break;
  }
  cursor.x    = pacman.x;
  cursor.y    = pacman.y;
  cursor.xdir = pacman.xdir;
  cursor.ydir = pacman.ydir;



  for(int i = 0;i < 6;i++){
    maze[i].Deactivate();
    maze[i].cursor.powerState = pacman.powerState;
  }

  switch(curSurface){
    case 'T':
      maze[0].Activate(cursor,curState);
      break;
    case 'N':
      maze[1].Activate(cursor,curState);
      break;
    case 'W':
      maze[2].Activate(cursor,curState);
      break;
    case 'S':
      maze[3].Activate(cursor,curState);
      break;
    case 'E':
      maze[4].Activate(cursor,curState);
      break;
    case 'B':
      maze[5].Activate(cursor,curState);
      break;
  }
}


void FullMaze_3D::Draw(){
  for(int i = 1;i < 5;i++){
    //printf("full: %d\n", i);
    maze[i].Draw3D();
  }
}

void FullMaze_3D::SetMaze(int ***input){
  for(int i = 0;i < 6;i++){
    for(int j = 0;j < blockNumber;j++){
      for(int k = 0;k < blockNumber;k++){
        maze[i].SetMaze(k,j,input[i][k][j]);
      }
    }
  }
}

void FullMaze_3D::Print(){
  for(int i = 0;i < 6;i++){
    maze[i].Print();
  }
}