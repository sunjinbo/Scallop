/* ====================================================================
 * File: ScaRecordView.cpp
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

#include "ScaRecordView.h"
#include "ScaRecordContainer.h"
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
// CScaRecordView::NewL
// ---------------------------------------------------------------------------
// 
CScaRecordView* CScaRecordView::NewL( CScaAppUi& aAppUi )
    {
    CScaRecordView* self = new (ELeave) CScaRecordView( aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScaRecordView::~CScaRecordView
// ---------------------------------------------------------------------------
// 
CScaRecordView::~CScaRecordView()
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaRecordView::Id
// ---------------------------------------------------------------------------
// 
TUid CScaRecordView::Id() const
    {
    return KScaRecordViewId;
    }

// ---------------------------------------------------------------------------
// CScaRecordView::DoActivateL
// ---------------------------------------------------------------------------
// 
void CScaRecordView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
    TUid /*aCustomMessageId*/, const TDesC8& /*aCustomMessage*/ )
    {
    FUNC_LOG;
    iContainer = CScaRecordContainer::NewL( iAppUi.ClientRect(), iAppUi, *iResReader );
    iContainer->SetBackgroundL( R_SCALLOP_BAK_RECORDVIEW );
    iContainer->SetMenuBarL( R_SCALLOP_MENUBAR_CLEARBACK );
    AppUi()->AddToViewStackL( *this, iContainer );
    }

// ---------------------------------------------------------------------------
// CScaRecordView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CScaRecordView::DoDeactivate()
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
// CScaRecordView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CScaRecordView::HandleClientRectChange()
    {
    FUNC_LOG;
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------------------------
// CScaRecordView::CScaMenuView
// ---------------------------------------------------------------------------
//
CScaRecordView::CScaRecordView( CScaAppUi& aAppUi )
    : iFs( CCoeEnv::Static()->FsSession() ), iAppUi( aAppUi )
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaRecordView::ConstructL
// ---------------------------------------------------------------------------
//
void CScaRecordView::ConstructL()
    {
    FUNC_LOG;
    BaseConstructL( R_SCALLOP_VIEW );
    TFileName fileName;
    fileName.Append( KResourceFileName );
    iResReader = CResReader::NewL( iFs, fileName );
    }

// End of File
