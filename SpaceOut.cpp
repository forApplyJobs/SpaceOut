//-----------------------------------------------------------------
// Space Out Application
// C++ Source - SpaceOut.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "SpaceOut.h"
#include <cstdlib>
#include <iostream>

//-----------------------------------------------------------------
// Game Engine Functions
//-----------------------------------------------------------------
BOOL GameInitialize(HINSTANCE hInstance)
{
  // Create the game engine
  _pGame = new GameEngine(hInstance, TEXT("Elemental"),
    TEXT("Elemental"), IDI_SPACEOUT, IDI_SPACEOUT_SM, 21*50, 15*50);
  if (_pGame == NULL)
    return FALSE;

  // Set the frame rate
  _pGame->SetFrameRate(30);

  // Store the instance handle
  _hInstance = hInstance;

  return TRUE;
}

void GameStart(HWND hWindow)
{
  // Seed the random number generator
  srand(GetTickCount());

  // Create the offscreen device context and bitmap
  _hOffscreenDC = CreateCompatibleDC(GetDC(hWindow));
  _hOffscreenBitmap = CreateCompatibleBitmap(GetDC(hWindow),
    _pGame->GetWidth(), _pGame->GetHeight());
  SelectObject(_hOffscreenDC, _hOffscreenBitmap);
  
  // Create and load the bitmaps
  HDC hDC = GetDC(hWindow);
  _leftMoveBitmap= new Bitmap(hDC, IDB_LEFTMOVE, _hInstance);
  _wallBMP= new Bitmap(hDC, IDB_BITMAP3, _hInstance);
  _wandBMP= new Bitmap(hDC, IDB_BITMAP2, _hInstance);
  _pDesertBitmap = new Bitmap(hDC, IDB_DESERT, _hInstance);
  _pCarBitmap = new Bitmap(hDC, IDB_AVATAR, _hInstance);
  _pSmCarBitmap = new Bitmap(hDC, IDB_HEART, _hInstance);
  _pMissileBitmap = new Bitmap(hDC, IDB_MISSILE, _hInstance);
  _pBlobboBitmap = new Bitmap(hDC, IDB_BLOBBO, _hInstance);
  _pBMissileBitmap = new Bitmap(hDC, IDB_BMISSILE, _hInstance);
  _pJellyBitmap = new Bitmap(hDC, IDB_JELLY, _hInstance);
  _missileWaterBitmap= new Bitmap(hDC, IDB_JMISSILE, _hInstance);
  _pJMissileBitmap = new Bitmap(hDC, IDB_JMISSILE, _hInstance);
  _pTimmyBitmap = new Bitmap(hDC, IDB_TIMMY, _hInstance);
  _pTMissileBitmap = new Bitmap(hDC, IDB_TMISSILE, _hInstance);
  _pSmExplosionBitmap = new Bitmap(hDC, IDB_SMEXPLOSION, _hInstance);
  _pLgExplosionBitmap = new Bitmap(hDC, IDB_LGEXPLOSION, _hInstance);
  _pGameOverBitmap = new Bitmap(hDC, IDB_GAMEOVER, _hInstance);
  _bossBitmap=new Bitmap(hDC, IDB_BOSS, _hInstance);
  _pDarken=new Bitmap(hDC, IDB_BITMAP10, _hInstance);
  _suBMP=new Bitmap(hDC, IDB_SU, _hInstance);
  _surukenBMP=new Bitmap(hDC, IDB_SURUKEN, _hInstance);

  isElementSelected = 0;
  bool fightCycle = false;
  // Create the starry background
  _pBackground = new StarryBackground(21*50, 15*50);

  path = new coord * [1000];
  //Create dungeon
  map = new int* [maxrow];
  _iCoordination = new int[2];
  for (int i = 0; i < maxrow; i++) {
      map[i] = new int[maxcol];
  }
  for (int y = 0; y < maxrow; y++) {
      for (int x = 0; x < maxcol; x++) {
          map[y][x] = 0;
          if (y == 0 || y == maxrow - 1 || x == 0 || x == maxcol - 1)
          {
              map[y][x] = 100; //base wall code
          }
          if (y % 2 == 0 && x % 2 == 0)
          {
              map[y][x] = 100;
          }
      }
  }
  for (wall = 0; wall < maxwall; wall++) {
      int x, y, x1, y1, x2, y2; // x1 y1'den x2 y2'ye eri�im var m�
      bool wallOK;

      coord* c1, * c2;

      wallOK = false;
      do
      {
          x = (rand() % (maxcol - 2)) + 1;
          y = (rand() % (maxrow - 2)) + 1;

          if ((x % 2 == 0 && y % 2 == 1) || (x % 2 == 1 && y % 2 == 0))
          {
              if (x % 2 == 1 && y % 2 == 0) {
                  x1 = x2 = x;
                  y1 = y - 1;
                  y2 = y + 1;
              }
              if (x % 2 == 0 && y % 2 == 1) {
                  y1 = y2 = y;
                  x1 = x - 1;
                  x2 = x + 1;
              }
              if (map[y][x] == 0)
              {
                  map[y][x] = 101; //additional wall code
                  wallOK = true;

                  c1 = new coord(x1, y1);
                  c2 = new coord(x2, y2);

                  if (findpathBFS(c1, c2, map, maxrow, maxcol, 0, path)->dist < 0) {
                      map[y][x] = 0;
                      wallOK = false;
                  }

              }
          }

      } while (wallOK == false);
  }


    // Initialize the game variables
 
  // Play the background music
  _pGame->PlayMIDISong(TEXT("Music.mid"));

  // Start the game
  NewGame();
}

