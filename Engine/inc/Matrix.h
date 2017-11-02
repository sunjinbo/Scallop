/* ====================================================================
 * File: Matrix.h
 * Created: 06/13/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_MATRIX_H
#define C_MATRIX_H

// INCLUDE FILES
#include <e32std.h>
#include <e32def.h>
#include "AquaticObserver.h"
#include "AquaticHandler.h"
#include "ScaPath.h"

// FORWARD DECLARATIONS
class CAquatic;
class CComboBehavior;
class MMatrixObserver;
class CFuncKeyUtils;

// CLASS DECLARATION
/**
* CMatrix class
*
* @since S60 5.0
*/
class CMatrix : public CBase, public MAquaticObserver,
    public MAquaticHandler, public MScaPathObserver
    {
public:
    friend class CFuncKeyUtils;
public: // Constructor and Destructor
    static CMatrix* NewL( MMatrixObserver& aObserver );
    virtual ~CMatrix();

public: // New functions
    TBool ClickL( TInt aX, TInt aY );
    TBool DragL( TInt aX, TInt aY );
    void Clear();
    void Maturate();
    void Start();
    void Stop();
    void FuncKey( TAquaticType aType );

public: // from base class MAquaticObserver
    virtual TAquaticData Aquatic( TInt aX, TInt aY );
    virtual TInt Count() const;

public: // from base class MAquaticHandler
    virtual void AddAquaticsL( const RArray<TAquaticData>& aList );
    virtual void ChangeAquaticL( TPoint aPos, TAquaticType aNewType ) ;
    virtual void RemoveAquatic( TPoint aPos );
    virtual void RemoveAquatic( const RArray<TAquaticData>& aList );
    virtual void MoveAquatic(  const RArray<TAquaticData>& aPath );

public: // from base class MScaPathObserver
    virtual void Path( const RArray<TPoint>& aPath );

private: // Default C++ constructor
    CMatrix( MMatrixObserver& aObserver );
    void ConstructL();

private: // New functions
    TInt Find( const TPoint& aPos,TInt& aIndex ) const;
    CAquatic* CreateL( TAquaticType aType );
    void SelectAquatic( CAquatic& aAquatic );
    void UnselectAquatic();
    void BuildMap();

private: // Member data
    MMatrixObserver& iObserver;
    RPointerArray<CAquatic> iAquaticArray;
    CAquatic* iSelectedAquatic;
    CScaPath* iPath;
    CFuncKeyUtils* iFuncKeyUtils;
    TBool iMatrixChanged;
    TBool iHasPath;
    };

#endif // C_MATRIX_H

// End of file
