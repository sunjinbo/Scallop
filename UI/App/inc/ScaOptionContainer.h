/* ====================================================================
 * File: ScaOptionContainer.h
 * Created: 10/28/09
 * Modified:10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAOPTIONCONTAINER_H
#define C_SCAOPTIONCONTAINER_H

// INCLUDE FILES
#include <BaseContainer.h>
#include <CheckboxObserver.h>

// FORWARD DECLARATIONS
class MResReader;
class CScaLayoutManager;
class CIcon;
class CCheckbox;
class CButton;
class CTextPane;
class CProgressBar;
class CBoard;

// CLASS DECLARATION

/**
* CModePage class
*
* @since S60 5.0
*/
class CModePage : public CBase
    {
public: // Constructor and destructor
    static CModePage* NewL( TResourceReader& aReader );
    virtual ~CModePage();

public: // New functions
    const TDesC* Title() const;
    const TDesC* Details() const;
    TInt BitmapId() const;
    TInt MaskId() const;

private: // Constructor
    CModePage();
     void ConstructL( TResourceReader& aReader );

private: // Member data
    HBufC* iModeTitle;
    HBufC* iModeDetails;
    TInt iBitmapId;
    TInt iMaskId;
    };

/**
* CScaOptionContainer class
*
* @since S60 5.0
*/
class CScaOptionContainer : public CBaseContainer, public MCheckboxObserver
    {

public: // Constructor and destructor

    static CScaOptionContainer* NewL( 
                    const TRect& aRect, 
                    MButtonObserver& aObserver, 
                    MResReader& aReader  );

    virtual ~CScaOptionContainer();

public: // from CCoeControl
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

public: // from MCheckboxObserver
    void CheckedL( TBool aCheck );

public: // from MButtonObserver
    void HandleButtonEventL( const CButton* aBtn );

private: // Constructor
    CScaOptionContainer( MButtonObserver& aObserver, MResReader& aReader );
    void ConstructL( const TRect& aRect );

private: // New functions
    void SetupModePagesL( TResourceReader& aReader );
    void ShowModePageL( TInt aModeIx );

private: // Member data
    CScaLayoutManager* iLayoutManager; // Own
    CBoard* iSoundBoard; // Own
    CBoard* iModeTitleBoard; // Own
    CBoard* iModeBoard; // Own
    CIcon* iModePicture; // Own
    CTextPane* iSoundTitle; // Own
    CTextPane* iModeTitle; // Own
    CTextPane* iModeDetails; // Own
    CTextPane* iModeName; // Own
    CButton* iModeBack; // Own
    CButton* iModeForward; // Own
    CProgressBar* iSoundProgress; // Own
    CCheckbox* iModeCheckbox; // Own
    RPointerArray<CModePage> iModePageArray;
    TInt iCurrentMode;
    };

#endif // C_SCAOPTIONCONTAINER_H

// End of File
