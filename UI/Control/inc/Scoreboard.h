/* ====================================================================
 * File: Scoreboard.h
 * Created: 11/25/09
 * Modified: 11/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCOREBOARD_H
#define C_SCOREBOARD_H

// INCLUDE FILES
#include <e32const.h>
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CGraphicsManager;
class CGraphicsLayer;

// CLASS DECLARATION
/**
* CScoreboard class
*
* @since S60 5.0
*/
class CScoreboard : public CCoeControl
    {
public: // Constructor and destructor
    IMPORT_C static CScoreboard* NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect );
    IMPORT_C virtual ~CScoreboard();

public: // New functions
    IMPORT_C void SetIconSize( const TSize& aSize );
    IMPORT_C void SetFontHeight( TInt aFontHeightInTwips );
    IMPORT_C void SetBitmap( CFbsBitmap* aBitmap );
    IMPORT_C void SetMask( CFbsBitmap* aMask );
    IMPORT_C void SetTextL( const TDesC& aText );
    IMPORT_C void SetValue( TInt aValue );
    IMPORT_C void AppendValue( TInt aIncValue );
    IMPORT_C void SetTextBaseline( TInt aTextBaseline );
    IMPORT_C void SetColor( const TRgb& aColor );
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );
    IMPORT_C TInt Value() const;

public: // from CCoeControl
    void SizeChanged();

private: // Constructor
    CScoreboard( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // Member data
    CGraphicsManager& iGraphicsManager;
    CGraphicsLayer* iBackgroundLayer;
    CGraphicsLayer* iTextLayer;
    HBufC* iText;
    TInt iValue;
    TSize iIconSize;
    TPoint iIconPosition;
    TInt iFontHeightInTwips;
    TInt iTextBaseline;
    TRgb iColor;
    };

#endif // C_SCOREBOARD_H

// End of File
