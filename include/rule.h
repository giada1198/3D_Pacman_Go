#ifndef RULE_IS_INCLUDED
#define RULE_IS_INCLUDED

#include "yspng.h"

class Rule
{
    public:
        YsRawPngDecoder bgImg;
        Rule();
        void PacManMotion(int x, int y,int gx, int gy, int pixSize, int lpt);
        void Draw(int);
        void FillBackground(void) const;
};

#endif


