/* ====================================================================
 * File: ScaMenuView.h
 * Created: 10/23/09
 * Modified: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAMENUVIEW_H
#define C_SCAMENUVIEW_H

// INCLUDE FILES
#include <aknview.h>

// FORWARD DECLARATIONS
class RFs;
class CScaMenuContainer;
class CScaAppUi;
class CResReader;

// CLASS DECLARATION

/**
* CScaMenuView class
*
* @since S60 5.0
*/
class CScaMenuView : public CAknView
    {
public: // Constructor and destructor

    static CScaMenuView* NewL( CScaAppUi& aAppUi );
    virtual ~CScaMenuView();

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
    CScaMenuView( CScaAppUi& aAppUi );

    /**
    * 2nd phase constructor.
    */
    void ConstructL();

private: // Member data
    RFs& iFs;
    CScaAppUi& iAppUi;
    CScaMenuContainer* iContainer;
    CResReader* iResReader;

    };

#endif // C_SCAMENUVIEW_H

// End of File
