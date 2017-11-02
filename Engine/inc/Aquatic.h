/* ====================================================================
 * File: Aquatic.h
 * Created: 06/13/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_AQUATIC_H
#define C_AQUATIC_H

// INCLUDE FILES
#include <e32base.h>
#include "AquaticData.h"

// FORWARD DECLARATIONS
class MAquaticObserver;
class MAquaticHandler;

// CLASS DECLARATION
/**
* CAquatic class
*
* @since S60 5.0
*/
class CAquatic : public CBase
    {
public: // Destructor
    virtual ~CAquatic(){}

public: // New functions
    virtual void SetType( TAquaticType aType );
    virtual void SetXY( TInt aX, TInt aY );
    virtual void SetAquaticData( const TAquaticData& aData );
    virtual void ActivateL();
    virtual void ActivateL( TInt aX, TInt aY );
    virtual void Sleep();
    virtual void Awake();
    void SetSelected( TBool aSelected );
    TBool Selected() const;
    TAquaticData AquaticData() const;
    
protected: // Constructor
    CAquatic( MAquaticObserver& aObserver, MAquaticHandler& aHandler );
    virtual void ConstructL();

protected: // Member data
    MAquaticObserver& iObserver;
    MAquaticHandler& iHandler;
    TBool iSelected;
    TAquaticData iAquaticData;
    };

#endif // C_AQUATIC_H

// End of file
