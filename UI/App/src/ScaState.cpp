/* ====================================================================
 * File: ScaState.cpp
 * Created: 10/17/09
 * Modified: 11/07/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDES
#include <Scallop.rsg>
#include "ScaState.h"
#include "ScaState.hrh"
#include "Scallop.hrh"
#include "ScaViewIds.h"
#include "ScaAppUi.h"
#include "ScaLogger.h"

// ======== MEMBER FUNCTIONS ========

// -----------------------------------------------------------------------------
// CScaState::~CScaState
// Destructor
// -----------------------------------------------------------------------------
//
CScaState::~CScaState()
    { // no implementation required
    }

// -----------------------------------------------------------------------------
// CScaState::ConstructL
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CScaState::ConstructL()
    { // no implementation required
    }

// -----------------------------------------------------------------------------
// CScaState::CScaState
// -----------------------------------------------------------------------------
//
CScaState::CScaState( CScaAppUi& aAppUi ) : iAppUi( aAppUi )
    { // no implementation required
    }

//*******************************************************//
//                 STATE SUB-CLASSES
// not all methods are over riddnen by these sub-state
// classes, they only implement methods where their 
// behavior differs
//*******************************************************//

///////////////////////////////////////
///     CWelcomeState
///////////////////////////////////////

// ---------------------------------------------------------------------------
// CWelcomeState::NewL
// ---------------------------------------------------------------------------
//
CWelcomeState* CWelcomeState::NewL( CScaAppUi& aAppUi )
    {
    CWelcomeState* self = new(ELeave) CWelcomeState( aAppUi );   
    CleanupStack::PushL( self );  
    self->ConstructL();
    CleanupStack::Pop();
    return self;  
    }

