#include <string>
#include <sstream>
#include "ysglfontdata.h"
#include "yspng.h"
#include "yspngenc.h"
#include "fssimplewindow.h"
#include "score.h"
using namespace std;

Score::Score(){
    png.Decode("../pacman.png");
    png.Flip();
    ResetScore();
}

void Score::SetGhost(int player,int pacman_eaten){
    data[player].pacman_eaten = pacman_eaten;
}

void Score::SetPacman(int player,int ghost_eaten,int pells,int cherry){
    data[player].pells = pells;
    data[player].ghost_eaten = ghost_eaten;
    data[player].cherry = cherry;
}


void Score::SetPlayer1(int pells1,int livesLeft1,int ghost_eaten1,int pac_eaten1,int timeLeft)
{
    data[0].pells = pells1;
    data[0].livesLeft = livesLeft1;
    data[0].ghost_eaten = ghost_eaten1;
    data[0].pacman_eaten = pac_eaten1;
    data[0].score = data[0].pells*20 + data[0].livesLeft*20 + data[0].ghost_eaten*50 + data[0].pacman_eaten*50 + timeLeft;
}

void Score::SetPlayer2(int pells2,int livesLeft2,int ghost_eaten2,int pac_eaten2, int timeLeft){
    data[1].pells = pells2;
    data[1].livesLeft = livesLeft2;
    data[1].ghost_eaten = ghost_eaten2;
    data[1].pacman_eaten = pac_eaten2;
    data[1].score = data[1].pells*20 + data[1].livesLeft*25 + data[1].ghost_eaten*50 + data[1].pacman_eaten*50 + timeLeft;

}

void Score::ResetScore(){
  for(int i = 0;i < 2;i++){
    data[i].pells = 0;
    data[i].livesLeft = 0;
    data[i].time = 0;
    data[i].cherry = 0;
    data[i].pacman_eaten = 0;
    data[i].ghost_eaten = 0;
    data[i].score = 0;
  }
}

void Score::Draw(void) {
    // position the background picture
    for(int i = 0;i<2;i++){
    data[i].score = data[i].pells*20 + data[i].ghost_eaten*100 + data[i].pacman_eaten*150 + data[i].cherry*30;
    }
    FillBackground();
    glRasterPos2i(130,599);
    glDrawPixels(png.wid,png.hei,GL_RGBA,GL_UNSIGNED_BYTE,png.rgba);
    glColor3ub(0, 0, 0);

    glColor3ub(255,255,255);
    glRasterPos2i(200+ 280, 450);
    char score1[1024],score2[1024];
    IntToChar(data[0].score,"Player1 Score: ",nullString,score1);
    YsGlDrawFontBitmap16x20(score1);
    glRasterPos2i(200+280, 500);
    IntToChar(data[1].score,"Player2 Score: ",nullString,score2);
    YsGlDrawFontBitmap16x20(score2);

    // winner
    glRasterPos2i(200+270, 170);
    char *winner;
    winner  = new char[256];
    if(data[0].score > data[1].score){
        strcpy(winner,"Player 1 Won !");
    }else if (data[0].score < data[1].score){
        strcpy(winner,"Player 2 Won !");
    }else{
        strcpy(winner,"A Draw ! Congratulations!");
    }
    YsGlDrawFontBitmap24x40(winner);
    if(winner != nullptr){
        delete [] winner;
    }
}

void Score::FillBackground(void)const{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1600,0);
    glVertex2i(1600,600);
    glVertex2i(0,600);
    glEnd();
}