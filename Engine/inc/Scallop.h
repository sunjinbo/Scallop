/* ====================================================================
 * File: Scallop.h
 * Created: 06/13/09
 * Modified: 09/09/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef SCALLOP_H
#define SCALLOP_H

// INCLUDE FILES
#include "Aquatic.h"
#include "ScaPath.h"

// CLASS DECLARATION
/**
* CScallop class
*
* @since S60 5.0
*/
class CScallop : public CAquatic, public MScaPathObserver
    {
public: // Constructor and Destructor
    static CScallop* NewL( MAquaticObserver& aObserver, MAquaticHandler& aHandler );
    virtual ~CScallop();

public: // from base class CAquatic
    void ActivateL( TInt aX, TInt aY );

public: // from base class MScaPathObserver
    void Path( const RArray<TPoint>& aPath );

protected: // Constructor
    CScallop( MAquaticObserver& aObserver, MAquaticHandler& aHandler );
    void ConstructL();

protected: // New functions
    virtual void DoClick( TInt aX, TInt aY );

private: // Member Data
    };

#endif // SCALLOP_H


// End of file
