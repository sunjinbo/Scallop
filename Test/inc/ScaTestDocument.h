/* ====================================================================
 * File: ScaTestDocument.h
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __SCATEST_DOCUMENT_H__
#define __SCATEST_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CScaTestAppUi;
class CEikApplication;


/*! 
  @class CScaTestDocument
  
  @discussion An instance of class CScaTestDocument is the Document part of the AVKON
  application framework for the ScaTest example application
  */
class CScaTestDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CScaTestDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CScaTestDocument
  */
    static CScaTestDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CScaTestDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CScaTestDocument
  */
    static CScaTestDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CScaTestDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CScaTestDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CScaTestAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CScaTestDocument object
  */
    void ConstructL();

/*!
  @function CScaTestDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CScaTestDocument(CEikApplication& aApp);

    };


#endif // __SCATEST_DOCUMENT_H__
