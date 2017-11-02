/* ====================================================================
 * File: SvgUtils.h
 * Created: 10/29/09
 * Modified: 10/29/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SVGUTILS_H
#define C_SVGUTILS_H

// INCLUDE FILES
#include "BmpUtils.h"


// CLASS DECLARATION
/**
* CSvgUtils class
*
* For handles creation and drawing of .SVG file.
*
* @since S60 5.0
*/
class CSvgUtils : public CBmpUtils
    {
public: // Constructor and destructor

    IMPORT_C static CSvgUtils* NewL( const TDesC& aFileName, TInt aFrom, TInt aTo );
    IMPORT_C static CSvgUtils* NewLC( const TDesC& aFileName, TInt aFrom, TInt aTo );
    IMPORT_C virtual ~CSvgUtils();

public: // New functions

    IMPORT_C void SetSize( TInt aIndex, TSize aSize );
    IMPORT_C void SetSizeAndRotation( TInt aIndex, TSize aSize, TInt aAngle );
    IMPORT_C CFbsBitmap* Bitmap( TInt aIndex ) const;

protected: // Default destructor
    
    CSvgUtils( TInt aFrom, TInt aTo );
    void ConstructL( const TDesC& aFileName );

protected: // New function

    void LoadBitmapL ();

    };

#endif // C_SVGUTILS_H

// End of File
