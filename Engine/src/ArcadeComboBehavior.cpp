/* ====================================================================
 * File: ArcadeComboBehavior.cpp
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "ArcadeComboBehavior.h"
#include "AquaticObserver.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CArcadeComboBehavior::NewL
// ----------------------------------------------------------------------------
//
CArcadeComboBehavior* CArcadeComboBehavior::NewL()
    {
    CArcadeComboBehavior* self = new (ELeave) CArcadeComboBehavior;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CArcadeComboBehavior::~CComboBehavior
// ----------------------------------------------------------------------------
//
CArcadeComboBehavior::~CArcadeComboBehavior()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CArcadeComboBehavior::Combo
// ----------------------------------------------------------------------------
//
void CArcadeComboBehavior::Combo( RArray<TAquaticData>& /*aArray*/ )
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CArcadeComboBehavior::CArcadeComboBehavior
// ----------------------------------------------------------------------------
//
CArcadeComboBehavior::CArcadeComboBehavior()
    {
    }

// ----------------------------------------------------------------------------
// CArcadeComboBehavior::ConstructL
// ----------------------------------------------------------------------------
//
void CArcadeComboBehavior::ConstructL()
    { // no implementation required.
    }

// End of file
