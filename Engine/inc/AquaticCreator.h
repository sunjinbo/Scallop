/* ====================================================================
 * File: AquaticCreator.h
 * Created: 06/13/09
 * Modified: 10/04/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_AQUATICCREATOR_H
#define C_AQUATICCREATOR_H

// INCLUDE FILES
#include <e32base.h>
#include "AquaticData.h"

// FORWARD DECLARATIONS
class MAquaticObserver;
class MAquaticHandler;
class CGameLevel;

// CLASS DECLARATION
/**
* CAquaticCreator class
*
* @since S60 5.0
*/
class CAquaticCreator : public CBase
    {
public: // 2nd stages constructor and destructor
    static CAquaticCreator* NewL( 
        MAquaticObserver& aObserver, MAquaticHandler& aHandler );
    virtual ~CAquaticCreator();

public: // New functions
    void Create( CGameLevel& aLevel );
    TBool Next();

protected: // Constructor
    CAquaticCreator( 
        MAquaticObserver& aObserver, MAquaticHandler& aHandler );
    void ConstructL();

private: // New functions
    TAquaticData RandAquatic() const;
    TPoint RandPostion() const;
    TInt Rand( TInt aRange ) const;

private: // Member Data
    MAquaticObserver& iObserver;
    MAquaticHandler& iHandler;
    RArray<TAquaticType> iAvailableTypeList;
    RArray<TAquaticData> iList;
    };

#endif // C_AQUATICCREATOR_H

// End of file
