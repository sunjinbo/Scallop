/* ====================================================================
 * File: GameLevelMgr.h
 * Created: 09/16/09
 * Modified: 09/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef GAMELEVELMGR_H
#define GAMELEVELMGR_H

// INCLUDE FILES
#include <e32base.h>
#include "PathRepository.h"

// FORWARD DECLARATIONS
class CGameLevel;
class CCoeEnv;
class TResourceReader;

// CLASS DECLARATION

/**
* CGameLevelMgr class
*
* @since S60 5.0
*/
class CGameLevelMgr : public CBase, public MPathRepository
    {
public: // Constructor and Destructor
    static CGameLevelMgr* NewL( TInt aResId, const TDesC& aResPath );
    static CGameLevelMgr* NewLC( TInt aResId, const TDesC& aResPath );
    virtual ~CGameLevelMgr();

public: // from base class MPathRepository
    virtual void GetPath( TDes& aPath ) const;

public: // New functions
    void Start( TInt aLevelID );
    TBool Next();
    CGameLevel* GameLevel() const;

private: // Constructor
    CGameLevelMgr();
    void ConstructL( TInt aResId, const TDesC& aResPath );

private: // New functions
    void ReadLevelsL( TResourceReader& aReader );
    void Sort();
    TInt Find( TInt aId ) const;
    TInt MaxLevelID() const;
    TInt NearestLevelID( TInt aId ) const;

private: // Member data
    CCoeEnv& iCoeEnv;
    RPointerArray<CGameLevel> iGameLevelArray;
    TInt iLevelID;
    TInt iResFileOffset;
    TBool iIgnoreList;
    HBufC* iResPath;
    };

#endif // GAMELEVELMGR_H

// End of file