void GameEnd()
{
  // Close the MIDI player for the background music
  _pGame->CloseMIDIPlayer();

  // Cleanup the offscreen device context and bitmap
  DeleteObject(_hOffscreenBitmap);
  DeleteDC(_hOffscreenDC);  

  // Cleanup the bitmaps
  delete _pDesertBitmap;
  delete _pCarBitmap;
  delete _pSmCarBitmap;
  delete _pMissileBitmap;
  delete _pBlobboBitmap;
  delete _pBMissileBitmap;
  delete _pJellyBitmap;
  delete _pJMissileBitmap;
  delete _pTimmyBitmap;
  delete _pTMissileBitmap;
  delete _pSmExplosionBitmap;
  delete _pLgExplosionBitmap;
  delete _pGameOverBitmap;

  // Cleanup the background
  delete _pBackground;

  // Cleanup the sprites
  _pGame->CleanupSprites();

  // Cleanup the game engine
  delete _pGame;
}

void GameActivate(HWND hWindow)
{
  // Resume the background music
  _pGame->PlayMIDISong(TEXT(""), FALSE);
}

void GameDeactivate(HWND hWindow)
{
  // Pause the background music
  _pGame->PauseMIDISong();
}

void GamePaint(HDC hDC)
{
    //for (int y = 0; y < maxrow; y++) {
    //    for (int x = 0; x < maxcol; x++) {
    //        if (map[y][x] >= 100)
    //        {
    //            _wallBMP->Draw(hDC, x * 50, y * 50);
    //        }
    //    }
    //}
  // Draw the background
  _pBackground->Draw(hDC);
 
  
  //_element[0]->Draw(hDC);
  // Draw the desert bitmap
  //_pDesertBitmap->Draw(hDC, 0, 371);
  

  // Draw the sprites
  _pGame->DrawSprites(hDC);

  if (!fightCycle)
  {
      //_pDarken->Draw(hDC, _pCarSprite->GetPosition().left - 1000, _pCarSprite->GetPosition().top - 1000, TRUE);
  }
  
  //_pForestBitmap->Draw(hDC, 0, 0);

  // Draw the sprites
  // 
  //_pGame->DrawSprites(hDC);

  // Draw the score
  TCHAR szText[64];
  RECT  rect = { 460, 0, 510, 30 };
  wsprintf(szText, "%d %d", _iScore,_numOfEnemies);
  SetBkMode(hDC, TRANSPARENT);
  SetTextColor(hDC, RGB(255, 255, 255));
  DrawText(hDC, szText, -1, &rect, DT_SINGLELINE | DT_RIGHT | DT_VCENTER);

  // Draw the number of remaining lives (cars)
  for (int i = 0; i < _iNumLives; i++)
    _pSmCarBitmap->Draw(hDC, 520 + (_pSmCarBitmap->GetWidth() * i),
      10, TRUE);

  // Draw the game over message, if necessary
  if (_bGameOver)
    _pGameOverBitmap->Draw(hDC, 190, 149, TRUE);
}

