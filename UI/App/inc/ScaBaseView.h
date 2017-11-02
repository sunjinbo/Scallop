/* ====================================================================
 * File: ScaBaseView.h
 * Created: 10/23/09
 * Modified: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCABASEVIEW_H
#define C_SCABASEVIEW_H

// INCLUDE FILES
#include <aknview.h>

// FORWARD DECLARATIONS
class CScaAppUi;

// CLASS DECLARATION

/**
* CScaMenuView class
*
* @since S60 5.0
*/
class CScaBaseView : public CAknView
    {
public: // Destructor

    virtual ~CScaBaseView();

public: // New functions
    virtual void SetMenuBarL( TInt aResourceId ) = 0;
    virtual void SetBackgroundL( TInt aResourceId ) = 0;

public: // from CAknView
    /**
    * HandleClientRectChange
    * From CAknView, Handles the clientrect.
    */
    void HandleClientRectChange();

public: // Constructors and destructor

    /**
    * C++ default constructor.
    */
    CScaBaseView( CScaAppUi& aAppUi );

protected: // Member data
    CScaAppUi& iAppUi;

    };

#endif // C_SCABASEVIEW_H

// End of File
