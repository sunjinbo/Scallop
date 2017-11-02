/* ====================================================================
 * File: ScaMenuView.cpp
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
#include "ScaMenuView.h"
#include "ScaMenuContainer.h"
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
// CScaMenuView::NewL
// ---------------------------------------------------------------------------
// 
CScaMenuView* CScaMenuView::NewL( CScaAppUi& aAppUi )
    {
    CScaMenuView* self = new (ELeave) CScaMenuView( aAppUi );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScaMenuView::~CScaMenuView
// ---------------------------------------------------------------------------
// 
CScaMenuView::~CScaMenuView()
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaMenuView::Id
// ---------------------------------------------------------------------------
// 
TUid CScaMenuView::Id() const
    {
    return KScaMenuViewId;
    }

// ---------------------------------------------------------------------------
// CScaMenuView::DoActivateL
// ---------------------------------------------------------------------------
// 
void CScaMenuView::DoActivateL( const TVwsViewId& , TUid , const TDesC8& )
    {
    FUNC_LOG;
    iContainer = CScaMenuContainer::NewL( iAppUi.ClientRect(), iAppUi, *iResReader );
    iContainer->SetBackgroundL( R_SCALLOP_BAK_MENUVIEW );
    INFO( "Consturct background successfully!" );
    iContainer->SetMenuBarL( R_SCALLOP_MENUBAR_DOUBLEEMPTY );
    INFO( "Consturct menubar successfully!" )
    AppUi()->AddToViewStackL( *this, iContainer );
    }

// ---------------------------------------------------------------------------
// CScaMenuView::DoDeactivate
// ---------------------------------------------------------------------------
//
void CScaMenuView::DoDeactivate()
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
// CScaMenuView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CScaMenuView::HandleClientRectChange()
    {
    FUNC_LOG;
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------------------------
// CScaMenuView::CScaMenuView
// ---------------------------------------------------------------------------
//
CScaMenuView::CScaMenuView( CScaAppUi& aAppUi )
    : iFs( CCoeEnv::Static()->FsSession() ), iAppUi( aAppUi )
    { // No implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaMenuView::ConstructL
// ---------------------------------------------------------------------------
//
void CScaMenuView::ConstructL()
    {
    FUNC_LOG;
    BaseConstructL( R_SCALLOP_VIEW );
    TFileName fileName;
    fileName.Append( KResFileName );
    iResReader = CResReader::NewL( iFs, fileName );
    }

// End of File
