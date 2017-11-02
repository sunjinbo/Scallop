/* ====================================================================
 * File: ClassicEngineFactory.cpp
 * Created: 08/16/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <coemain.h>
#include <f32file.h>
#include <ScaEngine.rsg>
#include "ClassicEngineFactory.h"
#include "ClassicComboBehavior.h"
#include "ClassicScorekeeper.h"
#include "ScaEngine.h"
#include "GameLevelMgr.h"
#include "ScaLogger.h"

// CONSTANTS
_LIT( KClassicResFolder, "classic" );
_LIT( KDoubleBackslash, "\\" );

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CClassicEngineFactory::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CClassicEngineFactory* CClassicEngineFactory::NewL()
    {
    CClassicEngineFactory* self = new (ELeave) CClassicEngineFactory;
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CClassicEngineFactory::~CClassicEngineFactory
// ----------------------------------------------------------------------------
//
CClassicEngineFactory::~CClassicEngineFactory()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CClassicEngineFactory::ScaEngine
// ----------------------------------------------------------------------------
//
CEngineBase* CClassicEngineFactory::ScaEngineL( MEngineObserver& aObserver )
    {
    FUNC_LOG;
    CScaEngine* engine = CScaEngine::NewLC( aObserver );
    CClassicComboBehavior* combo = CClassicComboBehavior::NewL();
    engine->SetComboBehavior( combo ); // transfer ownership
    TFileName path;
    User::LeaveIfError( GetPrivatePath( path ) );
    path.Append( KClassicResFolder );
    path.Append( KDoubleBackslash );
    CGameLevelMgr* levelMgr = 
        CGameLevelMgr::NewL( R_SCALLOP_GAMELEVELLIST_CLASSIC, path );
    engine->SetGameLevelMgr( levelMgr ); // transfer ownership
    CClassicScorekeeper* scorekeeper = CClassicScorekeeper::NewL( *engine );
    engine->SetScorekeeper( scorekeeper ); // transfer ownership
    CleanupStack::Pop(); // engine
    return engine;
    }

// ----------------------------------------------------------------------------
// CClassicEngineFactory::ConstructL
// ----------------------------------------------------------------------------
//
void CClassicEngineFactory::ConstructL()
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CClassicEngineFactory::CClassicEngineFactory
// ----------------------------------------------------------------------------
//
CClassicEngineFactory::CClassicEngineFactory()
    : iFs( CCoeEnv::Static()->FsSession() )
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CClassicEngineFactory::GetPrivatePath
// ----------------------------------------------------------------------------
//
TInt CClassicEngineFactory::GetPrivatePath( TFileName& aPath )
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
