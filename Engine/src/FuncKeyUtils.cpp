/* ====================================================================
 * File: FuncKeyUtils.cpp
 * Created: 10/06/09
 * Modified: 10/06/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILE
#include "FuncKeyUtils.h"
#include "EngineDefines.h"
#include "Matrix.h"
#include "AquaticData.h"
#include "ScaLogger.h"

// CONSTANTS
const TInt KMaxMutatedNumber = 15;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CFuncKeyUtils::NewL
// ----------------------------------------------------------------------------
//
CFuncKeyUtils* CFuncKeyUtils::NewL( CMatrix& aMatrix )
    {
    CFuncKeyUtils* self = CFuncKeyUtils::NewLC( aMatrix );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CFuncKeyUtils::NewLC
// ----------------------------------------------------------------------------
//
CFuncKeyUtils* CFuncKeyUtils::NewLC( CMatrix& aMatrix )
    {
    CFuncKeyUtils* self = new (ELeave) CFuncKeyUtils( aMatrix );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CFuncKeyUtils::~CFuncKeyUtils
// ----------------------------------------------------------------------------
//
CFuncKeyUtils::~CFuncKeyUtils()
    {
    FUNC_LOG;
    iMutatedArray.Close();
    iKnownArray.Close();
    iUnknownArray.Close();
    }

// ----------------------------------------------------------------------------
// CFuncKeyUtils::SetMutatedType
// ----------------------------------------------------------------------------
//
void CFuncKeyUtils::SetMutatedType( TAquaticType aType )
    {
    FUNC_LOG;
    iMutatedType = aType;
    }

// ----------------------------------------------------------------------------
// CFuncKeyUtils::GetMutatedAquatics
// ----------------------------------------------------------------------------
//
void CFuncKeyUtils::GetMutatedAquatics( RArray<TAquaticData>& aArray )
    {
    FUNC_LOG;
    if ( iMutatedType != EAquaticNull )
        {
        Reset();
        Initialise();
        
        TInt mutatedNum( 0 );
        TInt index( 0 );
        TBool condition( EFalse );
        do
        {
        condition = EFalse;
        for ( TInt i = index; i < iKnownArray.Count(); i++ )
            {
            TAquaticData aquaticData( iKnownArray[i] );
            TPoint pos( aquaticData.Position() );
            TFixedArray<TPoint, EOTNum> ota;
            ota[EOTUp] = TPoint( pos.iX, pos.iY - 1 );
            ota[EOTDown] = TPoint( pos.iX, pos.iY + 1 );
            ota[EOTLeft] = TPoint( pos.iX - 1, pos.iY );
            ota[EOTRight] = TPoint( pos.iX + 1, pos.iY );
            for ( TInt j = 0; j < EOTNum; j++ )
                {
                TInt ix( Find( iUnknownArray, ota[ j ] ) );
                if ( ix != KErrNotFound )
                    {
                    iMutatedArray.Append( iUnknownArray[ix] );
                    iUnknownArray.Remove( ix );
                    }
                }
            }
        
        index = iKnownArray.Count();
        
        for ( TInt m = 0; m < iMutatedArray.Count(); m++ )
            {
            condition = ETrue;
            aArray.Append( iMutatedArray[ m ] );
            iKnownArray.Append( iMutatedArray[ m ] );
            ++mutatedNum;
            if ( mutatedNum == KMaxMutatedNumber )
                {
                condition = EFalse;
                break;
                }
            }
        iMutatedArray.Reset();
        
        }while( condition );

        }
    }

// ----------------------------------------------------------------------------
// CFuncKeyUtils::CFuncKeyUtils
// ----------------------------------------------------------------------------
//
CFuncKeyUtils::CFuncKeyUtils( CMatrix& aMatrix )
    : iMatrix( aMatrix ), iMutatedType( EAquaticNull )
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CFuncKeyUtils::ConstructL
// ----------------------------------------------------------------------------
//
void CFuncKeyUtils::ConstructL()
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CFuncKeyUtils::Initialise
// ----------------------------------------------------------------------------
//
void CFuncKeyUtils::Initialise()
    {
    FUNC_LOG;
    TInt count( iMatrix.iAquaticArray.Count() );
    for ( TInt ix = 0; ix < count; ix++ )
        {
        CAquatic* aquatic( iMatrix.iAquaticArray[ ix ] );
        TAquaticData aquaticData( aquatic->AquaticData() );
        if ( ! aquaticData.IsMature() )
            {
            continue;
            }
        
        if ( aquaticData.Type() == iMutatedType )
            {
            iKnownArray.Append( aquaticData );
            }
        else
            {
            iUnknownArray.Append( aquaticData );
            }
        }
    }

// ----------------------------------------------------------------------------
// CFuncKeyUtils::Reset
// ----------------------------------------------------------------------------
//
void CFuncKeyUtils::Reset()
    {
    FUNC_LOG;
    iMutatedArray.Reset();
    iKnownArray.Reset();
    iUnknownArray.Reset();
    }

// ----------------------------------------------------------------------------
// CFuncKeyUtils::Find
// ----------------------------------------------------------------------------
//
TInt CFuncKeyUtils::Find( const RArray<TAquaticData>& aArray, const TPoint& aPos )
    {
    TInt ix( KErrNotFound );
    TInt count( aArray.Count() );
    for ( TInt i = 0; i < count; i++ )
        {
        if ( aArray[ i ].Position() == aPos )
            {
            ix = i;
            break;
            }
        }
    return ix;
    }

// End of file
