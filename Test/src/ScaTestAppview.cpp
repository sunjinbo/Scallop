/* ====================================================================
 * File: ScaTestAppView.cpp
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */
 
#include <fbs.h>
#include <bitstd.h>
#include <eikenv.h>
#include <coemain.h>
#include <ScaTest.rsg>
#include <aknnotewrappers.h>
#include <EngineCommon.h>
#include <ClassicEngineFactory.h>
#include <StrategyEngineFactory.h>
#include <Aquatic.hrh>
#include <AquaticData.h>
#include <EngineBase.h>
#include <BmpUtils.h>
#include <menubar.mbg>
#include "ScaTestAppView.h"

const TInt KDoDelayTimeout = 0;
const TInt KDoFrameUpdateTimeout = 50000;

// Standard construction sequence
CScaTestAppView* CScaTestAppView::NewL(const TRect& aRect)
    {
    CScaTestAppView* self = CScaTestAppView::NewLC(aRect);
    CleanupStack::Pop(self);
    return self;
    }

CScaTestAppView* CScaTestAppView::NewLC(const TRect& aRect)
    {
    CScaTestAppView* self = new (ELeave) CScaTestAppView;
    CleanupStack::PushL(self);
    self->ConstructL(aRect);
    return self;
    }

CScaTestAppView::CScaTestAppView()
    : iDrag( 0 )  
    {
    // no implementation required
    }

CScaTestAppView::~CScaTestAppView()
    {
    ReleaseBmpBuffer();
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        }
    delete iClassicEngineFactory;
    delete iStrategyEngineFactory;
    delete iEngine;
    }

void CScaTestAppView::Start()
    {
    iEngine->HandleCommandL( EEngineCmdStart );
    }

void CScaTestAppView::Stop()
    {
    iEngine->HandleCommandL( EEngineCmdStop );
    }
    
void CScaTestAppView::Pause()
    {
    iEngine->HandleCommandL( EEngineCmdPause );
    }

void CScaTestAppView::Resume()
    {
    iEngine->HandleCommandL( EEngineCmdResume );
    }

void CScaTestAppView::Restart()
    {
    iEngine->HandleCommandL( EEngineCmdRestart );
    }
    
void CScaTestAppView::Refresh()
    {
    iEngine->HandleCommandL( EEngineCmdRefresh );
    }

void CScaTestAppView::FuncKey()
    {
    iEngine->HandleCommandL( EEngineCmdFuncKey );
    }

void CScaTestAppView::StateChanged( TEngineAction aAction )
    {
    switch ( aAction )
        {
        case EEngineActionStart:
            break;
        case EEngineActionPause:
            break;
        case EEngineActionStop:
            break;
        case EEngineActionLevelExpired:
            _LIT(KLevelExpired,"Level Expired!");
            CAknInformationNote* informationNote01 = new (ELeave) CAknInformationNote;
            informationNote01->ExecuteLD(KLevelExpired);
            break;
        case EEngineActionLevelFailed:
            _LIT(KLevelFailed,"Level Failed!");
            CAknInformationNote* informationNote02 = new (ELeave) CAknInformationNote;
            informationNote02->ExecuteLD(KLevelFailed);
            break;
        case EEngineActionGameOver:
            _LIT(KGameOver,"Game Over!");
            CAknInformationNote* informationNote03 = new (ELeave) CAknInformationNote;
            informationNote03->ExecuteLD(KGameOver);
            break;
        default:
            break;
        }
    }

void CScaTestAppView::AuqaticChanged( TAquaticAction aAction, const RArray<TAquaticData>& aList )
    {
    switch( aAction )
        {
        case EAquaticActionBorn:
            DrawBornGrids( aList );
            //ClearAllPath();
            break;
        case EAquaticActionMatured:
            DrawMaturedGrids( aList );
            //ClearAllPath();
            break;
        case EAquaticActionMoved:
            DrawMovedGrids( aList );
            //ClearAllPath();
            break;
        case EAquaticActionChanged:
            DrawChangedGrids( aList );
            //ClearAllPath();
            break;
        case EAquaticActionReleased:
            DrawReleasedGrids( aList );
            //ClearAllPath();
            break;
        case EAquaticActionUpdated:
            DrawUpdatedGrids( aList );
            //ClearAllPath();
            break;
        case EAquaticActionSelected:
            DrawSelectedGrids( aList );
            break;
        case EAquaticActionUnselected:
            DrawUnselectedGrids( aList );
            break;
        default:
            break;
        }
    }

