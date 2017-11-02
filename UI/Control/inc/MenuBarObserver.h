/* ====================================================================
 * File: MenuBarObserver.h
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_MENUBAROBSERVER_H
#define M_MENUBAROBSERVER_H

// INCLUDE FILES
#include <e32def.h>

// CLASS DECLARATION

/**
* MMenuBarObserver class
*
* @since S60 5.0
*/
class MMenuBarObserver
    {
public: // callback function
    virtual void HandleMenuBarEventL( TInt aBtnId ) = 0;
    };

#endif // M_MENUBAROBSERVER_H

// End of file
