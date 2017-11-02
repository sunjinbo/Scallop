/* ====================================================================
 * File: ComboBehavior.cpp
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "ComboBehavior.h"
#include "AquaticObserver.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CComboBehavior::~CComboBehavior
// ----------------------------------------------------------------------------
//
CComboBehavior::~CComboBehavior()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CComboBehavior::AddObserver
// ----------------------------------------------------------------------------
//
void CComboBehavior::SetObserver( MAquaticObserver* aObserver )
    {
    FUNC_LOG;
    iObserver = aObserver;
    }

// ----------------------------------------------------------------------------
// CComboBehavior::CComboBehavior
// ----------------------------------------------------------------------------
//
CComboBehavior::CComboBehavior()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CComboBehavior::ConstructL
// ----------------------------------------------------------------------------
//
void CComboBehavior::ConstructL()
    { // no implementation required.
    FUNC_LOG;
    }

// End of file
