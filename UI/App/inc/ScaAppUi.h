/* ====================================================================
 * File: ScaAppUi.h
 * Created: 10/23/09
 * Modified: 10/29/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAAPPUI_H
#define C_SCAAPPUI_H

// INCLUDE FILES
#include <aknViewAppUi.h>
#include <ButtonObserver.h>

// FORWARD DECLARATIONS
class CScaState;
class CScaWelcomeView;
class CScaMenuView;
class CScaGameView;
class CScaOptionView;
class CScaRecordView;
class CScaHelpView;
class CScaAboutView;
class CButton;

// CLASS DECLARATION
/**
* CScaAppUi class
*
* @since S60 5.0
*/
class CScaAppUi : public CAknViewAppUi, 
    public MButtonObserver
    {
public: // 2nd phase constructor.

    virtual ~CScaAppUi();
    void ConstructL();
    
public: // New functions
    void ActivateViewL( TUid aViewId );
    void Quit();
    void SetState( CScaState* iState );
    void SetMenuTitleResourceId( TInt aMenuTitleResourceId );
    void Start();
    void Stop();
    void Pause();
    void Restart();
    void Resume();
    void FuncKey();
    void Failed();
    
private: // from CAknAppUi
    void HandleResourceChangeL( TInt aType );

private: // from MButtonObserver
    void HandleButtonEventL( const CButton* aBtn );

private: // Member data

    CScaWelcomeView* iWelcomeView;
    CScaMenuView* iMenuView;
    CScaGameView* iGameView;
    CScaOptionView* iOptionView;
    CScaRecordView* iRecordView;
    CScaHelpView* iHelpView;
    CScaAboutView* iAboutView;
    
    CScaState* iState;
    TUid iCurrentViewId;

    };

#endif // C_SCAAPPUI_H

// End of File
