/* ====================================================================
 * File: ScaWelcomeView.cpp
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
#include "ScaWelcomeView.h"
#include "ScaWelcomeContainer.h"
#include "ScaAppUi.h"
#include "Scallop.hrh"
#include "ScaMenuView.h"
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
// CScaWelcomeView::NewL
// ---------------------------------------------------------------------------
// 
CScaWelcomeView* CScaWelcomeView::NewL( CScaAppUi& aAppUi )
    {
    CScaWelcomeView* self = new (ELeave) CScaWelcomeView( aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScaWelcomeView::~CScaWelcomeView
// ---------------------------------------------------------------------------
// 
CScaWelcomeView::~CScaWelcomeView()
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaWelcomeView::Id
// ---------------------------------------------------------------------------
// 
TUid CScaWelcomeView::Id() const
    {
    return KScaWelcomeViewId;
    }

// ---------------------------------------------------------------------------
// CScaWelcomeView::DoActivateL
// ---------------------------------------------------------------------------
// 
void CScaWelcomeView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/ )
    {
    FUNC_LOG;
    iContainer = CScaWelcomeContainer::NewL( iAppUi.ClientRect(), iAppUi, *iResReader );
    AppUi()->AddToViewStackL( *this, iContainer );
    }

// ---------------------------------------------------------------------------
// CScaWelcomeView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CScaWelcomeView::DoDeactivate()
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
// CScaWelcomeView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CScaWelcomeView::HandleClientRectChange()
    {
    FUNC_LOG;
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------------------------
// CScaWelcomeView::CScaMenuView
// ---------------------------------------------------------------------------
//
CScaWelcomeView::CScaWelcomeView( CScaAppUi& aAppUi )
    : iFs( CCoeEnv::Static()->FsSession() ), iAppUi( aAppUi )
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaWelcomeView::ConstructL
// ---------------------------------------------------------------------------
//
void CScaWelcomeView::ConstructL()
    {
    FUNC_LOG;
    BaseConstructL( R_SCALLOP_VIEW );
    TFileName fileName;
    fileName.Append( KResourceFileName );
    iResReader = CResReader::NewL( iFs, fileName );
    }

// End of File
