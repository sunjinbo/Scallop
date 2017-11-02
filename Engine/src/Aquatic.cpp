/* ====================================================================
 * File: Aquatic.cpp
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "Aquatic.h"
#include "AquaticHandler.h"
#include "AquaticObserver.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CAquatic::SetType
// ----------------------------------------------------------------------------
//
void CAquatic::SetType( TAquaticType aType )
    {
    FUNC_LOG;
    iAquaticData.SetType( aType );
    }

// ----------------------------------------------------------------------------
// CAquatic::SetXY
// ----------------------------------------------------------------------------
//
void CAquatic::SetXY( TInt aX, TInt aY )
    {
    FUNC_LOG;
    iAquaticData.SetXY( aX, aY );
    }

// ----------------------------------------------------------------------------
// CAquatic::SetAquaticData
// ----------------------------------------------------------------------------
//
void CAquatic::SetAquaticData( const TAquaticData& aData )
    {
    FUNC_LOG;
    iAquaticData = aData;
    }

// ----------------------------------------------------------------------------
// CAquatic::ActivateL
// ----------------------------------------------------------------------------
//
void CAquatic::ActivateL()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CAquatic::ActivateL
// ----------------------------------------------------------------------------
//
void CAquatic::ActivateL( TInt /*aX*/, TInt /*aY*/ )
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CAquatic::Sleep
// ----------------------------------------------------------------------------
//
void CAquatic::Sleep()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CAquatic::Awake
// ----------------------------------------------------------------------------
//
void CAquatic::Awake()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CAquatic::SetSelected
// ----------------------------------------------------------------------------
//
void CAquatic::SetSelected( TBool aSelected )
    {
    FUNC_LOG;
    iSelected = aSelected;
    }

// ----------------------------------------------------------------------------
// CAquatic::Selected
// ----------------------------------------------------------------------------
//
TBool CAquatic::Selected() const
    {
    FUNC_LOG;
    return iSelected;
    }

// ----------------------------------------------------------------------------
// CAquatic::AquaticData
// ----------------------------------------------------------------------------
//
TAquaticData CAquatic::AquaticData() const
    {
    return iAquaticData;
    }

// ----------------------------------------------------------------------------
// CAquatic::CAquatic
// ----------------------------------------------------------------------------
//
CAquatic::CAquatic( MAquaticObserver& aObserver, 
    MAquaticHandler& aHandler )
    : iObserver( aObserver ), iHandler( aHandler ), iSelected( EFalse )
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CAquatic::ConstructL
// ----------------------------------------------------------------------------
//
void CAquatic::ConstructL()
    {
    FUNC_LOG;
    // It's a good way would impose to set the type of aquatic
    // for CAquatic's child class later.
    if ( iAquaticData.IsNull() )
        {
        User::Leave( KErrUnknown );
        }
    }

// End of file
