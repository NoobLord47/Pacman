#include "header.h"
#include "JPGImage.h"
#include "PacmanTileManager.h"

PacmanTileManager::PacmanTileManager(void)
{
}

PacmanTileManager::~PacmanTileManager(void)
{
}

// Get the size of a tile - width
int PacmanTileManager::GetTileWidth()
{
	return 30;
}

// Get the size of a tile - height
int PacmanTileManager::GetTileHeight()
{
	return 30;
}

// Draw a tile at a location on the screen determined by the tile
// position and the base X and Y co-ordinates
// OVERRIDE THIS TO DRAW YOUR TILE!!!
// Draw a tile
void PacmanTileManager::DrawTileAt(
	BaseEngine* pEngine,
	SDL_Surface* pSurface,
	int iMapX, int iMapY,
	int iStartPositionScreenX, int iStartPositionScreenY )
{
	// Base class implementation just draws some grey tiles

	switch( GetValue(iMapX,iMapY) )
	{
	case 0:
	case 1:
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour( GetValue(iMapX,iMapY) ),
			pSurface );
		break;

	case 2:
	    pEngine->DrawOval(
			iStartPositionScreenX+GetValue(iMapX,iMapY)*2+15,
			iStartPositionScreenY+GetValue(iMapX,iMapY)*2+15,
			iStartPositionScreenX + GetTileWidth() - GetValue(iMapX,iMapY)*2 -17,
			iStartPositionScreenY + GetTileHeight() - GetValue(iMapX,iMapY)*2 -17,
			pEngine->GetColour( GetValue(iMapX,iMapY) ),
			pSurface );
		break;

	case 3:

	case 4:
	    pEngine->DrawOval(
			iStartPositionScreenX+GetValue(iMapX,iMapY)*2+9,
			iStartPositionScreenY+GetValue(iMapX,iMapY)*2+9,
			iStartPositionScreenX + GetTileWidth() - GetValue(iMapX,iMapY)*2 -14,
			iStartPositionScreenY + GetTileHeight() - GetValue(iMapX,iMapY)*2 -14,
			pEngine->GetColour( GetValue(iMapX,iMapY) ),
			pSurface );
		break;

	case 5:
	case 6:
	case 7:
	case 8:
		pEngine->DrawRectangle(
			iStartPositionScreenX,
			iStartPositionScreenY,
			iStartPositionScreenX + GetTileWidth() - 1,
			iStartPositionScreenY + GetTileHeight() - 1,
			pEngine->GetColour( 0 ), //keep at 0 - black
			pSurface );

		pEngine->DrawOval(
			iStartPositionScreenX+GetValue(iMapX,iMapY)*2+5,
			iStartPositionScreenY+GetValue(iMapX,iMapY)*2+5,
			iStartPositionScreenX + GetTileWidth() - GetValue(iMapX,iMapY)*2 -6,
			iStartPositionScreenY + GetTileHeight() - GetValue(iMapX,iMapY)*2 -6,
			pEngine->GetColour( GetValue(iMapX,iMapY) ),
			pSurface );
			/*image2.LoadImage("strawberry.png");
            image1.ShrinkFrom( &image2, 2 );
            image1.RenderImageWithMask( pEngine->GetForeground(),0, 0,
                        iStartPositionScreenX-15,
                                       iStartPositionScreenY-15,
                        image1.GetWidth(), image1.GetHeight() );*/

		break;
	}
}
