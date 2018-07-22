#ifndef SCORE_IS_INCLUDED
#define SCORE_IS_INCLUDED
#include <string>
#include "yspng.h"

typedef struct DataStruct{
  int pells;
  int livesLeft;
  int time;
  int ghost_eaten;
  int pacman_eaten;
  int cherry;
  int score;
}Data;

extern const std::string nullString;
extern void IntToChar(int input,std::string header,std::string footer,char* charArray);

class Score
{
  public:
    YsRawPngDecoder png;
    Data data[2];
    Score();
    void Draw();
    void ResetScore();
    void SetPlayer1(int,int,int,int,int);
    void SetPlayer2(int,int,int,int,int);
    void SetGhost(int,int);
    void SetPacman(int,int,int,int);
    void FillBackground(void) const;
};
#endif

