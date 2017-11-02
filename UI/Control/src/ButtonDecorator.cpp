/* ====================================================================
 * File: ButtonDecorator.cpp
 * Created: 11/16/09
 * Modified: 11/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "ButtonDecorator.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CButtonDecorator::~CButtonDecorator
// ----------------------------------------------------------------------------
//
CButtonDecorator::~CButtonDecorator()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CButtonDecorator::CButtonDecorator
// ----------------------------------------------------------------------------
//
CButtonDecorator::CButtonDecorator()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CButtonDecorator::ConstructL
// ----------------------------------------------------------------------------
//
void CButtonDecorator::ConstructL( CButton* iButton, const TRect& aRect )
    {
    User::LeaveIfNull( iButton );

    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( iButton->Rect() );

    // Calc the decorator's rect
    CalcDecoratorRect();

    InitComponentArrayL();

    iButton->SetObserver( this );
    iButton->SetContainerWindowL( *this );
    Components().AppendLC( iButton );
    CleanupStack::Pop( iButton );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CButtonDecorator::CalcDecoratorRect
// ----------------------------------------------------------------------------
//
void CButtonDecorator::CalcDecoratorRect()
    {
    }

// End of File
