/* ====================================================================
 * File: Scallop.cpp
 * Created: 10/23/09
 * Modified: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <eikstart.h> // EikStart
#include "ScaApplication.h" // CScaApplication


// ======== GLOBAL FUNCTIONS ========

// ---------------------------------------------------------------------------
// Create an application, and return a pointer to it .
// ---------------------------------------------------------------------------
//
CApaApplication* NewApplication()
    {
    return new CScaApplication;
    }

// ---------------------------------------------------------------------------
// Main function of the application executable.
// ---------------------------------------------------------------------------
// 
GLDEF_C TInt E32Main()
    {
    return EikStart::RunApplication( NewApplication );
    }

// End of File
