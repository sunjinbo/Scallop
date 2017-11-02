/* ====================================================================
 * File: FuncKeyPane.h
 * Created: 12/04/09
 * Modified: 12/04/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_FUNCKEYPANE_H
#define C_FUNCKEYPANE_H

// INCLUDE FILES
#include <coecntrl.h>
#include <Aquatic.hrh>

// FORWARD DECLARATIONS
class CGraphicsManager;
class CGraphicsLayer;

// CLASS DECLARATION

/**
* CFuncKeyPane class
*
* @since S60 5.0
*/
class CFuncKeyPane : public CCoeControl
    {
public: // Constructor and destructor
    IMPORT_C static CFuncKeyPane* NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect );
    IMPORT_C virtual ~CFuncKeyPane();

public: // New functions
    IMPORT_C void SetAndDraw( TAquaticType aType, TInt aValue );
    IMPORT_C TAquaticType CurrentType() const;
    IMPORT_C TInt CurrentValue() const;
    IMPORT_C void Clear();
    IMPORT_C TBool IsFull() const;
    IMPORT_C TBool IsEmpty() const;

public: // from CCoeControl
    void SizeChanged();

private: // Constructor
    CFuncKeyPane( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // New function
    void DoDraw();
    void SelectColor( TAquaticType aType );

protected: // Data
    CGraphicsManager& iGraphicsManager;
    CGraphicsLayer* iLayer;
    TAquaticType iType;
    TInt iCurrentValue;
    TSize iBigSquareSize;
    TSize iSmallSquareSize;
    TInt iSquareMargin;
    };

#endif // C_FUNCKEYPANE_H

// End of File
