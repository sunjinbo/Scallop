/* ====================================================================
 * File: ClassicEngineFactory.h
 * Created: 08/16/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_CLASSICENGINEFACTORY_H
#define C_CLASSICENGINEFACTORY_H

// INCLUDE FILES
#include <e32base.h>
#include "EngineFactory.h"

// FORWARD DECLARATIONS
class RFs;

// CLASS DECLARATION
/**
* CClassicEngineFactory class
*
* @since S60 5.0
*/
class CClassicEngineFactory : public CBase, public MEngineFactory
    {
public: // Two-phased constructor and destructor
    IMPORT_C static CClassicEngineFactory* NewL();
    virtual ~CClassicEngineFactory();

public: // New functions
    virtual CEngineBase* ScaEngineL( MEngineObserver& aObserver );

private: // Normal 2-nd stage construction.
    void ConstructL();
    CClassicEngineFactory();

private: // New function
    TInt GetPrivatePath( TFileName& aPath );

private: // Member data
    RFs& iFs;
    };

#endif // C_CLASSICENGINEFACTORY_H

// End of file
