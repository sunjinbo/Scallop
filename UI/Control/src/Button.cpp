/* ====================================================================
 * File: Button.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <BmpUtils.h>
#include <Btn.mbg>
#include "Button.h"
#include "ButtonObserver.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KMbmButtonFileName, "Z:\\resource\\apps\\btn.mbm" );
#else
_LIT( KMbmButtonFileName, "\\resource\\apps\\btn.mbm" );
#endif // __WINS__

const TInt KInvaildBitmapIndex = 0;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CButton::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CButton* CButton::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CButton* self = new (ELeave) CButton( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CButton::~CButton
// ----------------------------------------------------------------------------
//
EXPORT_C CButton::~CButton()
    {
    delete iBackgroundLayer;
    delete iTextLayer;
    delete iText;
    }

// ----------------------------------------------------------------------------
// CButton::Id
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CButton::Id() const
    {
    return iBtnId;
    }

// ----------------------------------------------------------------------------
// CButton::SetId
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetId( TInt aBtnId )
    {
    iBtnId = aBtnId;
    }

// ----------------------------------------------------------------------------
// CButton::SetFlag
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetFlag( TInt aFlag )
    {
    iFlag = aFlag;
    }

// ----------------------------------------------------------------------------
// CButton::SetIconAttribute
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetIconAttribute( const TSize& aSize, TAlign aAlign)
    {
    iIconSize = aSize;
    iAlign = aAlign;

    TRect rect( Rect() );

    TInt margin = rect.Height() - iIconSize.iHeight;
    margin = margin >= 0 ? margin : 0;
    margin /= 2;
    
    iIconPosition.iY = rect.iTl.iY + margin;

    switch ( iAlign )
        {
        case ELeft:
            iIconPosition.iX = rect.iBr.iX;
            break;
        case ECenter:
            margin = rect.Width() - iIconSize.iWidth;
            margin = margin >= 0 ? margin : 0;
            margin /= 2;
            iIconPosition.iX = rect.iTl.iX - margin;
            break;
        case ERight:
            iIconPosition.iX = rect.iBr.iX - iIconSize.iWidth;
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CButton::SetFontHeight
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetFontHeight( TInt aFontHeightInTwips )
    {
    iFontHeightInTwips = aFontHeightInTwips;
    iTextLayer->SetFontHeight( aFontHeightInTwips );
    }

// ----------------------------------------------------------------------------
// CButton::SetBitmap
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetBitmap( CFbsBitmap* aBitmap )
    {
    iBackgroundLayer->DrawBitmap( Rect(), aBitmap );
    }

// ----------------------------------------------------------------------------
// CButton::SetMask
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetMask( CFbsBitmap* aMask )
    {
    iBackgroundLayer->DrawMask( Rect(), aMask );
    }

// ----------------------------------------------------------------------------
// CButton::SetTextL
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetTextL( const TDesC& aText )
    {
    if ( iText )
        {
        delete iText;
        iText = NULL;
        }
    iText =  HBufC::NewL( aText.Length() );
    TPtr text( iText->Des() );
    text.Copy( aText );

    iTextLayer->Clear();
    iTextLayer->DrawText( *iText, Rect(), iTextBaseline );
    }

// ----------------------------------------------------------------------------
// CButton::SetTextAlign
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetTextAlign( CGraphicsContext::TTextAlign aAlign )
    {
    iTextLayer->SetTextAlign( aAlign );
    }

// ----------------------------------------------------------------------------
// CButton::SetTextBaseline
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetTextBaseline( TInt aTextBaseline )
    {
    iTextBaseline = aTextBaseline;
    }

// ----------------------------------------------------------------------------
// CButton::SetColor
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetColor( const TRgb& aColor )
    {
    iColor= aColor;
    iTextLayer->SetColor( iColor );
    }

// ----------------------------------------------------------------------------
// CButton::SetPressColor
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetPressColor( const TRgb& aPressColor )
    {
    iPressColor= aPressColor;
    }

// ----------------------------------------------------------------------------
// CButton::SetVisible
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetVisible( TBool aVisible )
    {
    iBackgroundLayer->SetVisible( aVisible );
    iTextLayer->SetVisible( aVisible );
    }

// ----------------------------------------------------------------------------
// CButton::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::ConstructFromResourceL( TResourceReader& aReader )
    {
    iBtnId = aReader.ReadInt32 ();
    iFlag = aReader.ReadInt32 ();
    iIconSize.iWidth = aReader.ReadInt32 ();
    iIconSize.iHeight = aReader.ReadInt32 ();
    iAlign = (TAlign)(aReader.ReadInt32 ());

    SetIconAttribute( iIconSize, iAlign );

    CBmpUtils* utils = CBmpUtils::NewL( 
        KMbmButtonFileName, 
        EMbmBtnMenu,
        EMbmBtnLastElement 
        );
    CleanupStack::PushL( utils );

    TInt bitmapIx = aReader.ReadInt32 ();
    if ( bitmapIx != KInvaildBitmapIndex )
        {
        utils->SetSize( bitmapIx, iIconSize );
        CFbsBitmap* bitmap = utils->Bitmap( bitmapIx );
        iBackgroundLayer->DrawBitmap( TRect( iIconPosition, iIconSize ), bitmap );
        }

    TInt maskIx = aReader.ReadInt32 ();
    if ( maskIx != KInvaildBitmapIndex )
        {
        utils->SetSize( maskIx, iIconSize );
        CFbsBitmap* mask = utils->Bitmap( maskIx );
        iBackgroundLayer->DrawMask( TRect( iIconPosition, iIconSize ), mask );
        }

    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;

    iFontHeightInTwips = aReader.ReadInt32();
    iTextLayer->SetFontHeight( iFontHeightInTwips );
    
    iTextBaseline = aReader.ReadInt32();

    iColor = TRgb( aReader.ReadInt32() );
    iTextLayer->SetColor( iColor );
    
    iPressColor = TRgb( aReader.ReadInt32() );
    HBufC* txt = aReader.ReadHBufCL();
    if ( txt )
        {
        SetTextL( *txt );
        }
    }

// ----------------------------------------------------------------------------
// CButton::SetObserver
// ----------------------------------------------------------------------------
//
EXPORT_C void CButton::SetObserver( MButtonObserver* aObserver )
    {
    iObserver = aObserver;
    }

// ----------------------------------------------------------------------------
// CButton::SizeChanged
// ----------------------------------------------------------------------------
//
void CButton::SizeChanged()
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CButton::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CButton::HandlePointerEventL( const TPointerEvent& aPointerEvent )
    {
    switch( aPointerEvent.iType )
        {
        case TPointerEvent::EButton1Down:
            {
            if ( iText )
                {
                iTextLayer->SetColor( iPressColor );
                iTextLayer->DrawText( *iText, Rect(), iTextBaseline );
                }
            }
            break;
        case TPointerEvent::EDrag:
        case TPointerEvent::EMove:
            break;
        case TPointerEvent::EButton1Up:
            {
            if ( iText )
                {
                iTextLayer->SetColor( iColor );
                iTextLayer->DrawText( *iText, Rect(), iTextBaseline );
                }

            if ( iObserver )
                {
                iObserver->HandleButtonEventL( this );
                }
            }
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CButton::CButton
// ----------------------------------------------------------------------------
//
CButton::CButton( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CButton::ConstructL
// ----------------------------------------------------------------------------
//
void CButton::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );
    iIconSize = aRect.Size();
    iAlign = ECenter;
    iBackgroundLayer = CGraphicsLayer::NewL( aRect, ECtrlBackground );
    iGraphicsManager.RegisterLayer( iBackgroundLayer );
    iTextLayer = CGraphicsLayer::NewL( aRect, ECtrlText );
    iGraphicsManager.RegisterLayer( iTextLayer );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// End of File
