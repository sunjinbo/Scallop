/* ====================================================================
 * File: ScaTestDocument.cpp
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#include "ScaTestAppUi.h"
#include "ScaTestDocument.h"

// Standard Symbian OS construction sequence
CScaTestDocument* CScaTestDocument::NewL(CEikApplication& aApp)
    {
    CScaTestDocument* self = NewLC(aApp);
    CleanupStack::Pop(self);
    return self;
    }

CScaTestDocument* CScaTestDocument::NewLC(CEikApplication& aApp)
    {
    CScaTestDocument* self = new (ELeave) CScaTestDocument(aApp);
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

void CScaTestDocument::ConstructL()
    {
	// no implementation required
    }    

CScaTestDocument::CScaTestDocument(CEikApplication& aApp) : CAknDocument(aApp) 
    {
	// no implementation required
    }

CScaTestDocument::~CScaTestDocument()
    {
	// no implementation required
    }

CEikAppUi* CScaTestDocument::CreateAppUiL()
    {
    // Create the application user interface, and return a pointer to it,
    // the framework takes ownership of this object
    CEikAppUi* appUi = new (ELeave) CScaTestAppUi;
    return appUi;
    }

