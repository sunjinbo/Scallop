/* ====================================================================
 * File: MBitmapUtils.h
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_BITMAPUTILS_H
#define M_BITMAPUTILS_H

// INCLUDE FILES
#include <e32std.h>

// FORWARD DECLARATIONS
class CFbsBitmap;

// CLASS DECLARATION

/**
* MBitmapUtils class
*
* @since S60 5.0
*/
class MBitmapUtils
    {
public: // interface functions
    virtual void SetSize( TInt aIndex, TSize aSize ) = 0;
    virtual void SetSizeAndRotation( TInt aIndex, TSize aSize, TInt aAngle ) = 0;
    virtual CFbsBitmap* Bitmap( TInt aIndex ) const = 0;
    };

#endif // M_BITMAPUTILS_H

// End of File

