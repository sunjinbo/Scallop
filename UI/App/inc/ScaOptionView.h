/* ====================================================================
 * File: ScaOptionView.h
 * Created: 10/23/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAOPTIONVIEW_H
#define C_SCAOPTIONVIEW_H

// INCLUDE FILES
#include <aknview.h>

// FORWARD DECLARATIONS
class RFs;
class CScaOptionContainer;
class CScaAppUi;
class CResReader;

/**
* CScaOptionView class
*
* @since S60 5.0
*/
class CScaOptionView : public CAknView
    {
public: // Constructor and destructor
    static CScaOptionView* NewL( CScaAppUi& aAppUi );
    virtual ~CScaOptionView();

public: // from CAknView
    /**
    * Id
    * @return Id Uid value
    */
    TUid Id() const;


    void DoActivateL(
        const TVwsViewId& aPrevViewId,
        TUid aCustomMessageId,
        const TDesC8& aCustomMessage );

    void DoDeactivate();
    
    void HandleClientRectChange();


public: // Constructors

    /**
    * CScaOptionView.
    * C++ default constructor.
    */
    CScaOptionView( CScaAppUi& aAppUi );

    /**
    * ConstructL.
    * 2nd phase constructor.
    */
    void ConstructL();

private: // Data
    RFs& iFs;
    CScaAppUi& iAppUi;
    CScaOptionContainer* iContainer;
    CResReader* iResReader;
    };

#endif // C_SCAOPTIONVIEW_H

// End of File
