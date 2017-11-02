/* ====================================================================
 * File: FuncKeyPane.cpp
 * Created: 12/04/09
 * Modified: 12/04/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "FuncKeyPane.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"

// CONSTANTS
const TInt KFuncKeyFullValue = 5;
const TInt KFuncKeyEmptyValue = 0;
const TInt KMaxWidthParts = 16;
const TInt KMaxHeightParts = 4;
const TInt KBigSquarePartsNr = 4;
const TInt KSmallSquarePartsNr = 2;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CFuncKeyPane::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CFuncKeyPane* CFuncKeyPane::NewL( 
    CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CFuncKeyPane* self = new (ELeave) CFuncKeyPane( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::~CFuncKeyPane
// ----------------------------------------------------------------------------
//
EXPORT_C CFuncKeyPane::~CFuncKeyPane()
    {
    delete iLayer;
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::SetAndDraw
// ----------------------------------------------------------------------------
//
EXPORT_C void CFuncKeyPane::SetAndDraw( TAquaticType aType, TInt aValue )
    {
    iType = aType;
    iCurrentValue = aValue;
    DoDraw();
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::CurrentValue
// ----------------------------------------------------------------------------
//
EXPORT_C TAquaticType CFuncKeyPane::CurrentType() const
    {
    return iType;
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::CurrentValue
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CFuncKeyPane::CurrentValue() const
    {
    return iCurrentValue;
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::Clear
// ----------------------------------------------------------------------------
//
EXPORT_C void CFuncKeyPane::Clear()
    {
    iCurrentValue = KFuncKeyEmptyValue;
    iType = EAquaticNull;
    DoDraw();
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::IsFull
// ----------------------------------------------------------------------------
//
EXPORT_C TBool CFuncKeyPane::IsFull() const
    {
    return iCurrentValue == KFuncKeyFullValue ? ETrue : EFalse;
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::IsEmpty
// ----------------------------------------------------------------------------
//
EXPORT_C TBool CFuncKeyPane::IsEmpty() const
    {
    return iCurrentValue == KFuncKeyEmptyValue ? ETrue : EFalse;
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::SizeChanged
// ----------------------------------------------------------------------------
//
void CFuncKeyPane::SizeChanged()
    {
    TInt wm = Rect().Width() / KMaxWidthParts;
    TInt hm = Rect().Height() / KMaxHeightParts;   
    iSquareMargin = wm > hm ? hm : wm;
    iBigSquareSize.iWidth = iSquareMargin * KBigSquarePartsNr;
    iBigSquareSize.iHeight = iSquareMargin * KBigSquarePartsNr;
    iSmallSquareSize.iWidth = iSquareMargin * KSmallSquarePartsNr;
    iSmallSquareSize.iHeight = iSquareMargin * KSmallSquarePartsNr;
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::CFuncKeyPane
// ----------------------------------------------------------------------------
//
CFuncKeyPane::CFuncKeyPane( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager ),
    iType( EAquaticNull ),
    iCurrentValue( KFuncKeyEmptyValue )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::ConstructL
// ----------------------------------------------------------------------------
//
void CFuncKeyPane::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    iLayer = CGraphicsLayer::NewL( aRect, ECtrlForeground );
    iGraphicsManager.RegisterLayer( iLayer );
    
    DoDraw();

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::DoDraw
// ----------------------------------------------------------------------------
//
void CFuncKeyPane::DoDraw()
    {
    TPoint thePosition( Rect().iTl );
    // Draw small squares
    for ( TInt ix = 0;  ix < KFuncKeyFullValue - 1; ix++ )
        {
        
        if ( ix < iCurrentValue )
            {
            SelectColor( iType );
            iLayer->DrawRect( TRect( thePosition, iSmallSquareSize ) );
            }
        else
            {
            SelectColor( EAquaticNull );
            iLayer->DrawRect( TRect( thePosition, iSmallSquareSize ) );
            }
        
        thePosition.iX += ( iSmallSquareSize.iWidth + iSquareMargin );
        }

    // Draw big square
    if ( ! IsFull() )
        {
        SelectColor( EAquaticNull );
        }
    else
        {
        SelectColor( iType );
        }

    iLayer->DrawRect( TRect( thePosition, iBigSquareSize ) );
    }

// ----------------------------------------------------------------------------
// CFuncKeyPane::SelectColor
// ----------------------------------------------------------------------------
//
void CFuncKeyPane::SelectColor( TAquaticType aType )
    {
    switch ( aType )
        {
        case EBlueScallop:
            iLayer->SetColor( KRgbBlue );
            break;
        case EDarkBlueScallop:
            iLayer->SetColor( KRgbDarkBlue );
            break;
        case EGreenScallop:
            iLayer->SetColor( KRgbGreen );
            break;
        case EDarkGreenScallop:
            iLayer->SetColor( KRgbDarkGreen );
            break;
        case ERedScallop:
            iLayer->SetColor( KRgbRed );
            break;
        case EMulberryScallop:
            iLayer->SetColor( KRgbMagenta );
            break;
        case EOrangeScallop:
            iLayer->SetColor( KRgbCyan ); // Todo:
            break;
        case EYellowScallop:
            iLayer->SetColor( KRgbYellow );
            break;
        default:
            iLayer->SetColor( KRgbGray );
            break;
        }
    }

// End of File
