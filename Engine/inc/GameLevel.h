/* ====================================================================
 * File: GameLevel.h
 * Created: 09/16/09
 * Modified: 09/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef GAMELEVEL_H
#define GAMELEVEL_H

// INCLUDE FILES
#include <e32base.h>
#include "Aquatic.hrh"
#include "EngineDefines.h"

// FORWARD DECLARATIONS
class TResourceReader;
class TAquaticData;
class RFs;
class MPathRepository;

// CLASS DECLARATION

/**
* CGameLevel class
*
* @since S60 5.0
*/
class CGameLevel : public CBase
    {
public: // Constructor and Destructor
    static CGameLevel* NewL( TResourceReader& aReader, MPathRepository& aRep );
    static CGameLevel* NewLC( TResourceReader& aReader, MPathRepository& aRep );
    static TInt Compare( const CGameLevel& aFirst, const CGameLevel& aSecond );
    virtual ~CGameLevel();

public: // New functions
    TInt Id() const;
    TInt Time() const;
    TInt Score() const;
    TInt Bonus() const;
    void GetAvailableType( RArray<TAquaticType>& aList );
    const TDesC* Prompt() const;
    void GetAquaticDataL( RArray<TAquaticData>& aList );

private: // Constructor
    CGameLevel( MPathRepository& aRep );
    void ConstructL( TResourceReader& aReader );

private: // New functions
    void SkipChar( TChar aChar );
    TInt ReadCode();

private: // Member data
    RFs& iFs;
    MPathRepository& iRepository;
    TInt iId;
    TInt iTime;
    TInt iScore;
    TInt iBonus;
    HBufC* iType;
    HBufC* iPrompt;
    TLex iLex;
    TBool iLexIsValid;
    };

#endif // GAMELEVEL_H

// End of file