void CScaTestAppView::PathChanged( TPathAction aAction, const RArray<TPoint>& aList )
    {
    switch( aAction )
        {
        case EPathActionDisplayed:
            DrawPath( aList );
            break;
        case EPathActionDisappeared:
            ClearPath( aList );
            break;
        default:
            break;
        }
    }

void CScaTestAppView::ScorekeeperChanged( TScorekeeperAction aAction, TInt aValue )
    {
    switch ( aAction )
        {
        case EScorekeeperActionLevel:
            DrawLevel( aValue );
            break;
       case  EScorekeeperActionScore:
            DrawScore( aValue );
            break;
        case EScorekeeperActionBonus:
            DrawBonus( aValue );
            break;
        case EScorekeeperActionMoves:
            break;
        default:
            break;
        }
    }

void CScaTestAppView::FuncKeyChanged( TAquaticType aType, TInt aValue )
    {
    DrawFuncKey( aType, aValue );
    }

void CScaTestAppView::ConstructL(const TRect& aRect)
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect(aRect);
    CreateBmpBufferL();

    TFontSpec fontSpec = iEikonEnv->AnnotationFont()->FontSpecInTwips();
    fontSpec.iHeight  -= fontSpec.iHeight / 4;
    fontSpec.iFontStyle.SetBitmapType( ESubPixelGlyphBitmap );
    iEikonEnv->ScreenDevice()->GetNearestFontInTwips( iFont, fontSpec );

    if ( aRect.Width() < aRect.Height() )
        {
        iSquareSideLen = aRect.Width() / KMainMatrixWidth;
        iScorePos.SetXY( 10, 265 );
        iBonusPos.SetXY( 10, 280 );
        iLevelPos.SetXY( 120, 265 );
        }
    else
        {
        iSquareSideLen = aRect.Height() / KMainMatrixWidth;
        }

    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
                    KDoDelayTimeout,
                    KDoFrameUpdateTimeout,
                    TCallBack( TimerCallback, this ) );

    iClassicEngineFactory = CClassicEngineFactory::NewL();
    iStrategyEngineFactory = CStrategyEngineFactory::NewL();
    iEngine = iStrategyEngineFactory->ScaEngineL( *this );

    DoDraw();
    
    DrawFuncKey( EAquaticNull, 0 );

    // Enable Drag Events.
    EnableDragEvents();
    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// Draw this application's view to the screen
void CScaTestAppView::Draw(const TRect& /*aRect*/) const
    { // no implementation required.
    }

void CScaTestAppView::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
        {
        iDrag = 0;
        iDragPos = TPoint( -1, -1 );
        TInt w = aPointerEvent.iPosition.iX / iSquareSideLen;
        TInt h = aPointerEvent.iPosition.iY / iSquareSideLen;
        if ( w < KMainMatrixWidth && h < KMainMatrixHeight )
            {
            iEngine->ClickL( w, h );
            }
        }
    
    if ( aPointerEvent.iType == TPointerEvent::EDrag )
        {
        TInt w = aPointerEvent.iPosition.iX / iSquareSideLen;
        TInt h = aPointerEvent.iPosition.iY / iSquareSideLen;
        if ( w < KMainMatrixWidth && h < KMainMatrixHeight )
            {
            if ( iDragPos != TPoint( w, h ) )
                {
                iDragPos = TPoint( w, h );
                iDrag++;
                ClearAllPath();
                iEngine->DragL( w, h );
                }
            }
        }

    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        if ( iDrag > 0 )
            {
            ClearAllPath();
            TInt w = aPointerEvent.iPosition.iX / iSquareSideLen;
            TInt h = aPointerEvent.iPosition.iY / iSquareSideLen;
            if ( w < KMainMatrixWidth && h < KMainMatrixHeight )
                {
                iEngine->ClickL( w, h );
                }
            }
        }
    }

TInt CScaTestAppView::TimerCallback( TAny* aPtr )
    {
    CScaTestAppView* self = static_cast<CScaTestAppView*> ( aPtr );
    self->DoFrame();
    return 0;
    }

void CScaTestAppView::DoDraw()
    {
    DrawGrids();
    DrawBitmap();
    }

