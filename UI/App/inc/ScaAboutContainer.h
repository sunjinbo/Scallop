/* ====================================================================
 * File: ScaAboutContainer.h
 * Created: 10/28/09
 * Modified:10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAABOUTCONTAINER_H
#define C_SCAABOUTCONTAINER_H

// INCLUDE FILES
#include <BaseContainer.h>

// FORWARD DECLARATIONS
class MResReader;
class CScaLayoutManager;

// CLASS DECLARATION
/**
* CScaAboutContainer class
*
* @since S60 5.0
*/
class CScaAboutContainer : public CBaseContainer
    {

public: // Constructor and destructor

    static CScaAboutContainer* NewL( 
                    const TRect& aRect, 
                    MButtonObserver& aObserver, 
                    MResReader& aReader  );

    virtual ~CScaAboutContainer();

public: // from CCoeControl
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

protected: // Constructor

    CScaAboutContainer( MButtonObserver& aObserver, MResReader& aReader );
    void ConstructL( const TRect& aRect );

protected: // Member data
    CScaLayoutManager* iLayoutManager;
    };

#endif // C_SCAABOUTCONTAINER_H

// End of File
