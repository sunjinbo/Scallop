/* ====================================================================
 * File: ScaHelpView.h
 * Created: 10/23/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAHELPVIEW_H
#define C_SCAHELPVIEW_H

// INCLUDE FILES
#include <aknview.h>

// FORWARD DECLARATIONS
class RFs;
class CScaHelpContainer;
class CScaAppUi;
class CResReader;

/**
* CScaHelpView class
*
* @since S60 5.0
*/
class CScaHelpView : public CAknView
    {
public: // Constructor and destructor
    static CScaHelpView* NewL( CScaAppUi& aAppUi );
    virtual ~CScaHelpView();

public: // from CAknView
    /**
    * Id
    * @return Id Uid value
    */
    TUid Id() const;


    void DoActivateL( const TVwsViewId& aPrevViewId,
                      TUid aCustomMessageId,
                      const TDesC8& aCustomMessage );
    void DoDeactivate();
    void HandleClientRectChange();


public: // Constructors

    /**
    * CScaHelpView.
    * C++ default constructor.
    */
    CScaHelpView( CScaAppUi& aAppUi );

    /**
    * ConstructL.
    * 2nd phase constructor.
    */
    void ConstructL();

private: // Data
    RFs& iFs;
    CScaAppUi& iAppUi;
    CScaHelpContainer* iContainer;
    CResReader* iResReader;
    };

#endif // C_SCAHELPVIEW_H

// End of File
