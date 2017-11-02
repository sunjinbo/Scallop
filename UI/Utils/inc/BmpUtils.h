/* ====================================================================
 * File: BmpUtils.h
 * Created: 03/14/09
 * Modified: 05/08/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BMPUTILS_H
#define C_BMPUTILS_H

// INCLUDE FILES
#include <e32base.h>
#include <e32std.h>
#include "BitmapUtils.h"

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CBmpUtils class
*
* For handles creation and drawing of .bmp file.
*
* @since S60 5.0
*/
class CBmpUtils : public CBase, public MBitmapUtils
    {
public: // Constructor and destructor

    IMPORT_C static CBmpUtils* NewL( const TDesC& aFileName, TInt aFrom, TInt aTo );
    IMPORT_C virtual ~CBmpUtils();

public: // New functions

    IMPORT_C virtual void SetSize( TInt aIndex, TSize aSize );
    IMPORT_C virtual void SetSizeAndRotation( TInt aIndex, TSize aSize, TInt aAngle );
    IMPORT_C virtual CFbsBitmap* Bitmap( TInt aIndex ) const;

protected: // Default destructor

    CBmpUtils( TInt aFrom, TInt aTo );
    void ConstructL( const TDesC& aFileName );

protected: // New functions
    virtual void LoadBitmapL ();

protected: // Data members
    TInt iFrom;
    TInt iTo;
    HBufC* iFileName;
    RPointerArray<CFbsBitmap>  iBitmapArray;

    };

#endif // C_BMPUTILS_H

// End of File
