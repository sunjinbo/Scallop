/* ====================================================================
 * File: ScaEngine.h
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAENGINE_H
#define C_SCAENGINE_H

// INCLUDE FILES
#include <e32base.h>
#include "EngineBase.h"
#include "MatrixObserver.h"
#include "ScorekeeperObserver.h"

// FORWARD DECLARATIONS
class CMatrix;
class CScorekeeper;
class CComboBehavior;
class CAquaticCreator;
class CGameLevelMgr;

// CLASS DECLARATION
/**
* CScaEngine class
*
* @since S60 5.0
*/
class CScaEngine : public CEngineBase,
    public MMatrixObserver, public MScorekeeperObserver
    {
public: // Constructor and Destructor
    static CScaEngine* NewL( MEngineObserver& aObserver );
    static CScaEngine* NewLC( MEngineObserver& aObserver );
    virtual ~CScaEngine();

public: // New functions
    void SetComboBehavior( CComboBehavior* aComboBehavior );
    void SetGameLevelMgr( CGameLevelMgr* aLevelManager );
    void SetScorekeeper( CScorekeeper* aScorekeeper );

public: // from base class CEngineBase
    IMPORT_C void HandleCommandL( TEngineCmd aCmd );
    IMPORT_C void ClickL( TInt aX, TInt aY );
    IMPORT_C void DragL( TInt aX, TInt aY );

private: // from base class MMatrixObserver
    void StateChanged( TMatrixState aState, const RArray<TAquaticData>& aList );
    void StateChanged( TMatrixPathState aState, const RArray<TPoint>& aList );

private: // from base class MScorekeeperObserver
    void StateChanged( TScorekeeperState aNewState );

private: // Default C++ constructor
    CScaEngine( MEngineObserver& aObserver );
    void ConstructL();

private: // Member data
    CMatrix* iMatrix;
    CScorekeeper* iScorekeeper;
    CComboBehavior* iComboBehavior;
    CAquaticCreator* iAquaticCreator;
    CGameLevelMgr* iLevelManager;
    };

#endif // C_SCAENGINE_H

// End of file
