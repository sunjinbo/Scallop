/* ====================================================================
 * File: MenubarControl.h
 * Created: 03/15/09
 * Modified: 03/15/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_MENUBAR_H
#define C_MENUBAR_H

// INCLUDE FILES
#include <coecntrl.h>
#include "ButtonObserver.h"

// FORWARD DECLARATIONS
class CGraphicsManager;
class CButton;

// CLASS DECLARATION
/**
* CMenubarControl class
*
* @since S60 3.1
*/
class CMenuBar : public CCoeControl, public MButtonObserver
    {
public: // Constructor and destructor

    static CMenuBar* NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect );
    virtual ~CMenuBar();

public: // New functions

    void ConstructBtn1FromResourceL( TResourceReader& aReader );
    void ConstructBtn2FromResourceL( TResourceReader& aReader );

    void SetObserver( MButtonObserver* aObserver );

public: // from class MButtonObserver

    virtual void HandleButtonEventL( const CButton* aBtn );

public: // from class CCoeControl

    void SizeChanged();

protected: // Constructor

    CMenuBar( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // New functions
    void LayoutMenuBar();
    void LayoutTextAlign();
    void ConstructFromResourceL( TResourceReader& aReader, CButton& aBtn );

protected: // Data members
    CGraphicsManager& iGraphicsManager;
    MButtonObserver* iObserver; // Not own.
    CButton* iBtn1;
    CButton* iBtn2;
    TRect iBtn1Rect;
    TRect iBtn2Rect;
    };

#endif // C_MENUBAR_H

// End of File
