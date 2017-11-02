/* ====================================================================
 * File: StrategyComboBehavior.cpp
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "StrategyComboBehavior.h"
#include "AquaticObserver.h"
#include "EngineCommon.h"
#include "ScaEngine.pan"
#include "ScaLogger.h"

// CONSTANTS
const TInt KMinStrategyComboNum = 4;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::NewL
// ----------------------------------------------------------------------------
//
CStrategyComboBehavior* CStrategyComboBehavior::NewL()
    {
    CStrategyComboBehavior* self = CStrategyComboBehavior::NewLC();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::NewLC
// ----------------------------------------------------------------------------
//
CStrategyComboBehavior* CStrategyComboBehavior::NewLC()
    {
    CStrategyComboBehavior* self = new (ELeave) CStrategyComboBehavior;
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::~CComboBehavior
// ----------------------------------------------------------------------------
//
CStrategyComboBehavior::~CStrategyComboBehavior()
    {
    FUNC_LOG;
    iAquaticBox.Close();
    iSeedBox.Close();
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::Combo
// ----------------------------------------------------------------------------
//
void CStrategyComboBehavior::Combo( RArray<TAquaticData>& aArray )
    {
    FUNC_LOG;
    Init();
    while ( iAquaticBox.Count() )
        {
        Seed( iAquaticBox[0] );
        Crop();
        if ( iSeedBox.Count() >= KMinStrategyComboNum )
            {
            for ( TInt i = 0; i < iSeedBox.Count(); i++ )
                {
                aArray.Append( iSeedBox[ i ] );
                }
            }
        iSeedBox.Reset();
        }
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::CStrategyComboBehavior
// ----------------------------------------------------------------------------
//
CStrategyComboBehavior::CStrategyComboBehavior()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::ConstructL
// ----------------------------------------------------------------------------
//
void CStrategyComboBehavior::ConstructL()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::FindInAquaticBox
// ----------------------------------------------------------------------------
//
TInt CStrategyComboBehavior::FindInAquaticBox( const TPoint& aPos,TInt& aIndex ) const
    {
    FUNC_LOG;
    TInt err( KErrNotFound );
    for ( TInt i = 0; i < iAquaticBox.Count(); ++i )
        {
        TAquaticData aquatic( iAquaticBox[ i ] );
        if ( aquatic.Position() == aPos )
            {
            aIndex = i;
            err = KErrNone;
            break;
            }
        }
    return err;
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::FindInSeedBox
// ----------------------------------------------------------------------------
//
TInt CStrategyComboBehavior::FindInSeedBox( const TPoint& aPos,TInt& aIndex ) const
    {
    FUNC_LOG;
    TInt err( KErrNotFound );
    for ( TInt i = 0; i < iSeedBox.Count(); ++i )
        {
        TAquaticData aquatic( iSeedBox[ i ] );
        if ( aquatic.Position() == aPos )
            {
            aIndex = i;
            err = KErrNone;
            break;
            }
        }
    return err;
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::Init
// ----------------------------------------------------------------------------
//
void CStrategyComboBehavior::Init()
    {
    FUNC_LOG;
    iAquaticBox.Reset();

    for ( TInt i = 0; i < KMainMatrixWidth; i++ )
        for ( TInt j = 0; j < KMainMatrixHeight; j++ )
            {
            __ASSERT_ALWAYS( iObserver, Panic( EEngineNullPointer ) );
            TAquaticData aquatic = iObserver->Aquatic( i, j );
            if ( aquatic.IsMature() )
                {
                iAquaticBox.Append( aquatic );
                }
            }

    iSeedBox.Reset();
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::Seed
// Seed recursive algorithm
// ----------------------------------------------------------------------------
//
void CStrategyComboBehavior::Seed( const TAquaticData& aAquatic )
    {
    FUNC_LOG;
    TAquaticData aquatic( aAquatic );
    MoveToSeedbox( aAquatic );

    TInt index ( -1 );
    TPoint pos;
    // Left
    pos = TPoint( aquatic.Position().iX - 1, aquatic.Position().iY );
    if ( FindInAquaticBox( pos, index ) == KErrNone )
        {
        if ( ( iAquaticBox[ index ].Type() == aquatic.Type()
            || iAquaticBox[ index ].Type() == EStarFish )
            && ( FindInSeedBox( pos, index ) == KErrNotFound ) )
            {
            Seed( iAquaticBox[ index ] );
            }
        }

    // Right
    pos = TPoint( aquatic.Position().iX + 1, aquatic.Position().iY );
    if ( FindInAquaticBox( pos, index ) == KErrNone )
        {
        if ( ( iAquaticBox[ index ].Type() == aquatic.Type()
            || iAquaticBox[ index ].Type() == EStarFish )
            && ( FindInSeedBox( pos, index ) == KErrNotFound ) )
            {
            Seed( iAquaticBox[ index ] );
            }
        }

    // Up
    pos = TPoint( aquatic.Position().iX, aquatic.Position().iY - 1 );
    if ( FindInAquaticBox( pos, index ) == KErrNone )
        {
        if ( ( iAquaticBox[ index ].Type() == aquatic.Type()
            || iAquaticBox[ index ].Type() == EStarFish )
            && ( FindInSeedBox( pos, index ) == KErrNotFound ) )
            {
            Seed( iAquaticBox[ index ] );
            }
        }
        
    // Down
    pos = TPoint( aquatic.Position().iX, aquatic.Position().iY + 1 );
    if ( FindInAquaticBox( pos, index ) == KErrNone )
        {
        if ( ( iAquaticBox[ index ].Type() == aquatic.Type()
            || iAquaticBox[ index ].Type() == EStarFish )
            && ( FindInSeedBox( pos, index ) == KErrNotFound ) )
            {
            Seed( iAquaticBox[ index ] );
            }
        }
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::Crop
// ----------------------------------------------------------------------------
//
void CStrategyComboBehavior::Crop()
    {
    FUNC_LOG;
    RArray<TAquaticData> temp;
    for ( TInt n = 0; n < iSeedBox.Count(); n++ )
        temp.Append( iSeedBox[n] );
 
    for ( TInt i = 0; i < temp.Count(); i++ )
        {
        TInt err( KErrNone );
        TInt count( 0 );
        TInt index( -1 );    
        TPoint pos( temp[ i ].Position() );

        err = FindInSeedBox( TPoint( pos.iX -1, pos.iY ), index );
        if ( err != KErrNotFound )
            {
            count++;
            }
        err = FindInSeedBox( TPoint( pos.iX + 1, pos.iY ), index );
        if ( err != KErrNotFound )
            {
            count++;
            }
        
        err = FindInSeedBox( TPoint( pos.iX, pos.iY-1 ), index );
        if ( err != KErrNotFound )
            {
            count++;
            }
        err = FindInSeedBox( TPoint( pos.iX, pos.iY+1 ), index );
        if ( err != KErrNotFound )
            {
            count++;
            }
        
        if ( count <= 1 )
            {
            FindInSeedBox( pos, index );
            iSeedBox.Remove( index);
            continue;
            }
        
        count = 0;
               err = FindInSeedBox( TPoint( pos.iX - 1, pos.iY - 1 ), index );
        if ( err != KErrNotFound )
            {
            count++;
            }
        err = FindInSeedBox( TPoint( pos.iX + 1, pos.iY - 1 ), index );
        if ( err != KErrNotFound )
            {
            count++;
            }
        
        err = FindInSeedBox( TPoint( pos.iX - 1, pos.iY + 1 ), index );
        if ( err != KErrNotFound )
            {
            count++;
            }
        err = FindInSeedBox( TPoint( pos.iX + 1, pos.iY + 1 ), index );
        if ( err != KErrNotFound )
            {
            count++;
            }
        if ( count == 0 )
        {
            FindInSeedBox( pos, index );
            iSeedBox.Remove(index );
            continue;
        }
        
        }
    temp.Close();
    }

// ----------------------------------------------------------------------------
// CStrategyComboBehavior::MoveToSeedbox
// ----------------------------------------------------------------------------
//
TInt CStrategyComboBehavior::MoveToSeedbox( const TAquaticData& aAquatic )
    {
    FUNC_LOG;
    TInt index ( 0 );
    if ( FindInAquaticBox( aAquatic.Position(), index ) == KErrNone
        && FindInSeedBox( aAquatic.Position(), index ) == KErrNotFound )
        {
        iSeedBox.Append( aAquatic );    
        iAquaticBox.Remove( index );
        return KErrNone;
        }
    return KErrNotFound;
    }

// End of file
