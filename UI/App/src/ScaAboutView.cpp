/* ====================================================================
 * File: ScaAboutView.cpp
 * Created: 10/23/09
 * Modified: 03/27/09
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
#include "ScaAboutView.h"
#include "ScaAboutContainer.h"
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
// CScaAboutView::NewL
// ---------------------------------------------------------------------------
// 
CScaAboutView* CScaAboutView::NewL( CScaAppUi& aAppUi )
    {
    CScaAboutView* self = new (ELeave) CScaAboutView( aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScaAboutView::~CScaAboutView
// ---------------------------------------------------------------------------
// 
CScaAboutView::~CScaAboutView()
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaAboutView::Id
// ---------------------------------------------------------------------------
// 
TUid CScaAboutView::Id() const
    {
    return KScaAboutViewId;
    }

// ---------------------------------------------------------------------------
// CScaAboutView::DoActivateL
// ---------------------------------------------------------------------------
// 
void CScaAboutView::DoActivateL( const TVwsViewId& , TUid , const TDesC8& )
    {
    FUNC_LOG;
    iContainer = CScaAboutContainer::NewL( iAppUi.ClientRect(), iAppUi, *iResReader );
    iContainer->SetBackgroundL( R_SCALLOP_BAK_ABOUTVIEW );
    iContainer->SetMenuBarL( R_SCALLOP_MENUBAR_EMPTYBACK );
    AppUi()->AddToViewStackL( *this, iContainer );
    }

// ---------------------------------------------------------------------------
// CScaAboutView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CScaAboutView::DoDeactivate()
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
// CScaAboutView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CScaAboutView::HandleClientRectChange()
    {
    FUNC_LOG;
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------------------------
// CScaAboutView::CScaAboutView
// ---------------------------------------------------------------------------
//
CScaAboutView::CScaAboutView( CScaAppUi& aAppUi )
    : iFs( CCoeEnv::Static()->FsSession() ), iAppUi( aAppUi )
    { // No implementation required.
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaAboutView::ConstructL
// ---------------------------------------------------------------------------
//
void CScaAboutView::ConstructL()
    {
    FUNC_LOG;
    BaseConstructL( R_SCALLOP_VIEW );
    TFileName fileName;
    fileName.Append( KResFileName );
    iResReader = CResReader::NewL( iFs, fileName );
    }

// End of File
