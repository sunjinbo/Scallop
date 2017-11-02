/* ====================================================================
 * File: ScaAppUi.cpp
 * Created: 10/23/09
 * Modified: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <avkon.hrh>
#include <eikbtgpc.h>
#include <Button.h>
#include <Scallop.rsg>
#include "ScaAppUi.h"
#include "ScaWelcomeView.h"
#include "ScaMenuView.h"
#include "ScaGameView.h"
#include "ScaHelpView.h"
#include "ScaAboutView.h"
#include "ScaOptionView.h"
#include "ScaRecordView.h"
#include "ScaState.h"
#include "ScaState.hrh"
#include "Scallop.hrh"
#include "ScaViewIds.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CScaAppUi::~CScaAppUi
// ---------------------------------------------------------------------------
// 
CScaAppUi::~CScaAppUi()
    {
    FUNC_LOG;
    delete iState;
    }

// ---------------------------------------------------------------------------
// CScaAppUi::ConstructL
// ---------------------------------------------------------------------------
// 
void CScaAppUi::ConstructL()
    {
    FUNC_LOG;
    BaseConstructL();

    Cba()->MakeVisible( EFalse ); 
    StatusPane()->MakeVisible( EFalse );

    iWelcomeView = CScaWelcomeView::NewL( *this );
    AddViewL( iWelcomeView );

    iMenuView = CScaMenuView::NewL( *this );
    AddViewL( iMenuView );
    
    iGameView = CScaGameView::NewL( *this );
    AddViewL( iGameView );
    
    iHelpView = CScaHelpView::NewL( *this );
    AddViewL( iHelpView );
    
    iAboutView = CScaAboutView::NewL( *this );
    AddViewL( iAboutView );
    
    iOptionView = CScaOptionView::NewL( *this );
    AddViewL( iOptionView );
    
    iRecordView = CScaRecordView::NewL( *this );
    AddViewL( iRecordView );
    
    iCurrentViewId = KScaWelcomeViewId;
    iState = CWelcomeState::NewL( *this );
    SetDefaultViewL( *iWelcomeView );

    }

// ---------------------------------------------------------------------------
// CScaAppUi::ActivateViewL
// ---------------------------------------------------------------------------
//
void CScaAppUi::ActivateViewL( TUid aViewId )
    {
    FUNC_LOG;
    INFO_1( "Current view id is %d", aViewId );
    iCurrentViewId = aViewId;
    ActivateLocalViewL( aViewId );
    }

// ---------------------------------------------------------------------------
// CScaAppUi::Quit
// ---------------------------------------------------------------------------
//
void CScaAppUi::Quit()
    {
    FUNC_LOG;
    //Exit();
    INFO( "We start to exit our Scallop application now!!!" );
    User::Exit( 0 );
    }

// ---------------------------------------------------------------------------
// CScaAppUi::SetState
// Ownship tranfer
// ---------------------------------------------------------------------------
//
void CScaAppUi::SetState( CScaState* aState )
    {
    FUNC_LOG;
    delete iState;
    iState = NULL;
    iState = aState;
    }

// ---------------------------------------------------------------------------
// CScaAppUi::SetMenuTitleResourceId
// ---------------------------------------------------------------------------
//
void CScaAppUi::SetMenuTitleResourceId( TInt aMenuTitleResourceId )
    {
    FUNC_LOG;
    if ( iCurrentViewId == KScaGameViewId )
        {
        iGameView->SetMenuTitleResourceId( aMenuTitleResourceId );
        }
    }

// ----------------------------------------------------------------------------
// CScaAppUi::Start
// ----------------------------------------------------------------------------
//
void CScaAppUi::Start()
    {
    FUNC_LOG;
    if ( iCurrentViewId == KScaGameViewId )
        {
        iGameView->Start();
        }
    }

// ----------------------------------------------------------------------------
// CScaAppUi::Stop
// ----------------------------------------------------------------------------
//
void CScaAppUi::Stop()
    {
    FUNC_LOG;
    if ( iCurrentViewId == KScaGameViewId )
        {
        iGameView->Stop();
        }
    }

// ----------------------------------------------------------------------------
// CScaAppUi::Pause
// ----------------------------------------------------------------------------
//
void CScaAppUi::Pause()
    {
    FUNC_LOG;
    if ( iCurrentViewId == KScaGameViewId )
        {
        iGameView->Pause();
        }
    }

// ----------------------------------------------------------------------------
// CScaAppUi::Restart
// ----------------------------------------------------------------------------
//
void CScaAppUi::Restart()
    {
    FUNC_LOG;
    if ( iCurrentViewId == KScaGameViewId )
        {
        iGameView->Restart();
        }
    }

// ----------------------------------------------------------------------------
// CScaAppUi::Resume
// ----------------------------------------------------------------------------
//
void CScaAppUi::Resume()
    {
    FUNC_LOG;
    if ( iCurrentViewId == KScaGameViewId )
        {
        iGameView->Resume();
        }
    }

// ----------------------------------------------------------------------------
// CScaAppUi::FuncKey
// ----------------------------------------------------------------------------
//
void CScaAppUi::FuncKey()
    {
    FUNC_LOG;
    if ( iCurrentViewId == KScaGameViewId )
        {
        iGameView->FuncKey();
        }
    }

// ----------------------------------------------------------------------------
// CScaAppUi::Failed
// ----------------------------------------------------------------------------
//
void CScaAppUi::Failed()
    {
    FUNC_LOG;
    iState->HandleCommandL( EStateFailed );
    }

// ---------------------------------------------------------------------------
// CScaAppUi::HandleResourceChangeL
// ---------------------------------------------------------------------------
//
void CScaAppUi::HandleResourceChangeL( TInt aType )
    {
    FUNC_LOG;
    CAknAppUi::HandleResourceChangeL( aType );    
    }

// ---------------------------------------------------------------------------
// CScaAppUi::HandleButtonEventL
// ---------------------------------------------------------------------------
//
void CScaAppUi::HandleButtonEventL( const CButton* aBtn )
    {
    FUNC_LOG;
    INFO_1( "Button event is %d", aBtn->Id() );
    switch( aBtn->Id() )
        {
        case EScallopCmdWelcome:
            iState->HandleCommandL( EStateTimeout );
            break;
        case EScallopCmdStart:
            iState->HandleCommandL( EStateStart );
            break;
        case EScallopCmdOption:
            iState->HandleCommandL( EStateOption );
            break;
        case EScallopCmdRecord:
            iState->HandleCommandL( EStateRecord );
            break;
        case EScallopCmdHelp:
            iState->HandleCommandL( EStateHelp );
            break;
        case EScallopCmdQuit:
            iState->HandleCommandL( EStateQuit );
            break;
        case EScallopCmdBack:
            iState->HandleCommandL( EStateBack );
            break;
        case EScallopCmdPause:
            iState->HandleCommandL( EStatePause );
            break;
        case EScallopCmdResume:
            iState->HandleCommandL( EStateResume );
            break;
        case EScallopCmdStop:
            iState->HandleCommandL( EStateStop );
            break;
        case EScallopCmdRestart:
            iState->HandleCommandL( EStateRestart );
            break;
        case EScallopCmdAbout:
            iState->HandleCommandL( EStateAbout );
            break;
        case EScallopCmdClear:
            iState->HandleCommandL( EStateClear);
            break;
        case EScallopCmdSound:
        case EScallopCmdMode:
            break;
        default:
            break;
        }
    }

// End of File
