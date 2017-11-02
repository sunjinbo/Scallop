/* ====================================================================
 * File: Checkbox.cpp
 * Created: 12/05/09
 * Modified: 12/05/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <BmpUtils.h>
#include <checkbox.mbg>
#include "Checkbox.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"
#include "Icon.h"
#include "TextPane.h"
#include "CheckboxObserver.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KMbmCheckboxFileName, "Z:\\resource\\apps\\checkbox.mbm" );
#else
_LIT( KMbmCheckboxFileName, "\\resource\\apps\\checkbox.mbm" );
#endif // __WINS__

const TInt KMinIconWidth = 25;
const TInt KMinIconHeight = 25;
const TInt KCheckboxMargin = 5;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CCheckbox::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CCheckbox* CCheckbox::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CCheckbox* self = new (ELeave) CCheckbox( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CCheckbox::~CCheckbox
// ----------------------------------------------------------------------------
//
EXPORT_C CCheckbox::~CCheckbox()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CCheckbox::Checked
// ----------------------------------------------------------------------------
//
EXPORT_C TBool CCheckbox::Checked() const
    {
    return iCheck;
    }

// ----------------------------------------------------------------------------
// CCheckbox::SetObserver
// ----------------------------------------------------------------------------
//
EXPORT_C void CCheckbox::SetObserver( MCheckboxObserver& aObserver )
    {
    iObserver = &aObserver;
    }

// ----------------------------------------------------------------------------
// CCheckbox::SetCheck
// ----------------------------------------------------------------------------
//
EXPORT_C void CCheckbox::SetCheck( TBool aCheck )
    {
    iCheck = aCheck;
    if ( iCheck )
        {
        iCheckIcon->SetVisible( ETrue );
        iUncheckIcon->SetVisible( EFalse );
        }
    else
        {
        iCheckIcon->SetVisible( EFalse );
        iUncheckIcon->SetVisible( ETrue );
        }
    }


// ----------------------------------------------------------------------------
// CCheckbox::SetVisible
// ----------------------------------------------------------------------------
//
EXPORT_C void CCheckbox::SetVisible( TBool aVisible )
    {
    iCheckIcon->SetVisible( aVisible );
    iUncheckIcon->SetVisible( aVisible );
    iTextPane->SetVisible( aVisible );
    }

// ----------------------------------------------------------------------------
// CCheckbox::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
EXPORT_C void CCheckbox::ConstructFromResourceL( TResourceReader& aReader )
    {
    // size
    TRect theRect( Rect() );
    TSize iconSize;
    iconSize.iWidth = aReader.ReadInt32 ();
    iconSize.iHeight = aReader.ReadInt32 ();
    TRect iconRect( theRect.iTl, iconSize );
    iCheckIcon->ResizeL( iconRect );
    iUncheckIcon->ResizeL( iconRect );

    TSize textSize;
    textSize.iWidth = Rect().Width() 
        - iconSize.iWidth 
        - KCheckboxMargin;
    textSize.iHeight = Rect().Height();
    TRect textRect( TPoint( theRect.iBr.iX - textSize.iWidth, theRect.iTl.iY ), textSize );
    iTextPane->ResizeL( textRect );

    CBmpUtils* utils = CBmpUtils::NewL( 
            KMbmCheckboxFileName, 
            EMbmCheckboxCheck,
            EMbmCheckboxLastElement 
            );
    CleanupStack::PushL( utils );
    
    // uncheck bitmap
    TInt bitmapIx = aReader.ReadInt32 ();
    utils->SetSize( bitmapIx, iconSize );
    iUncheckIcon->SetBitmap( utils->Bitmap( bitmapIx ) );
    TInt maskIx = aReader.ReadInt32 ();
    utils->SetSize( maskIx, iconSize );
    iUncheckIcon->SetMask( utils->Bitmap( maskIx ) );

    // check bitmap
    bitmapIx = aReader.ReadInt32 ();
    utils->SetSize( bitmapIx, iconSize );
    iCheckIcon->SetBitmap( utils->Bitmap( bitmapIx ) );
    maskIx = aReader.ReadInt32 ();
    utils->SetSize( maskIx, iconSize );
    iCheckIcon->SetMask( utils->Bitmap( maskIx ) );
    
    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;
    
    // state
    SetCheck( (TBool)aReader.ReadInt32 () );

    // text
    TInt fontHeight = aReader.ReadInt32 ();
    iTextPane->SetFontHeight( fontHeight );

    TInt baseline = aReader.ReadInt32 ();
    iTextPane->SetTextBaseline( baseline );
    
    TRgb color = TRgb( aReader.ReadInt32 () );
    iTextPane->SetColor( color );
    
    CGraphicsContext::TTextAlign align =
        CGraphicsContext::TTextAlign( aReader.ReadInt32 () );
    iTextPane->SetTextAlign( align );
    
    HBufC* txt = aReader.ReadHBufCL();
    iTextPane->SetTextL( *txt );
    }

// ----------------------------------------------------------------------------
// CCheckbox::SizeChanged
// ----------------------------------------------------------------------------
//
void CCheckbox::SizeChanged()
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CCheckbox::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CCheckbox::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    switch( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Up:
            {
            SetCheck( !iCheck );
            if ( iObserver )
                {
                iObserver->CheckedL( iCheck );
                }
            }
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CCheckbox::CCheckbox
// ----------------------------------------------------------------------------
//
CCheckbox::CCheckbox( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CCheckbox::ConstructL
// ----------------------------------------------------------------------------
//
void CCheckbox::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );
    
    
    TRect theRect( aRect.iTl, TSize( KMinIconWidth, KMinIconHeight ) );
    InitComponentArrayL();
    iCheckIcon = CIcon::NewL( iGraphicsManager, theRect );
    iCheckIcon->SetContainerWindowL( *this );
    Components().AppendLC( iCheckIcon );
    CleanupStack::Pop( iCheckIcon );

    iUncheckIcon = CIcon::NewL( iGraphicsManager, theRect );
    iUncheckIcon->SetContainerWindowL( *this );
    Components().AppendLC( iUncheckIcon );
    CleanupStack::Pop( iUncheckIcon );

    iTextPane = CTextPane::NewL( iGraphicsManager, theRect );
    iTextPane->SetContainerWindowL( *this );
    Components().AppendLC( iTextPane );
    CleanupStack::Pop( iTextPane );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// End of File
