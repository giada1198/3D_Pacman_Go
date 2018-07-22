#ifndef BUTTON_IS_INCLUDED
#define BUTTON_IS_INCLUDED

#include <string>

class Button
{
  private:
    int x, y;
    int dx1,dx2,dy1,dy2;
    char display[1024];
  public:
    Button();
    Button(int,int);
    void Draw();
    void ReadState(int,int);
    void SetText(std::string);
    int state;
};
#endif

