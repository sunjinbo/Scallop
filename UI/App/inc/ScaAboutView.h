/* ====================================================================
 * File: ScaAboutView.h
 * Created: 10/23/09
 * Modified: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAABOUTVIEW_H
#define C_SCAABOUTVIEW_H

// INCLUDE FILES
#include <aknview.h>

// FORWARD DECLARATIONS
class RFs;
class CScaAboutContainer;
class CScaAppUi;
class CResReader;

// CLASS DECLARATION

/**
* CScaAboutView class
*
* @since S60 5.0
*/
class CScaAboutView : public CAknView
    {
public: // Constructor and destructor

    static CScaAboutView* NewL( CScaAppUi& aAppUi );
    virtual ~CScaAboutView();

public: // from CAknView

    /**
    * Id
    * @return Id Uid value
    */
    TUid Id() const;
    
    void DoActivateL( const TVwsViewId& , TUid , const TDesC8& );
    void DoDeactivate();
    void HandleClientRectChange();

public: // Constructors

    /**
    * C++ default constructor.
    */
    CScaAboutView( CScaAppUi& aAppUi );

    /**
    * 2nd phase constructor.
    */
    void ConstructL();

private: // Member data
    RFs& iFs;
    CScaAppUi& iAppUi;
    CScaAboutContainer* iContainer;
    CResReader* iResReader;

    };

#endif // C_SCAABOUTVIEW_H

// End of File
