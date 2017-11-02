/* ====================================================================
 * File: Scoreboard.cpp
 * Created: 11/25/09
 * Modified: 11/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <BmpUtils.h>
#include <scoreboard.mbg>
#include "Scoreboard.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KMbmScoreboardFileName, "Z:\\resource\\apps\\scoreboard.mbm" );
#else
_LIT( KMbmScoreboardFileName, "\\resource\\apps\\scoreboard.mbm" );
#endif // __WINS__

const TInt KMaxTextNumber = 32;
const TInt KIconMargin = 2;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScoreboard::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CScoreboard* CScoreboard::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CScoreboard* self = new (ELeave) CScoreboard( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CScoreboard::~CScoreboard
// ----------------------------------------------------------------------------
//
EXPORT_C CScoreboard::~CScoreboard()
    {
    delete iBackgroundLayer;
    delete iTextLayer;
    delete iText;
    }

// ----------------------------------------------------------------------------
// CScoreboard::SetIconSize
// ----------------------------------------------------------------------------
//
EXPORT_C void CScoreboard::SetIconSize( const TSize& aSize )
    {
    iIconSize = aSize;
    iIconPosition = Rect().iTl;
    }

// ----------------------------------------------------------------------------
// CScoreboard::SetFontHeight
// ----------------------------------------------------------------------------
//
EXPORT_C void CScoreboard::SetFontHeight( TInt aFontHeightInTwips )
    {
    iFontHeightInTwips = aFontHeightInTwips;
    iTextLayer->SetFontHeight( aFontHeightInTwips );
    }

// ----------------------------------------------------------------------------
// CScoreboard::SetBitmap
// ----------------------------------------------------------------------------
//
EXPORT_C void CScoreboard::SetBitmap( CFbsBitmap* aBitmap )
    {
    iBackgroundLayer->DrawBitmap( Rect(), aBitmap );
    }

// ----------------------------------------------------------------------------
// CScoreboard::SetMask
// ----------------------------------------------------------------------------
//
EXPORT_C void CScoreboard::SetMask( CFbsBitmap* aMask )
    {
    iBackgroundLayer->DrawMask( Rect(), aMask );
    }

// ----------------------------------------------------------------------------
// CScoreboard::SetValue
// ----------------------------------------------------------------------------
//
EXPORT_C void CScoreboard::SetValue( TInt aValue )
    {
    iValue = aValue;
    TBuf<KMaxTextNumber> buf;
    if ( iText )
        {
        buf.Copy( *iText );
        }

    buf.AppendNum( iValue );
    TRect theTextRect( Rect() );
    theTextRect.iTl.iX += ( iIconSize.iWidth + KIconMargin );
    iTextLayer->SetTextAlign( CGraphicsContext::ELeft );
    iTextLayer->DrawText( buf, theTextRect, iTextBaseline );
    }

// ----------------------------------------------------------------------------
// CScoreboard::SetValue
// ----------------------------------------------------------------------------
//
EXPORT_C void CScoreboard::AppendValue( TInt aIncValue )
    {
    iValue += aIncValue;
    TBuf<KMaxTextNumber> buf;
    if ( iText )
        {
        buf.Copy( *iText );
        }

    buf.AppendNum( iValue );
    TRect theTextRect( Rect() );
    theTextRect.iTl.iX += ( iIconSize.iWidth + KIconMargin );
    iTextLayer->SetTextAlign( CGraphicsContext::ELeft );
    iTextLayer->DrawText( buf, theTextRect, iTextBaseline );
    }

// ----------------------------------------------------------------------------
// CScoreboard::SetTextL
// ----------------------------------------------------------------------------
//
void CScoreboard::SetTextL( const TDesC& aText )
    {
    if ( iText )
        {
        delete iText;
        iText = NULL;
        }
    iText =  HBufC::NewL( aText.Length() );
    TPtr text( iText->Des() );
    text.Copy( aText );
    }

// ----------------------------------------------------------------------------
// CScoreboard::SetTextBaseline
// ----------------------------------------------------------------------------
//
EXPORT_C void CScoreboard::SetTextBaseline( TInt aTextBaseline )
    {
    iTextBaseline = aTextBaseline;
    }

// ----------------------------------------------------------------------------
// CScoreboard::SetColor
// ----------------------------------------------------------------------------
//
EXPORT_C void CScoreboard::SetColor( const TRgb& aColor )
    {
    iColor= aColor;
    iTextLayer->SetColor( iColor );
    }

// ----------------------------------------------------------------------------
// CScoreboard::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
EXPORT_C void CScoreboard::ConstructFromResourceL( TResourceReader& aReader )
    {
    iIconSize.iWidth = aReader.ReadInt32 ();
    iIconSize.iHeight = aReader.ReadInt32 ();
    SetIconSize( iIconSize );

    CBmpUtils* utils = CBmpUtils::NewL( 
        KMbmScoreboardFileName, 
        EMbmScoreboardStarfish, 
        EMbmScoreboardLastElement 
        );
    CleanupStack::PushL( utils );

    TInt bitmapIx = aReader.ReadInt32 ();
    utils->SetSize( bitmapIx, iIconSize );
    CFbsBitmap* bitmap = utils->Bitmap( bitmapIx );
    iBackgroundLayer->DrawBitmap( TRect( iIconPosition, iIconSize ), bitmap );
    TInt maskIx = aReader.ReadInt32 ();
    utils->SetSize( maskIx, iIconSize );
    CFbsBitmap* mask = utils->Bitmap( maskIx );
    iBackgroundLayer->DrawMask( TRect( iIconPosition, iIconSize ), mask );

    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;

    iFontHeightInTwips = aReader.ReadInt32();
    iTextLayer->SetFontHeight( iFontHeightInTwips );
    
    iTextBaseline = aReader.ReadInt32();

    iColor = TRgb( aReader.ReadInt32() );
    iTextLayer->SetColor( iColor );

    iValue = aReader.ReadInt32();

    HBufC* txt = aReader.ReadHBufCL();
    SetTextL( *txt );
    
    SetValue( iValue );
    }

// ----------------------------------------------------------------------------
// CScoreboard::Value
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CScoreboard::Value() const
    {
    return iValue;
    }

// ----------------------------------------------------------------------------
// CScoreboard::SizeChanged
// ----------------------------------------------------------------------------
//
void CScoreboard::SizeChanged()
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CScoreboard::CScoreboard
// ----------------------------------------------------------------------------
//
CScoreboard::CScoreboard( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CScoreboard::ConstructL
// ----------------------------------------------------------------------------
//
void CScoreboard::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    iBackgroundLayer = CGraphicsLayer::NewL( aRect, ECtrlBackground );
    iGraphicsManager.RegisterLayer( iBackgroundLayer );
    iTextLayer = CGraphicsLayer::NewL( aRect, ECtrlText );
    iGraphicsManager.RegisterLayer( iTextLayer );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// End of File
