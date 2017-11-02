/* ====================================================================
 * File: AquaticHandler.h
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


#ifndef M_AQUATICHANDLER_H
#define M_AQUATICHANDLER_H

// INCLUDE FILES
#include <e32std.h>
#include "Aquatic.hrh"

// CLASS DECLARATION
/**
* MAquaticHandler class
*
* @since S60 5.0
*/
class MAquaticHandler
    {
public: // Interface functions
    virtual void AddAquaticsL( const RArray<TAquaticData>& aList ) = 0;
    virtual void ChangeAquaticL( TPoint aPos, TAquaticType aNewType ) = 0;
    virtual void RemoveAquatic( TPoint aPos ) = 0;
    virtual void RemoveAquatic( const RArray<TAquaticData>& aList ) = 0;
    virtual void MoveAquatic(  const RArray<TAquaticData>& aPath ) = 0;
    };

#endif // M_AQUATICHANDLER_H

// End of file
