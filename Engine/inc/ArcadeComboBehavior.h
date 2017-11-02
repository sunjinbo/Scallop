/* ====================================================================
 * File: ArcadeComboBehavior.h
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef ARCADECOMBOBEHAVIOR_H
#define ARCADECOMBOBEHAVIOR_H

// INCLUDE FILES
#include "ComboBehavior.h"

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CArcadeComboBehavior class
*
* @since S60 5.0
*/
class CArcadeComboBehavior : public CComboBehavior
    {
public: // Destructor
    static CArcadeComboBehavior* NewL();
    ~CArcadeComboBehavior();

public: // New functions
    virtual void Combo( RArray<TAquaticData>& aArray );

protected: // Constructor
    CArcadeComboBehavior();
    virtual void ConstructL();

protected: // New functions

private: // Member Data
    };

#endif // ARCADECOMBOBEHAVIOR_H

// End of file
