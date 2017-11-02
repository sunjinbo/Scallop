/* ====================================================================
 * File: ScaTestApplication.cpp
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#include "ScaTestDocument.h"
#include "ScaTestApplication.h"

// UID for the application, this should correspond to the uid defined in the mmp file
static const TUid KUidScaTestApp = {0x0A9A1AC2};

CApaDocument* CScaTestApplication::CreateDocumentL()
    {  
    // Create an ScaTest document, and return a pointer to it
    CApaDocument* document = CScaTestDocument::NewL(*this);
    return document;
    }

TUid CScaTestApplication::AppDllUid() const
    {
    // Return the UID for the ScaTest application
    return KUidScaTestApp;
    }

