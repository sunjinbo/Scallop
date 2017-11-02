/* ====================================================================
 * File: GraphicsLayer.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <fbs.h>
#include <eikenv.h>
#include <bitdev.h>
#include "GraphicsLayer.h"

// CONSTANTS
const TInt KDefaultFontHeightInTwips = 100;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CGraphicsLayer::NewL
// ----------------------------------------------------------------------------
//
CGraphicsLayer* CGraphicsLayer::NewL( const TRect& aRect, TLayerId aLayerId )
    {
    CGraphicsLayer* self = new (ELeave) CGraphicsLayer( aRect, aLayerId );
    CleanupStack::PushL (self );
    self->ConstructL ();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::~CGraphicsLayer
// ----------------------------------------------------------------------------
//
CGraphicsLayer::~CGraphicsLayer()
    {
    ReleaseBmpBuffer();
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::LayerId
// ----------------------------------------------------------------------------
//
TLayerId CGraphicsLayer::LayerId() const
    {
    return iLayerId;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::DrawBitmap
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::DrawBitmap( const TRect& aDestRect, const CFbsBitmap* aSource )
    {
    TPoint tl;
    tl.iX = aDestRect.iTl.iX - iRect.iTl.iX;
    tl.iY = aDestRect.iTl.iY - iRect.iTl.iY;
    TRect rect( tl, aDestRect.Size() );
    iBitmapGc->DrawBitmap( rect, aSource );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::DrawBitmap
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::DrawBitmap( const TPoint& aTopLeft, const CFbsBitmap* aSource )
    {
    iBitmapGc->DrawBitmap( aTopLeft, aSource );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::DrawMask
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::DrawMask( const TRect& aDestRect, const CFbsBitmap* aSource )
    {
    TPoint tl;
    tl.iX = aDestRect.iTl.iX - iRect.iTl.iX;
    tl.iY = aDestRect.iTl.iY - iRect.iTl.iY;
    TRect rect( tl, aDestRect.Size() );
    iMaskGc->DrawBitmap( rect, aSource );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::DrawMask
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::DrawMask( const TPoint& aTopLeft, const CFbsBitmap* aSource )
    {
    iMaskGc->DrawBitmap( aTopLeft, aSource );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::DrawText
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::DrawText( const TDesC& aText, const TRect& aBox, TInt aBaseline )
    {
    TPoint thePosition( aBox.iTl );
    thePosition -= iRect.iTl;
    TRect rect( thePosition, aBox.Size() );
    
    iBitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    iBitmapGc->SetBrushColor( iColor );
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetPenColor( iColor );
    iBitmapGc->UseFont( iFont );
    iBitmapGc->DrawText( aText, rect, aBaseline, iAlign );
    iBitmapGc->DiscardFont();

    iMaskGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    iMaskGc->SetBrushColor( KRgbBlack );
    iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iMaskGc->SetPenColor( KRgbBlack );
    iMaskGc->UseFont( iFont );
    iMaskGc->DrawText( aText, rect, aBaseline, iAlign );
    iMaskGc->DiscardFont();
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::DrawRect
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::DrawRect( const TRect& aRect )
    {
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetPenColor( iColor );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetBrushColor( iColor );
    iBitmapGc->DrawRect( aRect );

    iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iMaskGc->SetPenColor( KRgbBlack );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iMaskGc->SetBrushColor( KRgbBlack );
    iMaskGc->DrawRect( aRect );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::DrawEllipse
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::DrawEllipse( const TRect& aRect )
    {
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetBrushColor( iColor );
    iBitmapGc->DrawEllipse( aRect );
    iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iMaskGc->SetBrushColor( KRgbBlack );
    iMaskGc->DrawEllipse( aRect );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::DrawLine
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::DrawLine( const TPoint& aStart, const TPoint& aEnd )
    {
    
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    iBitmapGc->SetBrushColor( iColor );
    iBitmapGc->DrawLine( aStart, aEnd );

    iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    iMaskGc->SetBrushColor( KRgbBlack );
    iMaskGc->DrawLine( aStart, aEnd );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::Clear
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::Clear()
    {
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetPenColor( KRgbWhite );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetBrushColor( KRgbWhite );
    iBitmapGc->Clear( TRect( TPoint( 0,0 ), iRect.Size() ) );
    
    iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iMaskGc->SetPenColor( KRgbWhite );
    iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iMaskGc->SetBrushColor( KRgbWhite );
    iMaskGc->Clear( TRect( TPoint( 0,0 ), iRect.Size() ) );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::Clear
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::Clear( const TRect& aRect )
    {
    /*
    TPoint thePosition( aRect.iTl );
    thePosition -= iRect.iTl;
    TRect rect( thePosition, aRect.Size() );
    */
    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetPenColor( KRgbWhite );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetBrushColor( KRgbWhite );
    iBitmapGc->Clear( aRect );
    
    iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iMaskGc->SetPenColor( KRgbWhite );
    iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iMaskGc->SetBrushColor( KRgbWhite );
    iMaskGc->Clear( aRect );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::SetTransparency
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::SetTransparency( TInt aTransparency )
    {
    iTransparency = aTransparency;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::Bitmap
// ----------------------------------------------------------------------------
//
CFbsBitmap* CGraphicsLayer::Bitmap()
    {
    return iBitmap;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::Mask
// ----------------------------------------------------------------------------
//
CFbsBitmap* CGraphicsLayer::Mask()
    {
    return iMask;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::Rect
// ----------------------------------------------------------------------------
//
const TRect& CGraphicsLayer::Rect() const
    {
    return iRect;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::SetTextColor
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::SetColor( const TRgb& aColor )
    {
    iColor = aColor;
    iBitmapGc->SetBrushColor( iColor );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::BitBltMasked
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::BitBltMasked( const TPoint& aPoint, 
                                const CFbsBitmap* aBitmap,
                                const TRect& aSourceRect, 
                                const CFbsBitmap* aMaskBitmap, 
                                TBool aInvertMask )
    {
    iBitmapGc->SetPenStyle( CGraphicsContext::ENullPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    iBitmapGc->BitBltMasked( 
                aPoint,
                aBitmap,
                aSourceRect,
                aMaskBitmap,
                aInvertMask 
                );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::SetTextAlign
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::SetTextAlign( CGraphicsContext::TTextAlign aAlign )
    {
    iAlign = aAlign;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::SetVisible
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::SetVisible( TBool aVisible )
    {
    iVisible = aVisible;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::Visible
// ----------------------------------------------------------------------------
//
TBool CGraphicsLayer::Visible() const
    {
    return iVisible;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::SetFontHeightInTwips
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::SetFontHeight( TInt aFontHeightInTwips )
    {
    CEikonEnv* eikonEnv( CEikonEnv::Static() );
    TFontSpec fontSpec( eikonEnv->LegendFont()->FontSpecInTwips() );
#ifdef __WINS__
    fontSpec.iHeight = aFontHeightInTwips * 2;
#else
    fontSpec.iHeight = aFontHeightInTwips * 2;
#endif // __WINS__
    fontSpec.iFontStyle.SetBitmapType( EMonochromeGlyphBitmap );
    User::LeaveIfError( eikonEnv->ScreenDevice()->GetNearestFontInTwips( iFont, fontSpec ) );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::Compare
// ----------------------------------------------------------------------------
//
TInt CGraphicsLayer::Compare( const CGraphicsLayer& aFirst, const CGraphicsLayer& aSecond )
    {
     if ( aFirst.LayerId() > aSecond.LayerId() )
      return 1; 
     if ( aFirst.LayerId() < aSecond.LayerId() )
      return -1;
    return 0;
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::CGraphicsLayer
// ----------------------------------------------------------------------------
//
CGraphicsLayer::CGraphicsLayer( const TRect& aRect, TLayerId aLayerId )
    : iRect( aRect ),
    iLayerId( aLayerId ),
    iColor( KRgbBlack ),
    iAlign( CGraphicsContext::ECenter ),
    iVisible( ETrue )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::ConstructL
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::ConstructL()
    {
    SetFontHeight( KDefaultFontHeightInTwips );
    CreateBmpBufferL();
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::CreateBmpBufferL
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::CreateBmpBufferL()
    {
    ReleaseBmpBuffer();

    // Create double buffer bitmap
    iBitmap = new (ELeave) CFbsBitmap;
    User::LeaveIfError( iBitmap->Create( iRect.Size(), EColor16MU ) );

    // Create double buffer graphics context
    iBitmapDevice = CFbsBitmapDevice::NewL( iBitmap );
    User::LeaveIfError( iBitmapDevice->CreateContext( iBitmapGc ) );

    iBitmapGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iBitmapGc->SetPenColor( KRgbWhite );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBitmapGc->SetBrushColor( KRgbWhite );
    iBitmapGc->DrawRect( TRect( TPoint( 0,0 ), iRect.Size() ) );
    iBitmapGc->SetPenStyle( CGraphicsContext::ENullPen );
    iBitmapGc->SetBrushStyle( CGraphicsContext::ENullBrush );

    // Create double buffer mask
    iMask = new (ELeave) CFbsBitmap;
    User::LeaveIfError( iMask->Create( iRect.Size(), EColor16MU ) );

    // Create double buffer graphics context
    iMaskDevice = CFbsBitmapDevice::NewL( iMask );
    User::LeaveIfError( iMaskDevice->CreateContext( iMaskGc ) );

    iMaskGc->SetPenStyle( CGraphicsContext::ESolidPen );
    iMaskGc->SetPenColor( KRgbWhite );
    iMaskGc->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iMaskGc->SetBrushColor( KRgbWhite );
    iMaskGc->DrawRect( TRect( TPoint( 0,0 ), iRect.Size() ) );
    iMaskGc->SetPenStyle( CGraphicsContext::ENullPen );
    iMaskGc->SetBrushStyle( CGraphicsContext::ENullBrush );
    }

// ----------------------------------------------------------------------------
// CGraphicsLayer::ReleaseBmpBuffer
// ----------------------------------------------------------------------------
//
void CGraphicsLayer::ReleaseBmpBuffer()
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

    if ( iMaskGc )
        {
        delete iMaskGc;
        iMaskGc = NULL;
        }

    if ( iMaskDevice )
        {
        delete iMaskDevice;
        iMaskDevice = NULL;
        }

    if ( iMask )
        {
        delete iMask;
        iMask = NULL;
        }

    }

// End of File
