/* ====================================================================
 * File: InfoComponent.h
 * Created: 12/06/09
 * Modified: 12/06/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INFOCOMPONENT_H
#define C_INFOCOMPONENT_H

// INCLUDE FILES
#include <e32const.h>
#include <coecntrl.h>
#include "CheckboxObserver.h"
#include "ButtonObserver.h"

// FORWARD DECLARATIONS
class CGraphicsManager;
class CGraphicsLayer;
class CTextPane;
class CCheckbox;
class CButton;
class CPeriodic;
class MInfoComponentObserver;
class MResReader;

// CLASS DECLARATION

/**
* CInfoComponent class
*
* @since S60 5.0
*/
class CInfoComponent : public CCoeControl, public MCheckboxObserver, public MButtonObserver
    {
public: // Constructor and destructor
    IMPORT_C static CInfoComponent* NewL( 
        CGraphicsManager& aGraphicsManager, const TRect& aRect );
    IMPORT_C virtual ~CInfoComponent();

public: // New functions
    IMPORT_C void SetObserver( MInfoComponentObserver& aObserver );
    IMPORT_C void SetResReader( MResReader& aReader );
    IMPORT_C void SetInfoResourceIdL( TInt aInfoResourceId );
    IMPORT_C void SetTextL( const TDesC& aText );
    IMPORT_C void SetVisible( TBool aVisible );
    IMPORT_C void RestartTimer( TInt aSecond );
    IMPORT_C void StartTimer();
    IMPORT_C void StopTimer();

public: // from CCoeControl
    void SizeChanged();

public: // from MCheckboxObserver
    void CheckedL( TBool aCheck );

public: // from MButtonObserver
    void HandleButtonEventL( const CButton* aBtn );

private: // Constructor
    CInfoComponent( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // New functions
    enum TInfoComponent
        {
        EButton,
        ETextPane,
        ECheckbox
        };
    void LayoutComponent( TInfoComponent aComponent, TRect& aRect );
    static TInt TimerCallback( TAny* aPtr );
    void DoTimer();

private: // Data
    CGraphicsManager& iGraphicsManager;
    MInfoComponentObserver* iObserver; // Not own.
    MResReader* iResReader; // Not own.
    CGraphicsLayer* iDlgLayer; // Own.
    CTextPane* iTextPane; // Own.
    CCheckbox* iCheckbox; // Own.
    CButton* iBtnOk; // Own.
    CPeriodic* iPeriodic; // Own.
    TInt iTimer;
    };

#endif // C_INFOCOMPONENT_H

// End of File
