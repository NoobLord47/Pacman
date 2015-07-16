#include "header.h"
#include "Pacman.h"
#include "Ghost.h"
#include "GameMain.h"
#include "JPGImage.h"

Ghost::Ghost(GameMain* pEngine, int iMapX, int iMapY)
: DisplayableObject(pEngine)
, m_pMainEngine( pEngine )
, m_iMapX(iMapX)
, m_iMapY(iMapY)
, m_iDir(0)
{
	// The ball coordinate will be the centre of the ball
	// Because we start drawing half the size to the top-left.
	m_iStartDrawPosX = -15;
	m_iStartDrawPosY = -15;

	// Record the ball size as both height and width
	m_iDrawWidth = 30;
	m_iDrawHeight = 30;

	// Out item at specific coordinates
	m_iPreviousScreenX = m_iCurrentScreenX = iMapX*30+20+20;
	m_iPreviousScreenY = m_iCurrentScreenY = iMapY*30+15+40;

	// And make it visible
	SetVisible(true);
	img2.LoadImage("ghostdownblue1.png");
	img.ShrinkFrom( &img2, 2 );
}

Ghost::~Ghost(void)
{

}

void Ghost::Draw()
{
	// Do not draw if it should not be visible
	if ( !IsVisible() )
		return;

	int iSize = 15;

	img.RenderImageWithMask( m_pMainEngine->GetForeground(),0, 0,
					m_iCurrentScreenX-15, m_iCurrentScreenY-15,
					img.GetWidth(), img.GetHeight() );
	// Draw an image loaded from a file.

	// Store the position at which the object was last drawn
	// You MUST do this to ensure that the screen is updated when only drawing movable objects
	// This tells the system where to 'undraw' the object from
	StoreLastScreenPositionAndUpdateRect();
}

void Ghost::DoUpdate( int iCurrentTime )
{
	m_iPreviousScreenX = m_iCurrentScreenX;
	m_iPreviousScreenY = m_iCurrentScreenY;


	// If movement has finished
	if ( m_oMover.HasMovementFinished(iCurrentTime) )
	{
		PacmanTileManager& tm = m_pMainEngine->GetTileManager();

		// Set off a new movement
		switch( rand() % 10 )
		{
		case 0: // Increase dir by 1
			m_iDir = ( m_iDir + 1 )%4;
			break;
		case 1: // Reduce dir by 1
			m_iDir = ( m_iDir + 3 )%4;
			break;
		}

        /*The following SWICTH will change the behaviour so that the objects move around the walls instead
        of through them. i.e. it will check the tile position and only allow a move
        if there is no blocking wall.
		*/
		switch ( tm.GetValue(
				m_iMapX + GetXDiffForDirection(m_iDir),
				m_iMapY + GetYDiffForDirection(m_iDir) ) )
		{
		case 0: // Passageway
		case 2: // green Pellet
		case 3: // blue Pellet
		case 4: // pink Pellet
		case 5: // yellow Pellet
		case 6: // cyan Pellet
		case 7: // bigger white Pellet
		case 8: // Pellet
			// Allow move - set up new movement now
			m_iMapX += GetXDiffForDirection(m_iDir);
			m_iMapY += GetYDiffForDirection(m_iDir);

        if((m_pMainEngine->isStage1())==true)
        {
			m_oMover.Setup(
				m_iCurrentScreenX,
				m_iCurrentScreenY,
				m_iMapX *30 + 20 + 20,
				m_iMapY *30 + 15 + 40,
				iCurrentTime,
				iCurrentTime+300+rand()%200 );
        }
        else //speed of ghost is faster in second level
        {
            m_oMover.Setup(
				m_iCurrentScreenX,
				m_iCurrentScreenY,
				m_iMapX *30 + 20 + 20,
				m_iMapY *30 + 15 + 40,
				iCurrentTime,
				iCurrentTime+260+rand()%200 );
        }
			break;

		case 1: // if the ball touch the Wall
			m_iDir = rand()%4; // Rotate randomly
			break;
		}
	}
	// If making a move then do the move
	if ( !m_oMover.HasMovementFinished(iCurrentTime) )
	{
		// Ask the mover where the object should be
		m_oMover.Calculate( iCurrentTime );
		m_iCurrentScreenX = m_oMover.GetX();
		m_iCurrentScreenY = m_oMover.GetY();
	}
	// Ensure that the object gets redrawn on the display, if something changed
	RedrawObjects();
}











