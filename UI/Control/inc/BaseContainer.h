/* ====================================================================
 * File: BaseContainer.h
 * Created: 10/28/09
 * Modified:10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BASECONTAINER_H
#define C_BASECONTAINER_H

// INCLUDE FILES
#include <coecntrl.h>
#include "ButtonObserver.h"

// FORWARD DECLARATIONS
class CGraphicsManager;
class CPeriodic;
class CBackground;
class CMenuBar;
class MResReader;

// CLASS DECLARATION
/**
* CBaseContainer class
*
* @since S60 5.0
*/
class CBaseContainer : public CCoeControl, public MButtonObserver
    {

public: // Destructor

    IMPORT_C virtual ~CBaseContainer();

public: // New functions

    IMPORT_C void SetMenuBarL( TInt aResourceId );
    IMPORT_C void SetBackgroundL( TInt aResourceId );

public: // from CCoeControl

    IMPORT_C virtual void SizeChanged();
    IMPORT_C virtual void HandleResourceChange( TInt aType );

public: // from MButtonObserver

    IMPORT_C virtual void HandleButtonEventL( const CButton* aBtn );

protected: // Constructor

    IMPORT_C CBaseContainer( MButtonObserver& aObserver, MResReader& aReader );
    IMPORT_C virtual void ConstructL( const TRect& aRect );

protected: // New functions
    IMPORT_C void SetupGraphicsManagerL( const TRect& aRect );
    IMPORT_C static TInt TimerCallback( TAny* aPtr );
    TRect MenuBarRect();
    void Stop();
    void DoFrame();

protected: // Data
    MButtonObserver& iObserver;
    MResReader& iReader;
    CGraphicsManager* iGraphicsManager; // Own.
    CMenuBar* iMenuBar; // Own.
    CBackground* iBackground; // Own.
    CPeriodic* iPeriodic; // Own.

    };

#endif // C_BASECONTAINER_H

// End of File
