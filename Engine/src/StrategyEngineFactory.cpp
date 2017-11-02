/* ====================================================================
 * File: StrategyEngineFactory.cpp
 * Created: 08/16/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <coemain.h>
#include <f32file.h>
#include <ScaEngine.rsg>
#include "StrategyEngineFactory.h"
#include "StrategyComboBehavior.h"
#include "StrategyScorekeeper.h"
#include "ScaEngine.h"
#include "GameLevelMgr.h"
#include "ScaLogger.h"

// CONSTANTS
_LIT( KStrategyResFolder, "strategy" );
_LIT( KDoubleBackslash, "\\" );

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CStrategyEngineFactory::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CStrategyEngineFactory* CStrategyEngineFactory::NewL()
    {
    CStrategyEngineFactory* self = new (ELeave) CStrategyEngineFactory;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CStrategyEngineFactory::~CStrategyEngineFactory
// ----------------------------------------------------------------------------
//
CStrategyEngineFactory::~CStrategyEngineFactory()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CStrategyEngineFactory::ScaEngine
// ----------------------------------------------------------------------------
//
CEngineBase* CStrategyEngineFactory::ScaEngineL( MEngineObserver& aObserver )
    {
    FUNC_LOG;
    CScaEngine* engine = CScaEngine::NewLC( aObserver );
    CStrategyComboBehavior* combo = CStrategyComboBehavior::NewL();
    engine->SetComboBehavior( combo ); // transfer ownership
    TFileName path;
    User::LeaveIfError( GetPrivatePath( path ) );
    path.Append( KStrategyResFolder );
    path.Append( KDoubleBackslash );
    CGameLevelMgr* levelMgr = 
        CGameLevelMgr::NewL( R_SCALLOP_GAMELEVELLIST_STRATEGY, path );
    engine->SetGameLevelMgr( levelMgr ); // transfer ownership
    CStrategyScorekeeper* scorekeeper = CStrategyScorekeeper::NewL( *engine );
    engine->SetScorekeeper( scorekeeper ); // transfer ownership
    CleanupStack::Pop(); // engine
    return engine;
    }

// ----------------------------------------------------------------------------
// CStrategyEngineFactory::ConstructL
// ----------------------------------------------------------------------------
//
void CStrategyEngineFactory::ConstructL()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CStrategyEngineFactory::CStrategyEngineFactory
// ----------------------------------------------------------------------------
//
CStrategyEngineFactory::CStrategyEngineFactory()
    : iFs( CCoeEnv::Static()->FsSession() )
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CStrategyEngineFactory::GetPrivatePath
// ----------------------------------------------------------------------------
//
TInt CStrategyEngineFactory::GetPrivatePath( TFileName& aPath )
    {
    FUNC_LOG;
    TInt retVal( KErrNone );
    TFileName path;	
    iFs.PrivatePath( path );
    TFindFile findFile( iFs );	
    aPath = path;
    retVal = findFile.FindByDir( path, KNullDesC );
    if ( retVal == KErrNone )
        {
        aPath = findFile.File();
        }
    return retVal;
    }

// End of file
