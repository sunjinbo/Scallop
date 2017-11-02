/* ====================================================================
 * File: ClassicComboBehavior.cpp
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "ClassicComboBehavior.h"
#include "AquaticObserver.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CClassicComboBehavior::NewL
// ----------------------------------------------------------------------------
//
CClassicComboBehavior* CClassicComboBehavior::NewL()
    {
    CClassicComboBehavior* self = CClassicComboBehavior::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CClassicComboBehavior::NewLC
// ----------------------------------------------------------------------------
//
CClassicComboBehavior* CClassicComboBehavior::NewLC()
    {
    CClassicComboBehavior* self = new (ELeave) CClassicComboBehavior;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CClassicComboBehavior::~CComboBehavior
// ----------------------------------------------------------------------------
//
CClassicComboBehavior::~CClassicComboBehavior()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CClassicComboBehavior::Combo
// ----------------------------------------------------------------------------
//
void CClassicComboBehavior::Combo( RArray<TAquaticData>& /*aArray*/ )
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CClassicComboBehavior::CClassicComboBehavior
// ----------------------------------------------------------------------------
//
CClassicComboBehavior::CClassicComboBehavior()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CClassicComboBehavior::ConstructL
// ----------------------------------------------------------------------------
//
void CClassicComboBehavior::ConstructL()
    { // no implementation required.
    FUNC_LOG;
    }

// End of file
