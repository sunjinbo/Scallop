/* ====================================================================
 * File: EngineBase.h
 * Created: 08/16/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_ENGINEBASE_H
#define C_ENGINEBASE_H

// INCLUDE FILES
#include <e32base.h>
#include <e32def.h>

// ENUMERATES
enum TEngineCmd
    {
    EEngineCmdStart = 0,
    EEngineCmdPause,
    EEngineCmdRestart,
    EEngineCmdResume,
    EEngineCmdStop,
    EEngineCmdRefresh,
    EEngineCmdFuncKey
    };

// FORWARD DECLARATIONS
class MEngineObserver;

// CLASS DECLARATION
/**
* CScaEngine class
*
* @since S60 5.0
*/
class CEngineBase : public CBase
    {
public: // Friend class
    friend class CEngineBase;

public: // Virtual destructor.
    virtual ~CEngineBase(){}

public: // New functions
    virtual void HandleCommandL( TEngineCmd aCmd ) = 0;
    virtual void ClickL( TInt aX, TInt aY ) = 0;
    virtual void DragL( TInt aX, TInt aY ) = 0;

protected: // Default C++ constructor
    CEngineBase( MEngineObserver& aObserver );

protected: // Member data
    MEngineObserver& iObserver;

    };

#endif // C_ENGINEBASE_H

// End of file
