/* ====================================================================
 * File: Matrix.cpp
 * Created: 11/07/09
 * Modified: 11/07/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include <eikenv.h>
#include <BmpUtils.h>
#include <matrix.mbg>
#include <EngineCommon.h>
#include "Matrix.h"
#include "MatrixTask.h"
#include "MatrixTaskScheduler.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"

// Enumerates
enum TOrientation
    {
    EEast = 0,
    ENorth,
    ESouth,
    EWest,
    ENorthwest,
    ENortheast,
    ESouthwest,
    ESoutheast,
    ECentral,
    EOrientationCount
    };

// CONSTANTS
#if defined( __WINS__ )
_LIT( KMbmMatrixFileName, "Z:\\resource\\apps\\matrix.mbm" );
#else
_LIT( KMbmMatrixFileName, "\\resource\\apps\\matrix.mbm" );
#endif // __WINS__

_LIT( KPlusCharacter, "+" );
_LIT( KSpaceCharacter, " " );

// Tips
const TInt KNoTips = 0;
const TInt KMaxTipsMoves = 5;
const TInt KTipsMigrationlength = 2;
const TInt KTipsDelayTimeout = 0;
const TInt KTipsFrequencyTimeout = 1000000;
const TInt KTipsWidth = 150;
const TInt KTipsHeight = 32;
const TInt KTipsTextBaseline = 16;
const TInt KTipsTextFontHeightInTwips = 80;

// Margin
const TInt KBubbleSmallestMargin = 4;
const TInt KBubbleSmallMargin = 3;
const TInt KBubbleMargin = 2;
const TInt KBubbleLargeMargin = 1;
const TInt KBubbleLargestMargin = 0;
const TInt KBubblePathMargin = 4;
const TInt KBubbleScallopMargin = 0;

// Bubble Timeout
const TInt KBubbleShockDelayTimeout = 0;
const TInt KBubbleShockFrequencyTimeout = 250000;
const TInt KBubbleShockTotalTimes = 15;
const TInt KBubbleZoomDelayTimeout = 0;
const TInt KBubbleZoomFrequencyTimeout = 3000000;


// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// TZoomrix::TZoom
// ----------------------------------------------------------------------------
//
TZoom::TZoom( TZoom::TZoomState aZoomState )
    : iZoomState( aZoomState )
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// TZoom::Next
// ----------------------------------------------------------------------------
//
void TZoom::Next()
    {
    switch ( iZoomState )
        {
        case ESmallestToSmall: // smallest
            iZoomState = ESmallToNormal;
            break;
        case ESmallToNormal: // small
            iZoomState = ENormalToLarge;
            break;
        case ENormalToLarge: // normal
            iZoomState = ELargeToLargest;
            break;
        case ELargeToLargest: // large
            iZoomState = ELargestToLarge;
            break;
        case ELargestToLarge: // largest
            iZoomState = ELargeToNormal;
            break;
        case ELargeToNormal: // large
            iZoomState = ENormalToSmall;
            break;
        case ENormalToSmall: // normal
            iZoomState = ESmallToSmallest;
            break;
        case ESmallToSmallest: // small
            iZoomState = ESmallestToSmall;
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CMatrix* CMatrix::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CMatrix* self = new (ELeave) CMatrix( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CMatrix::~CMatrix
// ----------------------------------------------------------------------------
//
EXPORT_C CMatrix::~CMatrix()
    {
    delete iBmpUtils;
    delete iPathLayer;
    delete iBubbleLayer;
    delete iAuqaticLayer;
    delete iEffectsLayer;
    delete iTipsLayer;
    delete iScheduler;

    if ( iBubblePeriodic )
        {
        iBubblePeriodic->Cancel();
        delete iBubblePeriodic;
        }

    if ( iTipsPeriodic )
        {
        iTipsPeriodic->Cancel();
        delete iTipsPeriodic;
        }

    iBubblesZoom.Close();
    }

// ----------------------------------------------------------------------------
// CMatrix::DrawAquatic
// ----------------------------------------------------------------------------
//
EXPORT_C void CMatrix::UpdateAquaticL( TAquaticAction aAction, const RArray<TAquaticData>& aAquatics )
    {
    ClearPath();

    CMatrixTask* task = CMatrixTask::NewL( *this, *iScheduler );
    task->Append( aAquatics );
    
    switch( aAction )
        {
        case EAquaticActionBorn:
            //task->SetType( EDarken );
            task->SetType( EDraw );
            break;
        case EAquaticActionMatured:
            //task->SetType( EDarken );
            task->SetType( EDraw );
            break;
        case EAquaticActionMoved:
            task->SetType( EMove );
            break;
        case EAquaticActionChanged:
            task->SetType( EDraw );
            break;
        case EAquaticActionReleased:
            //task->SetType( ELighten );
            task->SetType( ERemove );
            break;
        case EAquaticActionUpdated:
            //task->SetType( EDarken );
            task->SetType( EDraw );
            break;
        case EAquaticActionSelected:
            task->SetType( ESelect );
            break;
        case EAquaticActionUnselected:
            task->SetType( EUnselect );
            break;
        default:
            break;
        }

    iScheduler->AddTask( task );
    }

// ----------------------------------------------------------------------------
// CMatrix::ShowPath
// ----------------------------------------------------------------------------
//
EXPORT_C void CMatrix::ShowPath( const RArray<TPoint>& aPath )
    {
    for ( TInt i = 0; i < aPath.Count(); i++ )
        {
        RomanceBubble( aPath[i], KRgbYellow );
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::ShowTips
// ----------------------------------------------------------------------------
//
EXPORT_C void CMatrix::ShowTips( TInt aValue )
    {
    (void)aValue;
    /*
    
    if ( iTipsMoves != KNoTips )
        {
        iTipsBuffer.Append( KSpaceCharacter );
        }
    else
        {
        iTipsPos = Rect().Center();
        }
 
    iTipsBuffer.Append( KPlusCharacter );
    iTipsBuffer.AppendNum( aValue );
    iTipsMoves = KMaxTipsMoves;
    iTipsPeriodic->Cancel();
    iTipsPeriodic->Start(
                        KTipsDelayTimeout,
                        KTipsFrequencyTimeout,
                        TCallBack( TipsCallback, this ) );
    */
    }

