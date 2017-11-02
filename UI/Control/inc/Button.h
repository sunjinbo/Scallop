/* ====================================================================
 * File: Button.h
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BUTTON_H
#define C_BUTTON_H

// INCLUDE FILES
#include <e32const.h>
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CGraphicsManager;
class CGraphicsLayer;
class MButtonObserver;

// CLASS DECLARATION
/**
* CButton class
*
* @since S60 5.0
*/
class CButton : public CCoeControl
    {
public: // Constructor and destructor
    IMPORT_C static CButton* NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect );
    IMPORT_C virtual ~CButton();

public: // New functions
    IMPORT_C TInt Id() const;
    IMPORT_C void SetId( TInt aBtnId );
    IMPORT_C void SetFlag( TInt aFlag );
    IMPORT_C void SetIconAttribute( const TSize& aSize, TAlign aAlign = ECenter );
    IMPORT_C void SetFontHeight( TInt aFontHeightInTwips );
    IMPORT_C void SetBitmap( CFbsBitmap* aBitmap );
    IMPORT_C void SetMask( CFbsBitmap* aMask );
    IMPORT_C void SetTextL( const TDesC& aText );
    IMPORT_C void SetTextAlign( CGraphicsContext::TTextAlign aAlign );
    IMPORT_C void SetTextBaseline( TInt aTextBaseline );
    IMPORT_C void SetColor( const TRgb& aColor );
    IMPORT_C void SetPressColor( const TRgb& aPressColor );
    IMPORT_C void SetVisible( TBool aVisible );
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
    IMPORT_C void SetObserver( MButtonObserver* aObserver );

public: // from CCoeControl
    void SizeChanged();
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

protected: // Constructor
    CButton( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

protected: // Data
    MButtonObserver* iObserver; // Not own.
    CGraphicsManager& iGraphicsManager;
    CGraphicsLayer* iBackgroundLayer;
    CGraphicsLayer* iTextLayer;
    HBufC* iText;
    TInt iBtnId;
    TInt iFlag;
    TSize iIconSize;
    TAlign iAlign;
    TInt iFontHeightInTwips;
    TInt iTextBaseline;
    TRgb iColor;
    TRgb iPressColor;
    TPoint iIconPosition;
    };

#endif // C_BUTTON_H

// End of File
