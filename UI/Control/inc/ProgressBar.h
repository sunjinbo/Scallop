/* ====================================================================
 * File: ProgressBar.h
 * Created: 11/07/09
 * Modified: 12/02/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_PROGRESSBAR_H
#define C_PROGRESSBAR_H

// INCLUDE FILES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CGraphicsManager;
class CGraphicsLayer;

// CLASS DECLARATION

/**
* CProgressBar class
*
* @since S60 5.0
*/
class CProgressBar : public CCoeControl
    {
public: // New enumerates
    enum TDirection
            {
            EVertical = 0,
            EHorizontal
            };

public: // Constructor and destructor
    IMPORT_C static CProgressBar* NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect );
    IMPORT_C virtual ~CProgressBar();

public: // New functions
    IMPORT_C void SetDirectionL( CProgressBar::TDirection aDirection );
    IMPORT_C void IncrementAndDraw( TInt aInc );
    IMPORT_C void DecrementAndDraw( TInt aDec );
    IMPORT_C void SetAndDraw( TInt aValue );
    IMPORT_C void SetMaxValue( TInt aMaxValue );
    IMPORT_C void SetBorder( TBool aBorder );
    IMPORT_C void SetColor( const TRgb& aColor );
    IMPORT_C void SetBorderColor( const TRgb& aBorderColor );
    IMPORT_C TInt CurrentValue() const;
    IMPORT_C TInt MaxValue() const;
    IMPORT_C TBool Border() const;
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

public: // from CCoeControl
    void SizeChanged();

private: // Constructor
    CProgressBar( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // New function
    /*
    * Gets the minimum size required to draw the control.
    */
    TSize MinimumSize();
    void DrawBorder();
    void DrawBars( TRgb aColor, TInt aNumber );

protected: // Data
    CGraphicsManager& iGraphicsManager;
    CGraphicsLayer* iLayer;
    CProgressBar::TDirection iDirection;
    TInt iMaxValue;
    TInt iCurrentValue;
    TBool iBorder;
    TRgb iColor;
    TRgb iBorderColor;
    TSize iBarSize;
    };

#endif // C_PROGRESSBAR_H

// End of File
