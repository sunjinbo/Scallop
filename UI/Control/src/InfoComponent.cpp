/* ====================================================================
 * File: InfoComponent.cpp
 * Created: 12/06/09
 * Modified: 12/06/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <aknutils.h>
#include <barsread.h>
#include <BmpUtils.h>
#include <Info.mbg>
#include "InfoComponent.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"
#include "Button.h"
#include "Checkbox.h"
#include "TextPane.h"
#include "ResReader.h"
#include "InfoComponentObserver.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KMbmInfoFileName, "Z:\\resource\\apps\\info.mbm" );
#else
_LIT( KMbmInfoFileName, "\\resource\\apps\\info.mbm" );
#endif // __WINS__

const TInt KTextLen = 4;
const TInt KTimerDelayTimeout = 0;
const TInt KTimerTimeout = 1000000;
const TInt KTimerTerminal = 0;

const TInt KInfoComponentHorizontal = 36;
const TInt KInfoComponentVertical = 10;

const TInt KTextPaneHorizontal = 27;
const TInt KTextPaneVertical = 6;
const TInt KTextPaneTopPos = 1;
const TInt KTextPaneLeftPos = 1;

const TInt KCheckboxHorizontal = 27;
const TInt KCheckboxVertical = 2;
const TInt KCheckboxTopPos = 7;
const TInt KCheckboxLeftPos = 1;

const TInt KButtonHorizontal = 5;
const TInt KButtonVertical = 5;
const TInt KButtonTopPos = 2;
const TInt KButtonLeftPos = 29;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CInfoComponent::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CInfoComponent* CInfoComponent::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CInfoComponent* self = new (ELeave) CInfoComponent( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CInfoComponent::~CInfoComponent
// ----------------------------------------------------------------------------
//
EXPORT_C CInfoComponent::~CInfoComponent()
    {
    delete iDlgLayer;
    if ( iPeriodic )
        {
        iPeriodic->Cancel();
        delete iPeriodic;
        }
    }

// ----------------------------------------------------------------------------
// CInfoComponent::SetObserver
// ----------------------------------------------------------------------------
//
EXPORT_C void CInfoComponent::SetObserver( MInfoComponentObserver& aObserver )
    {
    iObserver = &aObserver;
    }

// ----------------------------------------------------------------------------
// CInfoComponent::SetResReader
// ----------------------------------------------------------------------------
//
EXPORT_C void CInfoComponent::SetResReader( MResReader& aReader )
    {
    iResReader = &aReader;
    }

// ----------------------------------------------------------------------------
// CInfoComponent::SetInfoResourceId
// ----------------------------------------------------------------------------
//
EXPORT_C void CInfoComponent::SetInfoResourceIdL( TInt aInfoResourceId )
    {
    User::LeaveIfNull( iResReader );
    HBufC8* resourceBuf = NULL;
    resourceBuf = iResReader->ResourceData( aInfoResourceId );
    User::LeaveIfNull( resourceBuf );
    TResourceReader reader;
    reader.SetBuffer( resourceBuf );

    CBmpUtils* utils = CBmpUtils::NewL( 
        KMbmInfoFileName, 
        EMbmInfoDlg,
        EMbmInfoLastElement 
        );
    CleanupStack::PushL( utils );

    TInt bitmapIx = reader.ReadInt32 ();
    utils->SetSize( bitmapIx, Rect().Size() );
    CFbsBitmap* bitmap = utils->Bitmap( bitmapIx );
    iDlgLayer->DrawBitmap( Rect(), bitmap );
    TInt maskIx = reader.ReadInt32 ();
    utils->SetSize( maskIx, Rect().Size() );
    CFbsBitmap* mask = utils->Bitmap( maskIx );
    iDlgLayer->DrawMask( Rect(), mask );

    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;

    TInt textPane = reader.ReadInt32();
    TInt btn = reader.ReadInt32();
    TInt checkbox = reader.ReadInt32();

    HBufC8* textPaneBuf = iResReader->ResourceData( textPane );
    reader.SetBuffer( textPaneBuf );
    iTextPane->ConstructFromResourceL( reader );
    HBufC8* btnBuf = iResReader->ResourceData( btn );
    reader.SetBuffer( btnBuf );
    iBtnOk->ConstructFromResourceL( reader );
    HBufC8* checkboxBuf = iResReader->ResourceData( checkbox );
    reader.SetBuffer( checkboxBuf );
    iCheckbox->ConstructFromResourceL( reader );
    }

// ----------------------------------------------------------------------------
// CInfoComponent::SetTextL
// ----------------------------------------------------------------------------
//
EXPORT_C void CInfoComponent::SetTextL( const TDesC& aText )
    {
    iTextPane->SetTextL( aText );
    }

// ----------------------------------------------------------------------------
// CInfoComponent::SetVisible
// ----------------------------------------------------------------------------
//
EXPORT_C void CInfoComponent::SetVisible( TBool aVisible )
    {
    iDlgLayer->SetVisible( aVisible );
    iTextPane->SetVisible( aVisible );
    iCheckbox->SetVisible( aVisible );
    iBtnOk->SetVisible( aVisible );
    }

// ----------------------------------------------------------------------------
// CInfoComponent::RestartTimer
// ----------------------------------------------------------------------------
//
EXPORT_C void CInfoComponent::RestartTimer( TInt aSecond )
    {
    iTimer = aSecond;
    StartTimer();
    }

// ----------------------------------------------------------------------------
// CInfoComponent::StartTimer
// ----------------------------------------------------------------------------
//
EXPORT_C void CInfoComponent::StartTimer()
    {
    iPeriodic->Cancel();
    iPeriodic->Start(
            KTimerDelayTimeout,
            KTimerTimeout,
            TCallBack( TimerCallback, this ) 
            );
    }

// ----------------------------------------------------------------------------
// CInfoComponent::StopTimer
// ----------------------------------------------------------------------------
//
EXPORT_C void CInfoComponent::StopTimer()
    {
    if ( iPeriodic->IsActive() )
        {
        iPeriodic->Cancel();
        }
    }

// ----------------------------------------------------------------------------
// CInfoComponent::SizeChanged
// ----------------------------------------------------------------------------
//
void CInfoComponent::SizeChanged()
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CInfoComponent::CheckedL
// ----------------------------------------------------------------------------
//
void CInfoComponent::CheckedL( TBool aCheck )
    {
    if ( iObserver )
        {
        iObserver->CheckedL( aCheck );
        }
    }

// ----------------------------------------------------------------------------
// CInfoComponent::HandleButtonEventL
// ----------------------------------------------------------------------------
//
void CInfoComponent::HandleButtonEventL( const CButton* /*aBtn*/ )
    {
    SetVisible( EFalse );
    }

