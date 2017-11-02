/* ====================================================================
 * File: ClassicScorekeeper.cpp
 * Created: 10/08/09
 * Modified: 10/08/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "ClassicScorekeeper.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CClassicScorekeeper::NewL
// ----------------------------------------------------------------------------
//
CClassicScorekeeper* CClassicScorekeeper::NewL( MScorekeeperObserver& aObserver )
    {
    CClassicScorekeeper* self = CClassicScorekeeper::NewLC( aObserver );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CClassicScorekeeper::NewLC
// ----------------------------------------------------------------------------
//
CClassicScorekeeper* CClassicScorekeeper::NewLC( MScorekeeperObserver& aObserver )
    {
    CClassicScorekeeper* self = new( ELeave ) CClassicScorekeeper( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CClassicScorekeeper::~CClassicScorekeeper
// ----------------------------------------------------------------------------
//
CClassicScorekeeper::~CClassicScorekeeper()
    {
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CClassicScorekeeper::CClassicScorekeeper
// ----------------------------------------------------------------------------
//
CClassicScorekeeper::CClassicScorekeeper( MScorekeeperObserver& aObserver )
    : CScorekeeper( aObserver )
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CClassicScorekeeper::ConstructL
// ----------------------------------------------------------------------------
//
void CClassicScorekeeper::ConstructL()
    {
    FUNC_LOG;
    CScorekeeper::ConstructL();
    }

// ----------------------------------------------------------------------------
// CClassicScorekeeper::Store
// ----------------------------------------------------------------------------
//
void CClassicScorekeeper::Store()
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CClassicScorekeeper::Restore
// ----------------------------------------------------------------------------
//
void CClassicScorekeeper::Restore()
    {
    FUNC_LOG;
    iCompletedTotalScore = 0; // Todo: read value from CR
    iCompletedLevelID = 1; // Todo: read value from CR
    }

// End of file
