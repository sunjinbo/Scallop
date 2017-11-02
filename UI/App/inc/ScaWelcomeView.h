/* ====================================================================
 * File: ScaWelcomeView.h
 * Created: 10/23/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAWELCOMEVIEW_H
#define C_SCAWELCOMEVIEW_H

// INCLUDE FILES
#include <aknview.h>

// FORWARD DECLARATIONS
class RFs;
class CScaWelcomeContainer;
class CScaAppUi;
class CResReader;

/**
* CScaWelcomeView class
*
* @since S60 5.0
*/
class CScaWelcomeView : public CAknView
    {
public: // Constructor and destructor
    static CScaWelcomeView* NewL( CScaAppUi& aAppUi );
    virtual ~CScaWelcomeView();

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
    * CScaWelcomeView.
    * C++ default constructor.
    */
    CScaWelcomeView( CScaAppUi& aAppUi );

    /**
    * ConstructL.
    * 2nd phase constructor.
    */
    void ConstructL();

private: // Data
    RFs& iFs;
    CScaAppUi& iAppUi;
    CScaWelcomeContainer* iContainer;
    CResReader* iResReader;
    };

#endif // C_SCAWELCOMEVIEW_H

// End of File
