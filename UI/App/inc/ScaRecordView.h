/* ====================================================================
 * File: ScaRecordView.h
 * Created: 10/23/09
 * Modified: 11/06/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCARECORDVIEW_H
#define C_SCARECORDVIEW_H

// INCLUDE FILES
#include <aknview.h>
#include "Scallop.hrh"

// FORWARD DECLARATIONS
class RFs;
class CScaRecordContainer;
class CScaAppUi;
class CResReader;

/**
* CScaRecordView class
*
* @since S60 5.0
*/
class CScaRecordView : public CAknView
    {
public: // Constructor and destructor
    static CScaRecordView* NewL( CScaAppUi& aAppUi );
    virtual ~CScaRecordView();

public: // from CAknView
    /**
    * Id
    * @return Id Uid value
    */
    TUid Id() const;

    /**
    * DoActivateL
    * From CAknExView, activate an AknView.
    * @param aPrevViewId The id of the previous view
    * @param aCustomMessageId message identifier
    * @param aCustomMessage custom message provided when the view is changed
    */
    void DoActivateL( const TVwsViewId& aPrevViewId,
                      TUid aCustomMessageId,
                      const TDesC8& aCustomMessage );

    /**
    * DoDeactivate
    * From AknView, deactivate an AknView
    * Remove the container class instance from the App UI's stack and
    * deletes the instance
    */
    void DoDeactivate();

    /**
    * HandleClientRectChange
    * From CAknView, Handles the clientrect.
    */
    void HandleClientRectChange();

public: // Constructors

    /**
    * CScaRecordView.
    * C++ default constructor.
    */
    CScaRecordView( CScaAppUi& aAppUi );

    /**
    * ConstructL.
    * 2nd phase constructor.
    */
    void ConstructL();

private: // Data
    RFs& iFs;
    CScaAppUi& iAppUi;
    CScaRecordContainer* iContainer;
    CResReader* iResReader;
    };

#endif // C_SCARECORDVIEW_H

// End of File
