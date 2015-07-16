#include "header.h"
#include "BaseEngine.h"
#include "Pacman.h"
#include "GameMain.h"
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//code for the yellow ball
int temp, itemp;
bool booster = false;
bool slime = false;
int life = 3;
bool wins = false;

Pacman::Pacman(GameMain* pEngine, int iMapX, int iMapY)
    : DisplayableObject(pEngine)
    , m_pMainEngine(pEngine)
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
}
Pacman::~Pacman(void)
{
}

bool Pacman::checkBooster(void)
{
    return booster;
}

void Pacman::Draw()
{
    // Do not draw if it should not be visible
    if ( !IsVisible() )
        return;

    int iTick = m_pMainEngine->GetTime()/20; // 1 per 20ms
    int iFrame = iTick % 30;

    if ( iFrame > 10 ) //open big mouth
    {
        if(m_iDir==0) //up
        {
            image2.LoadImage("pacopen3u.png");
            image1.ShrinkFrom( &image2, 2 );
            image1.RenderImageWithMask( m_pMainEngine->GetForeground(),0, 0,
                        m_iCurrentScreenX-15, m_iCurrentScreenY-15,
                        image1.GetWidth(), image1.GetHeight() );
        }
        if(m_iDir==1) //right
        {
            image2.LoadImage("pacopen3.png");
            image1.ShrinkFrom( &image2, 2 );
            image1.RenderImageWithMask( m_pMainEngine->GetForeground(),0, 0,
                        m_iCurrentScreenX-15, m_iCurrentScreenY-15,
                        image1.GetWidth(), image1.GetHeight() );
        }
        if(m_iDir==2) //down
        {
            image2.LoadImage("pacopen3d.png");
            image1.ShrinkFrom( &image2, 2 );
            image1.RenderImageWithMask( m_pMainEngine->GetForeground(),0, 0,
                        m_iCurrentScreenX-15, m_iCurrentScreenY-15,
                        image1.GetWidth(), image1.GetHeight() );
        }
        if(m_iDir==3) //left
        {
            image2.LoadImage("pacopen3l.png");
            image1.ShrinkFrom( &image2, 2 );
            image1.RenderImageWithMask( m_pMainEngine->GetForeground(),0, 0,
                        m_iCurrentScreenX-15, m_iCurrentScreenY-15,
                        image1.GetWidth(), image1.GetHeight() );
        }
    }
    else //close mouth
    {
        if(m_iDir==0) //up
        {
            image2.LoadImage("pacopen1u.png");
            image1.ShrinkFrom( &image2, 2 );
            image1.RenderImageWithMask( m_pMainEngine->GetForeground(),0, 0,
                        m_iCurrentScreenX-15, m_iCurrentScreenY-15,
                        image1.GetWidth(), image1.GetHeight() );
        }
        if(m_iDir==1) //right
        {
            image2.LoadImage("pacopen1.png");
            image1.ShrinkFrom( &image2, 2 );
            image1.RenderImageWithMask( m_pMainEngine->GetForeground(),0, 0,
                        m_iCurrentScreenX-15, m_iCurrentScreenY-15,
                        image1.GetWidth(), image1.GetHeight() );
        }
        if(m_iDir==2) //down
        {
            image2.LoadImage("pacopen1d.png");
            image1.ShrinkFrom( &image2, 2 );
            image1.RenderImageWithMask( m_pMainEngine->GetForeground(),0, 0,
                        m_iCurrentScreenX-15, m_iCurrentScreenY-15,
                        image1.GetWidth(), image1.GetHeight() );
        }
        if(m_iDir==3) //left
        {
            image2.LoadImage("pacopen1l.png");
            image1.ShrinkFrom( &image2, 2 );
            image1.RenderImageWithMask( m_pMainEngine->GetForeground(),0, 0,
                        m_iCurrentScreenX-15, m_iCurrentScreenY-15,
                        image1.GetWidth(), image1.GetHeight() );
        }
    }
    // Store the position at which the object was last drawn
    // You MUST do this to ensure that the screen is updated when only drawing movable objects
    // This tells the system where to 'undraw' the object from
    StoreLastScreenPositionAndUpdateRect();
}

