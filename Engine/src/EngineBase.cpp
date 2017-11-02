/* ====================================================================
 * File: EngineBase.cpp
 * Created: 08/16/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "EngineBase.h"
#include "EngineObserver.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CEngineBase::CEngineBase
// ----------------------------------------------------------------------------
//
CEngineBase::CEngineBase( MEngineObserver& aObserver )
    : iObserver( aObserver )
    { // No implementation required.
    FUNC_LOG;
    }

// End of file
