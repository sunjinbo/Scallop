/* ====================================================================
 * File: ScaPath.cpp
 * Created: 09/09/09
 * Modified: 09/09/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "ScaPath.h"
#include "EngineCommon.h"
#include "Node.h"
#include "EngineDefines.h"
#include "ScaLogger.h"

// CONSTANTS
const TInt KOrdinateMoveCost = 10;
const TInt KLateralMoveCost = 10;
const TInt KCrabwiseMoveCost = 14; 

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScaPath::NewL
// ----------------------------------------------------------------------------
//
CScaPath* CScaPath::NewL( MScaPathObserver& aObserver )
    {
    CScaPath* self = CScaPath::NewLC( aObserver );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CScaPath::NewLC
// ----------------------------------------------------------------------------
//
CScaPath* CScaPath::NewLC( MScaPathObserver& aObserver )
    {
    CScaPath* self = new (ELeave) CScaPath( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaPath::~CScaPath
// ----------------------------------------------------------------------------
//
CScaPath::~CScaPath()
    {
    FUNC_LOG;
    iMap.Close();
    iOpenList.Close();
    iCloseList.Close();
    }

// ----------------------------------------------------------------------------
// CScaPath::Search
// ----------------------------------------------------------------------------
//
void CScaPath::Search( const TPoint& aStart, const TPoint& aEnd )
    {
    FUNC_LOG;
    if ( ! CheckValidation( aStart, aEnd ) )
        {
        return;
        }
    // Let's get started.
    iStart = aStart;
    iEnd = aEnd;

    TBool goal( EFalse );
    iCloseList.Reset();
    iOpenList.Reset();
    
    TNode start( aStart );
    start.SetG( 0 );
    start.SetH( 0 );
    iOpenList.Append( start );

    while ( iOpenList.Count() > 0 )
        {
        TNode minFNode( MinimumFInOpenList() );
        TNode& currentNode = minFNode;
        RemoveFromOpenList( currentNode.Position() );
        iCloseList.Append( currentNode );

        TPoint currentPos( currentNode.Position() );
        TFixedArray<TPoint, EOTNum> array;
        array[EOTUp] = TPoint( currentPos.iX, currentPos.iY - 1 ); // up
        array[EOTDown] = TPoint( currentPos.iX, currentPos.iY + 1 ); // down
        array[EOTLeft] = TPoint( currentPos.iX - 1, currentPos.iY ); // left
        array[EOTRight] = TPoint( currentPos.iX + 1, currentPos.iY ); // right

        for ( TInt i = 0; i < EOTNum; i++ )
            {
            if ( KErrNotFound != FindInCloseList( array[ i ] )
                || IsObstacle( array[ i ] ) )
                {
                continue;
                }
            TInt ret = FindInOpenList( array[ i ] );
            if ( KErrNotFound != ret ) // Not in open list
                {
                if ( currentNode.G() + 10 < iOpenList[ ret ].G() )
                    {
                    iOpenList[ ret ].SetParent( currentNode.Position() );
                    iOpenList[ ret ].SetG( currentNode.G() + 10 );
                    }
                }
            else // in open list
                {
                TNode tempNode( array[ i ] );
                tempNode.SetParent( currentNode.Position() );
                TInt lateralCost = KLateralMoveCost * Abs( array[ i ].iX - aEnd.iX );
                TInt ordinateCost = KOrdinateMoveCost * Abs( array[ i ].iY - aEnd.iY );
                tempNode.SetH( lateralCost + ordinateCost );
                lateralCost = KLateralMoveCost * Abs( array[ i ].iX - currentNode.Position().iX );
                ordinateCost = KOrdinateMoveCost * Abs( array[ i ].iY - currentNode.Position().iY );
                tempNode.SetG( currentNode.G() + lateralCost + ordinateCost ); // optimize later
                iOpenList.Append( tempNode );

                if ( array[ i ] == aEnd )
                    {
                    goal = ETrue;
                    break;
                    }
                }
            }

        if ( goal )
            {
            RArray<TPoint> path;
            TRAPD( err, GetPathL( path ) );
            if ( err == KErrNone )
                {
                iObserver.Path( path );
                }
            path.Close();
            break;
            }
        }
    }

// ----------------------------------------------------------------------------
// CScaPath::BuildMap
// ----------------------------------------------------------------------------
//
void CScaPath::BuildMap( const RArray<TPoint>& aMap )
    {
    FUNC_LOG;
    iMap.Reset(); // Empties the map.
    for ( TInt i = 0; i < aMap.Count(); i++ )
        {
        TPoint pos( aMap[ i ] );
        iMap.Append( pos );
        }
    }

// ----------------------------------------------------------------------------
// CScaPath::CScaPath
// ----------------------------------------------------------------------------
//
CScaPath::CScaPath( MScaPathObserver& aObserver )
    : iObserver( aObserver )
    { // no implementation requrired
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaPath::ConstructL
// ----------------------------------------------------------------------------
//
void CScaPath::ConstructL()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaPath::FindInOpenList
// Finds the first node in the array which matches
// the specified node using a sequential search and 
// a matching algorithm.
// ----------------------------------------------------------------------------
//
TInt CScaPath::FindInOpenList( const TPoint& aPos )
    {
    FUNC_LOG;
    TIdentityRelation<TNode> order(TNode::Match);
    return iOpenList.Find( TNode( aPos ), order );
    }

// ----------------------------------------------------------------------------
// CScaPath::RemoveFromOpenList
// Removes the specified node from open list.
// ----------------------------------------------------------------------------
//
void CScaPath::RemoveFromOpenList( const TPoint& aPos )
    {
    FUNC_LOG;
    TInt i = FindInOpenList( aPos );
    if ( i != KErrNotFound )
        {
        iOpenList.Remove( i );
        }
    }

// ----------------------------------------------------------------------------
// CScaPath::FindInCloseList
// Finds the first node in the array which matches
// the specified node using a sequential search and 
// a matching algorithm.
// ----------------------------------------------------------------------------
//
TInt CScaPath::FindInCloseList( const TPoint& aPos )
    {
    FUNC_LOG;
    TIdentityRelation<TNode> order(TNode::Match);
    return iCloseList.Find( TNode( aPos ), order );
    }

// ----------------------------------------------------------------------------
// CScaPath::RemoveFromCloseList
// Removes the specified node from close list.
// ----------------------------------------------------------------------------
//
void CScaPath::RemoveFromCloseList( const TPoint& aPos )
    {
    FUNC_LOG;
    TInt i = FindInCloseList( aPos );
    if ( i != KErrNotFound )
        {
        iCloseList.Remove( i );
        }
    }

// ----------------------------------------------------------------------------
// CScaPath::IsObstacle
// ----------------------------------------------------------------------------
//
TBool CScaPath::IsObstacle( const TPoint& aPos )
    {
    FUNC_LOG;
    TBool retVal ( EFalse );
    if ( ( aPos.iX >= KMainMatrixWidth ) || ( aPos.iX < 0 )
        || ( aPos.iY >= KMainMatrixHeight ) || ( aPos.iY < 0  ) )
        {
        retVal = ETrue;
        }
    else
        {
        for ( TInt i = 0; i < iMap.Count(); i++ )
            {
            if ( iMap[ i ] == aPos )
                {
                retVal = ETrue;
                break;
                }
            }
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// CScaPath::CheckValidationL
// ----------------------------------------------------------------------------
//
TBool CScaPath::CheckValidation( const TPoint& aStart, const TPoint& aEnd )
    {
    FUNC_LOG;
    TBool retVal = ETrue;
    // 1. Check the starting point if it is the same as the destination
    if ( aStart == aEnd )
        {
        retVal = EFalse;
        }

    // 2. Check the destination if it is located an obstacle.
    if ( IsObstacle( aEnd ) )
        {
        retVal = EFalse;
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// CScaPath::MinimumFInOpenList
// ----------------------------------------------------------------------------
//
TNode CScaPath::MinimumFInOpenList()
    {
    FUNC_LOG;
    TNode node;
    TInt retVal;
    TInt minF;
    TInt count( iOpenList.Count() );
    if (count )
        {
        retVal = count - 1;
        minF = iOpenList[ count - 1 ].F();
        }

    for ( TInt i = count - 1; i >= 0 ; i-- )
        {
        if ( minF > iOpenList[ i ].F() )
            {
            minF = iOpenList[ i ].F();
            retVal = i;
            }
        }
    return iOpenList[ retVal ];
    }

// ----------------------------------------------------------------------------
// CScaPath::GetPathL
// ----------------------------------------------------------------------------
//
TInt CScaPath::GetPathL( RArray<TPoint>& aPath )
    {
    FUNC_LOG;
    aPath.Reset();
    TInt ix = FindInOpenList( iEnd );
    User::LeaveIfError( ix );
    aPath.Append( iOpenList[ ix ].Position() );
    TInt count = aPath.Count() - 1;
    while ( aPath[ count ] != iStart )
        {
        TPoint parent;
        ix = FindParent( parent, aPath[ count ] );
        User::LeaveIfError( ix );
        aPath.Append( parent );
        count++;
        }
    return KErrNone;
    }

// ----------------------------------------------------------------------------
// CScaPath::FindParent
// ----------------------------------------------------------------------------
//
TInt CScaPath::FindParent( TPoint& aParent, const TPoint& aChild )
    {
    FUNC_LOG;
    TInt i = FindInOpenList( aChild );
    if ( i == KErrNotFound )
        {
        i = FindInCloseList( aChild );
        if ( i == KErrNotFound )
            {
            return KErrNotFound;
            }
        aParent = iCloseList[ i ].Parent();
        return KErrNone;
        }
    aParent = iOpenList[ i ].Parent();
    return KErrNone;
    }

// End of file
