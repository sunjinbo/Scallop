/* ====================================================================
 * File: TextPane.h
 * Created: 12/05/09
 * Modified: 12/05/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_TEXTPANE_H
#define C_TEXTPANE_H

// INCLUDE FILES
#include <e32const.h>
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CGraphicsManager;
class CGraphicsLayer;


// CLASS DECLARATION

/**
* CTextPane class
*
* @since S60 5.0
*/
class CTextPane : public CCoeControl
    {
public: // Constructor and destructor
    IMPORT_C static CTextPane* NewL( 
        CGraphicsManager& aGraphicsManager, const TRect& aRect );
    IMPORT_C virtual ~CTextPane();

public: // New functions
    IMPORT_C void ResizeL( const TRect& aRect );
    IMPORT_C void SetFontHeight( TInt aFontHeightInTwips );
    IMPORT_C void SetTextBaseline( TInt aTextBaseline );
    IMPORT_C void SetTextAlign( CGraphicsContext::TTextAlign aAlign );
    IMPORT_C void SetColor( const TRgb& aColor );
    IMPORT_C void SetTextL( const TDesC& aText );
    IMPORT_C void SetVisible( TBool aVisible );
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

public: // from CCoeControl
    void SizeChanged();

private: // Constructor
    CTextPane( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // New functions
    void DoDraw();
    void SetAttributes();
    void AppendL( const TDesC& aText );
    void BuildTextBox();

private: // Data
    CGraphicsManager& iGraphicsManager;
    CGraphicsLayer* iTextLayer; // Own
    RPointerArray<HBufC> iTextArray;
    TInt iLine;
    TInt iFontHeightInTwips;
    TInt iTextBaseline;
    TRgb iColor;
    CGraphicsContext::TTextAlign iAlign;
    TSize iTextBoxSize;
    };

#endif // C_TEXTPANE_H

// End of File
