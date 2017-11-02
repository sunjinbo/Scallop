/* ====================================================================
 * File: GameLevelMgr.cpp
 * Created: 09/16/09
 * Modified: 09/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <eikenv.h>
#include <bautils.h>
#include <AknUtils.h>
#include "GameLevelMgr.h"
#include "GameLevel.h"
#include "Scorekeeper.h"
#include "AquaticCreator.h"
#include "ScaLogger.h"

// CONSTANTS
_LIT( KScaEngineResourceFile, "\\resource\\apps\\scaengine.rsc" );


// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CGameLevelMgr::NewL
// ----------------------------------------------------------------------------
//
CGameLevelMgr* CGameLevelMgr::NewL( TInt aResId, const TDesC& aResPath )
    {
    CGameLevelMgr* self = CGameLevelMgr::NewLC( aResId, aResPath );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::NewLC
// ----------------------------------------------------------------------------
//
CGameLevelMgr* CGameLevelMgr::NewLC( TInt aResId, const TDesC& aResPath )
    {
    CGameLevelMgr* self = new (ELeave) CGameLevelMgr;
    CleanupStack::PushL( self );
    self->ConstructL( aResId, aResPath );
    return self;
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::~CGameLevelMgr
// ----------------------------------------------------------------------------
//
CGameLevelMgr::~CGameLevelMgr()
    {
    FUNC_LOG;
    iGameLevelArray.ResetAndDestroy();
    delete iResPath;
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::Path
// ----------------------------------------------------------------------------
//
void CGameLevelMgr::GetPath( TDes& aPath ) const
    {
    FUNC_LOG;
    aPath.Append( *iResPath );
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::Start
// ----------------------------------------------------------------------------
//
void CGameLevelMgr::Start( TInt aLevelID )
    {
    FUNC_LOG;
    iLevelID = NearestLevelID( aLevelID );
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::Next
// ----------------------------------------------------------------------------
//
TBool CGameLevelMgr::Next()
    {
    FUNC_LOG;
    TBool retVal( EFalse );
    if ( iLevelID < MaxLevelID() )
        {
        iLevelID++;
        iLevelID = NearestLevelID( iLevelID );
        retVal = ETrue;
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::GameLevel
// ----------------------------------------------------------------------------
//
CGameLevel* CGameLevelMgr::GameLevel() const
    {
    FUNC_LOG;
    TInt ix( Find( iLevelID ) );
    return iGameLevelArray[ ix ];
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::CGameLevelMgr
// ----------------------------------------------------------------------------
//
CGameLevelMgr::CGameLevelMgr()
    : iCoeEnv( *CCoeEnv::Static() )
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::ConstructL
// ----------------------------------------------------------------------------
//
void CGameLevelMgr::ConstructL( TInt aResId, const TDesC& aResPath )
    {
    FUNC_LOG;
    // Load resource file
    RFs& fileSession = iCoeEnv.FsSession();
    TFileName rscFileName( KScaEngineResourceFile );
    TInt err = CompleteWithAppPath( rscFileName );
    INFO_1( "srcFileName = %S", &rscFileName );
    if ( err != KErrNotSupported )
        {
        INFO( "Getting application path failed!" );
        User::LeaveIfError( err );
        }

    // Get the exact filename of the resource file
    BaflUtils::NearestLanguageFile( fileSession, rscFileName );
    INFO_1( "srcFileName = %S", &rscFileName );
    // Check if the resource file exists or not
    if ( ! BaflUtils::FileExists( fileSession, rscFileName ) )
        {
        INFO( "The RSC file is not exist!" );
        User::Leave( KErrNotFound );
        }
    TRAP( err, iResFileOffset = iCoeEnv.AddResourceFileL( rscFileName ) );
    INFO( "Add to resource file successfully!!!" );
    TResourceReader reader;
    iCoeEnv.CreateResourceReaderLC( reader, aResId );
    INFO( "Create resource reader successfully!!!" );
    TRAPD( error, ReadLevelsL( reader ) );
    if ( error )
        {
        INFO( "Read Levels failed!!!" );
        iGameLevelArray.ResetAndDestroy();
        User::Leave( error );
        }
    
    CleanupStack::PopAndDestroy(); // reader
    iCoeEnv.DeleteResourceFile( iResFileOffset );
    iResFileOffset = 0;
    
    // Save path
    iResPath =  HBufC::NewL( aResPath.Length() );
    TPtr text( iResPath->Des() );
    text.Copy( aResPath );
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::ReadLevelsL
// ----------------------------------------------------------------------------
//
void CGameLevelMgr::ReadLevelsL( TResourceReader& aReader )
    {
    FUNC_LOG;
    iIgnoreList = (aReader.ReadUint8() == 0) ? EFalse : ETrue;

    // The second WORD contains the number 
    // of DATA structs within the resource
    TInt number = aReader.ReadInt16();

    // Add all newly created CGameLevel objects to the array
    for ( TInt ix = 0; ix < number; ix++ )
        {
        CGameLevel* gameLevel = CGameLevel::NewL( aReader, *this );
        iGameLevelArray.Append( gameLevel );
        }
    // Sorts these game levels by id
    Sort();
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::Sort
// ----------------------------------------------------------------------------
//
void CGameLevelMgr::Sort()
    {
    FUNC_LOG;
    TLinearOrder<CGameLevel> order( CGameLevel::Compare );
    iGameLevelArray.Sort( order );
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::Find
// ----------------------------------------------------------------------------
//
TInt CGameLevelMgr::Find( TInt aId ) const
    {
    FUNC_LOG;
    TInt retVal ( KErrNotFound );
    for ( TInt ix = 0; ix < iGameLevelArray.Count(); ix++ )
        {
        CGameLevel* gameLevel = iGameLevelArray[ ix ];
        if ( gameLevel->Id() == aId )
            {
            retVal = ix;
            break;
            }
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::MaxLevelID
// ----------------------------------------------------------------------------
//
TInt CGameLevelMgr::MaxLevelID() const
    {
    FUNC_LOG;
    TInt count( iGameLevelArray.Count() );
    TInt maxIx( count - 1 );
    if ( count > 0 )
        {
        CGameLevel* level = iGameLevelArray[ maxIx ];
        return level->Id();
        }
    return -1;
    }

// ----------------------------------------------------------------------------
// CGameLevelMgr::NearestLevelID
// ----------------------------------------------------------------------------
//
TInt CGameLevelMgr::NearestLevelID( TInt aId ) const
    {
    FUNC_LOG;
    TInt maxId( MaxLevelID() );
    if ( aId < maxId )
        {
        for ( TInt ix = aId; ix <= maxId; ix++ )
            {
            if ( KErrNotFound != Find( ix ) )
                {
                return ix;
                }
            }
        }
    return maxId;
    }

// End of file
