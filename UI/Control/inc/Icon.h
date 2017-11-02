/* ====================================================================
 * File: Icon.h
 * Created: 12/05/09
 * Modified: 13/05/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_ICON_H
#define C_ICON_H

// INCLUDE FILES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CGraphicsManager;
class CGraphicsLayer;

// CLASS DECLARATION
/**
* CIcon class
*
* @since S60 5.0
*/
class CIcon : public CCoeControl
    {
public: // Constructor and destructor
    IMPORT_C static CIcon* NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect );
    IMPORT_C virtual ~CIcon();

public: // New functions
    IMPORT_C void SetBitmap( CFbsBitmap* aBitmap );
    IMPORT_C void SetBitmapL( TInt aBitmapIx );
    IMPORT_C void SetMask( CFbsBitmap* aMask );
    IMPORT_C void SetMaskL( TInt aMaskIx );
    IMPORT_C void Clear();
    IMPORT_C void SetVisible( TBool aVisible );
    IMPORT_C void ResizeL( const TRect& aRect );
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

private: // Constructor
    CIcon( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // Member data
    CGraphicsManager& iGraphicsManager;
    CGraphicsLayer* iIconLayer;
    };

#endif // C_ICON_H

// End of File