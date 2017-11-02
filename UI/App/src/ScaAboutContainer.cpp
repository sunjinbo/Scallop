/* ====================================================================
 * File: ScaAboutContainer.cpp
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
#include "ScaAboutContainer.h"
#include "ScaLayoutManager.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScaAboutContainer::~CScaAboutContainer
// ----------------------------------------------------------------------------
//
CScaAboutContainer* CScaAboutContainer::NewL(  const TRect& aRect, 
    MButtonObserver& aObserver, 
    MResReader& aReader  )
    {
    CScaAboutContainer* self = new (ELeave) CScaAboutContainer( aObserver, aReader );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaAboutContainer::~CScaAboutContainer
// ----------------------------------------------------------------------------
//
CScaAboutContainer::~CScaAboutContainer()
    {
    delete iLayoutManager;
    }

// ----------------------------------------------------------------------------
// CScaAboutContainer::OfferKeyEventL
// ----------------------------------------------------------------------------
//
TKeyResponse CScaAboutContainer::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    FUNC_LOG;
    if ( aType == EEventKey && aKeyEvent.iCode == '5' ) // for test
        {
        User::Exit( 0 );
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// CScaAboutContainer::CScaAboutContainer
// ----------------------------------------------------------------------------
//
CScaAboutContainer::CScaAboutContainer( 
    MButtonObserver& aObserver, MResReader& aReader  )
    : CBaseContainer( aObserver, aReader )
    { // No implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaAboutContainer::ConstructL
// ----------------------------------------------------------------------------
//
void CScaAboutContainer::ConstructL( const TRect& aRect )
    {
    FUNC_LOG;
    CBaseContainer::ConstructL( aRect );
    
    iLayoutManager = CScaLayoutManager::NewL();
    iLayoutManager->ResolutionChanged();

    }

// End of File
