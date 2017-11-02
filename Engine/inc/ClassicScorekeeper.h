/* ====================================================================
 * File: ClassicScorekeeper.h
 * Created: 10/08/09
 * Modifed: 10/08/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_CLASSICSCOREKEEPER_H
#define C_CLASSICSCOREKEEPER_H

// INCLUDE FILES
#include "Scorekeeper.h"

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CStrategyScorekeeper class
*
* @since S60 5.0
*/
class CClassicScorekeeper : public CScorekeeper
    {
public: // Constructor and Destructor
    static CClassicScorekeeper* NewL( MScorekeeperObserver& aObserver );
    static CClassicScorekeeper* NewLC( MScorekeeperObserver& aObserver );
    virtual ~CClassicScorekeeper();

private: // Constractor
    CClassicScorekeeper( MScorekeeperObserver& aObserver );
    void ConstructL();
    virtual void Store();
    virtual void Restore();

private: // Member data
    };

#endif // C_CLASSICSCOREKEEPER_H

// End of file