void GameCycle()
{
    
  if (!_bGameOver)
  {
    // Randomly add aliens
    //if ((rand() % _iDifficulty) == 0)
    //  AddAlien();
      if (!fightCycle) {
          AlienAI();
          if (_numOfEnemies <= 0) {
              fightCycle = true;
              NewGame2();
          }
      }
      else {
        AlienRandomMove();
      }
      
    // Update the background
    _pBackground->Update();

    // Update the sprites
    _pGame->UpdateSprites();

    // Obtain a device context for repainting the game
    HWND  hWindow = _pGame->GetWindow();
    HDC   hDC = GetDC(hWindow);

    // Paint the game to the offscreen device context
    GamePaint(_hOffscreenDC);

    // Blit the offscreen bitmap to the game screen
    BitBlt(hDC, 0, 0, _pGame->GetWidth(), _pGame->GetHeight(),
      _hOffscreenDC, 0, 0, SRCCOPY);

    // Cleanup
    ReleaseDC(hWindow, hDC);
  }
}

void HandleKeys()
{
  if (!_bGameOver)
  {
    // Move the car based upon left/right key presses
    _pCarSprite->SetPrevPosition(_pCarSprite->GetPosition());
    POINT ptVelocity = _pCarSprite->GetVelocity();
    if (GetAsyncKeyState('A') < 0)
    {
      // Move left
      ptVelocity.x = max(ptVelocity.x - 1, -4);
      _pCarSprite->SetVelocity(ptVelocity);
      //_pCarSprite->SetBitmap(_leftMoveBitmap);

    }
    else if (GetAsyncKeyState('D') < 0)
    {
      // Move right
      ptVelocity.x = min(ptVelocity.x + 2, 6);
      _pCarSprite->SetVelocity(ptVelocity);
    }
    if (GetAsyncKeyState('W') < 0) {
        ptVelocity.y = max(ptVelocity.y - 1, -4);
        _pCarSprite->SetVelocity(ptVelocity);

    }

    else if (GetAsyncKeyState('S') < 0)
    {

        ptVelocity.y = min(ptVelocity.y + 2, 6);
        _pCarSprite->SetVelocity(ptVelocity);
    }

    if (GetAsyncKeyState('E') < 0) {
        checkElement();

    }if (GetAsyncKeyState('X') < 0) {
        fightCycle = true;
        NewGame2();

    }

    // Fire missiles based upon spacebar presses
    if ((++_iFireInputDelay > 6) && GetAsyncKeyState(VK_SPACE) < 0)
    {
      // Create a new missile sprite
      RECT  rcBounds = { 0, 0, 21*50, 15*50 };
      RECT  rcPos = _pCarSprite->GetPosition();
      Sprite* pSprite;
      if (isElementSelected == 0) {
          pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);
      }
      else if(isElementSelected == 1) {
          pSprite = new Sprite(_wallBMP, rcBounds, BA_DIE);
      }
      else if (isElementSelected == 2) {
          pSprite = new Sprite(_wallBMP, rcBounds, BA_DIE);
      }
      else if (isElementSelected == 3) {
          pSprite = new Sprite(_wallBMP, rcBounds, BA_DIE);
      }
      pSprite->SetPosition(rcPos.left + 15, 400);
      pSprite->SetVelocity(0, -7);
      _pGame->AddSprite(pSprite);

      // Play the missile (fire) sound
      PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC |
        SND_RESOURCE | SND_NOSTOP);

      // Reset the input delay
      _iFireInputDelay = 0;
    }
  }

  // Start a new game based upon an Enter (Return) key press
  if (_bGameOver && (GetAsyncKeyState(VK_RETURN) < 0))
    // Start a new game
    NewGame();
}

