/* ====================================================================
 * File: ScaEngine.cpp
 * Created: 06/13/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "ScaEngine.h"
#include "EngineObserver.h"
#include "Matrix.h"
#include "Scorekeeper.h"
#include "ComboBehavior.h"
#include "AquaticCreator.h"
#include "ScaEngine.pan"
#include "GameLevelMgr.h"
#include "GameLevel.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScaEngine::NewL
// ----------------------------------------------------------------------------
//
CScaEngine* CScaEngine::NewL( MEngineObserver& aObserver )
    {
    CScaEngine* self = CScaEngine::NewLC( aObserver );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CScaEngine::NewLC
// ----------------------------------------------------------------------------
//
CScaEngine* CScaEngine::NewLC( MEngineObserver& aObserver )
    {
    CScaEngine* self = new (ELeave) CScaEngine( aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaEngine::~CScaEngine
// ----------------------------------------------------------------------------
//
CScaEngine::~CScaEngine()
    {
    FUNC_LOG;
    delete iMatrix;
    delete iAquaticCreator;

    delete iScorekeeper;
    delete iComboBehavior;
    delete iLevelManager;
    }

// ----------------------------------------------------------------------------
// CScaEngine::SetComboBehavior
// ----------------------------------------------------------------------------
//
void CScaEngine::SetComboBehavior( CComboBehavior* aComboBehavior )
    {
    FUNC_LOG;
    __ASSERT_ALWAYS( aComboBehavior, Panic( EEngineNullPointer ) );
    if ( iComboBehavior )
        {
        delete iComboBehavior;
        iComboBehavior = NULL;
        }
    iComboBehavior = aComboBehavior;
    iComboBehavior->SetObserver( iMatrix );
    }

// ----------------------------------------------------------------------------
// CScaEngine::SetGameLevelMgr
// ----------------------------------------------------------------------------
//
void CScaEngine::SetGameLevelMgr( CGameLevelMgr* aLevelManager )
    {
    FUNC_LOG;
    __ASSERT_ALWAYS( aLevelManager, Panic( EEngineNullPointer ) );
    if ( iLevelManager )
        {
        delete iLevelManager;
        iLevelManager = NULL;
        }
    iLevelManager = aLevelManager;
    }

// ----------------------------------------------------------------------------
// CScaEngine::SetScorekeeper
// ----------------------------------------------------------------------------
//
void CScaEngine::SetScorekeeper( CScorekeeper* aScorekeeper )
    {
    FUNC_LOG;
    __ASSERT_ALWAYS( aScorekeeper, Panic( EEngineNullPointer ) );
    if ( iScorekeeper )
        {
        delete iScorekeeper;
        iScorekeeper = NULL;
        }
    iScorekeeper = aScorekeeper;
    }

// ----------------------------------------------------------------------------
// CScaEngine::HandleCommandL
// ----------------------------------------------------------------------------
//
EXPORT_C void CScaEngine::HandleCommandL( TEngineCmd aCmd )
    {
    FUNC_LOG;
    INFO_1( "aCmd = %d", aCmd );
    switch( aCmd )
        {
        case EEngineCmdStart:
                {
                iMatrix->Clear();
                iLevelManager->Start( iScorekeeper->Level() );
                CGameLevel* level = iLevelManager->GameLevel();
                TLevelData levelData;
                levelData.iLevelID = level->Id();
                levelData.iTime = level->Time();
                levelData.iPassScore = level->Score();
                levelData.iPassBonus = level->Bonus();
                if ( level->Prompt() )
                    {
                    levelData.iPrompt.Copy( *level->Prompt() );
                    }
                iScorekeeper->SetupLevel( levelData );
                iAquaticCreator->Create( *level );
                }
                break;
        case EEngineCmdPause:
                {
                iMatrix->Stop();
                iScorekeeper->Stop();
                break;
                }
        case EEngineCmdRestart:
                {
                iMatrix->Clear();
                iScorekeeper->Clear();
                CGameLevel* level = iLevelManager->GameLevel();
                iAquaticCreator->Create( *level );
                break;
                }
        case EEngineCmdResume:
                {
                iMatrix->Start();
                iScorekeeper->Start();
                break;
                }
        case EEngineCmdStop:
                {
                iMatrix->Clear();
                iScorekeeper->Clear();
                break;
                }
        case EEngineCmdRefresh:
                {
                break;
                }
        case EEngineCmdFuncKey:
                {
                if ( iScorekeeper->IsFuncKeyFull() )
                    {
                    iMatrix->FuncKey( iScorekeeper->FuncKeyType() );
                    iScorekeeper->ClearFuncKey();
                    RArray<TAquaticData> array;
                    iComboBehavior->Combo( array );
                    iMatrix->RemoveAquatic( array );
                    array.Close();
                    }
                break;
                }
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CScaEngine::ClickL
// Handles pointer event in matrix.
// ----------------------------------------------------------------------------
//
EXPORT_C void CScaEngine::ClickL( TInt aX, TInt aY )
    {
    FUNC_LOG;
    INFO_2( "aX = %d, aY = %d", aX, aY );
    if ( iMatrix->ClickL( aX, aY ) )
        {
        RArray<TAquaticData> array;
        iComboBehavior->Combo( array );
        if ( array.Count() > 0 )
            {
            iMatrix->RemoveAquatic( array );
            iScorekeeper->FuncKey( array );
            }
        else
            {
            iMatrix->Maturate();
            iComboBehavior->Combo( array );
            if ( array.Count() > 0 )
                {
                iMatrix->RemoveAquatic( array );
                iScorekeeper->FuncKey( array );
                }
            
            if ( !iAquaticCreator->Next() )
                {
                iObserver.StateChanged( EEngineActionLevelFailed );
                iMatrix->Clear();
                iScorekeeper->Clear();
                iScorekeeper->ClearFuncKey();
                }
            }
        array.Close();
        }
    }

// ----------------------------------------------------------------------------
// CScaEngine::DragL
// ----------------------------------------------------------------------------
//
EXPORT_C void CScaEngine::DragL( TInt aX, TInt aY )
    {
    FUNC_LOG;
    INFO_2( "aX = %d, aY = %d", aX, aY );
    iMatrix->DragL( aX, aY );
    }

// ----------------------------------------------------------------------------
// CScaEngine::StateChanged
// From base class MMatrixObserver
// ----------------------------------------------------------------------------
//
void CScaEngine::StateChanged( TMatrixState aState, 
            const RArray<TAquaticData>& aList )
    {
    FUNC_LOG;
    TAquaticAction action;
    switch( aState )
        {
        case EMatrixBorn:
            {
            action = EAquaticActionBorn;
            break;
            }
        case EMatrixMatured:
            {
            action = EAquaticActionMatured;
            break;
            }
        case EMatrixMoved:
            {
            action = EAquaticActionMoved;
            break;
            }
        case EMatrixChanged:
            {
            action = EAquaticActionChanged;
            break;
            }
        case EMatrixReleased:
            {
            iScorekeeper->Dismiss( aList );
            action = EAquaticActionReleased;
            break;
            }
        case EMatrixRemoved:
            {
            action = EAquaticActionReleased;
            break;
            }
        case EMatrixUpdated:
            {
            action = EAquaticActionUpdated;
            break;
            }
        case EMatrixUnselected:
            {
            action = EAquaticActionUnselected;
            break;
            }
        case EMatrixSelected:
            {
            action = EAquaticActionSelected;
            break;
            }
        default:
            break;
        }

    iObserver.AuqaticChanged( action, aList );
    }

// ----------------------------------------------------------------------------
// CScaEngine::StateChanged
// From base class MMatrixObserver
// ----------------------------------------------------------------------------
//
void CScaEngine::StateChanged( TMatrixPathState aState, 
    const RArray<TPoint>& aList )
    {
    FUNC_LOG;
    INFO_1( "aState = %d", aState );
    switch( aState )
        {
        case EMatrixPathDisplayed:
            {
            iObserver.PathChanged( EPathActionDisplayed, aList );
            break;
            }
        case EMatrixPathDisappeared:
            {
            iObserver.PathChanged( EPathActionDisappeared, aList );
            break;
            }
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CScaEngine::StateChanged
// From base class MScorekeeperObserver
// ----------------------------------------------------------------------------
//
void CScaEngine::StateChanged( TScorekeeperState aNewState )
    {
    FUNC_LOG;
    TScorekeeperAction action;
    switch( aNewState )
        {
        case EScorekeeperLevelUpdated:
            {
            action = EScorekeeperActionLevel;
            iObserver.ScorekeeperChanged( action, iScorekeeper->Level() );
            }
            break;
        case EScorekeeperScoreUpdated:
            {
            action = EScorekeeperActionScore;
            iObserver.ScorekeeperChanged( action, iScorekeeper->Score() );
            }
            break;
        case EScorekeeperBonusUpdated:
            {
            action = EScorekeeperActionBonus;
            iObserver.ScorekeeperChanged( action, iScorekeeper->Bonus() );
            }
            break;
        case EScorekeeperMovesUpdated:
            { // Todo:
            }
            break;
        case EScorekeeperFuncKeyUpdated:
            {
            iObserver.FuncKeyChanged( 
                iScorekeeper->FuncKeyType(),
                iScorekeeper->FuncKey() 
                );
            }
            break;
        case EScorekeeperPromptUpdated:
            {
            TBuf<KPromptLen> prompt;
            prompt.Copy( *iScorekeeper->Prompt() );
            if ( prompt.Length() > 0 )
                {
                iObserver.PromptChanged( prompt );
                }
            }
            break;
        case EScorekeeperProgressUpdated:
            {
            iObserver.ScorekeeperChanged( 
                EScorekeeperActionProgress, 
                iScorekeeper->Progress() 
                );
            }
            break;
        case EScorekeeperLevelExpired:
            {
            iObserver.StateChanged( EEngineActionLevelExpired );
            iMatrix->Clear();
            iScorekeeper->Clear();
            iScorekeeper->ClearFuncKey();
            }
            break;
        case EScorekeeperLevelFailed:
            {
            iObserver.StateChanged( EEngineActionLevelFailed );
            }
            break;
        case EScorekeeperLevelCompleted:
            {
            iMatrix->Clear();
            if ( iLevelManager->Next() )
                {
                CGameLevel* level = iLevelManager->GameLevel();
                TLevelData levelData;
                levelData.iLevelID = level->Id();
                levelData.iPassScore = level->Score();
                levelData.iPassBonus = level->Bonus();
                iScorekeeper->SetupLevel( levelData );
                TAquaticType funcKeyType( iScorekeeper->FuncKeyType() );
                TBool reserve( EFalse );
                RArray<TAquaticType> array;
                level->GetAvailableType( array );
                for ( TInt i = 0; i < array.Count(); i++ )
                    {
                    if ( array[ i ] == funcKeyType )
                        {
                        reserve = ETrue;
                        break;
                        }
                    }
                array.Close();
                if ( ! reserve )
                    {
                    iScorekeeper->ClearFuncKey();
                    }
                iAquaticCreator->Create( *level );
                }
            else
                {
                iScorekeeper->Clear();
                iScorekeeper->ClearFuncKey();
                iObserver.StateChanged( EEngineActionGameOver );
                }
            }
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CScaEngine::CScaEngine
// ----------------------------------------------------------------------------
//
CScaEngine::CScaEngine( MEngineObserver& aObserver )
    : CEngineBase( aObserver )
    { // No implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaEngine::ConstructL
// ----------------------------------------------------------------------------
//
void CScaEngine::ConstructL()
    {
    FUNC_LOG;
    iMatrix = CMatrix::NewL( *this );
    iAquaticCreator = CAquaticCreator::NewL( *iMatrix, *iMatrix );
    }

// End of file
