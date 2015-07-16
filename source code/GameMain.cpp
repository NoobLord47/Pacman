#include "header.h"
#include "BaseEngine.h"
#include "Ghost.h"
#include "Pacman.h"
#include "GameMain.h"
#include "JPGImage.h"
#include "TileManager.h"
#include "FontManager.h"

Font* font;
FontManager m_oFontManager;
bool stage1 = true; //variable to distinguish level 1 and level 2

GameMain::GameMain(void) //void
: BaseEngine( 20 ) //max objects
, m_state(stateInit)
{
}

GameMain::~GameMain(void)
{

}

void GameMain::SetupBackgroundBuffer()
{
    switch( m_state )
	{
	case stateInit: // Reload the level data
	FillBackground( 0 );

    imgg2.LoadImage("logo.png");
	imgg.ShrinkFrom( &imgg2, 1 ); //2, 300,120
	imgg.RenderImageWithMask( this->GetBackground(),0, 0,
					160, 30,
					imgg.GetWidth(), imgg.GetHeight() );
	// Draw an image loaded from a file.
	break;

	case level1:
    FillBackground( 1 );
    {
	char* data[] = { /*a=black tile, b=red wall, c=green
                       d=blue, e=purple, f=yellow
                       g=cyan, h=big white, i=small white
                     */
		"bbbbbbbbbbbbbbbbbbbbbbbbb",
		"bahhhhhhhhhhhhhhhhhhhhhhb",
		"bhbhbhbbbbbhbhbbbbhbbbbhb", //13,2
		"bhbhbhhhbhbhbhbhbhhhhhhhb",
		"bhbbbhbhbhbhbhhhhhbbbhbhb",
		"bhhhhhhhhhbhbhbbbhbhhhhhb",
		"bhbbbbbhbbbhbhhbhcbbbhbhb", //c==17,6
		"bhbhbhhhhhhhhhbhhhhhbhbhb",
		"bhbhbhbbbbbhbhbbbbbhbbbhb",
		"bhhhhhbhhhhhhhhhhbhhhhhhb", //13,9
		"bhbbbhhbbbbhbhbbhbbhbbbhb",
		"bhbhhbhhhhhhbhbhhbhhhhhhb",
		"bhhhbhhbhbbhhhhbhbbhbbbhb",
		"bhbbbbhchhbbbhbbhhhhhhbhb", //7,13
		"bhbhhhhbbhbabhhhhbbhbhbhb",
		"bhbbbbbhbhbbbhbbbhbhbhbhb",
		"bhhhhhhhhhhhhhhhhhhhhhhhb",
		"bbbbbbbbbbbbbbbbbbbbbbbbb" };

	// Specify how many tiles (spacing) wide and high
	m_oTiles.SetSize( 28, 18 );
	// Set up the tiles
	for ( int x = 0 ; x < 28 ; x++ )
		for ( int y = 0 ; y < 18 ; y++ )
			m_oTiles.SetValue( x, y, data[y][x]-'a' );

	for ( int y = 0 ; y < 18 ; y++ )
	{
		for ( int x = 0 ; x < 28 ; x++ )
			printf("%d ", m_oTiles.GetValue(x,y) );
		printf("\n" );
	}

	// Specify the screen x,y of top left corner
	m_oTiles.SetBaseTilesPositionOnScreen( 25, 40 );
    }
break;


    case level2:
        FillBackground( 0 );

        {
	char* data[] = { /*a=black tile, b=red wall, c=green
                       d=blue, e=purple, f=yellow
                       g=cyan, h=big white, i=small white
                     */
		"bbbbbbbbbbbbbbbbbbbbbbbbb",
		"babhbhhhhhbhbhbhhhhhbhbhb",
		"bhbhbbbbbhhhbhhhbbbbbhbhb",
		"bhbhhhhhbbbhbhbbbhhhhhbhb", //c=20,3//
		"bhbbbbbhbhhhhhhhbebbbbbhb", //e=17,4
		"bhhhhhhhhhbhbhbhhhhhhhhhb",
		"bhbhbhbhbbbhbhbhbhbbbhbhb",
		"bhbhhbhhhhhhhhbhhhhhbhbhb",
		"bhbhbhhbbhbhbhbbbbbhbbbhb",
		"bhbbhhbhhhhhhhhhhhbhhhhhb", //c=4,9//
		"bhbhbhhbbbbhbhbbhhbhbhbhb",
		"bhbhhbhhhhhhhbbhhbbhbhbhb",
		"bhhhhhhbbbhbhbhhbbhhhbbhb",
		"bhbbbbhbhbhbhbbhhhhbhhbhb", //e=12,13//
		"bhbhhhhbhbhbhhbbhhbabhbhb",
		"bhbbhbhbhbhbhhhhhhhbhhbhb", //c=6,15
		"bhhhhhhhhhhhhbbhbbhhhhhhb",
		"bbbbbbbbbbbbbbbbbbbbbbbbb" };

	// Specify how many tiles (spacing) wide and high
	m_oTiles.SetSize( 28, 18 );
	// Set up the tiles
	for ( int x = 0 ; x < 28 ; x++ )
		for ( int y = 0 ; y < 18 ; y++ )
			m_oTiles.SetValue( x, y, data[y][x]-'a' );

	for ( int y = 0 ; y < 18 ; y++ )
	{
		for ( int x = 0 ; x < 28 ; x++ )
			printf("%d ", m_oTiles.GetValue(x,y) );
		printf("\n" );
	}

	// Specify the screen x,y of top left corner
	m_oTiles.SetBaseTilesPositionOnScreen( 25, 40 );
    }
break;

    case stateMain:
		FillBackground( 0 );
		// Tell it to draw tiles from x1,y1 to x2,y2 in tile array,
		// to the background of this screen
		m_oTiles.DrawAllTiles( this,
			this->GetBackground(),
			0, 0, 27, 17 );
		break; // Drop out to the complicated stuff

	case statePaused:
		FillBackground( 0 );
		m_oTiles.DrawAllTiles( this,
			this->GetBackground(),
			0, 0, 27, 17 );
		break;

    case gameOver:
        FillBackground( 0 );

        imgg2.LoadImage("gameover.png");
        imgg.ShrinkFrom( &imgg2, 1 );
        imgg.RenderImageWithMask( this->GetBackground(),0, 0,
					210, 200,
					imgg.GetWidth(), imgg.GetHeight() );
	// Draw an image loaded from a file.
        break;

    case win:
        FillBackground( 0 );

        imgg2.LoadImage("win.png");
        imgg.ShrinkFrom( &imgg2, 2 );
        imgg.RenderImageWithMask( this->GetBackground(),0, 0,
					200, 300,
					imgg.GetWidth(), imgg.GetHeight() );
	// Draw an image loaded from a file.
        break;
	} // End switch
}

