/* ====================================================================
 * File: MatrixTask.h
 * Created: 04/19/09
 * Modified: 04/19/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_MATRIXTASK_H
#define C_MATRIXTASK_H

// INCLUDE FILES
#include <e32std.h>
#include <e32base.h>
#include <AquaticData.h>

// ENUMERATES
enum TTaskType
    {
    EDraw,
    ERemove,
    EMove,
    ESelect,
    EUnselect,
    EDarken,
    ELighten,
    EZoomIn,
    EZoomOut,
    EBlasting
    };

enum TGrayScale
    {
    EGs0, // non transparency
    EGs64,
    EGs128, // semi transparency
    EGs192,
    EGs255 // full transparency
    };

// FORWARD DECLARATIONS
class CMatrix;
class MMatrixTaskObserver;

// CLASS DECLARATION
/**
* CMatrixTask class
*
* @since S60 5.0
*/
class CMatrixTask : public CTimer
    {
public: // Constructor and Destructor
    static CMatrixTask* NewL( CMatrix& aMatrix, MMatrixTaskObserver& aObserver );
    virtual ~CMatrixTask();

public: // New functions
    void SetType( TTaskType aType );
    void Append( const TAquaticData& aAquatic );
    void Append( const RArray<TAquaticData>& aArray );
    void DoTask();

protected: // Constructor
    CMatrixTask( CMatrix& aMatrix, MMatrixTaskObserver& aObserver );
    void ConstructL();

protected: // from CTimer
    void RunL();

private: // New fucntions
    void DoDraw( TGrayScale aGs = EGs0 );
    void DoRemove();
    void DoMove();
    void DrawAquatic( const TAquaticData& aAquatic, TGrayScale aGs = EGs0 );
    void RemoveAquatic( const TAquaticData& aAquatic );

protected: // Data members
    MMatrixTaskObserver& iObserver;
    CMatrix& iMatrix;
    RArray<TAquaticData> iArray;
    TTaskType iType;
    TInt iGradients;
    TInt iMoves;
    };

#endif // C_MATRIXTASK_H

// End of File
