/* ====================================================================
 * File: PathRepository.h
 * Created: 10/08/09
 * Modified: 10/08/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_PATHREPOSITORY_H
#define M_PATHREPOSITORY_H

// INCLUDE FILES
#include <e32cmn.h>

// CLASS DECLARATION
/**
* MPathRepository class
*
* @since S60 5.0
*/
class MPathRepository
    {
public:
    virtual void GetPath( TDes& aPath ) const = 0;
    };

#endif // M_PATHREPOSITORY_H

// End of file