// ---------------------------------------------------------------------------
// CWelcomeState::~CWelcomeState
// ---------------------------------------------------------------------------
//
CWelcomeState::~CWelcomeState()
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CWelcomeState::HandleCommandL
// ---------------------------------------------------------------------------
//
void CWelcomeState::HandleCommandL( TInt aCmd )
    {
    switch( aCmd )
        {
        case EStateTimeout:
            iAppUi.ActivateViewL( KScaMenuViewId );
            CMenuState* menuState = CMenuState::NewL( iAppUi );
            iAppUi.SetState( menuState );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CWelcomeState::CWelcomeState
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CWelcomeState::CWelcomeState( CScaAppUi& aAppUi )
    : CScaState( aAppUi )
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CWelcomeState::ConstructL
// ---------------------------------------------------------------------------
//
void CWelcomeState::ConstructL()
    { // no implementation required
    }


///////////////////////////////////////
///     CMenuState
///////////////////////////////////////

// ---------------------------------------------------------------------------
// CMenuState::NewL
// ---------------------------------------------------------------------------
//
CMenuState* CMenuState::NewL( CScaAppUi& aAppUi )
    {
    CMenuState* self = new(ELeave) CMenuState( aAppUi );
    CleanupStack::PushL( self );  
    self->ConstructL();
    CleanupStack::Pop();
    return self;  
    }

// ---------------------------------------------------------------------------
// CMenuState::~CMenuState
// ---------------------------------------------------------------------------
//
CMenuState::~CMenuState()
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CMenuState::HandleCommandL
// ---------------------------------------------------------------------------
//
void CMenuState::HandleCommandL( TInt aCmd )
    {
    switch( aCmd )
        {
        case EStateStart:
            iAppUi.ActivateViewL( KScaGameViewId );
            //iAppUi.Start();
            CPlayState* playState = CPlayState::NewL( iAppUi );
            iAppUi.SetState( playState );
            break;
        case EStateOption:
            iAppUi.ActivateViewL( KScaOptionViewId );
            COptionState* optionState = COptionState::NewL( iAppUi );
            iAppUi.SetState( optionState );
            break;
        case EStateRecord:
            iAppUi.ActivateViewL( KScaRecordViewId );
            CRecordState* recordState = CRecordState::NewL( iAppUi );
            iAppUi.SetState( recordState );
            break;
        case EStateHelp:
            iAppUi.ActivateViewL( KScaHelpViewId );
            CHelpState* helpState = CHelpState::NewL( iAppUi );
            iAppUi.SetState( helpState );
            break;
        case EStateQuit:
            iAppUi.Quit();
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CMenuState::CMenuState
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CMenuState::CMenuState( CScaAppUi& aAppUi )
    : CScaState( aAppUi )
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CMenuState::ConstructL
// ---------------------------------------------------------------------------
//
void CMenuState::ConstructL()
    { // no implementation required
    }


///////////////////////////////////////
///     CPlayState
///////////////////////////////////////

// ---------------------------------------------------------------------------
// CPlayState::NewL
// ---------------------------------------------------------------------------
//
CPlayState* CPlayState::NewL( CScaAppUi& aAppUi )
    {
    CPlayState* self = new(ELeave) CPlayState( aAppUi );
    CleanupStack::PushL( self );  
    self->ConstructL();
    CleanupStack::Pop();
    return self;  
    }

// ---------------------------------------------------------------------------
// CPlayState::~CPlayState
// ---------------------------------------------------------------------------
//
CPlayState::~CPlayState()
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CPlayState::HandleCommandL
// ---------------------------------------------------------------------------
//
void CPlayState::HandleCommandL( TInt aCmd )
    {
    switch( aCmd )
        {
        case EStatePause:
            iAppUi.Pause();
            iAppUi.SetMenuTitleResourceId( R_SCALLOP_MENUBAR_RESUMESTOP );
            CPauseState* pauseState = CPauseState::NewL( iAppUi );
            iAppUi.SetState( pauseState );
            break;
        case EStateBack:
            iAppUi.ActivateViewL( KScaMenuViewId );
            CMenuState* menuState = CMenuState::NewL( iAppUi );
            iAppUi.SetState( menuState );
            break;
        case EStateFailed:
            iAppUi.SetMenuTitleResourceId( R_SCALLOP_MENUBAR_RESTARTBACK );
            CRestartState* restartState = CRestartState::NewL( iAppUi );
            iAppUi.SetState( restartState );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CPlayState::CPlayState
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPlayState::CPlayState( CScaAppUi& aAppUi )
    : CScaState( aAppUi )
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CPlayState::ConstructL
// ---------------------------------------------------------------------------
//
void CPlayState::ConstructL()
    { // no implementation required
    }


///////////////////////////////////////
///     CRestartState
///////////////////////////////////////

// ---------------------------------------------------------------------------
// CRestartState::NewL
// ---------------------------------------------------------------------------
//
CRestartState* CRestartState::NewL( CScaAppUi& aAppUi )
    {
    CRestartState* self = new(ELeave) CRestartState( aAppUi );
    CleanupStack::PushL( self );  
    self->ConstructL();
    CleanupStack::Pop();
    return self;  
    }

// ---------------------------------------------------------------------------
// CRestartState::~CRestartState
// ---------------------------------------------------------------------------
//
CRestartState::~CRestartState()
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CRestartState::HandleCommandL
// ---------------------------------------------------------------------------
//
void CRestartState::HandleCommandL( TInt aCmd )
    {
    switch( aCmd )
        {
        case EStateRestart:
            iAppUi.Restart();
            iAppUi.ActivateViewL( KScaMenuViewId );
            CMenuState* menuState = CMenuState::NewL( iAppUi );
            iAppUi.SetState( menuState );
            break;
        case EStateBack:
            iAppUi.SetMenuTitleResourceId( R_SCALLOP_MENUBAR_PAUSEBACK );
            CPlayState* playState = CPlayState::NewL( iAppUi );
            iAppUi.SetState( playState );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CRestartState::CRestartState
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CRestartState::CRestartState( CScaAppUi& aAppUi )
    : CScaState( aAppUi )
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CRestartState::ConstructL
// ---------------------------------------------------------------------------
//
void CRestartState::ConstructL()
    { // no implementation required
    }


///////////////////////////////////////
///     CPauseState
///////////////////////////////////////

// ---------------------------------------------------------------------------
// CPauseState::NewL
// ---------------------------------------------------------------------------
//
CPauseState* CPauseState::NewL( CScaAppUi& aAppUi )
    {
    CPauseState* self = new(ELeave) CPauseState( aAppUi );
    CleanupStack::PushL( self );  
    self->ConstructL();
    CleanupStack::Pop();
    return self;  
    }

// ---------------------------------------------------------------------------
// CPauseState::~CPauseState
// ---------------------------------------------------------------------------
//
CPauseState::~CPauseState()
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CPauseState::HandleCommandL
// ---------------------------------------------------------------------------
//
void CPauseState::HandleCommandL( TInt aCmd )
    {
    switch( aCmd )
        {
        case EStateStop:
            iAppUi.Stop();
            iAppUi.ActivateViewL( KScaMenuViewId );
            CMenuState* menuState = CMenuState::NewL( iAppUi );
            iAppUi.SetState( menuState );
            break;
        case EStateResume:
            iAppUi.Resume();
            iAppUi.SetMenuTitleResourceId( R_SCALLOP_MENUBAR_PAUSEBACK );
            CPlayState* playState = CPlayState::NewL( iAppUi );
            iAppUi.SetState( playState );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CPauseState::CPauseState
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CPauseState::CPauseState( CScaAppUi& aAppUi )
    : CScaState( aAppUi )
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CPauseState::ConstructL
// ---------------------------------------------------------------------------
//
void CPauseState::ConstructL()
    { // no implementation required
    }

///////////////////////////////////////
///     CHelpState
///////////////////////////////////////

// ---------------------------------------------------------------------------
// CHelpState::NewL
// ---------------------------------------------------------------------------
//
CHelpState* CHelpState::NewL( CScaAppUi& aAppUi )
    {
    CHelpState* self = new(ELeave) CHelpState( aAppUi );
    CleanupStack::PushL( self );  
    self->ConstructL();
    CleanupStack::Pop();
    return self;  
    }

// ---------------------------------------------------------------------------
// CHelpState::~CHelpState
// ---------------------------------------------------------------------------
//
CHelpState::~CHelpState()
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CHelpState::HandleCommandL
// ---------------------------------------------------------------------------
//
void CHelpState::HandleCommandL( TInt aCmd )
    {
    switch( aCmd )
        {
        case EStateBack:
            iAppUi.ActivateViewL( KScaMenuViewId );
            CMenuState* menuState = CMenuState::NewL( iAppUi );
            iAppUi.SetState( menuState );
            break;
        case EStateAbout:
            iAppUi.ActivateViewL( KScaAboutViewId );
            CAboutState* aboutState = CAboutState::NewL( iAppUi );
            iAppUi.SetState( aboutState );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CHelpState::CHelpState
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CHelpState::CHelpState( CScaAppUi& aAppUi )
    : CScaState( aAppUi )
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CHelpState::ConstructL
// ---------------------------------------------------------------------------
//
void CHelpState::ConstructL()
    { // no implementation required
    }
    

///////////////////////////////////////
///     CAboutState
///////////////////////////////////////

// ---------------------------------------------------------------------------
// CAboutState::NewL
// ---------------------------------------------------------------------------
//
CAboutState* CAboutState::NewL( CScaAppUi& aAppUi )
    {
    CAboutState* self = new(ELeave) CAboutState( aAppUi );
    CleanupStack::PushL( self );  
    self->ConstructL();
    CleanupStack::Pop();
    return self;  
    }

// ---------------------------------------------------------------------------
// CAboutState::~CAboutState
// ---------------------------------------------------------------------------
//
CAboutState::~CAboutState()
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CAboutState::HandleCommandL
// ---------------------------------------------------------------------------
//
void CAboutState::HandleCommandL( TInt aCmd )
    {
    switch( aCmd )
        {
        case EStateBack:
            iAppUi.ActivateViewL( KScaMenuViewId );
            CMenuState* menuState = CMenuState::NewL( iAppUi );
            iAppUi.SetState( menuState );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CAboutState::CAboutState
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CAboutState::CAboutState( CScaAppUi& aAppUi )
    : CScaState( aAppUi )
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CAboutState::ConstructL
// ---------------------------------------------------------------------------
//
void CAboutState::ConstructL()
    { // no implementation required
    }


///////////////////////////////////////
///     COptionState
///////////////////////////////////////

// ---------------------------------------------------------------------------
// COptionState::NewL
// ---------------------------------------------------------------------------
//
COptionState* COptionState::NewL( CScaAppUi& aAppUi )
    {
    COptionState* self = new(ELeave) COptionState( aAppUi );
    CleanupStack::PushL( self );  
    self->ConstructL();
    CleanupStack::Pop();
    return self;  
    }

// ---------------------------------------------------------------------------
// COptionState::~COptionState
// ---------------------------------------------------------------------------
//
COptionState::~COptionState()
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// COptionState::HandleCommandL
// ---------------------------------------------------------------------------
//
void COptionState::HandleCommandL( TInt aCmd )
    {  
    switch( aCmd )
        {
        case EStateBack:
            iAppUi.ActivateViewL( KScaMenuViewId );
            CMenuState* menuState = CMenuState::NewL( iAppUi );
            iAppUi.SetState( menuState );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// COptionState::COptionState
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
COptionState::COptionState( CScaAppUi& aAppUi )
    : CScaState( aAppUi )
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// COptionState::ConstructL
// ---------------------------------------------------------------------------
//
void COptionState::ConstructL()
    { // no implementation required
    }


///////////////////////////////////////
///     CRecordState
///////////////////////////////////////

// ---------------------------------------------------------------------------
// CRecordState::NewL
// ---------------------------------------------------------------------------
//
CRecordState* CRecordState::NewL( CScaAppUi& aAppUi )
    {
    CRecordState* self = new(ELeave) CRecordState( aAppUi );
    CleanupStack::PushL( self );  
    self->ConstructL();
    CleanupStack::Pop();
    return self;  
    }

// ---------------------------------------------------------------------------
// CRecordState::~CRecordState
// ---------------------------------------------------------------------------
//
CRecordState::~CRecordState()
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CRecordState::HandleCommandL
// ---------------------------------------------------------------------------
//
void CRecordState::HandleCommandL( TInt aCmd )
    {
    switch( aCmd )
        {
        case EStateBack:
            iAppUi.ActivateViewL( KScaMenuViewId );
            CMenuState* menuState = CMenuState::NewL( iAppUi );
            iAppUi.SetState( menuState );
            break;
        case EStateClear:
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CRecordState::CRecordState
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CRecordState::CRecordState( CScaAppUi& aAppUi )
    : CScaState( aAppUi )
    { // no implementation required
    }

// ---------------------------------------------------------------------------
// CRecordState::ConstructL
// ---------------------------------------------------------------------------
//
void CRecordState::ConstructL()
    { // no implementation required
    }
    

// End of File
