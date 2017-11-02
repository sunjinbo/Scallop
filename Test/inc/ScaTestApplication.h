/* ====================================================================
 * File: ScaTestApplication.h
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __SCATEST_APPLICATION_H__
#define __SCATEST_APPLICATION_H__

#include <aknapp.h>


/*! 
  @class CScaTestApplication
  
  @discussion An instance of CScaTestApplication is the application part of the AVKON
  application framework for the ScaTest example application
  */
class CScaTestApplication : public CAknApplication
    {
public:  // from CAknApplication

/*! 
  @function AppDllUid
  
  @discussion Returns the application DLL UID value
  @result the UID of this Application/Dll
  */
    TUid AppDllUid() const;

protected: // from CAknApplication
/*! 
  @function CreateDocumentL
  
  @discussion Create a CApaDocument object and return a pointer to it
  @result a pointer to the created document
  */
    CApaDocument* CreateDocumentL();
    };

#endif // __SCATEST_APPLICATION_H__
