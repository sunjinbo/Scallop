/* ====================================================================
 * File: ScaGameContainer.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <akndef.h>
#include <aknutils.h>
#include <barsread.h>
#include <EngineCommon.h>
#include <ClassicEngineFactory.h>
#include <StrategyEngineFactory.h>
#include <Aquatic.hrh>
#include <AquaticData.h>
#include <EngineBase.h>
#include <ButtonObserver.h>
#include <ResReader.h>
#include <Button.h>
#include <Scoreboard.h>
#include <ProgressBar.h>
#include <FuncKeyPane.h>
#include <InfoComponent.h>
#include <Scallop.rsg>
#include "ScaGameContainer.h"
#include "ScaLayoutManager.h"
#include "ScaAppUi.h"
#include "ScaLogger.h"

// CONSTANTS
const TInt KInfoComponentTimer = 25;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScaGameContainer::~CScaGameContainer
// ----------------------------------------------------------------------------
//
CScaGameContainer* CScaGameContainer::NewL( const TRect& aRect, 
    MButtonObserver& aObserver, 
    MResReader& aReader )
    {
    CScaGameContainer* self = new (ELeave) CScaGameContainer( aObserver, aReader );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::~CScaGameContainer
// ----------------------------------------------------------------------------
//
CScaGameContainer::~CScaGameContainer()
    {
    FUNC_LOG;
    delete iClassicEngineFactory;
    delete iStrategyEngineFactory;
    delete iEngine;
    delete iLayoutManager;
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::Start
// ----------------------------------------------------------------------------
//
void CScaGameContainer::Start()
    {
    FUNC_LOG;
    TRAP_IGNORE( iEngine->HandleCommandL( EEngineCmdStart ) );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::Stop
// ----------------------------------------------------------------------------
//
void CScaGameContainer::Stop()
    {
    FUNC_LOG;
    TRAP_IGNORE( 
        iEngine->HandleCommandL( EEngineCmdStop ) 
        );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::Pause
// ----------------------------------------------------------------------------
//
void CScaGameContainer::Pause()
    {
    FUNC_LOG;
    TRAP_IGNORE( 
        iEngine->HandleCommandL( EEngineCmdPause ) 
        );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::Restart
// ----------------------------------------------------------------------------
//
void CScaGameContainer::Restart()
    {
    FUNC_LOG;
    TRAP_IGNORE( 
        iEngine->HandleCommandL( EEngineCmdRestart ) 
        );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::Resume
// ----------------------------------------------------------------------------
//
void CScaGameContainer::Resume()
    {
    FUNC_LOG;
    TRAP_IGNORE( 
        iEngine->HandleCommandL( EEngineCmdResume ) 
        );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::FuncKey
// ----------------------------------------------------------------------------
//
void CScaGameContainer::FuncKey()
    {
    FUNC_LOG;
    TRAP_IGNORE( 
        iEngine->HandleCommandL( EEngineCmdFuncKey ) 
        );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::StateChanged
// ----------------------------------------------------------------------------
//
void CScaGameContainer::StateChanged( TEngineAction aAction )
    {
    FUNC_LOG;
    INFO_1( "The type of engine action is %d", aAction );
    switch( aAction )
        {
        case EEngineActionStart:
            break;
        case EEngineActionPause:
            break;
        case EEngineActionStop:
            break;
        case EEngineActionLevelExpired: // fall through
        case EEngineActionLevelFailed: // fall through
            static_cast<CScaAppUi*>( iEikonEnv->AppUi() )->Failed();
            break;
        case EEngineActionGameOver:
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::AuqaticChanged
// ----------------------------------------------------------------------------
//
void CScaGameContainer::AuqaticChanged( TAquaticAction aAction, const RArray<TAquaticData>& aList )
    {
    FUNC_LOG;
    INFO_1( "The type of aquatic action is %d", aAction );
    TRAP_IGNORE( 
        iMatrix->UpdateAquaticL( aAction, aList ) 
        );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::PathChanged
// ----------------------------------------------------------------------------
//
void CScaGameContainer::PathChanged( TPathAction aAction, const RArray<TPoint>& aList )
    {
    FUNC_LOG;
    INFO_1( "The type of path action is %d", aAction );
    switch( aAction )
        {
        case EPathActionDisplayed:
            iMatrix->ShowPath( aList );
            break;
        case EPathActionDisappeared:
            iMatrix->ClearPath();
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::ScorekeeperChanged
// ----------------------------------------------------------------------------
//
void CScaGameContainer::ScorekeeperChanged( TScorekeeperAction aAction, TInt aValue )
    {
    FUNC_LOG;
    INFO_2( "The type of path action is %d, and its value is %d", aAction, aValue );
    switch( aAction )
        {
        case EScorekeeperActionLevel:
            iLevel->SetValue( aValue );
            break;
        case EScorekeeperActionScore:
            iScore->SetValue( aValue );
            iMatrix->ShowTips( aValue );
            break;
        case EScorekeeperActionBonus:
            iBonus->SetValue( aValue );
            iMatrix->ShowTips( aValue );
            break;
        case EScorekeeperActionMoves:
            break;
        case EScorekeeperActionProgress:
            iProgress->SetAndDraw( aValue );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::PromptChanged
// ----------------------------------------------------------------------------
//
void CScaGameContainer::PromptChanged( const TDesC& aText )
    {
    iInfoComponent->SetVisible( ETrue );
    iInfoComponent->SetTextL( aText );
    iInfoComponent->RestartTimer( KInfoComponentTimer );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::FuncKeyChanged
// ----------------------------------------------------------------------------
//
void CScaGameContainer::FuncKeyChanged( TAquaticType aType, TInt aValue )
    {
    FUNC_LOG;
    INFO_2( "The type of FuncKey action is %d, and its value is %d", aType, aValue );

    iFuncKey->SetAndDraw( aType, aValue );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::ClickL
// ----------------------------------------------------------------------------
//
void CScaGameContainer::ClickL( TInt aX, TInt aY )
    {
    FUNC_LOG;
    INFO_2( "Click - x : %d, y : %d", aX, aY );
    iEngine->ClickL( aX, aY );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::DragL
// ----------------------------------------------------------------------------
//
void CScaGameContainer::DragL( TInt aX, TInt aY )
    {
    FUNC_LOG;
    INFO_2( "Drag - x : %d, y : %d", aX, aY );
    iEngine->DragL( aX, aY );
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::CheckedL
// ----------------------------------------------------------------------------
//
void CScaGameContainer::CheckedL( TBool /*aCheck*/ )
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::OfferKeyEventL
// ----------------------------------------------------------------------------
//
TKeyResponse CScaGameContainer::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    FUNC_LOG;
    if ( aType == EEventKey && aKeyEvent.iCode == '5' ) // for test
        {
        User::Exit( 0 );
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::CScaGameContainer
// ----------------------------------------------------------------------------
//
CScaGameContainer::CScaGameContainer( 
    MButtonObserver& aObserver, MResReader& aReader  )
    : CBaseContainer( aObserver, aReader )
    { // No implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaGameContainer::ConstructL
// ----------------------------------------------------------------------------
//
void CScaGameContainer::ConstructL( const TRect& aRect )
    {
    FUNC_LOG;
    CBaseContainer::ConstructL( aRect );

    // Controls
    iLayoutManager = CScaLayoutManager::NewL();
    iLayoutManager->ResolutionChanged();

    InitComponentArrayL();
    
    TRect theRect;
    iLayoutManager->LayoutRect( EMatrix, theRect );
    iMatrix = CMatrix::NewL( *iGraphicsManager, theRect );
    iMatrix->SetObserver( this );
    iMatrix->SetContainerWindowL( *this );
    Components().AppendLC( iMatrix );
    CleanupStack::Pop( iMatrix );

    iLayoutManager->LayoutRect( ELevel, theRect );
    iLevel = CScoreboard::NewL( *iGraphicsManager, theRect );
    iLevel->SetContainerWindowL( *this );
    ConstructFromResourceL( R_SCALLOP_SCOREBOARD_LEVEL );
    Components().AppendLC( iLevel );
    CleanupStack::Pop( iLevel );

    iLayoutManager->LayoutRect( EScore, theRect );
    iScore = CScoreboard::NewL( *iGraphicsManager, theRect );
    iScore->SetContainerWindowL( *this );
    ConstructFromResourceL( R_SCALLOP_SCOREBOARD_SCORE );
    Components().AppendLC( iScore );
    CleanupStack::Pop( iScore );

    iLayoutManager->LayoutRect( EBonus, theRect );
    iBonus = CScoreboard::NewL( *iGraphicsManager, theRect );
    iBonus->SetContainerWindowL( *this );
    ConstructFromResourceL( R_SCALLOP_SCOREBOARD_BONUS );
    Components().AppendLC( iBonus );
    CleanupStack::Pop( iBonus );

    iLayoutManager->LayoutRect( EProgress, theRect );
    iProgress = CProgressBar::NewL( *iGraphicsManager, theRect );
    iProgress->SetContainerWindowL( *this );
    ConstructFromResourceL( R_SCALLOP_PROGRESS );
    Components().AppendLC( iProgress );
    CleanupStack::Pop( iProgress );

    iLayoutManager->LayoutRect( EFuncKey, theRect );
    iFuncKey = CFuncKeyPane::NewL( *iGraphicsManager, theRect );
    iFuncKey->SetContainerWindowL( *this );
    Components().AppendLC( iFuncKey );
    CleanupStack::Pop( iFuncKey );

    iLayoutManager->LayoutRect( EInfoComponent, theRect );
    iInfoComponent = CInfoComponent::NewL( *iGraphicsManager, theRect );
    iInfoComponent->SetContainerWindowL( *this );
    iInfoComponent->SetObserver( *this );
    iInfoComponent->SetResReader( iReader );
    INFO( "SetInfoResourceIdL - begins" );
    iInfoComponent->SetInfoResourceIdL( R_SCALLOP_GAME_INFOCOMPONENT );
    INFO( "SetInfoResourceIdL - ends" );
    iInfoComponent->RestartTimer( KInfoComponentTimer );
    Components().AppendLC( iInfoComponent );
    CleanupStack::Pop( iInfoComponent );

    // Engine
    iClassicEngineFactory = CClassicEngineFactory::NewL();
    iStrategyEngineFactory = CStrategyEngineFactory::NewL();
    iEngine = iStrategyEngineFactory->ScaEngineL( *this );

    }

// ----------------------------------------------------------------------------
// CScaGameContainer::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
void CScaGameContainer::ConstructFromResourceL( TInt aResId )
    {
    FUNC_LOG;

    HBufC8* buffer = iReader.ResourceData( aResId );
    TResourceReader reader;
    reader.SetBuffer( buffer );

    switch( aResId )
        {
        case R_SCALLOP_SCOREBOARD_LEVEL:
            {
            INFO( "Construct level from resource - begins" );
            iLevel->ConstructFromResourceL( reader );
            INFO( "Construct level from resource - ends" );
            }
            break;

        case R_SCALLOP_SCOREBOARD_SCORE:
            {
            INFO( "Construct score from resource - begins" );
            iScore->ConstructFromResourceL( reader );
            INFO( "Construct score from resource - ends" );
            }
            break;

        case R_SCALLOP_SCOREBOARD_BONUS:
            {
            INFO( "Construct bonus from resource - begins" );
            iBonus->ConstructFromResourceL( reader );
            INFO( "Construct bonus from resource - ends" );
            }
            break;

        case R_SCALLOP_PROGRESS:
            {
            INFO( "Construct progress from resource - begins" );
            iProgress->ConstructFromResourceL( reader );
            INFO( "Construct progress from resource - ends" );
            }
            break;

        default:
            break;
        }

    }

// End of File
