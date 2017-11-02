/* ====================================================================
 * File: ScaWelcomeContainer.cpp
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
#include <Icon.h>
#include <Scallop.rsg>
#include "ScaWelcomeContainer.h"
#include "ScaLayoutManager.h"
#include "ScaLogger.h"

// CONSTANTS
const TInt KDoDelayTimeout = 0;
const TInt KDoFrameUpdateTimeout = 250000;
const TInt KWelcomeDelayTimeout = 3000000;
const TInt KWelcomeExpireTimeout = 3000000;


// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScaWelcomeContainer::~CScaWelcomeContainer
// ----------------------------------------------------------------------------
//
CScaWelcomeContainer* CScaWelcomeContainer::NewL(  const TRect& aRect, 
    MButtonObserver& aObserver, 
    MResReader& aReader  )
    {
    CScaWelcomeContainer* self = new (ELeave) CScaWelcomeContainer( aObserver, aReader );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaWelcomeContainer::~CScaWelcomeContainer
// ----------------------------------------------------------------------------
//
CScaWelcomeContainer::~CScaWelcomeContainer()
    {
    FUNC_LOG;
    delete iLayoutManager;
    if ( iTimer )
        {  
        iTimer->Cancel();
        delete iTimer;
        }
    }

// ----------------------------------------------------------------------------
// CScaWelcomeContainer::Expire
// ----------------------------------------------------------------------------
//
void CScaWelcomeContainer::Expire()
    {
    FUNC_LOG;
    iTimer->Cancel();
    iObserver.HandleButtonEventL( iWelcome );
    }

// ----------------------------------------------------------------------------
// CScaWelcomeContainer::OfferKeyEventL
// ----------------------------------------------------------------------------
//
TKeyResponse CScaWelcomeContainer::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    FUNC_LOG;
    if ( aType == EEventKey && aKeyEvent.iCode == '5' ) // for test
        {
        User::Exit( 0 );
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// CScaWelcomeContainer::CScaWelcomeContainer
// ----------------------------------------------------------------------------
//
CScaWelcomeContainer::CScaWelcomeContainer( 
    MButtonObserver& aObserver, MResReader& aReader  )
    : CBaseContainer( aObserver, aReader )
    { // No implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaWelcomeContainer::ConstructL
// ----------------------------------------------------------------------------
//
void CScaWelcomeContainer::ConstructL( const TRect& aRect )
    {
    FUNC_LOG;
    // Creates a control's window.
    // The created window is the child of the application's window group.
    CreateWindowL();

    // Sets the control's extent ¡ª specifying a TRect.
    // Calling this function results in a call to SizeChanged.
    SetRect( aRect ); 

    SetupGraphicsManagerL( aRect );

    iLayoutManager = CScaLayoutManager::NewL();
    iLayoutManager->ResolutionChanged();

    InitComponentArrayL();
    
    TRect theRect;
    
    iLayoutManager->LayoutRect( EWelcome, theRect );
    iWelcome = CButton::NewL( *iGraphicsManager, theRect );
    iWelcome->SetContainerWindowL( *this );
    HBufC8* buffer = iReader.ResourceData( R_SCALLOP_WELCOME_NOTE );
    TResourceReader reader;
    reader.SetBuffer( buffer );
    iWelcome->ConstructFromResourceL( reader );
    Components().AppendLC( iWelcome );
    CleanupStack::Pop( iWelcome );
    
    iLayoutManager->LayoutRect( EBrand, theRect );
    iBrand = CIcon::NewL( *iGraphicsManager, theRect );
    iBrand->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_WELCOME_BRAND );
    reader.SetBuffer( buffer );
    iBrand->ConstructFromResourceL( reader );
    Components().AppendLC( iBrand );
    CleanupStack::Pop( iBrand );

    iPeriodic = CPeriodic::NewL( CActive::EPriorityLow );
    iPeriodic->Cancel();
    iPeriodic->Start( 
            KDoDelayTimeout,
            KDoFrameUpdateTimeout,
            TCallBack( TimerCallback, this ) 
            );

    iTimer = CPeriodic::NewL( CActive::EPriorityLow );
    iTimer->Cancel();
    iTimer->Start( 
            KWelcomeDelayTimeout,
            KWelcomeExpireTimeout,
            TCallBack( WelcomeCallback, this ) 
            );

    // Enable Drag Events.
    EnableDragEvents();

    // Sets control as ready to be drawn.
    ActivateL();

    }

// ----------------------------------------------------------------------------
// CScaWelcomeContainer::WelcomeCallback
// ----------------------------------------------------------------------------
//
TInt CScaWelcomeContainer::WelcomeCallback( TAny* aPtr )
    {
    CScaWelcomeContainer* self = static_cast<CScaWelcomeContainer*> ( aPtr );
    self->Expire();
    return 0;
    }

// End of File
