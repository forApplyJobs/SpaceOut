//-----------------------------------------------------------------
// Space Out Application
// C++ Header - SpaceOut.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "Background.h"
#include "AlienSprite.h"
#include "Bomb.h"
#include <stack>
#include <queue>

class coord {
public:
    int x;
    int y;
    int dist;
    coord* prev;

public:
    coord::coord(int x, int y) {
        this->x = x;
        this->y = y;
        dist = 0;
        prev = NULL;
    }
    coord::coord(int x, int y, int dist) {
        this->x = x;
        this->y = y;
        this->dist = dist;
        prev = NULL;
    }
    coord::coord(int x, int y, int dist, coord* prev) {
        this->x = x;
        this->y = y;
        this->dist = dist;
        this->prev = prev;
    }

};
//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE         _hInstance;
coord **path;
int maxrow = 15, maxcol = 21;
int **map;
int maxwall = 54, wall;
int maxAlien = 15;

GameEngine*       _pGame;
HDC               _hOffscreenDC;
HBITMAP           _hOffscreenBitmap;
Bitmap*           _pDesertBitmap;
Bitmap*           _pCarBitmap;
Bitmap*           _missileWaterBitmap;
Bitmap*           _pSmCarBitmap;
Bitmap*           _bossBitmap;
Bitmap*           _pMissileBitmap;
Bitmap*           _pBlobboBitmap;
Bitmap*			  _wallBMP;
Bitmap*           _leftMoveBitmap;
Bitmap*           _wandBMP;
Bitmap*           _suBMP;
Bitmap*           _bombBMP;
Bitmap*           _surukenBMP;
Bitmap*           _avatarBMP;
Bitmap*           _keyBMP;
Sprite*			  _pDragSprite;
Bitmap*           _pBMissileBitmap;
Bitmap*           _pJellyBitmap;
Bitmap*           _pJMissileBitmap;
Bitmap*           _pTimmyBitmap;
Bitmap*           _pTMissileBitmap;
Bitmap*           _pSmExplosionBitmap;
Bitmap*           _pDarken;
Bitmap*           _pLgExplosionBitmap;
Bitmap*           _pGameOverBitmap;
StarryBackground* _pBackground;
Sprite*           _pCarSprite;
Sprite*           _pKeySprite;
Sprite*           _pBossSprite;
Sprite*           _element[4];
Bomb*             _bombs[4];
Sprite*           _Aliens[15];
int               _iFireInputDelay;
int               _iNumLives, _iScore, _iDifficulty,_numOfEnemies;
int *             _iCoordination;
int               _iBombCount;
int               _iTempPosX;
int               _iTempPosY;
int               _iTempPosXK;
int               _iTempPosYK;
BOOL              _bGameOver;
HDC hDC;
int isElementSelected;
boolean fightCycle;

//-----------------------------------------------------------------
// Function Declarations
//-----------------------------------------------------------------
void NewGame();
void NewGame2();
void AddAlien(int x, int y, int index);
coord* findpathBFS(coord* c1, coord* c2, int **map, int maxrow, int maxcol, int empty, coord** path);
void checkElement();
void AlienAI();
void AlienRandomMove();
void FindCoordination();
void ChooseMovePosition(Sprite* alien);
void CheckBombs();
void Explode(int index);
void MoveKey();
