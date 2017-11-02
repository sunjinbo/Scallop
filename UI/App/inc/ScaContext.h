/* ====================================================================
 * File: ScaContext.h
 * Created: 10/23/09
 * Modified: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_SCACONTEXT_H
#define M_SCACONTEXT_H

// INCLUDE
#include <e32std.h>

// CLASS DECLARATION

/**
* MScaContext class
*
* @since S60 5.0
*/
class MScaContext
    {
public: // Interface functions

    virtual void ChangeViewL( TInt aViewId ) = 0;
    virtual void ChangeEngineL( TInt aCmd ) = 0;
    virtual void ChangeMenuPaneL( TInt aResId ) = 0;

    };

#endif // M_SCACONTEXT_H

// End of File
