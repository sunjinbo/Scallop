/* ====================================================================
 * File: ScaDocument.cpp
 * Created: 10/23/09
 * Modified: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "ScaDocument.h"
#include "ScaAppUi.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CScaDocument::NewL
// ---------------------------------------------------------------------------
// 
CScaDocument* CScaDocument::NewL( CEikApplication& aApp )
    {
    CScaDocument* self = NewLC( aApp );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScaDocument::NewLC
// ---------------------------------------------------------------------------
//
CScaDocument* CScaDocument::NewLC( CEikApplication& aApp )
    {
    CScaDocument* self = new (ELeave) CScaDocument( aApp );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------------------------
// CScaDocument::~CScaDocument
// ---------------------------------------------------------------------------
//
CScaDocument::~CScaDocument()
    { // no implementation required
    FUNC_LOG;
    }

    
// ---------------------------------------------------------------------------
// CScaDocument::ConstructL
// ---------------------------------------------------------------------------
//
void CScaDocument::ConstructL()
    { // no implementation required
    FUNC_LOG;
    }   

// ---------------------------------------------------------------------------
// CScaDocument::CScaDocument
// ---------------------------------------------------------------------------
//
CScaDocument::CScaDocument( CEikApplication& aApp ) : CAknDocument( aApp ) 
    { // no implementation required
    FUNC_LOG;
    }

// ---------------------------------------------------------------------------
// CScaDocument::CreateAppUiL
// ---------------------------------------------------------------------------
//
CEikAppUi* CScaDocument::CreateAppUiL()
    {
    FUNC_LOG;
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CScaAppUi;
    return appUi;
    }

// End of File