void MouseButtonDown(int x, int y, BOOL bLeft)
{
    // Create a new missile sprite
    RECT  rcBounds = { 0, 0, 21 * 50, 15 * 50 };
    RECT  rcPos = _pCarSprite->GetPosition();
    Sprite* pSprite;
    int speed=1;
    if (isElementSelected == 0) {
        pSprite = new Sprite(_pMissileBitmap, rcBounds, BA_DIE);
        pSprite->SetNumFrames(4);
        speed = 12;
    }
    else if(isElementSelected == 1){
        pSprite = new Sprite(_suBMP, rcBounds, BA_DIE);
        pSprite->SetNumFrames(2);
        speed = 12;
    }
    else if (isElementSelected == 2) {
        pSprite = new Sprite(_wallBMP, rcBounds, BA_DIE);
        pSprite->SetNumFrames(1);
        speed = 8;
    }
    else if (isElementSelected == 3) {
        pSprite = new Sprite(_surukenBMP, rcBounds, BA_DIE);
        pSprite->SetNumFrames(2);
        speed = 15;
    }
    pSprite->SetPosition(rcPos);
    /*pSprite->SetNumFrames(4);*/
    float deltaX = x - rcPos.left;
    float deltaY = y - rcPos.top;
    float magnitude = sqrt(deltaX * deltaX + deltaY * deltaY);
    pSprite->SetVelocity(deltaX / magnitude * speed, deltaY / magnitude * speed);
    _pGame->AddSprite(pSprite);

    // Play the missile (fire) sound
    PlaySound((LPCSTR)IDW_MISSILE, _hInstance, SND_ASYNC |
        SND_RESOURCE | SND_NOSTOP);

    // Reset the input delay
    _iFireInputDelay = 0;
}

void MouseButtonUp(int x, int y, BOOL bLeft)
{
}

void MouseMove(int x, int y)
{
}

