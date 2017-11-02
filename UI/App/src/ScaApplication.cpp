/* ====================================================================
 * File: ScaApplication.cpp
 * Created: 10/23/09
 * Modified: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "ScaApplication.h"
#include "ScaDocument.h"
#include "ScaViewIds.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CScaApplication::CreateDocumentL
// ---------------------------------------------------------------------------
//
CApaDocument* CScaApplication::CreateDocumentL()
    {
    FUNC_LOG;
    CApaDocument* document = CScaDocument::NewL( *this );
    return document;
    }

// ---------------------------------------------------------------------------
// CScaApplication::AppDllUid
// ---------------------------------------------------------------------------
//
TUid CScaApplication::AppDllUid() const
    {
    // Return the UID for the Tetris application.
    return KUidScallopApp;
    }

// End of File
