/* ====================================================================
 * File: AquaticObserver.h
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


#ifndef M_AQUATICOBSERVER_H
#define M_AQUATICOBSERVER_H

// INCLUDE FILES
#include <e32std.h>
#include "Aquatic.h"
#include "Aquatic.hrh"

// CLASS DECLARATION
/**
* MAquaticObserver class
*
* @since S60 5.0
*/
class MAquaticObserver
    {
public: // Interface functions
    virtual TAquaticData Aquatic( TInt aX, TInt aY ) = 0;
    virtual TInt Count() const = 0 ;
    };

#endif // M_AQUATICOBSERVER_H

// End of file
