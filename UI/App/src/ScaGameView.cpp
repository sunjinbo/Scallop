/* ====================================================================
 * File: ScaGameView.cpp
 * Created: 10/23/09
 * Modified: 11/06/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <aknviewappui.h>
#include <aknconsts.h>
#include <akndef.h>
#include <aknutils.h>
#include <akntitle.h>
#include <barsread.h>
#include <coemain.h>
#include <Scallop.rsg>
#include <ResReader.h>
#include "ScaGameView.h"
#include "ScaGameContainer.h"
#include "ScaAppUi.h"
#include "Scallop.hrh"
#include "ScaViewIds.h"
#include "ScaLogger.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KResFileName, "z:\\resource\\apps\\scallop.rsc" );
#else
_LIT( KResFileName, "\\resource\\apps\\scallop.rsc" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CScaGameView::NewL
// ---------------------------------------------------------------------------
// 
CScaGameView* CScaGameView::NewL( CScaAppUi& aAppUi )
    {
    CScaGameView* self = new (ELeave) CScaGameView( aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScaGameView::~CScaGameView
// ---------------------------------------------------------------------------
// 
CScaGameView::~CScaGameView()
    { // No implementation required
    }

// ---------------------------------------------------------------------------
// CScaGameView::SetMenuTitleResourceId
// ---------------------------------------------------------------------------
// 
void CScaGameView::SetMenuTitleResourceId( TInt aMenuTitleResourceId )
    {
    FUNC_LOG;
    if ( iContainer )
        {
        iContainer->SetMenuBarL( aMenuTitleResourceId );
        }
    }

// ----------------------------------------------------------------------------
// CScaGameView::Start
// ----------------------------------------------------------------------------
//
void CScaGameView::Start()
    {
    FUNC_LOG;
    iContainer->Start();
    }

// ----------------------------------------------------------------------------
// CScaGameView::Stop
// ----------------------------------------------------------------------------
//
void CScaGameView::Stop()
    {
    FUNC_LOG;
    iContainer->Stop();
    }

// ----------------------------------------------------------------------------
// CScaGameView::Pause
// ----------------------------------------------------------------------------
//
void CScaGameView::Pause()
    {
    FUNC_LOG;
    iContainer->Pause();
    }

// ----------------------------------------------------------------------------
// CScaGameView::Restart
// ----------------------------------------------------------------------------
//
void CScaGameView::Restart()
    {
    FUNC_LOG;
    iContainer->Restart();
    }

// ----------------------------------------------------------------------------
// CScaGameView::Resume
// ----------------------------------------------------------------------------
//
void CScaGameView::Resume()
    {
    FUNC_LOG;
    iContainer->Resume();
    }

// ----------------------------------------------------------------------------
// CScaGameView::FuncKey
// ----------------------------------------------------------------------------
//
void CScaGameView::FuncKey()
    {
    FUNC_LOG;
    iContainer->FuncKey();
    }

// ---------------------------------------------------------------------------
// CScaGameView::Id
// ---------------------------------------------------------------------------
// 
TUid CScaGameView::Id() const
    {
    return KScaGameViewId;
    }

// ---------------------------------------------------------------------------
// CScaGameView::DoActivateL
// ---------------------------------------------------------------------------
// 
void CScaGameView::DoActivateL( const TVwsViewId& , TUid , const TDesC8& )
    {
    FUNC_LOG;
    iContainer = CScaGameContainer::NewL( iAppUi.ClientRect(), iAppUi, *iResReader );
    iContainer->SetBackgroundL( R_SCALLOP_BAK_GAMEVIEW );
    iContainer->SetMenuBarL( R_SCALLOP_MENUBAR_PAUSEBACK );
    AppUi()->AddToViewStackL( *this, iContainer );
    iContainer->Start();
    }

// ---------------------------------------------------------------------------
// CScaGameView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CScaGameView::DoDeactivate()
    {
    FUNC_LOG;
    if ( iContainer )
        {
        AppUi()->RemoveFromStack( iContainer );
        delete iContainer;
        iContainer = NULL;
        }
    }

// ---------------------------------------------------------------------------
// CScaGameView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CScaGameView::HandleClientRectChange()
    {
    FUNC_LOG;
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------------------------
// CScaGameView::CScaGameView
// ---------------------------------------------------------------------------
//
CScaGameView::CScaGameView( CScaAppUi& aAppUi )
    : iFs( CCoeEnv::Static()->FsSession() ), iAppUi( aAppUi )
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaGameView::ConstructL
// ---------------------------------------------------------------------------
//
void CScaGameView::ConstructL()
    {
    FUNC_LOG;
    BaseConstructL( R_SCALLOP_VIEW );
    TFileName fileName;
    fileName.Append( KResFileName );
    iResReader = CResReader::NewL( iFs, fileName );
    }

// End of File
