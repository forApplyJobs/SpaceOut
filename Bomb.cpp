//-----------------------------------------------------------------
// Alien Sprite Object
// C++ Source - AlienSprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "Bomb.h"
#include <math.h>
#include <iostream>

using namespace std;
//-----------------------------------------------------------------
// External Global Variables
//-----------------------------------------------------------------
extern Sprite* _pCarSprite;
extern Bitmap* _pBlobboBitmap;
extern Bitmap* _pBMissileBitmap;
extern Bitmap* _pJellyBitmap;
extern Bitmap* _pJMissileBitmap;
extern Bitmap* _pTimmyBitmap;
extern Bitmap* _pTMissileBitmap;
extern int     _iDifficulty;

//-----------------------------------------------------------------
// AlienSprite Constructor(s)/Destructor
//-----------------------------------------------------------------
Bomb::Bomb(Bitmap* pBitmap, RECT& rcBounds,
    BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds, burstTime,
        baBoundsAction)
{
}

Bomb::~Bomb()
{
}

//-----------------------------------------------------------------
// AlienSprite General Methods
//-----------------------------------------------------------------
SPRITEACTION Bomb::Update()
{
    // Call the base sprite Update() method
    SPRITEACTION saSpriteAction;
    saSpriteAction = Sprite::Update();

    return saSpriteAction;
}

void Bomb::SpendTime() {
    this->burstTime -= 1;
}