void CScaTestAppView::DoFrame()
    {
    Window().Invalidate( Rect() );
    ActivateGc();
    Window().BeginRedraw( Rect() );
    CWindowGc& gc = SystemGc();
    gc.BitBlt( TPoint( 0, 0 ), iBitmap );
    Window().EndRedraw();
    DeactivateGc();
    }

void CScaTestAppView::CreateBmpBufferL()
    {
    ReleaseBmpBuffer();

    // Create double buffer bitmap
    iBitmap = new (ELeave) CFbsBitmap;
    User::LeaveIfError( iBitmap->Create( Size(), EColor16MU ) );

    // Create double buffer graphics context
    iBitmapDevice = CFbsBitmapDevice::NewL( iBitmap );
    User::LeaveIfError( iBitmapDevice->CreateContext( iBitmapGc ) );

    iBitmapGc->SetBrushColor( KRgbDarkCyan );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->DrawRect( TRect( TPoint(0,0), Size() ) );
    
    }

void CScaTestAppView::ReleaseBmpBuffer()
    {
    if ( iBitmapGc )
        {
        delete iBitmapGc;
        iBitmapGc = NULL;
        }
    if ( iBitmapDevice )
        {
        delete iBitmapDevice;
        iBitmapDevice = NULL;
        }
    if ( iBitmap )
        {
        delete iBitmap;
        iBitmap = NULL;
        }
    }

void CScaTestAppView::DrawGrids()
    {
    iBitmapGc->SetBrushColor( KRgbGray );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    
    for ( TInt i = 0; i < KMainMatrixWidth; i++ )
        for ( TInt j = 0; j < KMainMatrixHeight; j++ )
            {
            iBitmapGc->DrawRect( TRect( 
                TPoint( i * iSquareSideLen, j * iSquareSideLen ), 
                TSize( iSquareSideLen, iSquareSideLen ) ) 
                );
            }
    }

void CScaTestAppView::DrawBornGrids( const RArray<TAquaticData>& aList )
    {
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    TInt count = aList.Count();
    for ( TInt i = 0; i < count; ++i )
        {
        TAquaticData aquatic = aList[ i ];
        TPoint pos = aquatic.Position();
        SetEdgeColor( aquatic.Type() );
        iBitmapGc->DrawRect( TRect( 
                TPoint( pos.iX * iSquareSideLen + 8, pos.iY * iSquareSideLen + 8 ), 
                TSize( iSquareSideLen - 16, iSquareSideLen - 16 ) )
                );
        }
    }

