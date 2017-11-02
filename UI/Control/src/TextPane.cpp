/* ====================================================================
 * File: TextPane.cpp
 * Created: 12/05/09
 * Modified: 12/05/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include "TextPane.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"

// CONSTANTS
const TInt KDefaultLineNumber = 1;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CTextPane::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CTextPane* CTextPane::NewL( 
    CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CTextPane* self = new (ELeave) CTextPane( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CTextPane::~CTextPane
// ----------------------------------------------------------------------------
//
EXPORT_C CTextPane::~CTextPane()
    {
    delete iTextLayer;
    iTextArray.ResetAndDestroy();
    iTextArray.Close();
    }

// ----------------------------------------------------------------------------
// CTextPane::ResizeL
// ----------------------------------------------------------------------------
//
EXPORT_C void CTextPane::ResizeL( const TRect& aRect )
    {
    if ( iTextLayer )
        {
        iGraphicsManager.UnregisterLayer( iTextLayer );
        delete iTextLayer;
        iTextLayer = NULL;
        }
    SetRect( aRect );
    iTextLayer = CGraphicsLayer::NewL( aRect, ECtrlText );
    iGraphicsManager.RegisterLayer( iTextLayer );
    }

// ----------------------------------------------------------------------------
// CTextPane::SetFontHeight
// ----------------------------------------------------------------------------
//
EXPORT_C void CTextPane::SetFontHeight( TInt aFontHeightInTwips )
    {
    iFontHeightInTwips = aFontHeightInTwips;
    iTextLayer->SetFontHeight( aFontHeightInTwips );
    }

// ----------------------------------------------------------------------------
// CTextPane::SetTextBaseline
// ----------------------------------------------------------------------------
//
EXPORT_C void CTextPane::SetTextBaseline( TInt aTextBaseline )
    {
    iTextBaseline = aTextBaseline;
    }

// ----------------------------------------------------------------------------
// CTextPane::SetTextAlign
// ----------------------------------------------------------------------------
//
EXPORT_C void CTextPane::SetTextAlign( CGraphicsContext::TTextAlign aAlign )
    {
    iAlign = aAlign;
    iTextLayer->SetTextAlign( aAlign );
    }

// ----------------------------------------------------------------------------
// CTextPane::SetColor
// ----------------------------------------------------------------------------
//
EXPORT_C void CTextPane::SetColor( const TRgb& aColor )
    {
    iColor= aColor;
    iTextLayer->SetColor( iColor );
    }

// ----------------------------------------------------------------------------
// CTextPane::SetTextL
// ----------------------------------------------------------------------------
//
EXPORT_C void CTextPane::SetTextL( const TDesC& aText )
    {
    iTextLayer->Clear();
    iTextArray.ResetAndDestroy();
    AppendL( aText );
    SetAttributes();
    DoDraw();
    }

// ----------------------------------------------------------------------------
// CTextPane::SetVisible
// ----------------------------------------------------------------------------
//
EXPORT_C void CTextPane::SetVisible( TBool aVisible )
    {
    iTextLayer->SetVisible( aVisible );
    }

// ----------------------------------------------------------------------------
// CTextPane::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
EXPORT_C void CTextPane::ConstructFromResourceL( TResourceReader& aReader )
    {
    iLine = aReader.ReadInt32 ();
    iFontHeightInTwips = aReader.ReadInt32();
    iTextBaseline = aReader.ReadInt32();

    iAlign = (CGraphicsContext::TTextAlign)(aReader.ReadInt32 ());
    iColor = TRgb( aReader.ReadInt32() );

    HBufC* txt = aReader.ReadHBufCL();
    if ( txt )
        {
        SetTextL( *txt );
        }
    }

// ----------------------------------------------------------------------------
// CTextPane::SizeChanged
// ----------------------------------------------------------------------------
//
void CTextPane::SizeChanged()
    {
    BuildTextBox();
    }

// ----------------------------------------------------------------------------
// CTextPane::CTextPane
// ----------------------------------------------------------------------------
//
CTextPane::CTextPane( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager ), iLine( KDefaultLineNumber )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CTextPane::ConstructL
// ----------------------------------------------------------------------------
//
void CTextPane::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    iTextLayer = CGraphicsLayer::NewL( aRect, ECtrlText );
    iGraphicsManager.RegisterLayer( iTextLayer );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CTextPane::DoDraw
// ----------------------------------------------------------------------------
//
void CTextPane::DoDraw()
    {
    TPoint thePosition( Rect().iTl );
    for ( TInt i = 0; i < iLine; i++ )
        {
        if ( i < iTextArray.Count() )
            {
            HBufC* text = iTextArray[ i ];
            iTextLayer->DrawText( 
                    *text, 
                    TRect( thePosition, iTextBoxSize ), 
                    iTextBaseline 
                    );
            }
        thePosition.iY += iTextBoxSize.iHeight;
        }
    }

// ----------------------------------------------------------------------------
// CTextPane::SetAttributes
// ----------------------------------------------------------------------------
//
void CTextPane::SetAttributes()
    {
    BuildTextBox();

    iTextLayer->SetFontHeight( iFontHeightInTwips );
    iTextLayer->SetColor( iColor );
    iTextLayer->SetTextAlign( iAlign );
    }

// ----------------------------------------------------------------------------
// CTextPane::AppendL
// ----------------------------------------------------------------------------
//
void CTextPane::AppendL( const TDesC& aText )
    {
    TPtrC ptr( aText );
    const TChar KLf( '\n' );
    const TInt pos = aText.Locate( KLf );

    HBufC* txt( NULL );
    if ( pos != KErrNotFound )
        {
        ptr.Set( aText.Ptr(), pos );
        txt = HBufC::NewL( ptr.Length() );
        TPtr txtPtr( txt->Des() );
        txtPtr.Copy( ptr );
        iTextArray.Append( txt );
        }
    else
        {
        if ( aText.Length() != 0 )
            {
            txt = HBufC::NewL( aText.Length() );
            TPtr txtPtr( txt->Des() );
            txtPtr.Copy( aText );
            iTextArray.Append( txt );
            }
        }

    if ( pos != KErrNotFound )
        {
        ptr.Set( &aText.Ptr()[ pos + 1 ], aText.Length() - pos - 1 );

        AppendL( ptr ); // recursive call
        }
    }

// ----------------------------------------------------------------------------
// CTextPane::BuildTextBox
// ----------------------------------------------------------------------------
//
void CTextPane::BuildTextBox()
    {
    TRect theRect( Rect() );
    iTextBoxSize.iHeight = theRect.Height() / iLine;
    iTextBoxSize.iWidth = theRect.Width();
    }

// End of File
