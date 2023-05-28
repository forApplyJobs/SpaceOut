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
int maxAlien = 10;

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
Sprite*			  _pDragSprite;
Bitmap*           _pBMissileBitmap;
Bitmap*           _pJellyBitmap;
Bitmap*           _pJMissileBitmap;
Bitmap*           _pTimmyBitmap;
Bitmap*           _pTMissileBitmap;
Bitmap*           _pSmExplosionBitmap;
Bitmap*           _pLgExplosionBitmap;
Bitmap*           _pGameOverBitmap;
StarryBackground* _pBackground;
Sprite*           _pCarSprite;
Sprite*           _pBossSprite;
Sprite*           _element[4];
Sprite*           _Aliens[10];
int               _iFireInputDelay;
int               _iNumLives, _iScore, _iDifficulty,_numOfEnemies;
BOOL              _bGameOver;
HDC hDC;
boolean isElementSelected;
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
