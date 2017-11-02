/* ====================================================================
 * File: Scorekeeper.h
 * Created: 06/16/09
 * Modifed: 06/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCOREKEEPER_H
#define C_SCOREKEEPER_H

// INCLUDE FILES
#include <e32base.h>
#include "ScorekeeperObserver.h"
#include "Aquatic.hrh"

// FORWARD DECLARATIONS
class TAquaticData;
class CPeriodic;

// CONSTANTS
const TInt KPromptLen = 128;

// CLASS DECLARATION
class TLevelData
    {
public: // Member data
    TInt iLevelID;
    TInt iTime;
    TInt iPassScore;
    TInt iPassBonus;
    TBuf<KPromptLen> iPrompt;
    };

/**
* CScorekeeper class
*
* @since S60 5.0
*/
class CScorekeeper : public CBase
    {
public: // Constructor and Destructor
    virtual ~CScorekeeper();

public: // New Functions
    void SetupLevel( const TLevelData& aLevel );
    TInt Level() const;
    TInt Score() const;
    TInt Bonus() const;
    TInt FuncKey() const;
    TInt Progress() const;
    const TDesC* Prompt() const;
    void Dismiss( const RArray<TAquaticData>& aList );
    void Clear();
    void Start();
    void Stop();
    TBool IsFuncKeyFull() const;
    TBool IsFuncKeyEmpty() const;
    TAquaticType FuncKeyType() const;
    void FuncKey( const RArray<TAquaticData>& aList );
    void ClearFuncKey();
    void Expire();

protected: // Constractor
    CScorekeeper( MScorekeeperObserver& aObserver );
    void ConstructL();

protected: // New functions
    virtual void Store() = 0;
    virtual void Restore() = 0;

private: // New functions
    void MakeBonus( TInt aFactor );
    void UpdateAll();
    TAquaticType ComboType( const RArray<TAquaticData>& aList ) const;
    static TInt TimerCallback( TAny* aPtr );

protected: // Member data
    MScorekeeperObserver& iObserver;
    TLevelData iLevel;
    TAquaticType iFuncKeyType;
    CPeriodic* iPeriodic;
    TInt iCompletedTotalScore;
    TInt iCompletedLevelID;
    TInt iLevelScore;
    TInt iLevelBonus;
    TInt iLevelTime;
    TInt iFuncKeyNum;
    TInt iFuncKeyVar;
    };

#endif // C_SCOREKEEPER_H

// End of file
