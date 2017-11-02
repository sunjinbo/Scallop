/* ====================================================================
 * File: GraphicsManager.h
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_GRAPHICSMANAGER_H
#define C_GRAPHICSMANAGER_H

// INCLUDE FILES
#include <e32base.h>

// FORWARD DECLARATIONS
class CGraphicsLayer;
class CFbsBitmap;


// CLASS DECLARATION

/**
* CGraphicsManager class
*
* @since S60 5.0
*/
class CGraphicsManager : public CBase
    {
public: // Constructor and destructor

    static CGraphicsManager* NewL( const TRect& aRect );
    virtual ~CGraphicsManager();

public: // New functions
    void Merge();
    CFbsBitmap* Bitmap();
    CFbsBitmap* Mask();
    void SetRect( const TRect& aRect );
    void RegisterLayer( CGraphicsLayer* aLayer );
    void UnregisterLayer( CGraphicsLayer* aLayer );

protected: // Constructor
    CGraphicsManager();
    void ConstructL( const TRect& aRect );

protected: // New functions
    TInt Find( CGraphicsLayer* aLayer, TInt& aIndex ) const;
    void CreateFoundationLayerL( const TRect& aRect );
    void Sort();

protected: // Data
    RPointerArray<CGraphicsLayer> iGraphicsLayers;
    CGraphicsLayer* iFoundationLayer;
    };

#endif // C_GRAPHICSMANAGER_H

// End of File
