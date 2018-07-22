#ifndef MENU_IS_INCLUDED
#define MENU_IS_INCLUDED

#include "yspng.h"

class Menu 
{   
    protected:
        YsRawPngDecoder bgImg;
    public:
        int highlight_x, highlight_y;
        int yMin,yMax;
        int hei,wid;
        Menu();
        int ReadInput(int);
        void DrawMenu(int);
        void HighlightDraw();
        void DrawPacMan(int xdir, int ydir, double x, double y)const;
        void DrawGhost(int xdir, int ydir, int color, int gx, int gy, bool eatable)const;
        void FillBackground(void) const;
};
#endif

