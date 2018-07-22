#ifndef MAZE3D_IS_INCLUDED
#define MAZE3D_IS_INCLUDED

#include <vector>
#include "maze.h"

extern int blockSize_3D;
extern const int blockNumber;
extern double myPi;

typedef struct Vector3Struct{
  double x;
  double y;
  double z;
}Vector3;

typedef struct CursorStruct_3D{
  int x;
  int y;
  int z;
  int xdir;
  int ydir;
  bool powerState = false;
}Coord_3D;

class CameraObject
{
  public:
      double x,y,z;
      double h,p,b;

      double fov,nearZ,farZ;

      CameraObject();
      void Initialize(void);
      void SetUpCameraProjection(void);
      void SetUpCameraTransformation(void);
      void GetForwardVector(double &vx,double &vy,double &vz);
};

class OrbitingViewer
{
  public:
      double h,p;
      double dist;
      double focusX,focusY,focusZ;
      OrbitingViewer();
      void Initialize(void);
      void SetUpCamera(CameraObject &camera);
};

class Maze_3D
{
  protected:
    int **maze;
    Coord_3D origin; // the (0,0) point on the global coordinates
    Vector3 origin3;
    Vector3 nextX;
    Vector3 nextY;
    int curState; // 0 not in this surface, 1 not clear box, 2 clear box
    char orientation;
    Color baseColor; // R,G,B
  public:
    Coord_3D cursor;
    std::vector<Ghost> ghost;
    Maze_3D();
    ~Maze_3D();
    void SetMaze(int,int,int);
    void SetOrientation(char);
    void Draw3D();
    void DrawPerl(double,double,double);
    void DrawSuperPerl(double,double,double);
    void DrawCherry(double,double,double);
    void DrawPacMan(double,double,double);
    void DrawGhost(double,double,double,int,int);
    void Print();
    void Activate(Coord_3D,int);// give cursor coordinates and state
    void Deactivate();
    const int ReturnElement(int,int) const;
};

class FullMaze_3D
{
  private:
    Maze_3D maze[6]; // 0-T,1-N,2-W,3-S,4-E,5-B
    Coord_3D cursor;
    char curSurface;
    int curState; // 1 for not clear, 2 for clear box
  public:
    FullMaze_3D();
    void Draw();
    void Print();
    void PrintGhost();
    void SetMaze(int ***);
    void SetCursor(PacMan);
    void SetGhost(std::vector<Ghost> *ghostInfo);
    const void ReturnMaze(int***) const;
};

#endif