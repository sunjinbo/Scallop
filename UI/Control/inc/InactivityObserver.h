/* ====================================================================
 * File: InactivityObserver.h
 * Created: 11/22/09
 * Modified: 11/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_INACTIVITYOBSERVER_H
#define M_INACTIVITYOBSERVER_H

// INCLUDE FILES
#include <e32def.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* MInactivityObserver class
*
* @since S60 5.0
*/
class MInactivityObserver
    {
public: // callback function
    virtual void Expired() = 0;
    };

#endif // M_INACTIVITYOBSERVER_H

// End of file
