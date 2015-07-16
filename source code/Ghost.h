#pragma once
#include "displayableobject.h"
#include "MovementPosition.h"
#include "JPGImage.h"

class GameMain;

class Ghost :
	public DisplayableObject
{
public:
	Ghost(GameMain* pEngine, int iMapX, int iMapY);
	~Ghost(void);

	void Draw();
	void DoUpdate( int iCurrentTime );

	int GetXDiffForDirection( int iDir )
	{
		switch( iDir%4 )
		{
		case 0: return 0; // Up
		case 1: return 1; // Right
		case 2: return 0; // Down
		case 3: return -1; // Left
		default: return 0; // Can never happen
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
		default: return 0; // Can never happen
		}
	}
ImageData img, img2; //load the image

private:
	GameMain* m_pMainEngine;
	MovementPosition m_oMover;

	int m_iMapX;
	int m_iMapY;
	int m_iDir;
};

