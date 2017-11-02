/* ====================================================================
 * File: ProgressBar.cpp
 * Created: 12/02/09
 * Modified: 12/02/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include "ProgressBar.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"

// CONSTANTS
const TInt KProgressBarMinValue = 0;
const TInt KFixedMargin = 2;
const TInt KMinBarHeight = 25;
const TInt KMinBarWidth = 5;
const TInt KBorderBreadth = 2;
const TInt KErrBadSize = -8000;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CProgressBar::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CProgressBar* CProgressBar::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CProgressBar* self = new (ELeave) CProgressBar( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CProgressBar::~CProgressBar
// ----------------------------------------------------------------------------
//
EXPORT_C CProgressBar::~CProgressBar()
    {
    delete iLayer;
    }

// ----------------------------------------------------------------------------
// CProgressBar::IncrementAndDraw
// ----------------------------------------------------------------------------
//
EXPORT_C void CProgressBar::SetDirectionL( CProgressBar::TDirection aDirection )
    {
    iDirection = aDirection;
    
    TRect theRect( Rect() );
    TSize theSize( theRect.Size() );
    TSize minSize( MinimumSize() );
    if ( theSize.iWidth < minSize.iWidth 
        || theSize.iHeight < minSize.iHeight )
        {
        User::Leave( KErrBadSize );
        }
    switch( iDirection )
        {
        case EVertical:
            iBarSize.iWidth = theRect.Width() 
                - 2 * ( KBorderBreadth +  KFixedMargin ) - 1;
            iBarSize.iHeight = ( theRect.Height()
                - 2 * KBorderBreadth
                - ( iMaxValue + 1 ) * KFixedMargin )
                / iMaxValue;
            break;
        case EHorizontal:
            iBarSize.iHeight = theRect.Height() 
                - 2 * ( KBorderBreadth +  KFixedMargin );
            iBarSize.iWidth = ( theRect.Width()
                - 2 * KBorderBreadth
                - ( iMaxValue + 1 ) * KFixedMargin )
                / iMaxValue;
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CProgressBar::IncrementAndDraw
// ----------------------------------------------------------------------------
//
EXPORT_C void CProgressBar::IncrementAndDraw( TInt aInc )
    {
    if ( iCurrentValue + aInc > iMaxValue )
        {
        SetAndDraw( iMaxValue );
        }
    else
        {
        SetAndDraw( iCurrentValue + aInc );
        }
    }

// ----------------------------------------------------------------------------
// CProgressBar::DecrementAndDraw
// ----------------------------------------------------------------------------
//
EXPORT_C void CProgressBar::DecrementAndDraw( TInt aDec )
    {
    if ( iCurrentValue - aDec < KProgressBarMinValue )
        {
        SetAndDraw( KProgressBarMinValue );
        }
    else
        {
        SetAndDraw( iCurrentValue - aDec );
        }
    }

// ----------------------------------------------------------------------------
// CProgressBar::SetAndDraw
// ----------------------------------------------------------------------------
//
EXPORT_C void CProgressBar::SetAndDraw( TInt aValue )
    {
    if ( ( aValue <= iMaxValue ) 
        && ( aValue >= KProgressBarMinValue )  )
        {
        iCurrentValue = aValue;
        DrawBorder();
        DrawBars( iBorderColor, iMaxValue );
        DrawBars( iColor, iCurrentValue );
        }
    }

// ----------------------------------------------------------------------------
// CProgressBar::SetMaxValue
// ----------------------------------------------------------------------------
//
EXPORT_C void CProgressBar::SetMaxValue( TInt aMaxValue )
    {
    iMaxValue = aMaxValue;
    }

// ----------------------------------------------------------------------------
// CProgressBar::SetBorder
// ----------------------------------------------------------------------------
//
EXPORT_C void CProgressBar::SetBorder( TBool aBorder )
    {
    iBorder = aBorder;
    }

// ----------------------------------------------------------------------------
// CProgressBar::SetColor
// ----------------------------------------------------------------------------
//
EXPORT_C void CProgressBar::SetColor( const TRgb& aColor )
    {
    iColor = aColor;
    }

// ----------------------------------------------------------------------------
// CProgressBar::SetBorderColor
// ----------------------------------------------------------------------------
//
EXPORT_C void CProgressBar::SetBorderColor( const TRgb& aBorderColor )
    {
    iBorderColor = aBorderColor;
    }

// ----------------------------------------------------------------------------
// CProgressBar::CurrentValue
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CProgressBar::CurrentValue() const
    {
    return iCurrentValue;
    }

// ----------------------------------------------------------------------------
// CProgressBar::MaxValue
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CProgressBar::MaxValue() const
    {
    return iMaxValue;
    }

// ----------------------------------------------------------------------------
// CProgressBar::Border
// ----------------------------------------------------------------------------
//
EXPORT_C TBool CProgressBar::Border() const
    {
    return iBorder;
    }

// ----------------------------------------------------------------------------
// CProgressBar::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
EXPORT_C void CProgressBar::ConstructFromResourceL( TResourceReader& aReader )
    {
    iMaxValue = aReader.ReadInt32 ();
    iCurrentValue = aReader.ReadInt32 ();
    iCurrentValue = 2;
    SetDirectionL( CProgressBar::TDirection( aReader.ReadInt32 () ) );
    iBorder = TBool( aReader.ReadInt32 () );
    iColor = TRgb ( aReader.ReadInt32 () );
    iBorderColor = TRgb ( aReader.ReadInt32 () );
    SetAndDraw( iCurrentValue );
    }

// ----------------------------------------------------------------------------
// CProgressBar::SizeChanged
// ----------------------------------------------------------------------------
//
void CProgressBar::SizeChanged()
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CProgressBar::CProgressBar
// ----------------------------------------------------------------------------
//
CProgressBar::CProgressBar( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CProgressBar::ConstructL
// ----------------------------------------------------------------------------
//
void CProgressBar::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    iLayer = CGraphicsLayer::NewL( aRect, ECtrlForeground );
    iGraphicsManager.RegisterLayer( iLayer );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CProgressBar::MinimumSize
// ----------------------------------------------------------------------------
//
TSize CProgressBar::MinimumSize()
    {
    TSize theSize;
    switch( iDirection )
        {
        case EVertical:
            theSize.iHeight = iMaxValue * KMinBarWidth // bar
                + ( iMaxValue + 1 ) * KFixedMargin // margin
                + 2 * KBorderBreadth; // border

            iSize.iWidth = KMinBarHeight // bar
                + 2 * KBorderBreadth; // border
            break;

        case EHorizontal:
            theSize.iWidth = iMaxValue * KMinBarWidth // bar
                + ( iMaxValue + 1 ) * KFixedMargin // margin
                + 2 * KBorderBreadth; // border

            theSize.iHeight = KMinBarHeight // bar
                + 2 * KBorderBreadth; // border
            break;

        default: // Default
            break;
        }

    return theSize;
    }

// ----------------------------------------------------------------------------
// CProgressBar::DrawBorder
// ----------------------------------------------------------------------------
//
void CProgressBar::DrawBorder()
    {
    iLayer->Clear();
    // Todo:
    }

// ----------------------------------------------------------------------------
// CProgressBar::DrawBars
// ----------------------------------------------------------------------------
//
void CProgressBar::DrawBars( TRgb aColor, TInt aNumber )
    {
    TPoint thePosition;
    TRect theRect( TPoint(0,0), Size() );
    iLayer->SetColor( aColor );
    for ( TInt ix = 0; ix < aNumber; ix++ )
        {
        switch( iDirection )
            {
            case EVertical:
                {
                thePosition.iX = theRect.iTl.iX
                    + KBorderBreadth
                    + KFixedMargin;

                thePosition.iY = theRect.iBr.iY
                    - KBorderBreadth
                    - KFixedMargin
                    - iBarSize.iHeight
                    - ( iBarSize.iHeight + KFixedMargin ) * ix;
                }
                break;
            case EHorizontal:
                {
                thePosition.iX = theRect.iTl.iX 
                    + KBorderBreadth
                    + KFixedMargin
                    + ( iBarSize.iWidth + KFixedMargin ) * ix;

                thePosition.iY = theRect.iTl.iY
                    + KBorderBreadth
                    + KFixedMargin;
                }
                break;
            default:
                break;
            }
        TRect r = TRect( thePosition, iBarSize );
        iLayer->DrawRect( r );
        }
    }

// End of File
