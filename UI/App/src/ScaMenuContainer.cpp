/* ====================================================================
 * File: ScaMenuContainer.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <akndef.h>
#include <aknutils.h>
#include <barsread.h>
#include <ButtonObserver.h>
#include <ResReader.h>
#include <Button.h>
#include <Scallop.rsg>
#include "ScaMenuContainer.h"
#include "ScaLayoutManager.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScaMenuContainer::~CScaMenuContainer
// ----------------------------------------------------------------------------
//
CScaMenuContainer* CScaMenuContainer::NewL(  const TRect& aRect, 
    MButtonObserver& aObserver, 
    MResReader& aReader  )
    {
    CScaMenuContainer* self = new (ELeave) CScaMenuContainer( aObserver, aReader );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaMenuContainer::~CScaMenuContainer
// ----------------------------------------------------------------------------
//
CScaMenuContainer::~CScaMenuContainer()
    {
    FUNC_LOG;
    delete iLayoutManager;
    }

// ----------------------------------------------------------------------------
// CScaMenuContainer::OfferKeyEventL
// ----------------------------------------------------------------------------
//
TKeyResponse CScaMenuContainer::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    FUNC_LOG;
    if ( aType == EEventKey && aKeyEvent.iCode == '5' ) // for test
        {
        User::Exit( 0 );
        }
    if ( aType == EEventKey && aKeyEvent.iCode == '1' ) // for test
        {
        iObserver.HandleButtonEventL( iBtnStart );
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// CScaMenuContainer::CScaMenuContainer
// ----------------------------------------------------------------------------
//
CScaMenuContainer::CScaMenuContainer( 
    MButtonObserver& aObserver, MResReader& aReader  )
    : CBaseContainer( aObserver, aReader )
    { // No implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaMenuContainer::ConstructL
// ----------------------------------------------------------------------------
//
void CScaMenuContainer::ConstructL( const TRect& aRect )
    {
    FUNC_LOG;
    CBaseContainer::ConstructL( aRect );
    INFO( "CBaseContainer works very good!" );
    
    iLayoutManager = CScaLayoutManager::NewL();
    iLayoutManager->ResolutionChanged( EPortrait );

    INFO( "CScaLayoutManager works very good!" );
    InitComponentArrayL();
    
    TRect rect;

    iLayoutManager->LayoutRect( EStart, rect );
    iBtnStart = CButton::NewL( *iGraphicsManager, rect );
    iBtnStart->SetObserver( this );
    iBtnStart->SetContainerWindowL( *this );
    ConstructBtnFromResourceL( R_SCALLOP_BTN_START );
    Components().AppendLC( iBtnStart );
    CleanupStack::Pop( iBtnStart );
    
    iLayoutManager->LayoutRect( EOption, rect );
    iBtnOption = CButton::NewL( *iGraphicsManager, rect );
    iBtnOption->SetObserver( this );
    iBtnOption->SetContainerWindowL( *this );
    ConstructBtnFromResourceL( R_SCALLOP_BTN_OPTION );
    Components().AppendLC( iBtnOption );
    CleanupStack::Pop( iBtnOption );
    
    iLayoutManager->LayoutRect( ERecord, rect );
    iBtnRecord = CButton::NewL( *iGraphicsManager, rect );
    iBtnRecord->SetObserver( this );
    iBtnRecord->SetContainerWindowL( *this );
    ConstructBtnFromResourceL( R_SCALLOP_BTN_RECORD );
    Components().AppendLC( iBtnRecord );
    CleanupStack::Pop( iBtnRecord );

    iLayoutManager->LayoutRect( EHelp, rect );
    iBtnHelp = CButton::NewL( *iGraphicsManager, rect );
    iBtnHelp->SetObserver( this );
    iBtnHelp->SetContainerWindowL( *this );
    ConstructBtnFromResourceL( R_SCALLOP_BTN_HELP );
    Components().AppendLC( iBtnHelp );
    CleanupStack::Pop( iBtnHelp );
    
    iLayoutManager->LayoutRect( EQuit, rect );
    iBtnQuit = CButton::NewL( *iGraphicsManager, rect );
    iBtnQuit->SetObserver( this );
    iBtnQuit->SetContainerWindowL( *this );
    ConstructBtnFromResourceL( R_SCALLOP_BTN_QUIT );
    Components().AppendLC( iBtnQuit );
    CleanupStack::Pop( iBtnQuit );

    INFO( "CButton works very good!" );
    }

// ----------------------------------------------------------------------------
// CScaMenuContainer::ConstructBtnFromResourceL
// ----------------------------------------------------------------------------
//
void CScaMenuContainer::ConstructBtnFromResourceL( TInt aResId )
    {
    FUNC_LOG;

    HBufC8* buffer = iReader.ResourceData( aResId );
    TResourceReader reader;
    reader.SetBuffer( buffer );
    
    switch( aResId )
        {
        case R_SCALLOP_BTN_START:
            iBtnStart->ConstructFromResourceL( reader );
            break;
        case R_SCALLOP_BTN_OPTION:
            iBtnOption->ConstructFromResourceL( reader );
            break;
        case R_SCALLOP_BTN_RECORD:
            iBtnRecord->ConstructFromResourceL( reader );
            break;
        case R_SCALLOP_BTN_HELP:
            iBtnHelp->ConstructFromResourceL( reader );
            break;
        case R_SCALLOP_BTN_QUIT:
            iBtnQuit->ConstructFromResourceL( reader );
            break;
        default:
            break;
        }

    }

// End of File