void CScaTestAppView::DrawMaturedGrids( const RArray<TAquaticData>& aList )
    {
    iBitmapGc->SetPenStyle( CGraphicsContext::ENullPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    TInt count = aList.Count();
    for ( TInt i = 0; i < count; ++i )
        {
        TAquaticData aquatic = aList[ i ];
        TPoint pos = aquatic.Position();
        SetEdgeColor( aquatic.Type() );
        iBitmapGc->DrawRect( TRect( 
                TPoint( pos.iX * iSquareSideLen, pos.iY * iSquareSideLen ), 
                TSize( iSquareSideLen, iSquareSideLen ) ) 
                );
        DrawEdge( pos, KRgbBlack );
        }
    }

void CScaTestAppView::DrawMovedGrids( const RArray<TAquaticData>& aList )
    {
    RArray<TAquaticData> list;
    TInt count = aList.Count();
    TPoint pos = aList[ 0 ].Position();
    list.Append( aList[ 0 ] );
    DrawMaturedGrids( list );
    list.Reset();
    pos = aList[ count - 1 ].Position();
    list.Append( aList[ count - 1 ] );
    DrawReleasedGrids( list );
    DrawEdge( pos, KRgbBlack );
    list.Close();
    }

void CScaTestAppView::DrawChangedGrids( const RArray<TAquaticData>& aList )
    {
    DrawMaturedGrids( aList );
    }
    
void CScaTestAppView::DrawReleasedGrids( const RArray<TAquaticData>& aList )
    {
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetBrushColor( KRgbGray );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    TInt count = aList.Count();
    for ( TInt i = 0; i < count; ++i )
        {
        TAquaticData aquatic = aList[ i ];
        TPoint pos = aquatic.Position();
        iBitmapGc->DrawRect( TRect( 
                TPoint( pos.iX * iSquareSideLen, pos.iY * iSquareSideLen ), 
                TSize( iSquareSideLen, iSquareSideLen ) ) 
                );
        }
    }

void CScaTestAppView::DrawUpdatedGrids( const RArray<TAquaticData>& aList )
    {
    iBitmapGc->SetPenStyle( CGraphicsContext::ENullPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    TInt count = aList.Count();
    for ( TInt i = 0; i < count; ++i )
        {
        TAquaticData aquatic = aList[ i ];
        TPoint pos = aquatic.Position();
        SetEdgeColor( aquatic.Type() );
        if ( !aquatic.IsMature() )
            {
            iBitmapGc->DrawRect( TRect( 
                    TPoint( pos.iX * iSquareSideLen + 8, pos.iY * iSquareSideLen + 8 ), 
                    TSize( iSquareSideLen - 16, iSquareSideLen - 16 ) )
                    );
            }
        else
            {
            iBitmapGc->DrawRect( TRect( 
                TPoint( pos.iX * iSquareSideLen, pos.iY * iSquareSideLen ), 
                TSize( iSquareSideLen, iSquareSideLen ) ) 
                );
            }
        DrawEdge( pos, KRgbBlack );
        }
    }

void CScaTestAppView::DrawSelectedGrids( const RArray<TAquaticData>& aList )
    {
    TInt count = aList.Count();
    for ( TInt i = 0; i < count; ++i )
        {
        TAquaticData aquatic = aList[ i ];
        TPoint pos = aquatic.Position();
        DrawEdge( pos, KRgbWhite );
        }
    }

void CScaTestAppView::DrawUnselectedGrids( const RArray<TAquaticData>& aList )
    {
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );

    for ( TInt i = 0; i < aList.Count(); i++ )
            {
            TPoint pos( aList[ i ].Position() );
            TPoint start, end;
            // up
            start.iX = pos.iX * iSquareSideLen;
            start.iY = pos.iY * iSquareSideLen;
            end.iX = ( pos.iX + 1 ) * iSquareSideLen;
            end.iY = pos.iY * iSquareSideLen;
            iBitmapGc->DrawLine( start, end );
            // left
            end.iX = pos.iX * iSquareSideLen;
            end.iY = ( pos.iY + 1 ) * iSquareSideLen;
            iBitmapGc->DrawLine( start, end );
            // down
            start.iX = ( pos.iX + 1 ) * iSquareSideLen;
            start.iY = ( pos.iY + 1 ) * iSquareSideLen;
            iBitmapGc->DrawLine( start, end );
            // right
            end.iX = ( pos.iX + 1 ) * iSquareSideLen;
            end.iY = pos.iY * iSquareSideLen;
            iBitmapGc->DrawLine( start, end );
            }
    }

void CScaTestAppView::SetEdgeColor( TAquaticType aType )
    {
    switch ( aType )
        {
        case EBlueScallop:
            iBitmapGc->SetBrushColor( KRgbBlue );
            break;
        case EDarkBlueScallop:
            iBitmapGc->SetBrushColor( KRgbDarkBlue );
            break;
        case EGreenScallop:
            iBitmapGc->SetBrushColor( KRgbGreen );
            break;
        case EDarkGreenScallop:
            iBitmapGc->SetBrushColor( KRgbDarkGreen );
            break;
        case ERedScallop:
            iBitmapGc->SetBrushColor( KRgbRed );
            break;
        case EMulberryScallop:
            iBitmapGc->SetBrushColor( KRgbMagenta );
            break;
        case EOrangeScallop:
            iBitmapGc->SetBrushColor( KRgbDarkYellow );
            break;
        case EYellowScallop:
            iBitmapGc->SetBrushColor( KRgbYellow );
            break;
        case EStarFish:
            iBitmapGc->SetBrushColor( KRgbBlack );
            break;
        case ETurtle: // fall through
        case EShark: // fall through
        case EOctopus: // fall through
        case ECuttleFish: // fall through
        case ESeaCrab: // fall through
        case EJellyfish: // fall through
            iBitmapGc->SetBrushColor( KRgbBlack );
            break;
        default:
            break;
        }
    }

void CScaTestAppView::SetZoneColor( TAquaticType /*aType*/ )
    {
    
    }

void CScaTestAppView::DrawPath( const RArray<TPoint>& aList )
    {
    ClearAllPath();
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    for ( TInt i = 0; i < aList.Count(); i++ )
        {
        if ( i == 0 )
        	{
        	iBitmapGc->SetPenColor( KRgbWhite );
        	}
        else if ( i == aList.Count() - 1 )
        	{
        	iBitmapGc->SetPenColor( KRgbWhite );
        	}
        else
        	{
        	iBitmapGc->SetPenColor( KRgbCyan );
        	}
 
        TPoint pos( aList[ i ] );
        TPoint start, end;
        // up
        start.iX = pos.iX * iSquareSideLen;
        start.iY = pos.iY * iSquareSideLen;
        end.iX = ( pos.iX + 1 ) * iSquareSideLen;
        end.iY = pos.iY * iSquareSideLen;
        iBitmapGc->DrawLine( start, end );
        // left
        end.iX = pos.iX * iSquareSideLen;
        end.iY = ( pos.iY + 1 ) * iSquareSideLen;
        iBitmapGc->DrawLine( start, end );
        // down
        start.iX = ( pos.iX + 1 ) * iSquareSideLen;
        start.iY = ( pos.iY + 1 ) * iSquareSideLen;
        iBitmapGc->DrawLine( start, end );
        // right
        end.iX = ( pos.iX + 1 ) * iSquareSideLen;
        end.iY = pos.iY * iSquareSideLen;
        iBitmapGc->DrawLine( start, end );
        }
    
    }

void CScaTestAppView::ClearPath( const RArray<TPoint>& aList )
    {
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    
    for ( TInt i = 0; i < aList.Count(); i++ )
        {
        TPoint pos( aList[ i ] );
        TPoint start, end;
        // up
        start.iX = pos.iX * iSquareSideLen;
        start.iY = pos.iY * iSquareSideLen;
        end.iX = ( pos.iX + 1 ) * iSquareSideLen;
        end.iY = pos.iY * iSquareSideLen;
        iBitmapGc->DrawLine( start, end );
        // left
        end.iX = pos.iX * iSquareSideLen;
        end.iY = ( pos.iY + 1 ) * iSquareSideLen;
        iBitmapGc->DrawLine( start, end );
        // down
        start.iX = ( pos.iX + 1 ) * iSquareSideLen;
        start.iY = ( pos.iY + 1 ) * iSquareSideLen;
        iBitmapGc->DrawLine( start, end );
        // right
        end.iX = ( pos.iX + 1 ) * iSquareSideLen;
        end.iY = pos.iY * iSquareSideLen;
        iBitmapGc->DrawLine( start, end );
        }
    }

void CScaTestAppView::DrawEdge( const TPoint& aPos, TRgb aColor )
    {
    iBitmapGc->SetPenColor( aColor );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    TPoint pos( aPos );
    TPoint start, end;
    // up
    start.iX = pos.iX * iSquareSideLen;
    start.iY = pos.iY * iSquareSideLen;
    end.iX = ( pos.iX + 1 ) * iSquareSideLen;
    end.iY = pos.iY * iSquareSideLen;
    iBitmapGc->DrawLine( start, end );
    // left
    end.iX = pos.iX * iSquareSideLen;
    end.iY = ( pos.iY + 1 ) * iSquareSideLen;
    iBitmapGc->DrawLine( start, end );
    // down
    start.iX = ( pos.iX + 1 ) * iSquareSideLen;
    start.iY = ( pos.iY + 1 ) * iSquareSideLen;
    iBitmapGc->DrawLine( start, end );
    // right
    end.iX = ( pos.iX + 1 ) * iSquareSideLen;
    end.iY = pos.iY * iSquareSideLen;
    iBitmapGc->DrawLine( start, end );
    }

void CScaTestAppView::ClearAllPath()
    {
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );

    for ( TInt i = 0; i < KMainMatrixWidth; i++ )
        for ( TInt j = 0; j < KMainMatrixHeight; j++ )
            {
            TPoint pos( i, j );
            TPoint start, end;
            // up
            start.iX = pos.iX * iSquareSideLen;
            start.iY = pos.iY * iSquareSideLen;
            end.iX = ( pos.iX + 1 ) * iSquareSideLen;
            end.iY = pos.iY * iSquareSideLen;
            iBitmapGc->DrawLine( start, end );
            // left
            end.iX = pos.iX * iSquareSideLen;
            end.iY = ( pos.iY + 1 ) * iSquareSideLen;
            iBitmapGc->DrawLine( start, end );
            // down
            start.iX = ( pos.iX + 1 ) * iSquareSideLen;
            start.iY = ( pos.iY + 1 ) * iSquareSideLen;
            iBitmapGc->DrawLine( start, end );
            // right
            end.iX = ( pos.iX + 1 ) * iSquareSideLen;
            end.iY = pos.iY * iSquareSideLen;
            iBitmapGc->DrawLine( start, end );
            }
    }

