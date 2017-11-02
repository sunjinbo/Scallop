/* ====================================================================
 * File: EngineFactory.h
 * Created: 08/16/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_ENGINEFACTORY_H
#define M_ENGINEFACTORY_H

// INCLUDE FILES
#include <e32base.h>

// FORWARD DECLARATIONS
class CEngineBase;
class MEngineObserver;

// CLASS DECLARATION
/**
* MEngineFactory class
*
* @since S60 5.0
*/
class MEngineFactory
    {
public: // New functions
    virtual CEngineBase* ScaEngineL( MEngineObserver& aObserver ) = 0;
    };

#endif // M_ENGINEFACTORY_H

// End of file
