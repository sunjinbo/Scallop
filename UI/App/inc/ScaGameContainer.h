/* ====================================================================
 * File: ScaGameContainer.h
 * Created: 10/28/09
 * Modified:10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAGAMECONTAINER_H
#define C_SCAGAMECONTAINER_H

// INCLUDE FILES
#include <BaseContainer.h>
#include <EngineObserver.h>
#include <InfoComponentObserver.h>
#include <Matrix.h>

// FORWARD DECLARATIONS
class MResReader;
class CScaLayoutManager;
class CEngineBase;
class CClassicEngineFactory;
class CStrategyEngineFactory;
class CScoreboard;
class CProgressBar;
class CFuncKeyPane;
class CInfoComponent;

// CLASS DECLARATION
/**
* CScaGameContainer class
*
* @since S60 5.0
*/
class CScaGameContainer : 
    public CBaseContainer, 
    public MEngineObserver,
    public MMatrixObserver,
    public MInfoComponentObserver
    {

public: // Constructor and destructor

    static CScaGameContainer* NewL( 
                    const TRect& aRect, 
                    MButtonObserver& aObserver, 
                    MResReader& aReader  );

    virtual ~CScaGameContainer();

public: // New functions
    void Start();
    void Stop();
    void Pause();
    void Restart();
    void Resume();
    void FuncKey();

public: // from MEngineObserver
    void StateChanged( TEngineAction aAction );
    void AuqaticChanged( TAquaticAction aAction, const RArray<TAquaticData>& aList );
    void PathChanged( TPathAction aAction, const RArray<TPoint>& aList );
    void ScorekeeperChanged( TScorekeeperAction aAction, TInt aValue );
    void PromptChanged( const TDesC& aText );
    void FuncKeyChanged( TAquaticType aType, TInt aValue );

public: // from MMatrixObserver
    void ClickL( TInt aX, TInt aY );
    void DragL( TInt aX, TInt aY );

public: // from MInfoComponentObserver
    void CheckedL( TBool aCheck );

public: // from CCoeControl
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType );

private: // Constructor
    CScaGameContainer( MButtonObserver& aObserver, MResReader& aReader );
    void ConstructL( const TRect& aRect );

private: // New functions
    void ConstructFromResourceL( TInt aResId );

protected: // Member data
    CScaLayoutManager* iLayoutManager; // Own.
    CMatrix* iMatrix; // Own.
    CScoreboard* iLevel; // Own.
    CScoreboard* iScore; // Own.
    CScoreboard* iBonus; // Own.
    CProgressBar* iProgress; // Own.
    CFuncKeyPane* iFuncKey; // Own.
    CInfoComponent* iInfoComponent; // Own.
    CEngineBase* iEngine; // Own.
    CClassicEngineFactory* iClassicEngineFactory; // Own.
    CStrategyEngineFactory* iStrategyEngineFactory; // Own.
    };

#endif // C_SCAGAMECONTAINER_H

// End of File
