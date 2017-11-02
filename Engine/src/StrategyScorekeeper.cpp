/* ====================================================================
 * File: StrategyScorekeeper.cpp
 * Created: 10/08/09
 * Modified: 10/08/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "StrategyScorekeeper.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CStrategyScorekeeper::NewL
// ----------------------------------------------------------------------------
//
CStrategyScorekeeper* CStrategyScorekeeper::NewL( MScorekeeperObserver& aObserver )
    {
    CStrategyScorekeeper* self = CStrategyScorekeeper::NewLC( aObserver );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CStrategyScorekeeper::NewLC
// ----------------------------------------------------------------------------
//
CStrategyScorekeeper* CStrategyScorekeeper::NewLC( MScorekeeperObserver& aObserver )
    {
    CStrategyScorekeeper* self = new( ELeave ) CStrategyScorekeeper( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CStrategyScorekeeper::~CStrategyScorekeeper
// ----------------------------------------------------------------------------
//
CStrategyScorekeeper::~CStrategyScorekeeper()
    {
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CStrategyScorekeeper::CStrategyScorekeeper
// ----------------------------------------------------------------------------
//
CStrategyScorekeeper::CStrategyScorekeeper( MScorekeeperObserver& aObserver )
    : CScorekeeper( aObserver )
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CStrategyScorekeeper::ConstructL
// ----------------------------------------------------------------------------
//
void CStrategyScorekeeper::ConstructL()
    {
    FUNC_LOG;
    CScorekeeper::ConstructL();
    }

// ----------------------------------------------------------------------------
// CStrategyScorekeeper::Store
// ----------------------------------------------------------------------------
//
void CStrategyScorekeeper::Store()
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CStrategyScorekeeper::Restore
// ----------------------------------------------------------------------------
//
void CStrategyScorekeeper::Restore()
    {
    FUNC_LOG;
    iCompletedTotalScore = 0; // Todo: read value from CR
    iCompletedLevelID = 1; // Todo: read value from CR
    }

// End of file
