/* ====================================================================
 * File: ScaPath.h
 * Created: 09/09/09
 * Modified: 09/09/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef SCAPATH_H
#define SCAPATH_H

// INCLUDE FILES
#include <e32base.h>

// FORWARD DECLARATIONS
class TNode;

// CLASS DECLARATION
/**
* MEngineObserver class
*
* @since S60 5.0
*/
class MScaPathObserver
    {
public: // Called when game engine state changes and observer needs to be notified.
    virtual void Path( const RArray<TPoint>& aPath ) = 0;
    };

/**
* CScaPath class
*
* A* algorithm
*
* @since S60 5.0
*/
class CScaPath : public CBase
    {
public: // Constructor and Destructor
    static CScaPath* NewL( MScaPathObserver& aObserver );
    static CScaPath* NewLC( MScaPathObserver& aObserver );
    virtual ~CScaPath();

public: // New functions
    void Search( const TPoint& aStart, const TPoint& aEnd );
    void BuildMap( const RArray<TPoint>& aMap );

private: // Constructor
    CScaPath( MScaPathObserver& iObserver );
    void ConstructL();

private: // New functions
    TInt FindInOpenList( const TPoint& aPos );
    void RemoveFromOpenList( const TPoint& aPos );
    TInt FindInCloseList( const TPoint& aPos );
    void RemoveFromCloseList( const TPoint& aPos );
    TBool IsObstacle( const TPoint& aPos );
    TBool CheckValidation( const TPoint& aStart, const TPoint& aEnd );
    TNode MinimumFInOpenList();
    TInt GetPathL( RArray<TPoint>& aPath );
    TInt FindParent( TPoint& aParent, const TPoint& aChild );

private: // Member data
    MScaPathObserver& iObserver;
    RArray<TPoint> iMap;
    RArray<TNode> iOpenList;
    RArray<TNode> iCloseList;
    TPoint iStart;
    TPoint iEnd;
    };

#endif // SCAPATH_H

// End of file
