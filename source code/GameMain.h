#pragma once

#include "BaseEngine.h"
#include "TileManager.h"
#include "PacmanTileManager.h"
#include "JPGImage.h"

class GameMain :
	public BaseEngine
{
public:
	GameMain(void);
	~GameMain(void);

	void SetupBackgroundBuffer();
	int InitialiseObjects();
	void DrawStrings();
	void GameAction();
	void MouseDown( int iButton, int iX, int iY );
	void MouseMoved( int iX, int iY );
	void KeyDown(int iKeyCode);
	bool isStage1();

	// Get a reference to the current tile manager
	PacmanTileManager& GetTileManager() { return m_oTiles; }
    // State number
	enum State { stateInit, stateMain, statePaused, gameOver, temp1, temp2, level1, level2, win };

    void DrawScreen();
	void DrawChanges();
    ImageData imgg, imgg2; //load the image

private:
	PacmanTileManager m_oTiles;
    State m_state;

};
