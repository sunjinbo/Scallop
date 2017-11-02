/* ====================================================================
 * File: ScaHelpView.cpp
 * Created: 10/23/09
 * Modified: 03/15/09
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
#include <Scallop.rsg>
#include <ResReader.h>
#include "ScaHelpView.h"
#include "ScaHelpContainer.h"
#include "ScaAppUi.h"
#include "Scallop.hrh"
#include "ScaViewIds.h"
#include "ScaLogger.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KResourceFileName, "Z:\\resource\\apps\\Scallop.rsc" );
#else
_LIT( KResourceFileName, "\\resource\\apps\\Scallop.rsc" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CScaHelpView::NewL
// ---------------------------------------------------------------------------
// 
CScaHelpView* CScaHelpView::NewL( CScaAppUi& aAppUi )
    {
    CScaHelpView* self = new (ELeave) CScaHelpView( aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScaHelpView::~CScaHelpView
// ---------------------------------------------------------------------------
// 
CScaHelpView::~CScaHelpView()
    { // No implementation required
    }

// ---------------------------------------------------------------------------
// CScaHelpView::Id
// ---------------------------------------------------------------------------
// 
TUid CScaHelpView::Id() const
    {
    return KScaHelpViewId;
    }

// ---------------------------------------------------------------------------
// CScaHelpView::DoActivateL
// ---------------------------------------------------------------------------
// 
void CScaHelpView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/ )
    {
    FUNC_LOG;
    iContainer = CScaHelpContainer::NewL( iAppUi.ClientRect(), iAppUi, *iResReader );
    iContainer->SetBackgroundL( R_SCALLOP_BAK_HELPVIEW );
    iContainer->SetMenuBarL( R_SCALLOP_MENUBAR_ABOUTBACK );
    AppUi()->AddToViewStackL( *this, iContainer );
    }

// ---------------------------------------------------------------------------
// CScaHelpView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CScaHelpView::DoDeactivate()
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
// CScaHelpView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CScaHelpView::HandleClientRectChange()
    {
    FUNC_LOG;
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------------------------
// CScaHelpView::CScaMenuView
// ---------------------------------------------------------------------------
//
CScaHelpView::CScaHelpView( CScaAppUi& aAppUi )
    : iFs( CCoeEnv::Static()->FsSession() ), 
    iAppUi( aAppUi )
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaHelpView::ConstructL
// ---------------------------------------------------------------------------
//
void CScaHelpView::ConstructL()
    {
    FUNC_LOG;
    BaseConstructL( R_SCALLOP_VIEW );
    TFileName fileName;
    fileName.Append( KResourceFileName );
    iResReader = CResReader::NewL( iFs, fileName );
    }

// End of File
