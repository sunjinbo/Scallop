/* ====================================================================
 * File: ScaState.cpp
 * Created: 10/23/09
 * Modified: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCASTATE_H
#define C_SCASTATE_H

// INCLUDE FILES
#include <e32base.h>

// FORWARD REFERENCES
class CScaAppUi;

// CLASS DECLARATION

/**
* CScaState class
*
* @since S60 5.0
*/
class CScaState : public CBase
    {
public: // Constructors and destructor

    /**
    * Destructor.
    */
    virtual ~CScaState();

public: // New funtions

    virtual void HandleCommandL( TInt aCmd ) = 0;

protected: // Constructors
    /**
    * C++ default constructor.
    */
    CScaState( CScaAppUi& iAppUi );

    /**
    * By default Symbian 2nd phase constructor is private.
    */
    virtual void ConstructL();

protected: // Member data

    CScaAppUi& iAppUi;

    };

/*******************************************************/
/*      SUB CLASS DECLARATIONS                         */
/*******************************************************/

////////////////////////////////////////////////////////
///     Declaration of CWelcomeState
////////////////////////////////////////////////////////
class CWelcomeState : public CScaState
    {
public:
    static CWelcomeState* NewL( CScaAppUi& aAppUi );
    virtual ~CWelcomeState();

public: // from CScaState
    
    void HandleCommandL( TInt aCmd );

protected: // Constructors
    CWelcomeState( CScaAppUi& aAppUi );
    void ConstructL();

    };

////////////////////////////////////////////////////////
///     Declaration of CMenuState
////////////////////////////////////////////////////////
class CMenuState : public CScaState
    {
public:
    static CMenuState* NewL( CScaAppUi& aAppUi );
    virtual ~CMenuState();

public: // from CScaState
    
    void HandleCommandL( TInt aCmd );

protected: // Constructors
    CMenuState( CScaAppUi& aAppUi );
    void ConstructL();

    };

////////////////////////////////////////////////////////
///     Declaration of CPlayState
////////////////////////////////////////////////////////
class CPlayState : public CScaState
    {
public:
    static CPlayState* NewL( CScaAppUi& aAppUi );
    virtual ~CPlayState();

public: // from CScaState
    
    void HandleCommandL( TInt aCmd );

protected: // Constructors
    CPlayState( CScaAppUi& aAppUi );
    void ConstructL();

    };

////////////////////////////////////////////////////////
///     Declaration of CRestartState
////////////////////////////////////////////////////////
class CRestartState : public CScaState
    {
public:
    static CRestartState* NewL( CScaAppUi& aAppUi );
    virtual ~CRestartState();

public: // from CScaState
    
    void HandleCommandL( TInt aCmd );

protected: // Constructors
    CRestartState( CScaAppUi& aAppUi );
    void ConstructL();

    };

////////////////////////////////////////////////////////
///     Declaration of CPauseState
////////////////////////////////////////////////////////
class CPauseState : public CScaState
    {
public:
    static CPauseState* NewL( CScaAppUi& aAppUi );
    virtual ~CPauseState();

public: // from CScaState
    
    void HandleCommandL( TInt aCmd );

protected: // Constructors
    CPauseState( CScaAppUi& aAppUi );
    void ConstructL();

    };

////////////////////////////////////////////////////////
///     Declaration of CHelpState
////////////////////////////////////////////////////////
class CHelpState : public CScaState
    {
public:
    static CHelpState* NewL( CScaAppUi& aAppUi );
    virtual ~CHelpState();

public: // from CScaState
    
    void HandleCommandL( TInt aCmd );

protected: // Constructors
    CHelpState( CScaAppUi& aAppUi );
    void ConstructL();

    };

////////////////////////////////////////////////////////
///     Declaration of CAboutState
////////////////////////////////////////////////////////
class CAboutState : public CScaState
    {
public:
    static CAboutState* NewL( CScaAppUi& aAppUi );
    virtual ~CAboutState();

public: // from CScaState
    
    void HandleCommandL( TInt aCmd );

protected: // Constructors
    CAboutState( CScaAppUi& aAppUi );
    void ConstructL();

    };

////////////////////////////////////////////////////////
///     Declaration of COptionState
////////////////////////////////////////////////////////
class COptionState : public CScaState
    {
public:
    static COptionState* NewL( CScaAppUi& aAppUi );
    virtual ~COptionState();

public: // from CScaState
    
    void HandleCommandL( TInt aCmd );

protected: // Constructors
    COptionState( CScaAppUi& aAppUi );
    void ConstructL();

    };

////////////////////////////////////////////////////////
///     Declaration of CRecordState
////////////////////////////////////////////////////////
class CRecordState : public CScaState
    {
public:
    static CRecordState* NewL( CScaAppUi& aAppUi );
    virtual ~CRecordState();

public: // from CScaState
    
    void HandleCommandL( TInt aCmd );

protected: // Constructors
    CRecordState( CScaAppUi& aAppUi );
    void ConstructL();

    };

#endif // C_SCASTATE_H

// End of File
