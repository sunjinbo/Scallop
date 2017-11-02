/* ====================================================================
 * File: ClassicComboBehavior.h
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef CLASSICCOMBOBEHAVIOR_H
#define CLASSICCOMBOBEHAVIOR_H

// INCLUDE FILES
#include "ComboBehavior.h"

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CClassicComboBehavior class
*
* @since S60 5.0
*/
class CClassicComboBehavior : public CComboBehavior
    {
public: // Destructor
    static CClassicComboBehavior* NewL();
    static CClassicComboBehavior* NewLC();
    ~CClassicComboBehavior();

public: // from base class CComboBehavior
    virtual void Combo( RArray<TAquaticData>& aArray );

protected: // Constructor
    CClassicComboBehavior();
    virtual void ConstructL();

protected: // New functions

private: // Member Data
    };

#endif // CLASSICCOMBOBEHAVIOR_H

// End of file
