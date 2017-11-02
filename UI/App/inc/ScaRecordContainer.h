/* ====================================================================
 * File: ScaRecordContainer.h
 * Created: 10/28/09
 * Modified:10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCARECORDCONTAINER_H
#define C_SCARECORDCONTAINER_H

// INCLUDE FILES
#include <BaseContainer.h>

// FORWARD DECLARATIONS
class MResReader;
class CScaLayoutManager;

// CLASS DECLARATION
/**
* CScaRecordContainer class
*
* @since S60 5.0
*/
class CScaRecordContainer : public CBaseContainer
    {

public: // Constructor and destructor

    static CScaRecordContainer* NewL( 
                    const TRect& aRect, 
                    MButtonObserver& aObserver, 
                    MResReader& aReader  );

    virtual ~CScaRecordContainer();

public: // from CCoeControl
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

protected: // Constructor

    CScaRecordContainer( MButtonObserver& aObserver, MResReader& aReader );
    void ConstructL( const TRect& aRect );

protected: // Member data
    CScaLayoutManager* iLayoutManager;
    };

#endif // C_SCARECORDCONTAINER_H

// End of File