void CScaTestAppView::DrawScore( TInt aScore )
    {
    iBitmapGc->SetBrushColor( KRgbDarkCyan );
    iBitmapGc->SetPenStyle( CGraphicsContext::ENullPen );
    TInt fontHeight = iFont->HeightInPixels();   
    TRect rect( TPoint( iScorePos.iX, iScorePos.iY - fontHeight ), TSize( 100, fontHeight ) );
    iBitmapGc->DrawRect( rect );
    iBitmapGc->UseFont( iFont );
    _LIT( KTestText, "Score:" );
    TBuf<30> scoreBuf;
    scoreBuf.Append( KTestText );
    scoreBuf.AppendNum( aScore );
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetBrushColor( KRgbDarkCyan );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->DrawText( scoreBuf, iScorePos );
    iBitmapGc->DiscardFont();
    }

void CScaTestAppView::DrawBonus( TInt aBonus )
    {
    iBitmapGc->SetBrushColor( KRgbDarkCyan );
    iBitmapGc->SetPenStyle( CGraphicsContext::ENullPen );
    TInt fontHeight = iFont->HeightInPixels();   
    TRect rect( TPoint( iBonusPos.iX, iBonusPos.iY - fontHeight ), TSize( 100, fontHeight ) );
    iBitmapGc->DrawRect( rect );
    iBitmapGc->UseFont( iFont );
    _LIT( KTestText, "Bonus:" );
    TBuf<30> bonusBuf;
    bonusBuf.Append( KTestText );
    bonusBuf.AppendNum( aBonus );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    //iBitmapGc->DrawRect( TRect( iBonusPos, TSize( 100, 25 ) ) );
    iBitmapGc->DrawText( bonusBuf, iBonusPos );
    iBitmapGc->DiscardFont();
    }

