/* ====================================================================
 * File: ScaTestAppUi.cpp
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto All rights reserved
 * ==================================================================== */

#include <avkon.hrh>
#include <aknnotewrappers.h> 
#include <s32file.h>
#include "ScaTest.pan"
#include "ScaTestAppUi.h"
#include "ScaTestAppView.h"
#include "ScaTest.hrh"
#include <AquaticData.h>
// ConstructL is called by the application framework
void CScaTestAppUi::ConstructL()
    {
    BaseConstructL();
    //Cba()->MakeVisible( EFalse ); 
    StatusPane()->MakeVisible( EFalse );

    iAppView = CScaTestAppView::NewL(ClientRect());    

    AddToStackL(iAppView);
    }

CScaTestAppUi::CScaTestAppUi()                              
    {
	// no implementation required
    }

CScaTestAppUi::~CScaTestAppUi()
    {
    if (iAppView)
        {
        RemoveFromStack(iAppView);
        delete iAppView;
        iAppView = NULL;
        }
    }

// handle any menu commands
void CScaTestAppUi::HandleCommandL(TInt aCommand)
    {
    switch(aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;
        case EScaTestStart:
            iAppView->Start();
            break;
        case EScaTestStop:
            iAppView->Stop();
            break;
        case EScaTestPause:
            iAppView->Pause();
            break;
        case EScaTestResume:
            iAppView->Resume();
            break;
        case EScaTestRestart:
            iAppView->Restart();
            break;
        case EScaTestRefresh:
            iAppView->Refresh();
            break;
        case EScaTestFuncKey:
            iAppView->FuncKey();
            break;
        case EScaTestMake:
            MakeL();
            break;
        default:
            Panic(EScaTestBasicUi);
            break;
        }
    }

void CScaTestAppUi::MakeL()
    {
    // create a file
    RFile file;
    _LIT( KTestFile, "c:\\private\\0A9A1AC2\\2.txt" );
    User::LeaveIfError( file.Create( CCoeEnv::Static()->FsSession(), KTestFile, EFileWrite ) );
    RFileWriteStream fws( file );
    CleanupClosePushL( fws );
    // create and save default data to file stream
    const TInt KScallopNumber = 12;
    fws.WriteUint32L( KScallopNumber );
    TAquaticData a1;
    a1.SetType( EGreenScallop );
    a1.SetXY( 0, 1 );
    a1.SetMature();
    a1.ExternalizeL( fws );

    TAquaticData a2;
    a2.SetType( EGreenScallop );
    a2.SetXY( 2, 5 );
    a2.SetMature();
    a2.ExternalizeL( fws );

    TAquaticData a3;
    a3.SetType( EYellowScallop );
    a3.SetXY( 9, 9 );
    a3.SetMature();
    a3.ExternalizeL( fws );
    
    ///////////
    
    TAquaticData a4;
    a4.SetType( ERedScallop );
    a4.SetXY( 1, 6 );
    a4.SetMature();
    a4.ExternalizeL( fws );

    TAquaticData a5;
    a5.SetType( ERedScallop );
    a5.SetXY( 1, 7 );
    a5.SetMature();
    a5.ExternalizeL( fws );

    TAquaticData a6;
    a6.SetType( ERedScallop );
    a6.SetXY( 1, 8 );
    a6.SetMature();
    a6.ExternalizeL( fws );

    TAquaticData a7;
    a7.SetType( ERedScallop );
    a7.SetXY( 2, 6 );
    a7.SetMature();
    a7.ExternalizeL( fws );

    TAquaticData a8;
    a8.SetType( ERedScallop );
    a8.SetXY( 2, 8 );
    a8.SetMature();
    a8.ExternalizeL( fws );
    
    TAquaticData a9;
    a9.SetType( ERedScallop );
    a9.SetXY( 3, 7 );
    a9.SetMature();
    a9.ExternalizeL( fws );

    ////////////////

    TAquaticData a10;
    a10.SetType( EGreenScallop );
    a10.SetXY( 1, 2 );
    a10.ExternalizeL( fws );
    
    TAquaticData a11;
    a11.SetType( ERedScallop );
    a11.SetXY( 0, 5 );
    a11.ExternalizeL( fws );

    TAquaticData a12;
    a12.SetType( EYellowScallop );
    a12.SetXY( 7, 6 );
    a12.ExternalizeL( fws );

    // commit data
    fws.CommitL();
    // close the file and the write stream object
    //fws.Close();
    CleanupStack::PopAndDestroy( &fws );
    file.Close();
    }

