/* ====================================================================
 * File: ScaMenuContainer.h
 * Created: 10/28/09
 * Modified:10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAMENUCONTAINER_H
#define C_SCAMENUCONTAINER_H

// INCLUDE FILES
#include <BaseContainer.h>

// FORWARD DECLARATIONS
class MResReader;
class CButton;
class CScaLayoutManager;

// CLASS DECLARATION
/**
* CBaseContainer class
*
* @since S60 5.0
*/
class CScaMenuContainer : public CBaseContainer
    {

public: // Constructor and destructor

    static CScaMenuContainer* NewL(  const TRect& aRect, 
            MButtonObserver& aObserver, 
            MResReader& aReader  );

    virtual ~CScaMenuContainer();

public: // from CCoeControl
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

protected: // Constructor

    CScaMenuContainer( MButtonObserver& aObserver, MResReader& aReader );
    void ConstructL( const TRect& aRect );

private: // New function
    void ConstructBtnFromResourceL( TInt aResId );

protected: // Member data
    CScaLayoutManager* iLayoutManager;
    CButton* iBtnStart;
    CButton* iBtnOption;
    CButton* iBtnRecord;
    CButton* iBtnHelp;
    CButton* iBtnQuit;
    };

#endif // C_SCAMENUCONTAINER_H

// End of File
