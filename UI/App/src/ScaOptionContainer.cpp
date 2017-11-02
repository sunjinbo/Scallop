/* ====================================================================
 * File: ScaOptionContainer.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <akndef.h>
#include <aknutils.h>
#include <barsread.h>
#include <ResReader.h>
#include <BmpUtils.h>
#include <Button.h>
#include <ProgressBar.h>
#include <TextPane.h>
#include <Checkbox.h>
#include <Icon.h>
#include <Board.h>
#include <Scallop.rsg>
#include "Scallop.hrh"
#include "ScaOptionContainer.h"
#include "ScaLayoutManager.h"
#include "ScaLogger.h"

// CONSTANTS
const TInt KMaxTextLen = 256;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CModePage::NewL
// ----------------------------------------------------------------------------
//
CModePage* CModePage::NewL( TResourceReader& aReader )
    {
    CModePage* self = new (ELeave) CModePage;
    CleanupStack::PushL (self );
    self->ConstructL ( aReader );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CModePage::~CModePage
// ----------------------------------------------------------------------------
//
CModePage::~CModePage()
    {
    FUNC_LOG;
    delete iModeTitle;
    delete iModeDetails;
    }

// ----------------------------------------------------------------------------
// CModePage::Title
// ----------------------------------------------------------------------------
//
const TDesC* CModePage::Title() const
    {
    return iModeTitle;
    }

// ----------------------------------------------------------------------------
// CModePage::Details
// ----------------------------------------------------------------------------
//
const TDesC* CModePage::Details() const
    {
    FUNC_LOG;
    return iModeDetails;
    }

// ----------------------------------------------------------------------------
// CModePage::BitmapId
// ----------------------------------------------------------------------------
//
TInt CModePage::BitmapId() const
    {
    FUNC_LOG;
    return iBitmapId;
    }

// ----------------------------------------------------------------------------
// CModePage::MaskId
// ----------------------------------------------------------------------------
//
TInt CModePage::MaskId() const
    {
    FUNC_LOG;
    return iMaskId;
    }

// ----------------------------------------------------------------------------
// CModePage::CModePage
// ----------------------------------------------------------------------------
//
CModePage::CModePage()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CModePage::ConstructL
// ----------------------------------------------------------------------------
// 
void CModePage::ConstructL( TResourceReader& aReader )
    {
    FUNC_LOG;
    iBitmapId = aReader.ReadUint32();
    iMaskId = aReader.ReadUint32();
    iModeTitle = aReader.ReadHBufCL();
    iModeDetails = aReader.ReadHBufCL();
    }

// ----------------------------------------------------------------------------
// CScaOptionContainer::~CScaOptionContainer
// ----------------------------------------------------------------------------
//
CScaOptionContainer* CScaOptionContainer::NewL(  const TRect& aRect, 
    MButtonObserver& aObserver, 
    MResReader& aReader  )
    {
    CScaOptionContainer* self = new (ELeave) CScaOptionContainer( aObserver, aReader );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaOptionContainer::~CScaOptionContainer
// ----------------------------------------------------------------------------
//
CScaOptionContainer::~CScaOptionContainer()
    {
    delete iLayoutManager;
    iModePageArray.ResetAndDestroy();
    iModePageArray.Close();
    }

// ----------------------------------------------------------------------------
// CScaOptionContainer::OfferKeyEventL
// ----------------------------------------------------------------------------
//
TKeyResponse CScaOptionContainer::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    FUNC_LOG;
    if ( aType == EEventKey && aKeyEvent.iCode == '5' ) // for test
        {
        User::Exit( 0 );
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// CScaOptionContainer::CheckedL
// ----------------------------------------------------------------------------
//
void CScaOptionContainer::CheckedL( TBool aCheck )
    {
    FUNC_LOG;
    aCheck;
    }

// ----------------------------------------------------------------------------
// CScaOptionContainer::HandleButtonEventL
// ----------------------------------------------------------------------------
//
void CScaOptionContainer::HandleButtonEventL( const CButton* aBtn )
    {
    FUNC_LOG;
    switch( aBtn->Id() )
        {
        case EScallopCmdModeBack:
            {
            --iCurrentMode;
            if ( iCurrentMode == -1 )
                {
                iCurrentMode = iModePageArray.Count() - 1;
                }
            ShowModePageL( iCurrentMode );
            }
            break;
        case EScallopCmdModeForward:
            {
            ++iCurrentMode;
            if ( iCurrentMode == iModePageArray.Count() )
                {
                iCurrentMode = 0;
                }
            ShowModePageL( iCurrentMode );
            }
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CScaOptionContainer::CScaOptionContainer
// ----------------------------------------------------------------------------
//
CScaOptionContainer::CScaOptionContainer( 
    MButtonObserver& aObserver, MResReader& aReader  )
    : CBaseContainer( aObserver, aReader )
    { // No implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaOptionContainer::ConstructL
// ----------------------------------------------------------------------------
//
void CScaOptionContainer::ConstructL( const TRect& aRect )
    {
    FUNC_LOG;
    CBaseContainer::ConstructL( aRect );
    
    iLayoutManager = CScaLayoutManager::NewL();
    iLayoutManager->ResolutionChanged();
    
    InitComponentArrayL();
    
    TRect theRect;

    iLayoutManager->LayoutRect( ESoundBoard, theRect );
    iSoundBoard = CBoard::NewL( *iGraphicsManager, theRect );
    iSoundBoard->SetContainerWindowL( *this );
    HBufC8* buffer = iReader.ResourceData( R_SCALLOP_OPTION_BARBOARD );
    TResourceReader reader;
    reader.SetBuffer( buffer );
    iSoundBoard->ConstructFromResourceL( reader );
    Components().AppendLC( iSoundBoard );
    CleanupStack::Pop( iSoundBoard );

    iLayoutManager->LayoutRect( EModeTitleBoard, theRect );
    iModeTitleBoard = CBoard::NewL( *iGraphicsManager, theRect );
    iModeTitleBoard->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_OPTION_BARBOARD );
    reader.SetBuffer( buffer );
    iModeTitleBoard->ConstructFromResourceL( reader );
    Components().AppendLC( iModeTitleBoard );
    CleanupStack::Pop( iModeTitleBoard );

    iLayoutManager->LayoutRect( EModeBoard, theRect );
    iModeBoard = CBoard::NewL( *iGraphicsManager, theRect );
    iModeBoard->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_OPTION_MODEBOARD );
    reader.SetBuffer( buffer );
    iModeBoard->ConstructFromResourceL( reader );
    Components().AppendLC( iModeBoard );
    CleanupStack::Pop( iModeBoard );

    iLayoutManager->LayoutRect( EModePicture, theRect );
    iModePicture = CIcon::NewL( *iGraphicsManager, theRect );
    iModePicture->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_OPTION_CLASSIC );
    reader.SetBuffer( buffer );
    iModePicture->ConstructFromResourceL( reader );
    Components().AppendLC( iModePicture );
    CleanupStack::Pop( iModePicture );

    iLayoutManager->LayoutRect( ESoundTitle, theRect );
    iSoundTitle = CTextPane::NewL( *iGraphicsManager, theRect );
    iSoundTitle->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_OPTION_SOUND_TITLE );
    reader.SetBuffer( buffer );
    iSoundTitle->ConstructFromResourceL( reader );
    Components().AppendLC( iSoundTitle );
    CleanupStack::Pop( iSoundTitle );

    iLayoutManager->LayoutRect( EModeTitle, theRect );
    iModeTitle = CTextPane::NewL( *iGraphicsManager, theRect );
    iModeTitle->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_OPTION_MODE_TITLE );
    reader.SetBuffer( buffer );
    iModeTitle->ConstructFromResourceL( reader );
    Components().AppendLC( iModeTitle );
    CleanupStack::Pop( iModeTitle );

    iLayoutManager->LayoutRect( EModeName, theRect );
    iModeName = CTextPane::NewL( *iGraphicsManager, theRect );
    iModeName->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_OPTION_MODE_NAME );
    reader.SetBuffer( buffer );
    iModeName->ConstructFromResourceL( reader );
    Components().AppendLC( iModeName );
    CleanupStack::Pop( iModeName );

    iLayoutManager->LayoutRect( EModeDetails, theRect );
    iModeDetails = CTextPane::NewL( *iGraphicsManager, theRect );
    iModeDetails->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_OPTION_MODE_DETAILS );
    reader.SetBuffer( buffer );
    iModeDetails->ConstructFromResourceL( reader );
    Components().AppendLC( iModeDetails );
    CleanupStack::Pop( iModeDetails );

    iLayoutManager->LayoutRect( EModeBack, theRect );
    iModeBack = CButton::NewL( *iGraphicsManager, theRect );
    iModeBack->SetContainerWindowL( *this );
    iModeBack->SetObserver( this );
    buffer = iReader.ResourceData( R_SCALLOP_MODE_BACK );
    reader.SetBuffer( buffer );
    iModeBack->ConstructFromResourceL( reader );
    Components().AppendLC( iModeBack );
    CleanupStack::Pop( iModeBack );

    iLayoutManager->LayoutRect( EModeForward, theRect );
    iModeForward = CButton::NewL( *iGraphicsManager, theRect );
    iModeForward->SetContainerWindowL( *this );
    iModeForward->SetObserver( this );
    buffer = iReader.ResourceData( R_SCALLOP_MODE_FORWARD );
    reader.SetBuffer( buffer );
    iModeForward->ConstructFromResourceL( reader );
    Components().AppendLC( iModeForward );
    CleanupStack::Pop( iModeForward );

    iLayoutManager->LayoutRect( ESoundProgress, theRect );
    iSoundProgress = CProgressBar::NewL( *iGraphicsManager, theRect );
    iSoundProgress->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_OPTION_SOUND_PROGRESS );
    reader.SetBuffer( buffer );
    iSoundProgress->ConstructFromResourceL( reader );
    Components().AppendLC( iSoundProgress );
    CleanupStack::Pop( iSoundProgress );

    iLayoutManager->LayoutRect( EModeCheckbox, theRect );
    iModeCheckbox = CCheckbox::NewL( *iGraphicsManager, theRect );
    iModeCheckbox->SetContainerWindowL( *this );
    iModeCheckbox->SetObserver( *this );
    buffer = iReader.ResourceData( R_SCALLOP_CHECKBOX_TIPS );
    reader.SetBuffer( buffer );
    iModeCheckbox->ConstructFromResourceL( reader );
    Components().AppendLC( iModeCheckbox );
    CleanupStack::Pop( iModeCheckbox );
    
    buffer = iReader.ResourceData( R_SCALLOP_MODES );
    reader.SetBuffer( buffer );
    SetupModePagesL( reader );
    
    iCurrentMode = 1;
    
    ShowModePageL( iCurrentMode );
    
    }

// ----------------------------------------------------------------------------
// CScaOptionContainer::SetupModePagesL
// ----------------------------------------------------------------------------
//
void CScaOptionContainer::SetupModePagesL( TResourceReader& aReader )
    {
    FUNC_LOG;
    TInt number = aReader.ReadInt16();

    // Add all newly created CModePage objects to the array
    for ( TInt index = 0; index < number; index++ )
        {
        CModePage* mode = CModePage::NewL( aReader );
        iModePageArray.Append( mode );
        }
    }

// ----------------------------------------------------------------------------
// CScaOptionContainer::ShowModePageL
// ----------------------------------------------------------------------------
//
void CScaOptionContainer::ShowModePageL( TInt aModeIx )
    {
    FUNC_LOG;
    iModePicture->Clear();
    TInt bmpId = iModePageArray[ aModeIx ]->BitmapId();
    iModePicture->SetBitmapL( bmpId );
    TInt maskId = iModePageArray[ aModeIx ]->MaskId();
    iModePicture->SetMaskL( maskId );
    TBuf<KMaxTextLen> title;
    title.Copy( *iModePageArray[ aModeIx ]->Title() );
    iModeName->SetTextL( title );
    TBuf<KMaxTextLen> details;
    details.Copy( *iModePageArray[ aModeIx ]->Details() );
    iModeDetails->SetTextL( details );
    }

// End of File
