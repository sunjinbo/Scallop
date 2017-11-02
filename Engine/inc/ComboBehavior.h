/* ====================================================================
 * File: ComboBehavior.h
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


#ifndef COMBOBEHAVIOR_H
#define COMBOBEHAVIOR_H

// INCLUDE FILES
#include <e32base.h>
#include "AquaticData.h"

// FORWARD DECLARATIONS
class MAquaticObserver;
class TAquaticData;

// CLASS DECLARATION
/**
* CComboBehavior class
*
* @since S60 5.0
*/
class CComboBehavior : public CBase
    {
public: // Destructor
    virtual ~CComboBehavior();

public: // New functions
    virtual void Combo( RArray<TAquaticData>& aArray ) = 0;
    void SetObserver( MAquaticObserver* aObserver );

protected: // Constructor
    CComboBehavior();
    virtual void ConstructL();

protected: // New functions

protected: // Member Data
    MAquaticObserver* iObserver;
    };

#endif // COMBOBEHAVIOR_H

// End of file