// ----------------------------------------------------------------------------
// CMatrix::ClearPath
// ----------------------------------------------------------------------------
//
EXPORT_C void CMatrix::ClearPath()
    {
    iPathLayer->Clear();
    }

// ----------------------------------------------------------------------------
// CMatrix::SetObserver
// ----------------------------------------------------------------------------
//
EXPORT_C void CMatrix::SetObserver( MMatrixObserver* aObserver )
    {
    iObserver = aObserver;
    }

// ----------------------------------------------------------------------------
// CMatrix::DoTips
// ----------------------------------------------------------------------------
//
void CMatrix::DoTips()
    {
    if ( --iTipsMoves != KNoTips )
        {
        iTipsPos.iX += KTipsMigrationlength;
        iTipsPos.iY -= KTipsMigrationlength;
        iTipsLayer->DrawText( 
                iTipsBuffer, 
                TRect( iTipsPos, TSize( KTipsWidth, KTipsHeight ) ), 
                KTipsTextBaseline
                );
        }
    else
        {
        iTipsBuffer.Delete( 0,iTipsBuffer.Length() );
        iTipsLayer->Clear();
        iTipsPeriodic->Cancel();
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::IsShock
// ----------------------------------------------------------------------------
//
TBool CMatrix::IsShock() const
    {
    return iShock;
    }

// ----------------------------------------------------------------------------
// CMatrix::Shock
// ----------------------------------------------------------------------------
//
void CMatrix::Shock()
    {
    iBubbleShockTimes++;
    if ( iBubbleShockTimes < KBubbleShockTotalTimes  )
        {
        if ( iBubbleShockTimes % 2 )
            {
            DrawBubbles( ETrue );
            }
        else
            {
            DrawBubbles( EFalse );
            }
        }
    else // stop shock and then start zoom.
        {
        StopShock();
        DrawBubbles( EFalse );
        TRAP_IGNORE( StartZoomL() );
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::StartShock
// ----------------------------------------------------------------------------
//
void CMatrix::StartShockL()
    {
    StopShock();

    iBubblePeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iBubblePeriodic->Cancel();
    
    iShock = ETrue;
    iBubbleShockTimes  = 0;
    iBubblePeriodic->Start(
                        KBubbleShockDelayTimeout,
                        KBubbleShockFrequencyTimeout,
                        TCallBack( TimerCallback, this ) );
    }

// ----------------------------------------------------------------------------
// CMatrix::StopShock
// ----------------------------------------------------------------------------
//
void CMatrix::StopShock()
    {
    if ( iBubblePeriodic
        && iBubblePeriodic->IsActive() )
        {
        iBubblePeriodic->Cancel();
        delete iBubblePeriodic;
        iBubblePeriodic = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::Zoom
// ----------------------------------------------------------------------------
//
void CMatrix::Zoom()
    {
    for ( TInt i = 0; i < KMainMatrixWidth; i++ )
        for ( TInt j = 0; j < KMainMatrixHeight; j++ )
            {
            iBubblesZoom[ i * j ].Next();
            }
    DrawBubbles(); // update all of bubbles.
    }

// ----------------------------------------------------------------------------
// CMatrix::StartZoomL
// ----------------------------------------------------------------------------
//
void CMatrix::StartZoomL()
    {
    StopZoom();

    iBubblePeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iBubblePeriodic->Cancel();
    
    iShock = EFalse;

    SetupZoom();

    iBubblePeriodic->Start(
                        KBubbleZoomDelayTimeout,
                        KBubbleZoomFrequencyTimeout,
                        TCallBack( TimerCallback, this ) 
                        );

    }

// ----------------------------------------------------------------------------
// CMatrix::StopZoom
// ----------------------------------------------------------------------------
//
void CMatrix::StopZoom()
    {
    if ( iBubblePeriodic
        && iBubblePeriodic->IsActive() )
        {
        iShock = EFalse;
        iBubblePeriodic->Cancel();
        delete iBubblePeriodic;
        iBubblePeriodic = NULL;
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::SizeChanged
// ----------------------------------------------------------------------------
//
void CMatrix::SizeChanged()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CMatrix::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CMatrix::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    if ( !iScheduler->AllTasksCompleted() )
        return;
    
    TInt w = ( aPointerEvent.iPosition.iX -  Rect().iTl.iX ) / iBubbleSize.iWidth;
    TInt h = ( aPointerEvent.iPosition.iY -  Rect().iTl.iY ) / iBubbleSize.iHeight;

    if ( aPointerEvent.iType == TPointerEvent::EButton1Down )
        {
        iDrag = 0;
        iDragPos = TPoint( -1, -1 );

        if ( w < KMainMatrixWidth && h < KMainMatrixHeight )
            {
            iObserver->ClickL( w, h );
            }
        }
    
    if ( aPointerEvent.iType == TPointerEvent::EDrag )
        {
        if ( w < KMainMatrixWidth && h < KMainMatrixHeight )
            {
            if ( iDragPos != TPoint( w, h ) )
                {
                iDragPos = TPoint( w, h );
                iDrag++;
                ClearPath();
                iObserver->DragL( w, h );
                }
            }
        }

    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        if ( iDrag > 0 )
            {
            ClearPath();
            if ( w < KMainMatrixWidth && h < KMainMatrixHeight )
                {
                iObserver->ClickL( w, h );
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::CMatrix
// ----------------------------------------------------------------------------
//
CMatrix::CMatrix( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager ), iDrag( 0 )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CMatrix::ConstructL
// ----------------------------------------------------------------------------
//
void CMatrix::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();
    
    // Sets rect
    SetRect( aRect );
    CalcBubbleSize();

    iBmpUtils = CBmpUtils::NewL( 
                KMbmMatrixFileName,
                EMbmMatrixBubble,
                EMbmMatrixLastElement );

    TSize theSize(  iBubbleSize );
    // smallest bubble
    theSize = iBubbleSize;
    theSize.iWidth -= KBubbleSmallestMargin;
    theSize.iHeight -= KBubbleSmallestMargin;
    iBmpUtils->SetSize( EMbmMatrixSmallestbubble, theSize );
    iBmpUtils->SetSize( EMbmMatrixSmallestbubble_mask, theSize );
    // small bubble
    theSize = iBubbleSize;
    theSize.iWidth -= KBubbleSmallMargin;
    theSize.iHeight -= KBubbleSmallMargin;
    iBmpUtils->SetSize( EMbmMatrixSmallbubble, theSize );
    iBmpUtils->SetSize( EMbmMatrixSmallbubble_mask, theSize );
    // normal bubble
    theSize = iBubbleSize;
    theSize.iWidth -= KBubbleMargin;
    theSize.iHeight -= KBubbleMargin;
    iBmpUtils->SetSize( EMbmMatrixBubble, theSize );
    iBmpUtils->SetSize( EMbmMatrixBubble_mask, theSize );
    // large bubble
    theSize = iBubbleSize;
    theSize.iWidth -= KBubbleLargeMargin;
    theSize.iHeight -= KBubbleLargeMargin;
    iBmpUtils->SetSize( EMbmMatrixLargebubble, theSize );
    iBmpUtils->SetSize( EMbmMatrixLargebubble_mask, theSize );
    // largest bubble
    theSize = iBubbleSize;
    theSize.iWidth -= KBubbleLargestMargin;
    theSize.iHeight -= KBubbleLargestMargin;
    iBmpUtils->SetSize( EMbmMatrixLargestbubble, theSize );
    iBmpUtils->SetSize( EMbmMatrixLargestbubble_mask, theSize );

    // scallop
    theSize = iBubbleSize;
    theSize.iWidth -= KBubbleScallopMargin;
    theSize.iHeight -= KBubbleScallopMargin;
    for ( TInt ix = EMbmMatrixBluescallop_matured; ix < EMbmMatrixLastElement; ++ix )
        {
        iBmpUtils->SetSize( ix, theSize );
        }

    // layer
    iPathLayer = CGraphicsLayer::NewL( aRect, ECtrlBackground );
    iGraphicsManager.RegisterLayer( iPathLayer );
    iBubbleLayer = CGraphicsLayer::NewL( aRect, ECtrlForeground );
    iGraphicsManager.RegisterLayer( iBubbleLayer );
    iAuqaticLayer = CGraphicsLayer::NewL( aRect, ECtrlEffects1 );
    iGraphicsManager.RegisterLayer( iAuqaticLayer );
    iEffectsLayer = CGraphicsLayer::NewL( aRect, ECtrlEffects2 );
    iGraphicsManager.RegisterLayer( iEffectsLayer );
    
    /*
    iTipsLayer = CGraphicsLayer::NewL( aRect, ECtrlText );
    iGraphicsManager.RegisterLayer( iTipsLayer );
    iTipsLayer->SetFontHeight( KTipsTextFontHeightInTwips );
    iTipsLayer->SetColor( KRgbRed );
    */
    
    iScheduler = CMatrixTaskScheduler::NewL();

    StartZoomL(); // start zoom timer.
    
    /*
    iTipsPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iTipsPeriodic->Cancel();
    */
    
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CMatrix::DrawBubbles
// ----------------------------------------------------------------------------
//
void CMatrix::DrawBubbles( TBool aShock )
    {
    iBubbleLayer->Clear();

    TRect rect( Rect() );
    for ( TInt i = 0; i < KMainMatrixWidth; i++ )
        for ( TInt j = 0; j < KMainMatrixHeight; j++ )
            {
            TPoint theBubblePosition;
            theBubblePosition.iX = iBubbleSize.iWidth * i + rect.iTl.iX;
            theBubblePosition.iY = iBubbleSize.iHeight * j + rect.iTl.iY;

            TRect theRect( theBubblePosition, iBubbleSize );
            TInt bitmapIx(0), maskIx(0);
            switch( iBubblesZoom[ i * j ].iZoomState )
                {
                case TZoom::ESmallestToSmall: // smallest
                    theRect.Shrink( KBubbleSmallestMargin, KBubbleSmallestMargin );
                    bitmapIx = EMbmMatrixSmallestbubble;
                    maskIx = EMbmMatrixSmallestbubble_mask;
                    break;
                case TZoom::ESmallToNormal: // fall through
                case TZoom::ESmallToSmallest: // samll
                    theRect.Shrink( KBubbleSmallMargin, KBubbleSmallMargin );
                    bitmapIx = EMbmMatrixSmallbubble;
                    maskIx = EMbmMatrixSmallbubble_mask;
                    break;
                case TZoom::ENormalToLarge: // fall through
                case TZoom::ENormalToSmall: // normal
                    theRect.Shrink( KBubbleMargin, KBubbleMargin );
                    bitmapIx = EMbmMatrixBubble;
                    maskIx = EMbmMatrixBubble_mask;
                    break;
                case TZoom::ELargeToLargest: // fall through
                case TZoom::ELargeToNormal: // large
                    theRect.Shrink( KBubbleLargeMargin, KBubbleLargeMargin );
                    bitmapIx = EMbmMatrixLargebubble;
                    maskIx = EMbmMatrixLargebubble_mask;
                    break;
                case TZoom::ELargestToLarge: // largest
                    theRect.Shrink( KBubbleLargestMargin, KBubbleLargestMargin );
                    bitmapIx = EMbmMatrixLargestbubble;
                    maskIx = EMbmMatrixLargestbubble_mask;
                    break;
                default:
                    break;
                }

            if ( aShock )
                {
                ShockRect( theRect );
                }

            iBubbleLayer->DrawBitmap( 
                        theRect, 
                        iBmpUtils->Bitmap( bitmapIx ) 
                        );
            iBubbleLayer->DrawMask( 
                        theRect,
                        iBmpUtils->Bitmap( maskIx ) 
                        );
            }

    }

// ----------------------------------------------------------------------------
// CMatrix::CalcBubbleSize
// ----------------------------------------------------------------------------
//
void CMatrix::CalcBubbleSize()
    {
    TRect rect( Rect() );
    TInt widthLength = rect.Width() / KMainMatrixWidth;
    TInt heightLength = rect.Width() / KMainMatrixHeight;
    TInt bubbleLength = widthLength >= heightLength ? heightLength : widthLength;
    iBubbleSize.iWidth = bubbleLength;
    iBubbleSize.iHeight = bubbleLength;
    }

// ----------------------------------------------------------------------------
// CMatrix::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CMatrix::TimerCallback( TAny* aPtr )
    {
    CMatrix* self = static_cast<CMatrix*> ( aPtr );
    if ( self->IsShock() )
        {
        self->Shock();
        }
    else // zoom
        {
        self->Zoom();
        }
    return 0;
    }

// ----------------------------------------------------------------------------
// CMatrix::TipsCallback
// ----------------------------------------------------------------------------
//
TInt CMatrix::TipsCallback( TAny* aPtr )
    {
    CMatrix* self = static_cast<CMatrix*> ( aPtr );
    self->DoTips();
    return 0;
    }

// ----------------------------------------------------------------------------
// CMatrix::Rand
// ----------------------------------------------------------------------------
//
TInt CMatrix::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// ----------------------------------------------------------------------------
// CMatrix::ShockRect
// ----------------------------------------------------------------------------
//
void CMatrix::ShockRect( TRect& aRect )
    {
    TInt dx(0), dy(0);
    switch( Rand( EOrientationCount ) )
        {
        case EEast:
            dx += 1;
            break;
        case ENorth:
            dy -= 1;
            break;
        case ESouth:
            dy += 1;
            break;
        case EWest:
            dx -= 1;
            break;
        case ENorthwest:
            dx -= 1;
            dy -= 1;
            break;
        case ENortheast:
            dx -= 1;
            dy += 1;
            break;
        case ESouthwest:
            dx += 1;
            dy -= 1;
            break;
        case ESoutheast:
            dx += 1;
            dy += 1;
            break;
        case ECentral:
            break;
        default:
            break;
        }
    aRect.Move( dx, dy );
    }

// ----------------------------------------------------------------------------
// CMatrix::SetupZoom
// ----------------------------------------------------------------------------
//
void CMatrix::SetupZoom()
    {
    iBubblesZoom.Reset();
    for ( TInt i = 0; i < KMainMatrixWidth; i++ )
        for ( TInt j = 0; j < KMainMatrixHeight; j++ )
            {
            TInt theZoomState = Rand( TZoom::EZoomStateCount );
            TZoom zoom( (TZoom::TZoomState)theZoomState );
            iBubblesZoom.Append( zoom );
            }
    }

// ----------------------------------------------------------------------------
// CMatrix::RomanceBubble
// ----------------------------------------------------------------------------
//
void CMatrix::RomanceBubble( const TPoint& aBubble, TRgb aColor )
    {
    TRect rect( Rect() );

    TPoint theBubblePosition;
    theBubblePosition.iX = iBubbleSize.iWidth * aBubble.iX;
    theBubblePosition.iY = iBubbleSize.iHeight * aBubble.iY;

    TRect theRect( theBubblePosition, iBubbleSize );
    theRect.Shrink( KBubblePathMargin, KBubblePathMargin );

    iPathLayer->SetColor( aColor );
    iPathLayer->DrawRect( theRect );
    }

// End of File
