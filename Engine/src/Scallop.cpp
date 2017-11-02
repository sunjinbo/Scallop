/* ====================================================================
 * File: Scallop.cpp
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "Scallop.h"
#include "EngineCommon.h"
#include "AquaticObserver.h"
#include "AquaticHandler.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScallop::NewL
// ----------------------------------------------------------------------------
//
CScallop* CScallop::NewL( MAquaticObserver& aObserver, MAquaticHandler& aHandler )
    {
    CScallop* self = new (ELeave) CScallop( aObserver, aHandler );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CScallop::~CScallop
// ----------------------------------------------------------------------------
//
CScallop::~CScallop()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScallop::ActivateL
// ----------------------------------------------------------------------------
//
void CScallop::ActivateL( TInt aX, TInt aY )
    {
    FUNC_LOG;
    CScaPath* scaPath = CScaPath::NewLC( *this );
    // Building map.
    RArray<TPoint> map;
    CleanupClosePushL( map );
    for ( TInt i = 0; i < KMainMatrixWidth; i++ )
        for ( TInt j = 0; j < KMainMatrixHeight; j++ )
            {
            TAquaticData aquatic( iObserver.Aquatic( i, j ) );
            if ( aquatic.IsMature() ) {
                map.Append( aquatic.Position() );
                }
            }
    scaPath->BuildMap( map );
    map.Close();
    CleanupStack::PopAndDestroy( &map );
    // Searching target.
    scaPath->Search( iAquaticData.Position(), TPoint( aX, aY ) );
    CleanupStack::PopAndDestroy(); // scaPath
    scaPath = NULL;
    }

// ----------------------------------------------------------------------------
// CScallop::Path
// ----------------------------------------------------------------------------
//
void CScallop::Path( const RArray<TPoint>& aPath )
    {
    FUNC_LOG;
    RArray<TAquaticData> path;
    TInt count( aPath.Count() );
    for ( TInt i = 0; i < aPath.Count(); i++ )
        {
        TAquaticData aquatic( iAquaticData.Type(), aPath[ i ] );
        aquatic.SetMature();
        path.Append( aquatic );
        }
    iHandler.MoveAquatic( path );
    path.Close();
    }

// ----------------------------------------------------------------------------
// CScallop::CScallop
// ----------------------------------------------------------------------------
//
CScallop::CScallop( MAquaticObserver& aObserver, MAquaticHandler& aHandler )
    : CAquatic( aObserver, aHandler )
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScallop::ConstructL
// ----------------------------------------------------------------------------
//
void CScallop::ConstructL()
    {
    FUNC_LOG;
    // CAquatic::ConstructL();
    }

// ----------------------------------------------------------------------------
// CScallop::DoClick
// ----------------------------------------------------------------------------
//
void CScallop::DoClick( TInt aX, TInt aY )
    {
    FUNC_LOG;
    aX, aY;
    }

// End of file
