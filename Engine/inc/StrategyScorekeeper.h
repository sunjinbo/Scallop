/* ====================================================================
 * File: StrategyScorekeeper.h
 * Created: 10/08/09
 * Modifed: 10/08/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_STRATEGYSCOREKEEPER_H
#define C_STRATEGYSCOREKEEPER_H

// INCLUDE FILES
#include "Scorekeeper.h"

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CStrategyScorekeeper class
*
* @since S60 5.0
*/
class CStrategyScorekeeper : public CScorekeeper
    {
public: // Constructor and Destructor
    static CStrategyScorekeeper* NewL( MScorekeeperObserver& aObserver );
    static CStrategyScorekeeper* NewLC( MScorekeeperObserver& aObserver );
    virtual ~CStrategyScorekeeper();

private: // Constractor
    CStrategyScorekeeper( MScorekeeperObserver& aObserver );
    void ConstructL();
    virtual void Store();
    virtual void Restore();

private: // Member data
    };

#endif // C_STRATEGYSCOREKEEPER_H

// End of file
