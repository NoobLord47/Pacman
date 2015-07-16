#pragma once
#include "DisplayableObject.h"
#include "MovementPosition.h"
#include "BaseEngine.h"
#include "TileManager.h"
#include "JPGImage.h"

class GameMain;


class Pacman :
	public DisplayableObject
{
public:
	Pacman(GameMain* pEngine, int iMapX, int iMapY);
	~Pacman(void);

	void Draw();
	void DoUpdate( int iCurrentTime );
	void DrawString();
	static bool checkBooster();
	void setPoisoned(); //
	int getLife();
    bool checkHit();
    const char* LifeCount();
    int getScore();
    void printScreen();

	int GetXDiffForDirection( int iDir )
	{
		switch( iDir%4 )
		{
		case 0: return 0; // Up
		case 1: return 1; // Right
		case 2: return 0; // Down
		case 3: return -1; // Left
		default:return 0; // Can never happen
		}
	}

	int GetYDiffForDirection( int iDir )
	{
		switch( iDir%4 )
		{
		case 0: return -1; // Up
		case 1: return 0; // Right
		case 2: return 1; // Down
		case 3: return 0; // Left
		default: return 2; // Can never happen
		}
	}

	ImageData image1, image2; //load the image

private:
	GameMain* m_pMainEngine;
	MovementPosition m_oMover;

    int score;
	int m_iMapX;
	int m_iMapY;
	int m_iDir;

};
