/* ====================================================================
 * File: MatrixTaskObserver.h
 * Created: 11/07/09
 * Modified: 11/07/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_MATRIXTASKOBSERVER_H
#define M_MATRIXTASKOBSERVER_H


// CLASS DECLARATION

/**
* MMatrixTaskObserver class
*
* @since S60 5.0
*/
class MMatrixTaskObserver
    {
public:
    // Called when matrix task completes and observer needs to be notified.
    virtual void TaskCompleted() = 0;
    };

#endif // M_MATRIXTASKOBSERVER_H

// End of File
