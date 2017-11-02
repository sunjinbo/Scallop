/* ====================================================================
 * File: ScaHelpContainer.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <akndef.h>
#include <aknutils.h>
#include <barsread.h>
#include <ButtonObserver.h>
#include <ResReader.h>
#include <Button.h>
#include <Icon.h>
#include <Board.h>
#include <TextPane.h>
#include <Scallop.rsg>
#include "ScaHelpContainer.h"
#include "ScaLayoutManager.h"
#include "Scallop.hrh"
#include "ScaLogger.h"

// CONSTANTS
_LIT( KBackslash, "/" );

const TInt KMaxTextLen = 256;
const TInt KFirstPageNum = 1;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CHelpPage::NewL
// ----------------------------------------------------------------------------
//
CHelpPage* CHelpPage::NewL( TResourceReader& aReader )
    {
    CHelpPage* self = new (ELeave) CHelpPage;
    CleanupStack::PushL (self );
    self->ConstructL ( aReader );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CHelpPage::~CHelpPage
// ----------------------------------------------------------------------------
//
CHelpPage::~CHelpPage()
    {
    FUNC_LOG;
    delete iHelpText;
    }

// ----------------------------------------------------------------------------
// CHelpPage::Title
// ----------------------------------------------------------------------------
//
const TDesC* CHelpPage::HelpText() const
    {
    return iHelpText;
    }

// ----------------------------------------------------------------------------
// CHelpPage::BitmapId
// ----------------------------------------------------------------------------
//
TInt CHelpPage::BitmapId() const
    {
    FUNC_LOG;
    return iBitmapId;
    }

// ----------------------------------------------------------------------------
// CHelpPage::MaskId
// ----------------------------------------------------------------------------
//
TInt CHelpPage::MaskId() const
    {
    FUNC_LOG;
    return iMaskId;
    }

// ----------------------------------------------------------------------------
// CHelpPage::CHelpPage
// ----------------------------------------------------------------------------
//
CHelpPage::CHelpPage()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CHelpPage::ConstructL
// ----------------------------------------------------------------------------
// 
void CHelpPage::ConstructL( TResourceReader& aReader )
    {
    FUNC_LOG;
    iBitmapId = aReader.ReadUint32();
    iMaskId = aReader.ReadUint32();
    iHelpText = aReader.ReadHBufCL();
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::~CScaHelpContainer
// ----------------------------------------------------------------------------
//
CScaHelpContainer* CScaHelpContainer::NewL(  const TRect& aRect, 
    MButtonObserver& aObserver, 
    MResReader& aReader  )
    {
    CScaHelpContainer* self = new (ELeave) CScaHelpContainer( aObserver, aReader );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::~CScaHelpContainer
// ----------------------------------------------------------------------------
//
CScaHelpContainer::~CScaHelpContainer()
    {
    delete iLayoutManager;
    iHelpPageArray.ResetAndDestroy();
    iHelpPageArray.Close();
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::OfferKeyEventL
// ----------------------------------------------------------------------------
//
TKeyResponse CScaHelpContainer::OfferKeyEventL( const TKeyEvent& aKeyEvent, TEventCode aType )
    {
    FUNC_LOG;
    if ( aType == EEventKey && aKeyEvent.iCode == '5' ) // for test
        {
        User::Exit( 0 );
        }
    return EKeyWasConsumed;
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::HandleButtonEventL
// ----------------------------------------------------------------------------
//
void CScaHelpContainer::HandleButtonEventL( const CButton* aBtn )
    {
    FUNC_LOG;
    switch( aBtn->Id() )
        {
        case EScallopCmdHelpBack:
            ShowBackPageL();
            break;
        case EScallopCmdHelpForward:
            ShowForwardPageL();
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::CScaHelpContainer
// ----------------------------------------------------------------------------
//
CScaHelpContainer::CScaHelpContainer( 
    MButtonObserver& aObserver, MResReader& aReader  )
    : CBaseContainer( aObserver, aReader )
    { // No implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::ConstructL
// ----------------------------------------------------------------------------
//
void CScaHelpContainer::ConstructL( const TRect& aRect )
    {
    FUNC_LOG;
    CBaseContainer::ConstructL( aRect );
    
    iLayoutManager = CScaLayoutManager::NewL();
    iLayoutManager->ResolutionChanged();

    InitComponentArrayL();

    TRect theRect;

    iLayoutManager->LayoutRect( EHelpTitleBoard, theRect );
    iHelpTitleBoard = CBoard::NewL( *iGraphicsManager, theRect );
    iHelpTitleBoard->SetContainerWindowL( *this );
    HBufC8* buffer = iReader.ResourceData( R_SCALLOP_OPTION_BARBOARD );
    TResourceReader reader;
    reader.SetBuffer( buffer );
    iHelpTitleBoard->ConstructFromResourceL( reader );
    Components().AppendLC( iHelpTitleBoard );
    CleanupStack::Pop( iHelpTitleBoard );

    iLayoutManager->LayoutRect( EHelpBoard, theRect );
    iHelpBoard = CBoard::NewL( *iGraphicsManager, theRect );
    iHelpBoard->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_HELP_HELPBOARD );
    reader.SetBuffer( buffer );
    iHelpBoard->ConstructFromResourceL( reader );
    Components().AppendLC( iHelpBoard );
    CleanupStack::Pop( iHelpBoard );

    iLayoutManager->LayoutRect( EHelpFirstPicture, theRect );
    iHelpFirstPicture = CIcon::NewL( *iGraphicsManager, theRect );
    iHelpFirstPicture->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_HELP_FIRST_PICTURE );
    reader.SetBuffer( buffer );
    iHelpFirstPicture->ConstructFromResourceL( reader );
    Components().AppendLC( iHelpFirstPicture );
    CleanupStack::Pop( iHelpFirstPicture );

    iLayoutManager->LayoutRect( EHelpSecondPicture, theRect );
    iHelpSecondPicture = CIcon::NewL( *iGraphicsManager, theRect );
    iHelpSecondPicture->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_HELP_SECOND_PICTURE );
    reader.SetBuffer( buffer );
    iHelpSecondPicture->ConstructFromResourceL( reader );
    Components().AppendLC( iHelpSecondPicture );
    CleanupStack::Pop( iHelpSecondPicture );

    iLayoutManager->LayoutRect( EHelpTitle, theRect );
    iHelpTitle = CTextPane::NewL( *iGraphicsManager, theRect );
    iHelpTitle->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_HELP_TITLE );
    reader.SetBuffer( buffer );
    iHelpTitle->ConstructFromResourceL( reader );
    Components().AppendLC( iHelpTitle );
    CleanupStack::Pop( iHelpTitle );

    iLayoutManager->LayoutRect( EHelpFirstText, theRect );
    iHelpFirstText = CTextPane::NewL( *iGraphicsManager, theRect );
    iHelpFirstText->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_HELP_FIRST_TEXT );
    reader.SetBuffer( buffer );
    iHelpFirstText->ConstructFromResourceL( reader );
    Components().AppendLC( iHelpFirstText );
    CleanupStack::Pop( iHelpFirstText );

    iLayoutManager->LayoutRect( EHelpSecondText, theRect );
    iHelpSecondText = CTextPane::NewL( *iGraphicsManager, theRect );
    iHelpSecondText->SetContainerWindowL( *this );
    buffer = iReader.ResourceData( R_SCALLOP_HELP_SECOND_TEXT );
    reader.SetBuffer( buffer );
    iHelpSecondText->ConstructFromResourceL( reader );
    Components().AppendLC( iHelpSecondText );
    CleanupStack::Pop( iHelpSecondText );

    iLayoutManager->LayoutRect( EHelpBack, theRect );
    iHelpBack = CButton::NewL( *iGraphicsManager, theRect );
    iHelpBack->SetContainerWindowL( *this );
    iHelpBack->SetObserver( this );
    buffer = iReader.ResourceData( R_SCALLOP_HELP_BACK );
    reader.SetBuffer( buffer );
    iHelpBack->ConstructFromResourceL( reader );
    Components().AppendLC( iHelpBack );
    CleanupStack::Pop( iHelpBack );

    iLayoutManager->LayoutRect( EHelpForward, theRect );
    iHelpForward = CButton::NewL( *iGraphicsManager, theRect );
    iHelpForward->SetContainerWindowL( *this );
    iHelpForward->SetObserver( this );
    buffer = iReader.ResourceData( R_SCALLOP_HELP_FORWARD );
    reader.SetBuffer( buffer );
    iHelpForward->ConstructFromResourceL( reader );
    Components().AppendLC( iHelpForward );
    CleanupStack::Pop( iHelpForward );

    buffer = iReader.ResourceData( R_SCALLOP_HELPS );
    reader.SetBuffer( buffer );
    SetupHelpPagesL( reader );
    
    iCurrentPage = KFirstPageNum;

    ShowHelpPageL( iCurrentPage );
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::SetupHelpPagesL
// ----------------------------------------------------------------------------
//
void CScaHelpContainer::SetupHelpPagesL( TResourceReader& aReader )
    {
    FUNC_LOG;
    TInt number = aReader.ReadInt16();

    // Add all newly created CModePage objects to the array
    for ( TInt index = 0; index < number; index++ )
        {
        CHelpPage* mode = CHelpPage::NewL( aReader );
        iHelpPageArray.Append( mode );
        }
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::ShowHelpPageL
// ----------------------------------------------------------------------------
//
void CScaHelpContainer::ShowHelpPageL( TInt aPageNum )
    {
    FUNC_LOG;
    TInt pageNr( PageNumber() );
    if ( aPageNum > 0 && aPageNum < pageNr + 1  )
        {
        TBuf<KMaxTextLen> title;
        title.AppendNum( aPageNum );
        title.Append( KBackslash );
        title.AppendNum( pageNr );
        iHelpTitle->SetTextL( title );
        
        TInt firstIx = aPageNum * 2 - 2;
        if ( firstIx < iHelpPageArray.Count() )
            {
            iHelpFirstPicture->Clear();
            TInt bmpId = iHelpPageArray[ firstIx ]->BitmapId();
            iHelpFirstPicture->SetBitmapL( bmpId );
            TInt maskId = iHelpPageArray[ firstIx ]->MaskId();
            iHelpFirstPicture->SetMaskL( maskId );

            TBuf<KMaxTextLen> firstBuffer;
            firstBuffer.Copy( *iHelpPageArray[ firstIx ]->HelpText() );
            iHelpFirstText->SetTextL( firstBuffer );
            }

        TInt secondIx = aPageNum * 2 - 1;
        if ( secondIx < iHelpPageArray.Count() )
            {
            iHelpSecondPicture->Clear();
            TInt bmpId = iHelpPageArray[ secondIx ]->BitmapId();
            iHelpSecondPicture->SetBitmapL( bmpId );
            TInt maskId = iHelpPageArray[ secondIx ]->MaskId();
            iHelpSecondPicture->SetMaskL( maskId );

            TBuf<KMaxTextLen> secondBuffer;
            secondBuffer.Copy( *iHelpPageArray[ secondIx ]->HelpText() );
            iHelpSecondText->SetTextL( secondBuffer );
            }

        }
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::ShowBackPageL
// ----------------------------------------------------------------------------
//
void CScaHelpContainer::ShowBackPageL()
    {
    FUNC_LOG;
    iCurrentPage--;
    if ( iCurrentPage < KFirstPageNum )
        {
        iCurrentPage = PageNumber();
        }
    ShowHelpPageL( iCurrentPage );
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::ShowForwardPageL
// ----------------------------------------------------------------------------
//
void CScaHelpContainer::ShowForwardPageL()
    {
    FUNC_LOG;
    iCurrentPage++;
    if ( iCurrentPage > PageNumber() )
        {
        iCurrentPage = KFirstPageNum;
        }
    ShowHelpPageL( iCurrentPage );
    }

// ----------------------------------------------------------------------------
// CScaHelpContainer::PageNumber
// ----------------------------------------------------------------------------
//
TInt CScaHelpContainer::PageNumber() const
        {
        TInt count( iHelpPageArray.Count() );
        return ( count / 2 + count % 2 );
        }

// End of File
