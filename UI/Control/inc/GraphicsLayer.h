/* ====================================================================
 * File: GraphicsManager.h
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_GRAPHICSLAYER_H
#define C_GRAPHICSLAYER_H

// INCLUDE FILES
#include <e32base.h>
#include <gdi.h>
#include "GraphicsLayer.hrh"

// FORWARD DECLARATIONS
class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;

// CLASS DECLARATION

/**
* CGraphicsLayer class
*
* @since S60 5.0
*/
class CGraphicsLayer : public CBase
    {
public: // Constructor and destructor

    static CGraphicsLayer* NewL( const TRect& aRect, TLayerId aLayerId );
    virtual ~CGraphicsLayer();

public: // New functions
    TLayerId LayerId() const;
    void DrawBitmap( const TRect& aDestRect, const CFbsBitmap* aSource );
    void DrawBitmap( const TPoint& aTopLeft, const CFbsBitmap* aSource );
    void DrawMask( const TRect& aDestRect, const CFbsBitmap* aSource );
    void DrawMask( const TPoint& aTopLeft, const CFbsBitmap* aSource );
    void DrawText( const TDesC& aText, const TRect& aBox, TInt aBaseline );
    void DrawRect( const TRect& aRect );
    void DrawEllipse( const TRect& aRect );
    void DrawLine( const TPoint& aStart, const TPoint& aEnd );
    void Clear();
    void Clear( const TRect& aRect );
    void SetTransparency( TInt aTransparency );
    CFbsBitmap* Bitmap();
    CFbsBitmap* Mask();
    const TRect& Rect() const;
    void SetColor( const TRgb& aColor );
    void BitBltMasked( 
            const TPoint& aPoint, 
            const CFbsBitmap* aBitmap,
            const TRect& aSourceRect,
            const CFbsBitmap* aMaskBitmap,
            TBool aInvertMask );
    void SetTextAlign( CGraphicsContext::TTextAlign aAlign );
    void SetVisible( TBool aVisble );
    TBool Visible() const;
    void SetFontHeight( TInt aFontHeightInTwips );
    static TInt Compare( const CGraphicsLayer& aFirst, const CGraphicsLayer& aSecond );

protected: // Constructor
    CGraphicsLayer( const TRect& aRect, TLayerId aLayerId );
    void ConstructL();

protected: // New functions
    void CreateBmpBufferL();
    void ReleaseBmpBuffer();

protected: // Data
    CFbsBitmap* iBitmap;
    CFbsBitmap* iMask;
    CFbsBitmapDevice* iBitmapDevice;
    CFbsBitmapDevice* iMaskDevice;
    CFbsBitGc* iBitmapGc;
    CFbsBitGc* iMaskGc;
    CFont* iFont;
    TRect iRect;
    TRgb iColor;
    TLayerId iLayerId;
    TInt iTransparency;
    CGraphicsContext::TTextAlign iAlign;
    TBool iVisible;
    };

#endif // C_GRAPHICSLAYER_H

// End of File