void HandleJoystick(JOYSTATE jsJoystickState)
{
}
void checkElement() {
    // Obtain the saucer's position
    RECT rcCar, rcElement;
    rcCar = _pCarSprite->GetPosition();
    int asteroidIndex = 0;
    // Find out which asteroid is closest to the saucer
    int iXCollision = 500, iYCollision = 400, iXYCollision = 900;
    for (int i = 0; i < 4; i++)
    {
        // Get the asteroid position
        rcElement = _element[i]->GetPosition();

        // Calculate the minimum XY collision distance
        int iXCollisionDist = (rcCar.left +
            (rcCar.right - rcCar.left) / 2) -
            (rcElement.left +
                (rcElement.right - rcElement.left) / 2);
        int iYCollisionDist = (rcCar.top +
            (rcCar.bottom - rcCar.top) / 2) -
            (rcElement.top +
                (rcElement.bottom - rcElement.top) / 2);
        if ((abs(iXCollisionDist) < abs(iXCollision)) ||
            (abs(iYCollisionDist) < abs(iYCollision)))
            if ((abs(iXCollisionDist) + abs(iYCollisionDist)) < iXYCollision)
            {
                iXYCollision = abs(iXCollision) + abs(iYCollision);
                iXCollision = iXCollisionDist;
                iYCollision = iYCollisionDist;
                asteroidIndex = i;
            }
    }

    // Move to dodge the asteroids, if necessary
    POINT ptVelocity;
    ptVelocity = _pCarSprite->GetVelocity();
    if (abs(iXCollision) < 110 && abs(iYCollision) < 110)
    {
        isElementSelected = asteroidIndex;
    }

}
BOOL SpriteCollision(Sprite* pSpriteHitter, Sprite* pSpriteHittee)
{
  // See if a player missile and an alien have collided
  Bitmap* pHitter = pSpriteHitter->GetBitmap();
  Bitmap* pHittee = pSpriteHittee->GetBitmap();
  if (((pHitter == _pMissileBitmap|| pHitter == _missileWaterBitmap) && (pHittee == _pBlobboBitmap ||
    pHittee == _pJellyBitmap || pHittee == _pTimmyBitmap || pHittee == _wallBMP || pHittee == _bossBitmap) ) ||
    (pHittee == _pMissileBitmap && (pHitter == _pBlobboBitmap ||
    pHitter == _pJellyBitmap || pHitter == _pTimmyBitmap || pHitter == _wallBMP || pHitter == _bossBitmap)))
     /* || (pHitter == _missileWaterBitmap && (pHittee == _pBlobboBitmap ||
          pHittee == _pJellyBitmap || pHittee == _pTimmyBitmap)) ||
      (pHittee == _missileWaterBitmap && (pHitter == _pBlobboBitmap ||
          pHitter == _pJellyBitmap || pHitter == _pTimmyBitmap))*/
  {
    // Play the small explosion sound
    PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC |
      SND_RESOURCE);

    // Kill both sprites
    

    // Create a large explosion sprite at the alien's position
    RECT rcBounds = { 0, 0, 21 * 50, 15 * 50 };
    RECT rcPos;

    if ((pHitter == _pMissileBitmap|| pHitter == _missileWaterBitmap) && (pHittee != _wallBMP)) {
        rcPos = pSpriteHitter->GetPosition();
        pSpriteHittee->SetHealth(pSpriteHittee->GetHealth() - 10);
        if (pSpriteHittee->GetHealth() <= 0)
        {
            pSpriteHittee->Kill();
            _numOfEnemies--;
            _iScore += 25;
        }
        pSpriteHitter->Kill();
    }
    else if ((pHittee == _pMissileBitmap || pHittee == _missileWaterBitmap) && (pHitter != _wallBMP)) {
        rcPos = pSpriteHittee->GetPosition();
        pSpriteHitter->SetHealth(pSpriteHitter->GetHealth() - 10);
        if (pSpriteHitter->GetHealth() <= 0)
        {
            pSpriteHitter->Kill();
            _iScore += 25;
            _numOfEnemies--;
        }
        pSpriteHittee->Kill();

    }
    else if(pHittee == _wallBMP || pHitter == _wallBMP) {
        rcPos = (pHitter == _wallBMP) ? pSpriteHittee->GetPosition() : pSpriteHitter->GetPosition();
        (pHitter == _wallBMP) ? pSpriteHittee->Kill() : pSpriteHitter->Kill();
    }
    
    Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
    pSprite->SetNumFrames(8, TRUE);
    pSprite->SetPosition(rcPos.left, rcPos.top);
    _pGame->AddSprite(pSprite);

    // Update the score
    
    _iDifficulty = max(100 - (_iScore / 40), 40);
  }

  auto pCar = (pHitter == _pCarBitmap) ? pSpriteHitter : pSpriteHittee;
  auto pWall = (pHitter == _wallBMP) ? pSpriteHitter : pSpriteHittee;

  if ((pHitter == _pCarBitmap && pHittee == _wallBMP) || (pHitter == _wallBMP && pHitter == _pCarBitmap)) {
      pCar->SetVelocity(0, 0);
      pCar->SetPosition(pCar->GetPrevPosition());
  }
  // See if an alien missile has collided with the car
  if ((pHitter == _pCarBitmap && (pHittee == _pBMissileBitmap ||
    pHittee == _pJMissileBitmap || pHittee == _pTMissileBitmap)) ||
    (pHittee == _pCarBitmap && (pHitter == _pBMissileBitmap ||
    pHitter == _pJMissileBitmap || pHitter == _pTMissileBitmap)))
  {
    // Play the large explosion sound
    PlaySound((LPCSTR)IDW_LGEXPLODE, _hInstance, SND_ASYNC |
      SND_RESOURCE);

    // Kill the missile sprite
    if (pHitter == _pCarBitmap)
      pSpriteHittee->Kill();
    else
      pSpriteHitter->Kill();

    // Create a large explosion sprite at the car's position
    RECT rcBounds = { 0, 0, 21*50, 15*50 };
    RECT rcPos;
    if (pHitter == _pCarBitmap)
      rcPos = pSpriteHitter->GetPosition();
    else
      rcPos = pSpriteHittee->GetPosition();
    Sprite* pSprite = new Sprite(_pLgExplosionBitmap, rcBounds);
    pSprite->SetNumFrames(8, TRUE);
    pSprite->SetPosition(rcPos.left, rcPos.top);
    _pGame->AddSprite(pSprite);

    // Move the car back to the start
    _pCarSprite->SetPosition(_iCoordination[1] * 50, _iCoordination[0] * 50);

    // See if the game is over
    if (--_iNumLives == 0)
    {
      // Play the game over sound
      PlaySound((LPCSTR)IDW_GAMEOVER, _hInstance, SND_ASYNC |
        SND_RESOURCE);
      _bGameOver = TRUE;
    }
  }

  return FALSE;
}

void SpriteDying(Sprite* pSprite)
{
  // See if an alien missile sprite is dying
  if (pSprite->GetBitmap() == _pBMissileBitmap ||
    pSprite->GetBitmap() == _pJMissileBitmap ||
    pSprite->GetBitmap() == _pTMissileBitmap)
  {
    // Play the small explosion sound
    PlaySound((LPCSTR)IDW_SMEXPLODE, _hInstance, SND_ASYNC |
      SND_RESOURCE | SND_NOSTOP);

    // Create a small explosion sprite at the missile's position
    RECT rcBounds = { 0, 0, 600, 450 };
    RECT rcPos = pSprite->GetPosition();
    Sprite* pSprite = new Sprite(_pSmExplosionBitmap, rcBounds);
    pSprite->SetNumFrames(8, TRUE);
    pSprite->SetPosition(rcPos.left, rcPos.top);
    _pGame->AddSprite(pSprite);
  }
}

