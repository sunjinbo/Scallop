/* ====================================================================
 * File: FuncKeyUtils.h
 * Created: 10/06/09
 * Modified: 10/06/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_FUNCKEYUTILS_H
#define C_FUNCKEYUTILS_H

// INCLUDE FILE
#include <e32base.h>
#include "Aquatic.hrh"

// FORWARD DECLARATIONS
class CMatrix;
class TAquaticData;

// CLASS DECLARATION
/**
* CFuncKeyUtils class
*
* @since S60 5.0
*/
class CFuncKeyUtils : public CBase
    {
public: // Constructor and Destructor
    static CFuncKeyUtils* NewL( CMatrix& aMatrix );
    static CFuncKeyUtils* NewLC( CMatrix& aMatrix  );
    virtual ~CFuncKeyUtils();

public: // New functions
    void SetMutatedType( TAquaticType aType );
    void GetMutatedAquatics( RArray<TAquaticData>& aArray );

private: // Constructor
    CFuncKeyUtils( CMatrix& aMatrix );
    void ConstructL();
    void Initialise();
    void Reset();
    TInt Find( const RArray<TAquaticData>& aArray, const TPoint& aPos );

private:
    CMatrix& iMatrix;
    TAquaticType iMutatedType;
    RArray<TAquaticData> iMutatedArray;
    RArray<TAquaticData> iKnownArray;
    RArray<TAquaticData> iUnknownArray;
    };

#endif //C_FUNCKEYUTILS_H

// End of file