// ----------------------------------------------------------------------------
// CInfoComponent::CInfoComponent
// ----------------------------------------------------------------------------
//
CInfoComponent::CInfoComponent( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CInfoComponent::ConstructL
// ----------------------------------------------------------------------------
//
void CInfoComponent::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    iDlgLayer = CGraphicsLayer::NewL( aRect, ECtrlBackground );
    iGraphicsManager.RegisterLayer( iDlgLayer );

    InitComponentArrayL();
    
    TRect theRect;
    LayoutComponent( ETextPane, theRect );
    iTextPane = CTextPane::NewL( iGraphicsManager, theRect );
    iTextPane->SetContainerWindowL( *this );
    Components().AppendLC( iTextPane );
    CleanupStack::Pop( iTextPane );
    
    LayoutComponent( ECheckbox, theRect );
    iCheckbox = CCheckbox::NewL( iGraphicsManager, theRect );
    iCheckbox->SetContainerWindowL( *this );
    iCheckbox->SetObserver( *this );
    Components().AppendLC( iCheckbox );
    CleanupStack::Pop( iCheckbox );

    LayoutComponent( EButton, theRect );
    iBtnOk = CButton::NewL( iGraphicsManager, theRect );
    iBtnOk->SetContainerWindowL( *this );
    iBtnOk->SetObserver( this );
    Components().AppendLC( iBtnOk );
    CleanupStack::Pop( iBtnOk );

    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CInfoComponent::LayoutComponent
// ----------------------------------------------------------------------------
//
void CInfoComponent::LayoutComponent( TInfoComponent aComponent, TRect& aRect )
    {
    TRect theRect( iDlgLayer->Rect() );
    TInt w = theRect.Width() / KInfoComponentHorizontal;
    TInt h = theRect.Height() / KInfoComponentVertical;
    TPoint tl, br;
    switch ( aComponent )
        {
        case EButton:
            tl.iX = theRect.iTl.iX + w * KButtonLeftPos;
            tl.iY = theRect.iTl.iY + h * KButtonTopPos;
            br.iX = tl.iX + w * KButtonHorizontal;
            br.iY = tl.iY + h * KButtonVertical;
            aRect.SetRect( tl, br );
            break;
        case ETextPane:
            tl.iX = theRect.iTl.iX + w * KTextPaneLeftPos;
            tl.iY = theRect.iTl.iY + h * KTextPaneTopPos;
            br.iX = tl.iX + w * KTextPaneHorizontal;
            br.iY = tl.iY + h * KTextPaneVertical;
            aRect.SetRect( tl, br );
            break;
        case ECheckbox:
            tl.iX = theRect.iTl.iX + w * KCheckboxLeftPos;
            tl.iY = theRect.iTl.iY + h * KCheckboxTopPos;
            br.iX = tl.iX + w * KCheckboxHorizontal;
            br.iY = tl.iY + h * KCheckboxVertical;
            aRect.SetRect( tl, br );
            break;
        default:
            break;
        }
    }

// ----------------------------------------------------------------------------
// CInfoComponent::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CInfoComponent::TimerCallback( TAny* aPtr )
    {
    CInfoComponent* self = static_cast<CInfoComponent*> ( aPtr );
    self->DoTimer();
    return 0;
    }

// ----------------------------------------------------------------------------
// CInfoComponent::DoTimer
// ----------------------------------------------------------------------------
//
void CInfoComponent::DoTimer()
    {
    if ( --iTimer != KTimerTerminal )
        {
        TBuf<KTextLen> txt;
        txt.AppendNum( iTimer );
        TRAP_IGNORE( iBtnOk->SetTextL( txt ) );
        }
    else
        {
        SetVisible( EFalse );
        }
    }

// End of File
