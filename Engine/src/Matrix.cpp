/* ====================================================================
 * File: Matrix.cpp
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "Matrix.h"
#include "ComboBehavior.h"
#include "EngineCommon.h"
#include "Aquatic.h"
#include "ScaEngine.pan"
#include "MatrixObserver.h"
#include "Scallop.h"
#include "StarFish.h"
#include "FuncKeyUtils.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CMatrix::NewL
// Creates a new instance of this class.
// ----------------------------------------------------------------------------
//
CMatrix* CMatrix::NewL( MMatrixObserver& aObserver )
    {
    CMatrix* self = new (ELeave) CMatrix( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CMatrix::~CMatrix
// ----------------------------------------------------------------------------
//
CMatrix::~CMatrix()
    {
    FUNC_LOG;
    delete iPath;
    iAquaticArray.ResetAndDestroy();
    iAquaticArray.Close();
    delete iFuncKeyUtils;
    }

// ----------------------------------------------------------------------------
// CMatrix::ClickL
// ----------------------------------------------------------------------------
//
TBool CMatrix::ClickL( TInt aX, TInt aY )
    {
    FUNC_LOG;
    TBool retVal( EFalse );
    TInt index( 0 );
    TInt err = Find( TPoint( aX, aY ), index );
    switch( err )
        {
        case KErrNone:
            {
            CAquatic* aquatic( iAquaticArray[ index ] );
            TAquaticData aquaticData( aquatic->AquaticData() );
            if ( iAquaticArray[ index ] == iSelectedAquatic )
                {
                if ( aquaticData.Type() > EYellowScallop )
                    {
                    aquatic->ActivateL();
                    retVal = ETrue;
                    }
                UnselectAquatic();
                }
            else
                {
                if ( aquaticData.IsMature() )
                    {
                    UnselectAquatic();
                    SelectAquatic( *iAquaticArray[ index ] );
                    }
                else
                    {
                    if ( iSelectedAquatic )
                        {
                        if ( ( iSelectedAquatic->AquaticData().Type() >= EBlueScallop )
                        && ( iSelectedAquatic->AquaticData().Type() <= EStarFish ) )
                            {
                            iSelectedAquatic->ActivateL( aX, aY );
                            retVal = ETrue;
                            }
                        UnselectAquatic();
                        }
                    }
                }
            break;
            }
        case KErrNotFound:
            {
            if ( iSelectedAquatic )
                {
                if ( ( iSelectedAquatic->AquaticData().Type() >= EBlueScallop )
                    && ( iSelectedAquatic->AquaticData().Type() <= EStarFish ) )
                    {
                    iSelectedAquatic->ActivateL( aX, aY );
                    retVal = ETrue;
                    }
                UnselectAquatic();
                }
            break;
            }
        default:
            break;
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// CMatrix::DragL
// ----------------------------------------------------------------------------
//
TBool CMatrix::DragL( TInt aX, TInt aY )
    {
    FUNC_LOG;
    TBool retval( EFalse );
    if ( iSelectedAquatic )
        {
        BuildMap();
        TPoint start( iSelectedAquatic->AquaticData().Position() );
        TPoint end( aX, aY );
        iPath->Search( start, end );
        retval = ETrue;
        }
    return retval;
    }

// ----------------------------------------------------------------------------
// CMatrix::Clear
// ----------------------------------------------------------------------------
//
void CMatrix::Clear()
    {
    FUNC_LOG;
    RArray<TAquaticData> array;
    TInt count( iAquaticArray.Count() );
    for ( TInt ix = 0; ix < count; ix++ )
        {
        array.Append( iAquaticArray[ ix ]->AquaticData() );
        }

    if ( count > 0 )
        {
        iAquaticArray.ResetAndDestroy();
        iObserver.StateChanged( EMatrixRemoved, array );
        }
    iMatrixChanged = ETrue;
    iHasPath = EFalse;
    array.Close();
    }

// ----------------------------------------------------------------------------
// CMatrix::Maturate
// ----------------------------------------------------------------------------
//
void  CMatrix::Maturate()
    {
    FUNC_LOG;
    RArray<TAquaticData> array;
    for ( TInt i = 0; i < iAquaticArray.Count(); i++ )
        {
        TAquaticData aquatic( iAquaticArray[ i ]->AquaticData() );
        if ( ! aquatic.IsMature() )
            {
            aquatic.SetMature();
            iAquaticArray[ i ]->SetAquaticData( aquatic );
            array.Append( aquatic );
            }
        }
    iObserver.StateChanged( EMatrixMatured, array );
    array.Close();
    }

// ----------------------------------------------------------------------------
// CMatrix::Start
// ----------------------------------------------------------------------------
//
void CMatrix::Start()
    {
    for ( TInt i = 0; i < iAquaticArray.Count(); i++ )
        {
        iAquaticArray[ i ]->Awake();
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::Stop
// ----------------------------------------------------------------------------
//
void CMatrix::Stop()
    {
    for ( TInt i = 0; i < iAquaticArray.Count(); i++ )
        {
        iAquaticArray[ i ]->Sleep();
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::FuncKey
// ----------------------------------------------------------------------------
//
void CMatrix::FuncKey( TAquaticType aType )
    {
    RArray<TAquaticData> array;
    iFuncKeyUtils->SetMutatedType( aType );
    iFuncKeyUtils->GetMutatedAquatics( array );
    TInt count( array.Count() );
    for ( TInt ix = 0; ix < count; ix++ )
        {
        TPoint pos( array[ ix ].Position() );
        TRAP_IGNORE( ChangeAquaticL( pos, aType ) );
        array[ ix ].SetType( aType );
        }
    iObserver.StateChanged( EMatrixUpdated, array );
    array.Close();
    }

// ----------------------------------------------------------------------------
// CMatrix::Aquatic
// ----------------------------------------------------------------------------
//
TAquaticData CMatrix::Aquatic( TInt aX, TInt aY )
    {
    FUNC_LOG;
    TAquaticData aquatic( EAquaticNull );
    TInt index( 0 );
    TInt err = Find( TPoint( aX, aY ), index );
    if (  err == KErrNone )
        {
        aquatic = iAquaticArray[ index ]->AquaticData();
        }
    return aquatic;
    }

// ----------------------------------------------------------------------------
// CMatrix::Count
// ----------------------------------------------------------------------------
//
TInt CMatrix::Count() const
    {
    return iAquaticArray.Count();
    }

// ----------------------------------------------------------------------------
// CMatrix::AddAquaticsL
// ----------------------------------------------------------------------------
//
void CMatrix::AddAquaticsL( const RArray<TAquaticData>& aList )
    {
    FUNC_LOG;
    for ( TInt i = 0; i < aList.Count(); i++ )
        {
        CAquatic* aquatic = CreateL( aList[ i ].Type() );
        aquatic->SetAquaticData( aList[ i ] );
        iAquaticArray.Append( aquatic );
        }
    iObserver.StateChanged( EMatrixUpdated, aList );
    iMatrixChanged = ETrue;
    }

// ----------------------------------------------------------------------------
// CMatrix::ChangeAquaticL
// ----------------------------------------------------------------------------
//
void CMatrix::ChangeAquaticL( TPoint aPos, TAquaticType aNewType )
    {
    FUNC_LOG;
    TInt ix( 0 );
    TInt err = Find( aPos, ix );
    if ( err == KErrNone )
        {
        CAquatic* aquatic = iAquaticArray[ ix ];
        TAquaticData aquaticData( aquatic->AquaticData() );
        RemoveAquatic( aPos );
        CAquatic* newAquatic = CreateL( aNewType );
        aquaticData.SetType( aNewType );
        newAquatic->SetAquaticData( aquaticData );
        iAquaticArray.Append( newAquatic );
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::RemoveAquatic
// ----------------------------------------------------------------------------
//
void CMatrix::RemoveAquatic( TPoint aPos )
    {
    FUNC_LOG;
    TInt index( 0 );
    TRAPD( err, Find( aPos, index ) );
    if ( err == KErrNone )
        {
        CAquatic* aquatic = iAquaticArray[ index ];
        delete aquatic;
        aquatic = NULL;
        iAquaticArray.Remove( index );
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::RemoveAquatic
// ----------------------------------------------------------------------------
//
void CMatrix::RemoveAquatic( const RArray<TAquaticData>& aList )
    {
    FUNC_LOG;
    TInt index( 0 );
    for ( TInt i = 0; i < aList.Count(); i++ )
        {
        RemoveAquatic( aList[ i ].Position() );
        }
    iObserver.StateChanged( EMatrixReleased, aList );
    iMatrixChanged = ETrue;
    }

// ----------------------------------------------------------------------------
// CMatrix::MoveAquatic
// ----------------------------------------------------------------------------
//
void CMatrix::MoveAquatic( const RArray<TAquaticData>& aPath )
    {
    FUNC_LOG;
    TInt count( aPath.Count() );
    __ASSERT_ALWAYS( count > 1, Panic( EEngineInvalidCount ) );
    TPoint startPos( aPath[ count - 1 ].Position() );
    TPoint endPos( aPath[ 0 ].Position() );
    TInt index( 0 );
    TRAPD( err, Find( endPos, index ) );
    if ( err == KErrNone )
        {
        CAquatic* end( iAquaticArray[ index ] );
        if ( ! end->AquaticData().IsMature() )
            {
            RemoveAquatic( endPos );
            }
        }

    if ( Find( startPos, index ) == KErrNone )
        {
        CAquatic* start( iAquaticArray[ index ] );
        start->SetXY( endPos.iX, endPos.iY );
        iObserver.StateChanged( EMatrixMoved, aPath );
        iMatrixChanged = ETrue;
        }
    }

// ----------------------------------------------------------------------------
// CMatrix::Path
// ----------------------------------------------------------------------------
//
void CMatrix::Path( const RArray<TPoint>& aPath )
    {
    FUNC_LOG;
    iObserver.StateChanged( EMatrixPathDisplayed, aPath );
    }

// ----------------------------------------------------------------------------
// CMatrix::CMatrix
// ----------------------------------------------------------------------------
//
CMatrix::CMatrix( MMatrixObserver& aObserver )
    : iObserver( aObserver ), iMatrixChanged( ETrue ),iHasPath( EFalse )
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CMatrix::ConstructL
// ----------------------------------------------------------------------------
//
void CMatrix::ConstructL()
    {
    FUNC_LOG;
    iPath = CScaPath::NewL( *this );
    iFuncKeyUtils = CFuncKeyUtils::NewL( *this );
    }

// ----------------------------------------------------------------------------
// CMatrix::Find
// ----------------------------------------------------------------------------
//
TInt CMatrix::Find( const TPoint& aPos,TInt& aIndex ) const
    {
    FUNC_LOG;
    TInt err( KErrNotFound );
    for ( TInt i = 0; i < iAquaticArray.Count(); ++i )
        {
        if ( iAquaticArray[ i ]->AquaticData().Position() == aPos )
            {
            aIndex = i;
            err = KErrNone;
            break;
            }
        }
    return err;
    }

// ----------------------------------------------------------------------------
// CMatrix::CreateL
// ----------------------------------------------------------------------------
//
CAquatic* CMatrix::CreateL( TAquaticType aType )
    {
    FUNC_LOG;
    CAquatic* aquatic( NULL );
    switch( aType )
        {
        case EBlueScallop: // fall through
        case EDarkBlueScallop: // fall through
        case EGreenScallop: // fall through
        case EDarkGreenScallop: // fall through
        case ERedScallop: // fall through
        case EMulberryScallop: // fall through
        case EOrangeScallop: // fall through
        case EYellowScallop: // fall through
            {
            aquatic = CScallop::NewL( *this, *this );
            aquatic->SetType( aType );
            break;
            }
        case EStarFish:
            {
            aquatic = CStarFish::NewL( *this, *this );
            break;
            }
        case ETurtle: // fall through
        case EShark: // fall through
        case EOctopus: // fall through
        case ECuttleFish: // fall through
        case ESeaCrab: // fall through
        case EJellyfish: // fall through
            {
            aquatic = CStarFish::NewL( *this, *this );
            break;
            }
            break;
        default:
            break;
        }
    return aquatic;
    }

// ----------------------------------------------------------------------------
// CMatrix::SelectAquatic
// ----------------------------------------------------------------------------
//
void CMatrix::SelectAquatic( CAquatic& aAquatic )
    {
    FUNC_LOG;
    RArray<TAquaticData> array;
    aAquatic.SetSelected( ETrue );
    iSelectedAquatic = &aAquatic;
    array.Append( aAquatic.AquaticData() );
    iObserver.StateChanged( EMatrixSelected, array );
    array.Close();
    }

// ----------------------------------------------------------------------------
// CMatrix::UnselectAquatic
// ----------------------------------------------------------------------------
//
void CMatrix::UnselectAquatic()
    {
    FUNC_LOG;
    if ( iSelectedAquatic )
    	{
        RArray<TAquaticData> array;
        array.Append( iSelectedAquatic->AquaticData() );
        iSelectedAquatic->SetSelected( EFalse );
        iSelectedAquatic = NULL;
        iObserver.StateChanged( EMatrixUnselected, array );
        array.Close();
    	}
    }

// ----------------------------------------------------------------------------
// CMatrix::BuildMap
// ----------------------------------------------------------------------------
//
void CMatrix::BuildMap()
    {
    FUNC_LOG;
    if ( iMatrixChanged )
        {
        // Building map.
        RArray<TPoint> map;
        for ( TInt i = 0; i < iAquaticArray.Count(); i++ )
            {
            TAquaticData aquatic( iAquaticArray[ i ]->AquaticData() );
            if ( aquatic.IsMature() ) {
                map.Append( aquatic.Position() );
                }
            }
        iPath->BuildMap( map );
        map.Close();

        iMatrixChanged = EFalse;
        }
    }

// End of file
