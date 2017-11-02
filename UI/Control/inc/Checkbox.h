/* ====================================================================
 * File: Checkbox.h
 * Created: 12/05/09
 * Modified: 12/05/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_CHECKBOX_H
#define C_CHECKBOX_H

// INCLUDE FILES
#include <e32const.h>
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CGraphicsManager;
class CGraphicsLayer;
class CIcon;
class CTextPane;
class MCheckboxObserver;

// CLASS DECLARATION
/**
* CCheckbox class
*
* @since S60 5.0
*/
class CCheckbox : public CCoeControl
    {
public: // Constructor and destructor
    IMPORT_C static CCheckbox* NewL( 
        CGraphicsManager& aGraphicsManager, const TRect& aRect );
    IMPORT_C virtual ~CCheckbox();

public: // New functions
    IMPORT_C TBool Checked() const;
    IMPORT_C void SetObserver( MCheckboxObserver& aObserver );
    IMPORT_C void SetCheck( TBool aCheck );
    IMPORT_C void SetVisible( TBool aVisible );
    IMPORT_C void ConstructFromResourceL( TResourceReader& aReader );

public: // from CCoeControl
    void SizeChanged();
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private: // Constructor
    CCheckbox( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // Data
    CGraphicsManager& iGraphicsManager;
    MCheckboxObserver* iObserver; // not own.
    CIcon* iCheckIcon; // own.
    CIcon* iUncheckIcon; // own.
    CTextPane* iTextPane; // own.
    TBool iCheck;
    };

#endif // C_CHECKBOX_H

// End of File