//-----------------------------------------------------------------
// Functions
//-----------------------------------------------------------------

void NewGame2()
{
    // Clear the sprites
    _pGame->CleanupSprites();



    // Create the car sprite
    RECT rcBounds = { 0, 0, 21 * 50, 15 * 50 };
    _pCarSprite = new Sprite(_pCarBitmap, rcBounds);
    _pCarSprite->SetNumFrames(2);
    _pCarSprite->SetFrameDelay(10);
    _pCarSprite->SetPosition(400, 400);
    _pGame->AddSprite(_pCarSprite);


    
    _pBossSprite = new AlienSprite(_bossBitmap, rcBounds, 100, BA_BOUNCE);
    _pBossSprite->SetNumFrames(3);
    _pBossSprite->SetFrameDelay(20);
    _pBossSprite->SetPosition(500, 500);
    _pBossSprite->Setbfrm(0);
    _pBossSprite->SetStep(2);
    _pGame->AddSprite(_pBossSprite);
    int counter = 0;
    for (int y = 0; y < maxrow; y++) {
        for (int x = 0; x < maxcol; x++) {
            if (rand() % 20 == 0)
            {
                if (map[y][x] == 0 && counter < maxAlien)
                {
                    //_wallBMP->Draw(hDC, x * 50, y * 50);

                    AddAlien(x * 50, y * 50, counter);
                    counter++;

                }
            }

        }
    }
    _numOfEnemies = counter;
    
    _element[0] = new Sprite(_wandBMP, rcBounds, BA_STOP);
    _element[0]->SetPosition(10, 10);
    _pGame->AddSprite(_element[0]);

    _element[1] = new Sprite(_wandBMP, rcBounds, BA_STOP);
    _element[1]->SetPosition(21*50 - 40, 10);
    _pGame->AddSprite(_element[1]);

    _element[2] = new Sprite(_wandBMP, rcBounds, BA_STOP);
    _element[2]->SetPosition(21*50-40, 15*50-60);
    _pGame->AddSprite(_element[2]);

    _element[3] = new Sprite(_wandBMP, rcBounds, BA_STOP);
    _element[3]->SetPosition(10, 15 * 50 - 60);
    _pGame->AddSprite(_element[3]);

    /*for (int y = 0; y < maxrow; y++) {
          for (int x = 0; x < maxcol; x++) {
              if (map[y][x] >= 100)
              {
                  _wallBMP->Draw(hDC, x * 50, y * 50);
              }
          }
      }*/
      // Initialize the game variables
    _iFireInputDelay = 0;
    _iScore = 0;
    _iNumLives = 3;
    _iDifficulty = 100;
    _bGameOver = FALSE;

    // Play the background music
    _pGame->PlayMIDISong();
}
void NewGame()
{
  // Clear the sprites
  _pGame->CleanupSprites();



  // Create the car sprite
  RECT rcBounds = { 0, 0, 21*50, 15*50 };
  _pCarSprite = new Sprite(_pCarBitmap, rcBounds);
  FindCoordination();
  _pCarSprite->SetPosition(_iCoordination[1] * 50, _iCoordination[0] * 50);
  _pCarSprite->SetNumFrames(2);
  _pCarSprite->SetFrameDelay(10);
  _pGame->AddSprite(_pCarSprite);

  for (int y = 0; y < maxrow; y++) {
      for (int x = 0; x < maxcol; x++) {
          if (map[y][x] >= 100)
          {
              //_wallBMP->Draw(hDC, x * 50, y * 50);
              Sprite* _wallSprite=new Sprite(_wallBMP, rcBounds, BA_BOUNCE);
              _wallSprite->SetPosition(x * 50, y * 50);
              _pGame->AddSprite(_wallSprite);

          }
      }
  }
  int counter = 0;
  for (int y = 0; y < maxrow; y++) {
      for (int x = 0; x < maxcol; x++) {
          if (rand() % 20 == 0)
          {
              if (map[y][x] == 0 && counter < maxAlien)
              {
                  //_wallBMP->Draw(hDC, x * 50, y * 50);

                  AddAlien(x * 50, y * 50, counter);
                  counter++;

              }
          }
          
      }
  }
  _numOfEnemies = counter;
  /*_element[0] = new Sprite(_wandBMP, rcBounds, BA_STOP);
  _element[0]->SetPosition(250, 200);
  _pGame->AddSprite(_element[0]);

  _element[1] = new Sprite(_wandBMP, rcBounds, BA_STOP);
  _element[1]->SetPosition(250, 200);
  _pGame->AddSprite(_element[1]);

  _element[2] = new Sprite(_wandBMP, rcBounds, BA_STOP);
  _element[2]->SetPosition(250, 200);
  _pGame->AddSprite(_element[2]);
  _element[3] = new Sprite(_wandBMP, rcBounds, BA_STOP);
  _element[3]->SetPosition(250, 200);
  _pGame->AddSprite(_element[3]);*/

  /*for (int y = 0; y < maxrow; y++) {
        for (int x = 0; x < maxcol; x++) {
            if (map[y][x] >= 100)
            {
                _wallBMP->Draw(hDC, x * 50, y * 50);
            }
        }
    }*/
  // Initialize the game variables
  _iFireInputDelay = 0;
  _iScore = 0;
  _iNumLives = 3;
  _iDifficulty = 100;
  _bGameOver = FALSE;

  // Play the background music
  _pGame->PlayMIDISong();
}
int distance(coord* c1, coord* c2) {
    int dx, dy;
    dx = abs(c1->x - c2->x);
    dy = abs(c1->y - c2->y);
    return dx + dy;
}
coord* findpathBFS(coord* c1, coord* c2, int **map, int maxrow, int maxcol, int empty, coord **path) {
    int** map2;
    std::queue<coord*> alt;
    coord * c, * ct;
    map2 = new int* [maxrow];
    for (int i = 0; i < maxrow; i++) {
        map2[i] = new int[maxcol];
    }
    for (int y = 0; y < maxrow; y++) {
        for (int x = 0; x < maxcol; x++) {
            map2[y][x] = map[y][x];
        }
    }
    alt.push(c1); //start

    while (!alt.empty()) {
        c = alt.front(); alt.pop();
        if (c->x == c2->x && c->y == c2->y) { // we reached the target
            // Here, you would construct the path from c1 to c2 using the parent pointers of the nodes
            // If you want the path length, you can return c->dist.
            return c;
        }
        if (map2[c->y][c->x] != empty) {
            continue;
        }


        map2[c->y][c->x] = 1;

        if (distance(c, c2) <= 1) { //target found
            int i = 0;
            while (c->prev != NULL) {
                path[i] = c;
                c = c->prev;
                i++;
            }
            return path[0];
        }


        if (c->x + 1 < maxcol) // Check bounds
            alt.push(new coord(c->x + 1, c->y, c->dist + 1, c));
        if (c->x - 1 >= 0) // Check bounds
            alt.push(new coord(c->x - 1, c->y, c->dist + 1, c));
        if (c->y + 1 < maxrow) // Check bounds
            alt.push(new coord(c->x, c->y + 1, c->dist + 1, c));
        if (c->y - 1 >= 0) // Check bounds
            alt.push(new coord(c->x, c->y - 1, c->dist + 1, c));
    }

    // If the queue is empty, and we didn't return from inside the loop, 
    // then there was no path from c1 to c2.
    return new coord(0 , 0, -1);
}
void AddAlien(int x, int y, int index)
{
  // Create a new random alien sprite
    RECT rcBounds = { 0, 0, 21 * 50, 15 * 50 };
  AlienSprite*  pSprite;
  switch(rand() % 3)
  {
  case 0:
    // Blobbo
    pSprite = new AlienSprite(_pBlobboBitmap, rcBounds,30, BA_BOUNCE);
    _Aliens[index] = pSprite;
    pSprite->SetNumFrames(8);
    pSprite->SetPosition(x, y);
    pSprite->Setbfrm(0);
    pSprite->SetStep(3);
    //pSprite->SetVelocity((rand() % 7) - 2, (rand() % 7) - 2);
    break;
  case 1:
    // Water Wall
    pSprite = new AlienSprite(_pJellyBitmap, rcBounds, 20, BA_BOUNCE);
    _Aliens[index] = pSprite;
    pSprite->SetNumFrames(2);
    pSprite->SetPosition(x, y);
    pSprite->Setbfrm(0);
    pSprite->SetStep(3);
    //pSprite->SetVelocity((rand() % 5) - 2, (rand() % 5) + 3);
    break;
  case 2:
    // Fire Wall
    pSprite = new AlienSprite(_pTimmyBitmap, rcBounds, 5, BA_WRAP);
    _Aliens[index] = pSprite;
    pSprite->SetNumFrames(2);
    pSprite->SetPosition(x, y);
    pSprite->Setbfrm(0);
    pSprite->SetStep(3);
    //pSprite->SetVelocity((rand() % 7) + 3, 0);
    break;
  }

  // Add the alien sprite
  _pGame->AddSprite(pSprite);
}
void PathFinding(Sprite* alien) {

    alien->Setbfrm(alien->Getbfrm() - alien->GetStep());
    if (alien->Getbfrm() <= 0)
    {
        alien->SetVelocity(0, 0);
        int alienPosX = ((alien->GetPosition()).left + (alien->GetPosition()).right) / 100;
        int alienPosY = ((alien->GetPosition()).top + (alien->GetPosition()).bottom) / 100;

        coord* alienCoord = new coord(alienPosX, alienPosY);

        int targetPosX = ((_pCarSprite->GetPosition()).left + (_pCarSprite->GetPosition()).right) / 100;
        int targetPosY = ((_pCarSprite->GetPosition()).top + (_pCarSprite->GetPosition()).bottom) / 100;

        coord* targetCoord = new coord(targetPosX, targetPosY);
        coord** nullPath = new coord * [1000];
        coord* pathx = findpathBFS(targetCoord, alienCoord, map, maxrow, maxcol, 0, path);
        
        //coord* nextPoint = path->prev;

        if (pathx->x != 0 && pathx->y!=0 && (pathx->x > alienCoord->x))
        {
            alien->SetVelocity(alien->GetStep(), 0);
            alien->Setbfrm(50);
        }
        else if(pathx->x != 0 && pathx->y != 0 && (pathx->x < alienCoord->x))
        {
            alien->SetVelocity(-alien->GetStep(), 0);
            alien->Setbfrm(50);
        }
        else if (pathx->x != 0 && pathx->y != 0 && (pathx->y > alienCoord->y))
        {
            alien->SetVelocity(0, alien->GetStep());
            alien->Setbfrm(50);
        }
        else if(pathx->x != 0 && pathx->y != 0 && (pathx->y < alienCoord->y))
        {
            alien->SetVelocity(0, -alien->GetStep());
            alien->Setbfrm(50);
        }
    }

    

}
void AlienAI() {

    for (int i = 0; i < maxAlien; i++)
    {
        if (_Aliens[i] != NULL)
        {
            PathFinding(_Aliens[i]);
        }
    }
}
void AlienRandomMove() {

    for (int i = 0; i < maxAlien; i++)
    {
        if (_Aliens[i] != NULL)
        {
            ChooseMovePosition(_Aliens[i]);
        }
    }
    ChooseMovePosition(_pBossSprite);
}
void FindCoordination() {
    for (int x = 0; x < maxrow; x++)
    {
        if (x > maxrow/2-1)
        {
            for (int y = 0; y < maxcol; y++)
            {
                if (map[x][y] == 0)
                {
                    _iCoordination[0] = x;
                    _iCoordination[1] = y;
                }
            }
        }
        
    }
}
void ChooseMovePosition(Sprite* alien) {

    int x = rand() % (12 * 50);
    int y = rand() % (12 * 50);



    alien->Setbfrm(alien->Getbfrm() - alien->GetStep());
    if (alien->Getbfrm() <= 0)
    {
        alien->SetVelocity(0, 0);
        int alienPosX = ((alien->GetPosition()).left + (alien->GetPosition()).right)/2;
        int alienPosY = ((alien->GetPosition()).top + (alien->GetPosition()).bottom)/2;


        if (x >= alienPosX && y>= alienPosY)
        {
            alien->SetVelocity(alien->GetStep(), alien->GetStep());
            alien->Setbfrm(50);
        }
        else if (x < alienPosX && y>= alienPosY)
        {
            alien->SetVelocity(-alien->GetStep(), alien->GetStep());
            alien->Setbfrm(50);
        }
        else if (x < alienPosX && y < alienPosY)
        {
            alien->SetVelocity(-alien->GetStep(), -alien->GetStep());
            alien->Setbfrm(50);
        }
        else if (x >= alienPosX && y < alienPosY)
        {
            alien->SetVelocity(alien->GetStep(), -alien->GetStep());
            alien->Setbfrm(50);
        }
    }
}
