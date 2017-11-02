/* ====================================================================
 * File: StarFish.cpp
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "StarFish.h"
#include "ScaLogger.h"


// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CStarFish::NewL
// ----------------------------------------------------------------------------
//
CStarFish* CStarFish::NewL( 
    MAquaticObserver& aObserver, MAquaticHandler& aHandler )
    {
    CStarFish* self = new (ELeave) CStarFish( aObserver, aHandler );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CStarFish::~CStarFish
// ----------------------------------------------------------------------------
//
CStarFish::~CStarFish()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CStarFish::operator==
// ----------------------------------------------------------------------------
//
TBool CStarFish::operator==( const CAquatic& anAquatic ) const
    {
    FUNC_LOG;
    TAquaticType aquaticType( anAquatic.AquaticData().Type() );
    if ( ( aquaticType > EAquaticNull )
        && ( aquaticType <= EYellowScallop ) )
        {
        return ETrue;
        }
    return EFalse;
    }

// ----------------------------------------------------------------------------
// CStarFish::CStarFish
// ----------------------------------------------------------------------------
//
CStarFish::CStarFish( MAquaticObserver& aObserver, MAquaticHandler& aHandler )
    : CScallop( aObserver, aHandler )
    {
    FUNC_LOG;
    // The property of aquatic type in these sort of class is fixed.
    // No need to be changed later anymore.
    SetType( EStarFish );
    }

// ----------------------------------------------------------------------------
// CStarFish::ConstructL
// ----------------------------------------------------------------------------
//
void CStarFish::ConstructL()
    { // no implementation required.
    FUNC_LOG;
    }

// End of file
