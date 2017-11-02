/* ====================================================================
 * File: ScaTestAppUi.h
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __SCATEST_APPUI_H__
#define __SCATEST_APPUI_H__

#include <aknappui.h>

// Forward reference
class CScaTestAppView;

/*! 
  @class CScaTestAppUi
  
  @discussion An instance of class CScaTestAppUi is the UserInterface part of the AVKON
  application framework for the ScaTest example application
  */
class CScaTestAppUi : public CAknAppUi
    {
public:
/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CScaTestAppUi object
  this needs to be public due to the way the framework constructs the AppUi 
  */
    void ConstructL();

/*!
  @function CScaTestAppUi
  
  @discussion Perform the first phase of two phase construction.
  This needs to be public due to the way the framework constructs the AppUi 
  */
    CScaTestAppUi();


/*!
  @function ~CScaTestAppUi
  
  @discussion Destroy the object and release all memory objects
  */
    ~CScaTestAppUi();


public: // from CAknAppUi
/*!
  @function HandleCommandL
  
  @discussion Handle user menu selections
  @param aCommand the enumerated code for the option selected
  */
    void HandleCommandL(TInt aCommand);
    
private:
    void MakeL();
    
private:
/*! @var iAppView The application view */
    CScaTestAppView* iAppView;
    };


#endif // __SCATEST_APPUI_H__