void Pacman::DoUpdate( int iCurrentTime )
{
    m_iPreviousScreenX = m_iCurrentScreenX;
    m_iPreviousScreenY = m_iCurrentScreenY;

    // Iterate through the object
    // We are looking for one which is too close to us
    DisplayableObject* pObject;
    for ( int iObjectId = 0 ;
            (pObject = m_pMainEngine->GetDisplayableObject( iObjectId )) != NULL ;
            iObjectId++ )
    {
        if ( pObject == this ) // This is us, skip it
            continue;
        // If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19
        // We are just using base class parts
        int iXDiff = pObject->GetXCentre() - m_iCurrentScreenX;
        int iYDiff = pObject->GetYCentre() - m_iCurrentScreenY;

        // Estimate the size - by re-calculating it
        int iTick = iCurrentTime/20; // 1 per 20ms
        int iFrame = iTick % 30;
        int iSize = 5 + iFrame;
        if ( iFrame > 10 )
            iSize = -4 + (30-iFrame);
        int iSizeOther = iSize; // Assume both the same size

        // Pythagorus' theorum:
        if ( ((iXDiff*iXDiff)+(iYDiff*iYDiff))
                < ((iSizeOther+iSize)*(iSizeOther+iSize)) )
        {
            // Move us to 1,1 and set direction right
            m_iMapX = 1;
            m_iMapY = 1;
            m_iDir = 0; // Face right

            m_oMover.Setup(
                m_iMapX *30 + 20 + 20, //m_iCurrentScreenX,
                m_iMapY *30 + 15 + 40, //m_iCurrentScreenY,
                m_iMapX *30 + 20 + 20,
                m_iMapY *30 + 15 + 40,
                iCurrentTime,
                iCurrentTime+350+rand()%100 );

            // Ask the mover where the object should be
            m_oMover.Calculate( iCurrentTime );
            m_iCurrentScreenX = m_oMover.GetX();
            m_iCurrentScreenY = m_oMover.GetY();

            life--; //decrease life count

            // Ensure that the object gets redrawn on the display, if something changed
            RedrawObjects();
            return;
        }
    }
    // If movement has finished
    if ( m_oMover.HasMovementFinished(iCurrentTime) )
    {
        PacmanTileManager& tm = m_pMainEngine->GetTileManager();

        // Handle any tile that we just moved onto
        switch ( tm.GetValue( m_iMapX, m_iMapY ) )
        {
        case 2:
            temp = iCurrentTime; //store the current time to use the booster
        case 3:
        case 4:
            itemp = iCurrentTime; //store the current time to activate the slime
        case 5:
        case 6:
        case 7:
        case 8:
            tm.UpdateTile( m_pMainEngine, m_iMapX, m_iMapY, 0 );
            score++;

            if(score==225)  //win state - change the number if user wants
                            //to go to win state earlier/faster
                wins = true;

            break;
        }
        printScreen(); //will print the scoreboard and life count

        if ( m_pMainEngine->IsKeyPressed( SDLK_UP ) )
            m_iDir = 0;
        if ( m_pMainEngine->IsKeyPressed( SDLK_RIGHT ) )
            m_iDir = 1;
        if ( m_pMainEngine->IsKeyPressed( SDLK_DOWN ) )
            m_iDir = 2;
        if ( m_pMainEngine->IsKeyPressed( SDLK_LEFT ) )
            m_iDir = 3;

        switch ( tm.GetValue(
                     m_iMapX + GetXDiffForDirection(m_iDir),
                     m_iMapY + GetYDiffForDirection(m_iDir) ) )
        {
        case 0: // Passageway
        case 2: // Pellet
        case 3: // Pellet
        case 4: // Pellet
        case 5: // Pellet
        case 6: // Pellet
        case 7: // Pellet
        case 8: // Pellet

            // Allow move - set up new movement now
            m_iMapX += GetXDiffForDirection(m_iDir);
            m_iMapY += GetYDiffForDirection(m_iDir);

            if((m_pMainEngine->isStage1())==true) //check if it's level 1
            {
                if(tm.GetValue(17,6)==0 || tm.GetValue(7,13)==0){
                    booster = true; //booster is acquired
                }
                    if(iCurrentTime-temp>8000)
                        booster = false; //time limit to use the booster
            }
            else if((m_pMainEngine->isStage1())==false)
            {
                if(tm.GetValue(17,4)==0)
                {
                    slime = true; //slimy jelly is activated
                }
                if(iCurrentTime-itemp>8000) //set time limit to activate slime
                {
                    slime = false;
                }
            }
            if(booster==false && slime==false) //normal speed
            {
                m_oMover.Setup(
                    m_iCurrentScreenX,
                    m_iCurrentScreenY,
                    m_iMapX *30 + 20 + 20,
                    m_iMapY *30 + 15 + 40,
                    iCurrentTime,
                    iCurrentTime+300+rand()%100 );
            }
            else if(booster==true) //booster allows pacman to have super speed
            {
                m_oMover.Setup(
                    m_iCurrentScreenX,
                    m_iCurrentScreenY,
                    m_iMapX *30 + 20 + 20,
                    m_iMapY *30 + 15 + 40,
                    iCurrentTime,
                    iCurrentTime+125+rand()%100 );
            }
            else if(slime==true) //slime makes the pacman moves slower
            {
                m_oMover.Setup(
                    m_iCurrentScreenX,
                    m_iCurrentScreenY,
                    m_iMapX *30 + 20 + 20,
                    m_iMapY *30 + 15 + 40,
                    iCurrentTime,
                    iCurrentTime+600+rand()%100 );
            }
            break;

        case 1: // Wall
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

void Pacman::setPoisoned() //
{
    booster = false; //undo the poison
}

int Pacman::getLife()
{
    return life;
}

bool Pacman::checkHit()
{
    return wins;
}

int Pacman::getScore()
{
    return score;
}

void Pacman::printScreen()
{
    stringstream scoreCount;
    stringstream lifeCount;
    scoreCount<<score;
    lifeCount<<life;

    string score_str = scoreCount.str();
    char* pchar = new char [score_str.length()];
    strcpy(pchar,score_str.c_str());

    string life_str = lifeCount.str();
    char* lchar = new char [life_str.length()];
    strcpy(lchar,life_str.c_str());

    if(booster==false && slime==false)
    {
        m_pMainEngine->CopyBackgroundPixels(0/*X*/, 5/*Y*/, m_pMainEngine->GetScreenWidth(), 40 );
        m_pMainEngine->DrawScreenString(650, 10, "Score: ", 0xffffff, NULL);
        m_pMainEngine->DrawScreenString(750, 10, pchar, 0xffffff, NULL);

        m_pMainEngine->DrawScreenString(10, 10, "Lives: ", 0xffffff, NULL);
        m_pMainEngine->DrawScreenString(90, 10, lchar, 0xffffff, NULL);
        m_pMainEngine->SetNextUpdateRect(0/*X*/, 5/*Y*/, m_pMainEngine->GetScreenWidth(), 40 );
    }
    else if(booster==true && slime==false)
    {
        m_pMainEngine->CopyBackgroundPixels(0/*X*/, 5/*Y*/, m_pMainEngine->GetScreenWidth(), 40 );
        m_pMainEngine->DrawScreenString(650, 10, "Score: ", 0xffffff, NULL);
        m_pMainEngine->DrawScreenString(750, 10, pchar, 0xffffff, NULL);

        m_pMainEngine->DrawScreenString(10, 10, "Lives: ", 0xffffff, NULL);
        m_pMainEngine->DrawScreenString(90, 10, lchar, 0xffffff, NULL);

        m_pMainEngine->DrawScreenString(300, 10, "Booster Acquired!", 0xffffff, NULL);
        m_pMainEngine->SetNextUpdateRect(0/*X*/, 5/*Y*/, m_pMainEngine->GetScreenWidth(), 40 );
    }
    else if(booster==false && slime==true)
    {
        m_pMainEngine->CopyBackgroundPixels(0/*X*/, 5/*Y*/, m_pMainEngine->GetScreenWidth(), 40 );
        m_pMainEngine->DrawScreenString(650, 10, "Score: ", 0xffffff, NULL);
        m_pMainEngine->DrawScreenString(750, 10, pchar, 0xffffff, NULL);

        m_pMainEngine->DrawScreenString(10, 10, "Lives: ", 0xffffff, NULL);
        m_pMainEngine->DrawScreenString(90, 10, lchar, 0xffffff, NULL);

        m_pMainEngine->DrawScreenString(320, 10, "Slimy Jelly!", 0xffffff, NULL);
        m_pMainEngine->SetNextUpdateRect(0/*X*/, 5/*Y*/, m_pMainEngine->GetScreenWidth(), 40 );
    }

}




