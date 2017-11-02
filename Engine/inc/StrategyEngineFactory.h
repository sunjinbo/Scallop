/* ====================================================================
 * File: StrategyEngineFactory.h
 * Created: 08/16/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_STRATEGYENGINEFACTORY_H
#define C_STRATEGYENGINEFACTORY_H

// INCLUDE FILES
#include <e32base.h>
#include "EngineFactory.h"

// FORWARD DECLARATIONS
class RFs;

// CLASS DECLARATION
/**
* CStrategyEngineFactory class
*
* @since S60 5.0
*/
class CStrategyEngineFactory : public CBase, public MEngineFactory
    {
public: // Two-phased constructor and destructor
    IMPORT_C static CStrategyEngineFactory* NewL();
    virtual ~CStrategyEngineFactory();

public: // New functions
    virtual CEngineBase* ScaEngineL( MEngineObserver& aObserver );

private: // Normal 2-nd stage construction.
    void ConstructL();
    CStrategyEngineFactory();

private: // New function
    TInt GetPrivatePath( TFileName& aPath );

private: // Member data
    RFs& iFs;
    };

#endif // C_STRATEGYENGINEFACTORY_H

// End of file
