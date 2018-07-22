#ifndef PLAYIMAGE_IS_INCLUDED
#define PLAYIMAGE_IS_INCLUDED

#include "yspng.h"

class PlayImage
{
    protected:
        YsRawPngDecoder img;
    public:
        PlayImage();
        void Draw(void);
};
#endif