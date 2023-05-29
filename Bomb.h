#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Sprite.h"

//-----------------------------------------------------------------
// AlienSprite Class
//-----------------------------------------------------------------
class Bomb : public Sprite
{
public:
    // Constructor(s)/Destructor
    Bomb(Bitmap* pBitmap, RECT& rcBounds,
        BOUNDSACTION baBoundsAction = BA_STOP);
    virtual ~Bomb();
    int burstTime;
    // General Methods
    virtual SPRITEACTION  Update();
    virtual void SpendTime();
};
