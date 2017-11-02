/* ====================================================================
 * File: MenuBar.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <AknUtils.h>
#include <barsread.h>
#include "MenuBar.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"
#include "Button.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CMenuBar::NewL
// ----------------------------------------------------------------------------
//
CMenuBar* CMenuBar::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CMenuBar* self = new (ELeave) CMenuBar( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CMenuBar::~CMenuBar
// ----------------------------------------------------------------------------
//
CMenuBar::~CMenuBar()
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CMenuBar::ConstructBtn1FromResourceL
// ----------------------------------------------------------------------------
//
void CMenuBar::ConstructBtn1FromResourceL( TResourceReader& aReader )
    {
    ConstructFromResourceL( aReader, *iBtn1 );
    }

// ----------------------------------------------------------------------------
// CMenuBar::ConstructBtn2FromResourceL
// ----------------------------------------------------------------------------
//
void CMenuBar::ConstructBtn2FromResourceL( TResourceReader& aReader )
    {
    ConstructFromResourceL( aReader, *iBtn2 );
    }

// ----------------------------------------------------------------------------
// CMenuBar::SetObserver
// ----------------------------------------------------------------------------
//
void CMenuBar::SetObserver( MButtonObserver* aObserver )
    {
    iObserver = aObserver;

    iBtn1->SetObserver( aObserver );
    iBtn2->SetObserver( aObserver );
    }

// ----------------------------------------------------------------------------
// CMenuBar::HandleButtonEventL
// ----------------------------------------------------------------------------
//
void CMenuBar::HandleButtonEventL( const CButton* aBtn )
    {
    if ( iObserver )
        {
        iObserver->HandleButtonEventL( aBtn );
        }
    }

// ----------------------------------------------------------------------------
// CMenuBar::SizeChanged
// ----------------------------------------------------------------------------
//
void CMenuBar::SizeChanged()
    { // No implementation required
    }

// ----------------------------------------------------------------------------
// CMenuBar::CMenuBar
// ----------------------------------------------------------------------------
//
CMenuBar::CMenuBar( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CMenuBar::ConstructL
// ----------------------------------------------------------------------------
//
void CMenuBar::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );
    
    // Layout menubar
    LayoutMenuBar();

    InitComponentArrayL();

    iBtn1 = CButton::NewL( iGraphicsManager, iBtn1Rect );
    iBtn1->SetObserver( this );
    iBtn1->SetContainerWindowL( *this );
    Components().AppendLC( iBtn1 );
    CleanupStack::Pop( iBtn1 );

    iBtn2 = CButton::NewL( iGraphicsManager, iBtn2Rect );
    iBtn2->SetObserver( this );
    iBtn2->SetContainerWindowL( *this );
    Components().AppendLC( iBtn2 );
    CleanupStack::Pop( iBtn2 );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CMenuBar::LayoutMenuBar
// ----------------------------------------------------------------------------
//
void CMenuBar::LayoutMenuBar()
    {
    switch ( AknLayoutUtils::CbaLocation() )
        {
        case AknLayoutUtils::EAknCbaLocationBottom: // Landscape and Portrait
            {
            TPoint tl( iPosition );
            TInt width( iSize.iWidth / 3 );
            iBtn1Rect.SetRect( tl, TSize( width, iSize.iHeight ) );
            tl.iX += ( width * 2 );
            iBtn2Rect.SetRect( tl, TSize( width, iSize.iHeight ) );
            }
            break;
        case AknLayoutUtils::EAknCbaLocationRight: // Only Landscape
            {
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPaneBottom, iBtn1Rect );
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPaneTop, iBtn2Rect );
            }
            break;
        case AknLayoutUtils::EAknCbaLocationLeft: // Only landscape
            {
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPaneBottom, iBtn2Rect );
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPaneTop, iBtn1Rect );
            }
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CMenuBar::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
void CMenuBar::ConstructFromResourceL( TResourceReader& aReader, CButton& aBtn )
    {
    TSize size( aBtn.Size() );

    TInt id = aReader.ReadInt32 ();
    aBtn.SetId( id );
    TInt flag = aReader.ReadInt32 ();
    aBtn.SetFlag( flag );
    
    TInt width = aReader.ReadInt32 ();
    TInt height = aReader.ReadInt32 ();
    TAlign align = (TAlign)(aReader.ReadInt32 ());
    aBtn.SetIconAttribute( TSize( width, height ), align );

    TInt bmpIx = aReader.ReadInt32 ();
    TInt maskIx = aReader.ReadInt32 ();

    TInt fontHeightInTwips = aReader.ReadInt32();
    aBtn.SetFontHeight( fontHeightInTwips );

    TInt textBaseline = aReader.ReadInt32();
    aBtn.SetTextBaseline( textBaseline );
    
    TRgb color = TRgb( aReader.ReadInt32() );
    aBtn.SetColor( color );

    TRgb pressColor = TRgb( aReader.ReadInt32() );
    aBtn.SetPressColor( pressColor );

    HBufC* txt = aReader.ReadHBufCL();
    if ( txt )
        {
        aBtn.SetTextL( *txt );
        }
    }

// End of File
