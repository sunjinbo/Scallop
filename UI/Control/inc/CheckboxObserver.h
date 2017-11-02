/* ====================================================================
 * File: CheckboxObserver.h
 * Created: 12/05/09
 * Modified: 12/05/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_CHECKBOXOBSERVER_H
#define M_CHECKBOXOBSERVER_H

// INCLUDE FILES
#include <e32def.h>

// CLASS DECLARATION

/**
* MCheckboxObserver class
*
* @since S60 5.0
*/
class MCheckboxObserver
    {
public: // callback function
    virtual void CheckedL( TBool aCheck ) = 0;
    };

#endif // M_BUTTONOBSERVER_H

// End of file
