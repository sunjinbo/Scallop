/* ====================================================================
 * File: ScaRecordContainer.cpp
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
#include "ScaRecordContainer.h"
#include "ScaLayoutManager.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScaRecordContainer::~CScaRecordContainer
// ----------------------------------------------------------------------------
//
CScaRecordContainer* CScaRecordContainer::NewL(  const TRect& aRect, 
    MButtonObserver& aObserver, 
    MResReader& aReader  )
    {
    CScaRecordContainer* self = new (ELeave) CScaRecordContainer( aObserver, aReader );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaRecordContainer::~CScaRecordContainer
// ----------------------------------------------------------------------------
//
CScaRecordContainer::~CScaRecordContainer()
    {
    FUNC_LOG;
    delete iLayoutManager;
    }

// ----------------------------------------------------------------------------
// CScaRecordContainer::OfferKeyEventL
// ----------------------------------------------------------------------------
//
TKeyResponse CScaRecordContainer::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    FUNC_LOG;
    if ( aType == EEventKey && aKeyEvent.iCode == '5' ) // for test
        {
        User::Exit( 0 );
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// CScaRecordContainer::CScaRecordContainer
// ----------------------------------------------------------------------------
//
CScaRecordContainer::CScaRecordContainer( 
    MButtonObserver& aObserver, MResReader& aReader  )
    : CBaseContainer( aObserver, aReader )
    { // No implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaRecordContainer::ConstructL
// ----------------------------------------------------------------------------
//
void CScaRecordContainer::ConstructL( const TRect& aRect )
    {
    FUNC_LOG;
    CBaseContainer::ConstructL( aRect );
    
    iLayoutManager = CScaLayoutManager::NewL();
    iLayoutManager->ResolutionChanged();
    
    }

// End of File
