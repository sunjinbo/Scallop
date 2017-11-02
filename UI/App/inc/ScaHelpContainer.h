/* ====================================================================
 * File: ScaHelpContainer.h
 * Created: 10/28/09
 * Modified:10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAHELPCONTAINER_H
#define C_SCAHELPCONTAINER_H

// INCLUDE FILES
#include <BaseContainer.h>

// FORWARD DECLARATIONS
class MResReader;
class CScaLayoutManager;
class CIcon;
class CButton;
class CTextPane;
class CBoard;

// CLASS DECLARATION

/**
* CHelpPage class
*
* @since S60 5.0
*/
class CHelpPage : public CBase
    {
public: // Constructor and destructor
    static CHelpPage* NewL( TResourceReader& aReader );
    virtual ~CHelpPage();

public: // New functions
    const TDesC* HelpText() const;
    TInt BitmapId() const;
    TInt MaskId() const;

private: // Constructor
    CHelpPage();
     void ConstructL( TResourceReader& aReader );

private: // Member data
    HBufC* iHelpText; // Own.
    TInt iBitmapId;
    TInt iMaskId;
    };

/**
* CScaHelpContainer class
*
* @since S60 5.0
*/
class CScaHelpContainer : public CBaseContainer
    {

public: // Constructor and destructor

    static CScaHelpContainer* NewL( 
                    const TRect& aRect, 
                    MButtonObserver& aObserver, 
                    MResReader& aReader  );

    virtual ~CScaHelpContainer();

public: // from CCoeControl
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

public: // from MButtonObserver
    void HandleButtonEventL( const CButton* aBtn );

private: // Constructor
    CScaHelpContainer( MButtonObserver& aObserver, MResReader& aReader );
    void ConstructL( const TRect& aRect );

private: // New functions
    void SetupHelpPagesL( TResourceReader& aReader );
    void ShowHelpPageL( TInt aPageNum );
    void ShowBackPageL();
    void ShowForwardPageL();
    TInt PageNumber() const;

private: // Member data
    CScaLayoutManager* iLayoutManager; // Own.
    CBoard* iHelpTitleBoard; // Own
    CBoard* iHelpBoard; // Own
    CIcon* iHelpFirstPicture; // Own
    CIcon* iHelpSecondPicture; // Own
    CTextPane* iHelpTitle; // Own.
    CTextPane* iHelpFirstText; // Own
    CTextPane* iHelpSecondText; // Own
    CButton* iHelpBack; // Own
    CButton* iHelpForward; // Own
    RPointerArray<CHelpPage> iHelpPageArray;
    TInt iCurrentPage;
    };

#endif // C_SCAHELPCONTAINER_H

// End of File
