//-----------------------------------------------------------------
// Alien Sprite Object
// C++ Source - AlienSprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "AlienSprite.h"
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
AlienSprite::AlienSprite(Bitmap* pBitmap, RECT& rcBounds,int iHealth,
  BOUNDSACTION baBoundsAction) : Sprite(pBitmap, rcBounds, iHealth,
  baBoundsAction)
{
}

AlienSprite::~AlienSprite()
{
}

//-----------------------------------------------------------------
// AlienSprite General Methods
//-----------------------------------------------------------------
SPRITEACTION AlienSprite::Update()
{
  // Call the base sprite Update() method
  SPRITEACTION saSpriteAction;
  saSpriteAction = Sprite::Update();

  // See if the alien should fire a missile
  //if ((rand() % (_iDifficulty / 2)) == 0)
  //  saSpriteAction |= SA_ADDSPRITE;

  return saSpriteAction;
}

Sprite* AlienSprite::AddSprite()
{
  // Create a new missile sprite
  RECT rcBounds = { 0, 0, 21 * 50, 15 * 50 };
  RECT    rcPos = GetPosition();
  Sprite* pSprite = NULL;
  RECT mCarPos = _pCarSprite->GetPosition();
  float x = mCarPos.left;
  float y = mCarPos.top;
  float deltaX = x - rcPos.left;
  float deltaY = y - rcPos.top;
  float magnitude = sqrt(deltaX * deltaX + deltaY * deltaY);
  int speed = 5;


  if (abs(deltaX) < 300 && abs(deltaY) < 300) {
      if (GetBitmap() == _pBlobboBitmap)
      {
          // Blobbo missile
          pSprite = new Sprite(_pBMissileBitmap, rcBounds, BA_DIE);
          pSprite->SetVelocity(deltaX / magnitude * speed, deltaY / magnitude * speed);
          pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom);
      }
      else if (GetBitmap() == _pJellyBitmap)
      {
          // Jelly missile
          pSprite = new Sprite(_pJMissileBitmap, rcBounds, BA_DIE);
          pSprite->SetVelocity(deltaX / magnitude * speed, deltaY / magnitude * speed);
          pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom);
      }
      else if(GetBitmap() == _pTimmyBitmap)
      {
          // Timmy missile
          pSprite = new Sprite(_pTMissileBitmap, rcBounds, BA_DIE);
          pSprite->SetVelocity(deltaX / magnitude * speed, deltaY / magnitude * speed);
          pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom);
      }
      else//boss
      {
          pSprite = new Sprite(_pTMissileBitmap, rcBounds, BA_DIE);
          pSprite->SetVelocity(deltaX / magnitude * speed, deltaY / magnitude * speed);
          pSprite->SetPosition(rcPos.left + (GetWidth() / 2), rcPos.bottom + (GetHeight() / 2));
      }

      // Set the missile sprite's position and return it
      
  }
  return pSprite;
}
