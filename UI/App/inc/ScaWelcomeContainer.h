/* ====================================================================
 * File: ScaWelcomeContainer.h
 * Created: 10/28/09
 * Modified:10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAWELCOMECONTAINER_H
#define C_SCAWELCOMECONTAINER_H

// INCLUDE FILES
#include <BaseContainer.h>

// FORWARD DECLARATIONS
class MResReader;
class CButton;
class CIcon;
class CScaLayoutManager;

// CLASS DECLARATION
/**
* CBaseContainer class
*
* @since S60 5.0
*/
class CScaWelcomeContainer : public CBaseContainer
    {

public: // Constructor and destructor

    static CScaWelcomeContainer* NewL(  const TRect& aRect, 
            MButtonObserver& aObserver, 
            MResReader& aReader  );

    virtual ~CScaWelcomeContainer();

public: // New functions
    void Expire();

public: // from CCoeControl
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

private: // Constructor
    CScaWelcomeContainer( MButtonObserver& aObserver, MResReader& aReader );
    void ConstructL( const TRect& aRect );

private: // New functions
    static TInt WelcomeCallback( TAny* aPtr );

private: // Member data
    CScaLayoutManager* iLayoutManager; // Own.
    CButton* iWelcome; // Own.
    CIcon* iBrand; // Own.
    CPeriodic* iTimer; // Own.
    };

#endif // C_SCAWELCOMECONTAINER_H

// End of File
