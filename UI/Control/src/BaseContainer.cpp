/* ====================================================================
 * File: BaseContainer.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <akndef.h>
#include <aknutils.h>
#include <barsread.h>
#include "BaseContainer.h"
#include "GraphicsManager.h"
#include "Background.h"
#include "MenuBar.h"
#include "ResReader.h"
#include "ScaLogger.h"

// CONSTANTS
const TInt KDoDelayTimeout = 0;
const TInt KDoFrameUpdateTimeout = 250000;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CBaseContainer::~CBaseContainer
// ----------------------------------------------------------------------------
//
EXPORT_C CBaseContainer::~CBaseContainer()
    {
    Stop();
    delete iGraphicsManager;
    }

// ----------------------------------------------------------------------------
// CBaseContainer::SetMenuBarL
// ----------------------------------------------------------------------------
//
EXPORT_C void CBaseContainer::SetMenuBarL( TInt aResourceId )
    {
    FUNC_LOG;
    HBufC8* resourceData( NULL );
    resourceData = iReader.ResourceData( aResourceId );
    User::LeaveIfNull( resourceData );
    TResourceReader reader;
    reader.SetBuffer( resourceData );
    
    TInt btn1Id = reader.ReadInt32();
    TInt btn2Id = reader.ReadInt32();

    HBufC8* btn1Buf = iReader.ResourceData( btn1Id );
    TResourceReader btn1Reader;
    btn1Reader.SetBuffer( btn1Buf );
    iMenuBar->ConstructBtn1FromResourceL( btn1Reader );

    HBufC8* btn2Buf = iReader.ResourceData( btn2Id );
    TResourceReader btn2Reader;
    btn2Reader.SetBuffer( btn2Buf );
    iMenuBar->ConstructBtn2FromResourceL( btn2Reader );
    }

// ----------------------------------------------------------------------------
// CBaseContainer::SetBackgroundL
// ----------------------------------------------------------------------------
//
EXPORT_C void CBaseContainer::SetBackgroundL( TInt aResourceId )
    {
    FUNC_LOG;
    HBufC8* resourceData( NULL );
    resourceData = iReader.ResourceData( aResourceId );
    User::LeaveIfNull( resourceData );
    TResourceReader reader;
    reader.SetBuffer( resourceData );
    iBackground->ConstructFromResourceL( reader );
    }

// ----------------------------------------------------------------------------
// CBaseContainer::SizeChanged
// ----------------------------------------------------------------------------
//
EXPORT_C void CBaseContainer::SizeChanged()
    {
    if( iGraphicsManager && iBackground && iMenuBar )
        {
        TRect rect;
        AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, rect );
        iGraphicsManager->SetRect( rect );
        iBackground->SetRect( rect );
        iMenuBar->SetRect( MenuBarRect() );
        }
    }

// ----------------------------------------------------------------------------
// CBaseContainer::HandleResourceChange
// ----------------------------------------------------------------------------
//
EXPORT_C void CBaseContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SetExtentToWholeScreen();
        }
    }

// ----------------------------------------------------------------------------
// CBaseContainer::HandleButtonEventL
// ----------------------------------------------------------------------------
//
EXPORT_C void CBaseContainer::HandleButtonEventL( const CButton* aBtn )
    {
    FUNC_LOG;
    iObserver.HandleButtonEventL( aBtn );
    }

// ----------------------------------------------------------------------------
// CBaseContainer::CBaseContainer
// ----------------------------------------------------------------------------
//
EXPORT_C CBaseContainer::CBaseContainer( 
    MButtonObserver& aObserver, MResReader& aReader  )
    : iObserver( aObserver ), iReader( aReader )
    { // No implementation required
    }

// ----------------------------------------------------------------------------
// CBaseContainer::ConstructL
// ----------------------------------------------------------------------------
//
EXPORT_C void CBaseContainer::ConstructL( const TRect& aRect )
    {
    FUNC_LOG;
    // Creates a control's window.
    // The created window is the child of the application's window group.
    CreateWindowL();

    // Sets the control's extent ¡ª specifying a TRect.
    // Calling this function results in a call to SizeChanged.
    SetRect( aRect ); 
    
    SetupGraphicsManagerL( aRect );

    InitComponentArrayL();
    
    INFO( "Create a instance of CBackground class..." );
    iBackground = CBackground::NewL( *iGraphicsManager, aRect );
    INFO( "Create iBackground successfully!!!" );
    iBackground->SetContainerWindowL( *this );
    Components().AppendLC( iBackground );
    CleanupStack::Pop( iBackground );
    
    INFO( "Create a instance of CMenuBar class..." );
    iMenuBar = CMenuBar::NewL( *iGraphicsManager, MenuBarRect() );
    INFO( "Create iMenuBar successfully!!!" );
    iMenuBar->SetContainerWindowL( *this );
    iMenuBar->SetObserver( &iObserver );
    Components().AppendLC( iMenuBar );
    CleanupStack::Pop( iMenuBar );

    iPeriodic = CPeriodic::NewL( CActive::EPriorityLow );
    iPeriodic->Cancel();
    iPeriodic->Start( 
            KDoDelayTimeout,
            KDoFrameUpdateTimeout,
            TCallBack( TimerCallback, this ) 
            );

    // Enable Drag Events.
    EnableDragEvents();

    // Sets control as ready to be drawn.
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBaseContainer::SetupGraphicsManagerL
// ----------------------------------------------------------------------------
//
EXPORT_C void CBaseContainer::SetupGraphicsManagerL( const TRect& aRect )
    {
    INFO( "Create a instance of CGraphicsManager class..." );
    iGraphicsManager = CGraphicsManager::NewL( aRect );
    INFO( "Create iGraphicsManager successfully!!!" );
    }

// ----------------------------------------------------------------------------
// CBaseContainer::Stop
// ----------------------------------------------------------------------------
//
EXPORT_C TInt CBaseContainer::TimerCallback( TAny* aPtr )
    {
    CBaseContainer* self = static_cast<CBaseContainer*> ( aPtr );
    self->DoFrame();
    return 0;
    }

// ----------------------------------------------------------------------------
// CBaseContainer::MenuBarRect
// ----------------------------------------------------------------------------
//
TRect CBaseContainer::MenuBarRect()
    {
    FUNC_LOG;
    TRect rect;
    switch ( AknLayoutUtils::CbaLocation() )
        {
        case AknLayoutUtils::EAknCbaLocationBottom: // Landscape and Portrait
            { 
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPane, rect );
            }
            break;
        case AknLayoutUtils::EAknCbaLocationRight: // Only Landscape
            {
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPane, rect );
            }
            break;
        case AknLayoutUtils::EAknCbaLocationLeft: // Only landscape
            { 
            AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EControlPaneTop, rect );
            }
            break;
        default:
            break;
        }
    return rect;
    }


// ----------------------------------------------------------------------------
// CBaseContainer::Stop
// ----------------------------------------------------------------------------
//
void CBaseContainer::Stop()
    {
    FUNC_LOG;
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();

        delete iPeriodic;
        iPeriodic = NULL;   
        }
    }

// ----------------------------------------------------------------------------
// CBaseContainer::DoFrame
// ----------------------------------------------------------------------------
//
void CBaseContainer::DoFrame()
    {
    Window().Invalidate( Rect() );
    ActivateGc();
    Window().BeginRedraw( Rect() );
    iGraphicsManager->Merge();
    CWindowGc& gc = SystemGc();
    gc.BitBltMasked( 
            TPoint( 0, 0 ), 
            iGraphicsManager->Bitmap(), 
            Rect(),
            iGraphicsManager->Mask(),
            EFalse
            );

    Window().EndRedraw();
    DeactivateGc();
    }


// End of File
