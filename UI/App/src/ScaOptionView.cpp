/* ====================================================================
 * File: ScaOptionView.cpp
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
#include "ScaOptionView.h"
#include "ScaOptionContainer.h"
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
// CScaOptionView::NewL
// ---------------------------------------------------------------------------
// 
CScaOptionView* CScaOptionView::NewL( CScaAppUi& aAppUi )
    {
    CScaOptionView* self = new (ELeave) CScaOptionView( aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScaOptionView::~CScaOptionView
// ---------------------------------------------------------------------------
// 
CScaOptionView::~CScaOptionView()
    { // No implementation required
    }

// ---------------------------------------------------------------------------
// CScaOptionView::Id
// ---------------------------------------------------------------------------
// 
TUid CScaOptionView::Id() const
    {
    return KScaOptionViewId;
    }

// ---------------------------------------------------------------------------
// CScaOptionView::DoActivateL
// ---------------------------------------------------------------------------
// 
void CScaOptionView::DoActivateL( const TVwsViewId& , TUid , const TDesC8& )
    {
    FUNC_LOG;
    iContainer = CScaOptionContainer::NewL( iAppUi.ClientRect(), iAppUi, *iResReader );
    iContainer->SetBackgroundL( R_SCALLOP_BAK_OPTIONVIEW );
    iContainer->SetMenuBarL( R_SCALLOP_MENUBAR_EMPTYBACK );
    AppUi()->AddToViewStackL( *this, iContainer );
    }

// ---------------------------------------------------------------------------
// CScaOptionView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CScaOptionView::DoDeactivate()
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
// CScaOptionView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CScaOptionView::HandleClientRectChange()
    {
    FUNC_LOG;
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------------------------
// CScaOptionView::CScaOptionView
// ---------------------------------------------------------------------------
//
CScaOptionView::CScaOptionView( CScaAppUi& aAppUi )
    : iFs( CCoeEnv::Static()->FsSession() ), iAppUi( aAppUi )
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaOptionView::ConstructL
// ---------------------------------------------------------------------------
//
void CScaOptionView::ConstructL()
    {
    FUNC_LOG;
    BaseConstructL( R_SCALLOP_VIEW );
    TFileName fileName;
    fileName.Append( KResFileName );
    iResReader = CResReader::NewL( iFs, fileName );
    }

// End of File
