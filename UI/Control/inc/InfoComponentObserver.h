/* ====================================================================
 * File: InfoComponentObserver.h
 * Created: 12/06/09
 * Modified: 12/06/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_INFOCOMPONENTOBSERVER_H
#define M_INFOCOMPONENTOBSERVER_H

// INCLUDE FILES
#include <e32def.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION

/**
* MInfoComponentObserver class
*
* @since S60 5.0
*/
class MInfoComponentObserver
    {
public: // callback function
    virtual void CheckedL( TBool aCheck ) = 0;
    };

#endif // M_INFOCOMPONENTOBSERVER_H

// End of file
