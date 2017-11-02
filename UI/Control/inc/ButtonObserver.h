/* ====================================================================
 * File: ButtonObserver.h
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_BUTTONOBSERVER_H
#define M_BUTTONOBSERVER_H

// INCLUDE FILES
#include <e32def.h>

// FORWARD DECLARATIONS
class CButton;

// CLASS DECLARATION

/**
* MButtonObserver class
*
* @since S60 5.0
*/
class MButtonObserver
    {
public: // callback function
    virtual void HandleButtonEventL( const CButton* aBtn ) = 0;
    };

#endif // M_BUTTONOBSERVER_H

// End of file
