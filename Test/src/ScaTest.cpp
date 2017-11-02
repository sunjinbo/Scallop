/* ====================================================================
 * File: ScaTest.cpp
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#include "ScaTestApplication.h"
#include <eikstart.h>

#ifdef __UI_FRAMEWORKS_V2__

// Create an application, and return a pointer to it
CApaApplication* NewApplication()
	{
	return new CScaTestApplication;
	}


TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	
	}

///////////////////////////////////////////////////////////////////////////////
//
// The following is required for wins on EKA1 (using the exedll target)
//
#if defined(__WINS__) && !defined(EKA2)
EXPORT_C TInt WinsMain(TDesC* aCmdLine)
	{
	return EikStart::RunApplication(NewApplication, aCmdLine);
	}

TInt E32Dll(TDllReason)
	{
	return KErrNone;
	}
#endif

#else // __UI_FRAMEWORKS_V2__

// Create an application, and return a pointer to it
EXPORT_C CApaApplication* NewApplication()
  {
  return new CScaTestApplication;
  }

// DLL entry point, return that everything is ok
GLDEF_C TInt E32Dll(TDllReason)
  {
  return KErrNone;
  }

#endif // __UI_FRAMEWORKS_V2__

