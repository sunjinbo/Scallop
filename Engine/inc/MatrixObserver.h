/* ====================================================================
 * File: MatrixObserver.h
 * Created: 06/13/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_MATRIXOBSERVER_H
#define M_MATRIXOBSERVER_H

// INCLUDE FILES
#include <e32std.h>
#include "AquaticData.h"

// Enumeration
enum TMatrixState
    {
    EMatrixBorn = 0,
    EMatrixMatured,
    EMatrixMoved,
    EMatrixChanged,
    EMatrixReleased,
    EMatrixRemoved,
    EMatrixUpdated,
    EMatrixUnselected,
    EMatrixSelected
    };

enum TMatrixPathState
    {
    EMatrixPathDisplayed,
    EMatrixPathDisappeared
    };

// CLASS DECLARATION
/**
* MMatrixObserver class
*
* @since S60 5.0
*/
class MMatrixObserver
    {
public: // New function
    virtual void StateChanged( TMatrixState aState, const RArray<TAquaticData>& aList ) = 0;
    virtual void StateChanged( TMatrixPathState aState, const RArray<TPoint>& aList ) = 0;
    };

#endif // M_MATRIXOBSERVER_H

// End of file