void CScaTestAppView::DrawLevel( TInt aLevel )
    {
    iBitmapGc->SetBrushColor( KRgbDarkCyan );
    iBitmapGc->SetPenStyle( CGraphicsContext::ENullPen );
    TInt fontHeight = iFont->HeightInPixels();
    TRect rect( TPoint( iLevelPos.iX, iLevelPos.iY - fontHeight ), TSize( 100, fontHeight ) );
    iBitmapGc->DrawRect( rect );
    iBitmapGc->UseFont( iFont );
    _LIT( KTestText, "Level:" );
    TBuf<30> bonusBuf;
    bonusBuf.Append( KTestText );
    bonusBuf.AppendNum( aLevel );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->DrawText( bonusBuf, iLevelPos );
    iBitmapGc->DiscardFont();
    }
    
void CScaTestAppView::DrawFuncKey( TAquaticType aType, TInt aValue )
    {
    // Draw background
    iBitmapGc->SetBrushColor( KRgbGray );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    for ( TInt i = 0; i < 5; i++ )
        {
        iBitmapGc->DrawRect( TRect( TPoint( 150 + i * 10, 280 ), TSize( 10, 10 ) ) );
        }

    // Draw foreground
    SetEdgeColor( aType );
    for ( TInt j = 0; j < aValue; j++ )
        {
        iBitmapGc->DrawRect( TRect( TPoint( 150 + j * 10, 280 ), TSize( 10, 10 ) ) );
        }
    }

void CScaTestAppView::DrawBitmap()
    {
    _LIT( KMbmMenubarFileName, "Z:\\resource\\apps\\menubar.mbm" );
    CBmpUtils* utils = CBmpUtils::NewL( 
                KMbmMenubarFileName, 
                EMbmMenubarPause, 
                EMbmMenubarLastElement 
                );
    CleanupStack::PushL( utils );
    utils->SetSize( EMbmMenubarAbout, TSize( 40, 40 ) );
    CFbsBitmap* bitmap = utils->Bitmap( EMbmMenubarAbout );
    utils->SetSize( EMbmMenubarAbout_mask, TSize( 40, 40 ) );
    CFbsBitmap* mask = utils->Bitmap( EMbmMenubarAbout_mask );

    iBitmapGc->BitBltMasked( 
                TPoint( 0, 0 ),
                bitmap,
                TRect( TPoint( 0, 0 ), TSize( 40, 40 ) ),
                mask,
                ETrue 
                );

    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;
    }
