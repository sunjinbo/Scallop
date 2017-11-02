/* ====================================================================
 * File: StrategyComboBehavior.h
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef STRATEGYCOMBOBEHAVIOR_H
#define STRATEGYCOMBOBEHAVIOR_H

// INCLUDE FILES
#include "ComboBehavior.h"

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CStrategyComboBehavior class
*
* @since S60 5.0
*/
class CStrategyComboBehavior : public CComboBehavior
    {
public: // Destructor
    static CStrategyComboBehavior* NewL();
    static CStrategyComboBehavior* NewLC();
    ~CStrategyComboBehavior();

public: // from base class CComboBehavior
    virtual void Combo( RArray<TAquaticData>& aArray );

protected: // Constructor
    CStrategyComboBehavior();
    virtual void ConstructL();

private: // New functions
    TInt FindInAquaticBox( const TPoint& aPos,TInt& aIndex ) const;
    TInt FindInSeedBox( const TPoint& aPos,TInt& aIndex ) const;
    void Init();
    void Seed( const TAquaticData& aAquatic );
    void Crop();
    TInt MoveToSeedbox( const TAquaticData& aAquatic );

private: // Member data
    RArray<TAquaticData> iAquaticBox;
    RArray<TAquaticData> iSeedBox;
    };

#endif // STRATEGYCOMBOBEHAVIOR_H

// End of file