int GameMain::InitialiseObjects()
{
	// Record the fact that we are about to change the array - so it doesn't get used elsewhere without reloading it
	DrawableObjectsChanged();

	// Destroy any existing objects
	DestroyOldObjects();

	// Create an array one element larger than the number of objects that you want.
	m_ppDisplayableObjects = new DisplayableObject*[6]; // i.e. 1 object

	// You MUST set the array entry after the last one that you create to NULL, so that the system knows when to stop.
	m_ppDisplayableObjects[0] = new Pacman(this,1,1);
	m_ppDisplayableObjects[1] = new Ghost(this,9,9);
	m_ppDisplayableObjects[2] = new Ghost(this,19,8);
	m_ppDisplayableObjects[3] = new Ghost(this,9,5);
	m_ppDisplayableObjects[4] = new Ghost(this,17,15);

	// i.e. The LAST entry has to be NULL. The fact that it is NULL is used in order to work out where the end of the array is.
	m_ppDisplayableObjects[5] = NULL;

	// NOTE: We also need to destroy the objects, but the method at the
	// top of this function will destroy all objects pointed at by the
	// array elements so we can ignore that here.
	return 0;
}

/* Draw text labels */
void GameMain::DrawStrings()
{
    font = m_oFontManager.GetFont("jigsawtr.ttf",48);

    switch( m_state )
	{
        case stateInit:
            CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
            DrawScreenString( 370, 255, "Level 1", 0xff00ff, g_pMainFont );
            DrawScreenString( 370, 300, "Level 2", 0xff00ff, g_pMainFont );
            SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
		break;

	    case statePaused:
            CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
            DrawScreenString( 370, 5, "Paused", 0xffffff, g_pMainFont );
            SetNextUpdateRect( 0, 280, GetScreenWidth(), 40 );
		break;

        case stateMain:
        break;

        case gameOver:
                CopyBackgroundPixels( 0, 0, GetScreenWidth(), 30 );
                DrawScreenString( 250, 100, "GAME OVER", 0xff0000, font );
                SetNextUpdateRect( 0, 0, GetScreenWidth(), 30 );
            break;

        case win:
                CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
                DrawScreenString( 143, 100, "*~*~*~*~*~*~*~*", 0x0000cc, font );
                DrawScreenString( 143, 150, "*  Stage Cleared  *", 0x0000cc, font );
                DrawScreenString( 143, 208, "*~*~*~*~*~*~*~*", 0x0000cc, font );
                SetNextUpdateRect( 0, 280, GetScreenWidth(), 40 );
                break;

        case temp1:
            CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
            //DrawScreenString( 190, 180, "PACMAN WORLD" , 0xff00ff, font );
            DrawScreenString( 370, 255, "Level 1", 0xffffff, g_pMainFont );
            DrawScreenString( 370, 300, "Level 2", 0xff00ff, g_pMainFont );
            SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
            break;

        case temp2:
            CopyBackgroundPixels( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
            //DrawScreenString( 190, 180, "PACMAN WORLD" , 0xff00ff, font );
            DrawScreenString( 370, 255, "Level 1", 0xff00ff, g_pMainFont );
            DrawScreenString( 370, 300, "Level 2", 0xffffff, g_pMainFont );
            SetNextUpdateRect( 0/*X*/, 280/*Y*/, GetScreenWidth(), 40/*Height*/ );
            break;
	}
}

/* Overridden GameAction to ensure that objects use the modified time */
void GameMain::GameAction()
{
	// If too early to act then do nothing
	if ( !TimeToAct() )
		return;

	// Don't act for another 10 ticks
	SetTimeToAct( 1 );

	switch( m_state )
	{
	case stateInit:

    case gameOver:
    case win:
	case statePaused:
		break;
	case stateMain:

	    if(Pacman(this,1,1).getLife()==0) //out of lives
            {
                m_state = gameOver;
                SetupBackgroundBuffer();
                Redraw(true);
            }
            if(Pacman(this,1,1).checkHit()==true) //stage cleared
            {
                m_state = win;
                SetupBackgroundBuffer();
                Redraw(true);
            }
            UpdateAllObjects( GetTime() );
            break;

    case level1:
    case level2:
		// Only tell objects to move when not paused etc
		UpdateAllObjects( GetTime() );
		break;
	}
	SDL_Flip(GetForeground());
}
//play button
void GameMain::MouseDown( int iButton, int iX, int iY )
{
    switch(iButton) {

    case SDL_BUTTON_LEFT:

        switch( m_state )
		{
		case stateInit:

			if(iX>=370 && iX<=470 && iY>=255 && iY<=280) {
                // Go to state main
                m_state = level1;
                stage1 = true;
                SetupBackgroundBuffer();
                Redraw(true);

                m_state = stateMain;
                SetupBackgroundBuffer();
                Redraw(true);
			}
			else if(iX>=370 && iX<=475 && iY>=300 && iY<=330) {
                // Go to state main
                m_state = level2;
                stage1 = false;
                SetupBackgroundBuffer();
                Redraw(true);

                m_state = stateMain;
                SetupBackgroundBuffer();
                Redraw(true);
			}
			break;

        case temp1:

            if(iX>=370 && iX<=470 && iY>=255 && iY<=280) {
                // Go to state main
                m_state = level1;
                stage1 = true;

                SetupBackgroundBuffer();
                Redraw(true);

                m_state = stateMain;
                SetupBackgroundBuffer();
                Redraw(true);
			}
			break;

        case temp2:

			if(iX>=370 && iX<=475 && iY>=300 && iY<=330) {
                // Go to state main
                m_state = level2;
                stage1 = false;
                // Force redraw of background
                SetupBackgroundBuffer();
                // Redraw the whole screen now
                Redraw(true);

                m_state = stateMain;
                SetupBackgroundBuffer();
                Redraw(true);
			}
			break;

        case gameOver: //???

            /*if(iX>=330 && iX<=475 && iY>=250 && iY<=280) {
                // Go to state main
                m_state = stateInit;
                // Force redraw of background
                SetupBackgroundBuffer();
                // Redraw the whole screen now
                Redraw(true);
                m_state = stateInit;
                break;
			}
			if(iX>=370 && iX<=430 && iY>=300 && iY<=330) {

                SetExitWithCode( 0 );
                break;
			}*/
            break;
		}
    }
}
//some animation to show that the mouse is over the button
void GameMain::MouseMoved(int iX, int iY)
{
    switch( m_state )
		{
		case stateInit:

			if(iX>=370 && iX<=470 && iY>=255 && iY<=280) {

                // Go to state main
                m_state = temp1;
                // Force redraw of background
                SetupBackgroundBuffer();
                // Redraw the whole screen now
                Redraw(true);
			}
			else if(iX>=370 && iX<=475 && iY>=300 && iY<=330) {
                // Go to state main
                m_state = temp2;
                // Force redraw of background
                SetupBackgroundBuffer();
                // Redraw the whole screen now
                Redraw(true);
			}
			break;

        case temp1:

            if(iX>=370 && iX<=470 && iY>=255 && iY<=280) {

                // Go to state main
                m_state = stateInit;
                // Force redraw of background
                SetupBackgroundBuffer();
                // Redraw the whole screen now
                Redraw(true);
			}
			if(iX>=370 && iX<=475 && iY>=300 && iY<=330) {
                // Go to state main
                m_state = stateInit;
                // Force redraw of background
                SetupBackgroundBuffer();
                // Redraw the whole screen now
                Redraw(true);
			}
			break;

        case temp2:

			if(iX>=370 && iX<=475 && iY>=300 && iY<=330) {
                // Go to state main
                m_state = stateInit;
                // Force redraw of background
                SetupBackgroundBuffer();
                // Redraw the whole screen now
                Redraw(true);
			}
			if(iX>=370 && iX<=470 && iY>=255 && iY<=280) {

                // Go to state main
                m_state = stateInit;
                // Force redraw of background
                SetupBackgroundBuffer();
                // Redraw the whole screen now
                Redraw(true);
			}
		}
}
/*
Handle any key presses here.
Note that the objects themselves (e.g. player) may also check whether a key is pressed
*/
void GameMain::KeyDown(int iKeyCode)
{
	switch ( iKeyCode )
	{
	case SDLK_ESCAPE: // End program when escape is pressed
		SetExitWithCode( 0 );
		break;

	case SDLK_SPACE: // SPACE Pauses
        switch( m_state )
		{
		case level1:
			// Go to state paused
			m_state = statePaused;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;

        case level2:
			// Go to state paused
			m_state = statePaused;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;

        case stateMain:
            // Go to state paused
			m_state = statePaused;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;

		case statePaused:

            m_state = stateMain;
			// Force redraw of background
			SetupBackgroundBuffer();
			// Redraw the whole screen now
			Redraw(true);
			break;
		} // End switch on current state
	}
}

void GameMain::DrawChanges()
{
	// NEW IF
	if ( m_state == stateInit || m_state == temp1 ||
         m_state == temp2 || m_state == gameOver || m_state == win)
		return; // Do not draw objects if initialising

	// Remove objects from their old positions
	UndrawChangingObjects();
	// Draw the text for the user
	DrawStrings();
	// Draw objects at their new positions
	DrawChangingObjects();
}

/* Draw the screen - copy the background buffer, then draw the text and objects. */
void GameMain::DrawScreen()
{
	// First draw the background
	CopyAllBackgroundBuffer();
	// And finally, draw the text
	DrawStrings();

	// NEW IF
	if ( m_state == stateInit || m_state == temp1 ||
         m_state == temp2 || m_state == gameOver || m_state == win)
		return; // Do not draw objects if initialising

	// Then draw the changing objects
	DrawChangingObjects();
}

bool GameMain::isStage1()
{
    return stage1;
}
