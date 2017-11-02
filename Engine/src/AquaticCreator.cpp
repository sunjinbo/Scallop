/* ====================================================================
 * File: AquaticCreator.cpp
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32std.h>
#include <e32math.h>

#include "AquaticCreator.h"
#include "EngineCommon.h"
#include "ScaEngine.pan"
#include "AquaticObserver.h"
#include "AquaticHandler.h"
#include "GameLevel.h"

#include "ScaLogger.h"

// CONSTANTS
const TInt KImmaturedNumber = 4;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CAquaticCreator::NewL
// ----------------------------------------------------------------------------
//
CAquaticCreator* CAquaticCreator::NewL( MAquaticObserver& aObserver, 
    MAquaticHandler& aHandler )
    {
    CAquaticCreator* self = 
        new (ELeave) CAquaticCreator( aObserver, aHandler );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CAquaticCreator::~CAquaticCreator
// ----------------------------------------------------------------------------
//
CAquaticCreator::~CAquaticCreator()
    {
    FUNC_LOG;
    iAvailableTypeList.Close();
    iList.Close();
    }

// ----------------------------------------------------------------------------
// CAquaticCreator::Create
// ----------------------------------------------------------------------------
//
void CAquaticCreator::Create( CGameLevel& aLevel )
    {
    FUNC_LOG;
    iAvailableTypeList.Reset();
    iList.Reset();
    aLevel.GetAvailableType( iAvailableTypeList );
    TRAP_IGNORE( aLevel.GetAquaticDataL( iList ) );
    TRAP_IGNORE( iHandler.AddAquaticsL( iList ) );
    }

// ----------------------------------------------------------------------------
// CAquaticCreator::Start
// ----------------------------------------------------------------------------
//
TBool CAquaticCreator::Next()
    {
    FUNC_LOG;
    TBool retVal( EFalse );
    TInt num = KMainMatrixWidth * KMainMatrixHeight - KImmaturedNumber;
    if ( iObserver.Count() <= num )
        {
        RArray<TAquaticData> list;
        for ( TInt i = 0; i < KImmaturedNumber; i++ )
            {
            list.Append( RandAquatic() );
            }
        TRAP_IGNORE( iHandler.AddAquaticsL( list ) );
        list.Close();
        retVal = ETrue;
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// CAquaticCreator::CAquaticCreator
// ----------------------------------------------------------------------------
//
CAquaticCreator::CAquaticCreator( 
    MAquaticObserver& aObserver, MAquaticHandler& aHandler )
    : iObserver( aObserver ), iHandler( aHandler )
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CAquaticCreator::ConstructL
// ----------------------------------------------------------------------------
//
void CAquaticCreator::ConstructL()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CAquaticCreator::RandAquatic
// ----------------------------------------------------------------------------
//
TAquaticData CAquaticCreator::RandAquatic() const
    {
    FUNC_LOG;
    TInt count = iAvailableTypeList.Count();
    TInt rand = Rand( count );
    TAquaticType type = ( TAquaticType )iAvailableTypeList[ rand ];
    TPoint postion( RandPostion() );
    return TAquaticData( type, postion );
    }

// ----------------------------------------------------------------------------
// CAquaticCreator::RandPostion
// ----------------------------------------------------------------------------
//
TPoint CAquaticCreator::RandPostion() const
    {
    FUNC_LOG;
    RArray<TPoint> list;
    for ( TInt i = 0; i < KMainMatrixWidth; i++ )
        for ( TInt j = 0; j < KMainMatrixHeight; j++ )
            {
            if ( iObserver.Aquatic( i, j ) == EAquaticNull )
                {
                list.Append( TPoint( i, j ) );
                }
            }
    TInt count = list.Count() ;
    TInt index( Rand( count ) );
    TPoint postion( list[ index ] );
    list.Close();
    return postion;
    }

// ----------------------------------------------------------------------------
// CAquaticCreator::Rand
// ----------------------------------------------------------------------------
//
TInt CAquaticCreator::Rand( TInt aRange ) const
    {
    FUNC_LOG;
    TTime time;
    time.UniversalTime();
    TInt64 seed( time.Int64() );
    TInt rand( Math::Rand( seed ) % aRange );
    User::After( 2000 );
    return rand;
    }

// End of file
