/* ====================================================================
 * File: LayoutManager.cpp
 * Created: 03/15/09
 * Modified: 03/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <AknUtils.h>
#include <e32property.h>
#include "LayoutManager.h"

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CTe2LayoutManager::NewL
// ----------------------------------------------------------------------------
//
CTe2LayoutManager* CTe2LayoutManager::NewL()
    {
    CTe2LayoutManager* self = new (ELeave) CTe2LayoutManager;
    CleanupStack::PushL (self );
    self->ConstructL ();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CTe2LayoutManager::~CTe2LayoutManager
// ----------------------------------------------------------------------------
//
CTe2LayoutManager::~CTe2LayoutManager()
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CTe2LayoutManager::ResolutionChanged
//
// Function can be used to update internal resolution value.
// Typically called by container in startup,
// and when dynamic layout variant switch has occured.
//
// ----------------------------------------------------------------------------
//
void CTe2LayoutManager::ResolutionChanged( TOrientation aOrientation )
    {
    // Get screen parameters for solving layout
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );

    switch ( screenRect.Width() )
        {
        case KQvgaPortraitWidth:
            {
                {
                if ( aOrientation == ELandscape )
                    iResolution = EQvgaLandscape;
                else
                    iResolution = EQvgaPortrait;
                }
            }
            break;
        case KQvgaLandscapeWidth: // Also KHvgaPortraitWidth
            {
            if ( screenRect.Height() == KQvgaLandscapeHeight )
                {
                if ( aOrientation == EPortrait )
                    iResolution = EQvgaPortrait;
                else
                    iResolution = EQvgaLandscape;
                }
            }
            break;
        default:
            iResolution = ENotSupported;
            break;
        }
    }

// ----------------------------------------------------------------------------
// CTe2LayoutManager::LayoutRect
// LayoutRect should be called from control's SizeChanged() method.
// ----------------------------------------------------------------------------
//
TRect CTe2LayoutManager::LayoutRect( TTe2Component aComponent ) const
    {
    TRect layoutRect( 0, 0, 0,0 );

    switch ( aComponent )
        {
        // Background
        case EBackground:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    layoutRect.SetRect( 
                            KQvgaLscBgLeft,
                            KQvgaLscBgTop,
                            KQvgaLscBgRight,
                            KQvgaLscBgBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    layoutRect.SetRect( 
                            KQvgaPrtBgLeft,
                            KQvgaPrtBgTop,
                            KQvgaPrtBgRight,
                            KQvgaPrtBgBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }
        
        // Logo
        case ELogo:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    layoutRect.SetRect( 
                            KQvgaLscLogoLeft,
                            KQvgaLscLogoTop,
                            KQvgaLscLogoRight,
                            KQvgaLscLogoBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    layoutRect.SetRect( 
                            KQvgaPrtLogoLeft,
                            KQvgaPrtLogoTop,
                            KQvgaPrtLogoRight,
                            KQvgaPrtLogoBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Softkey1
        case ESoftkey1:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    layoutRect.SetRect( 
                            KQvgaLscSk1Left,
                            KQvgaLscSk1Top,
                            KQvgaLscSk1Right,
                            KQvgaLscSk1Bottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    layoutRect.SetRect( 
                            KQvgaPrtSk1Left,
                            KQvgaPrtSk1Top,
                            KQvgaPrtSk1Right,
                            KQvgaPrtSk1Bottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Softkey2
        case ESoftkey2:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    layoutRect.SetRect( 
                            KQvgaLscSk2Left,
                            KQvgaLscSk2Top,
                            KQvgaLscSk2Right,
                            KQvgaLscSk2Bottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    layoutRect.SetRect( 
                            KQvgaPrtSk2Left,
                            KQvgaPrtSk2Top,
                            KQvgaPrtSk2Right,
                            KQvgaPrtSk2Bottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // MainMenu
        case EMainMenu:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    layoutRect.SetRect( 
                            KQvgaLscMMLeft,
                            KQvgaLscMMTop,
                            KQvgaLscMMRight,
                            KQvgaLscMMBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    layoutRect.SetRect( 
                            KQvgaPrtMMLeft,
                            KQvgaPrtMMTop,
                            KQvgaPrtMMRight,
                            KQvgaPrtMMBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Scroller
        case EScroller:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    layoutRect.SetRect( 
                            KQvgaLscScrollerLeft,
                            KQvgaLscScrollerTop,
                            KQvgaLscScrollerRight,
                            KQvgaLscScrollerBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    layoutRect.SetRect( 
                            KQvgaPrtScrollerLeft,
                            KQvgaPrtScrollerTop,
                            KQvgaPrtScrollerRight,
                            KQvgaPrtScrollerBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Primary Matrix
        case EPrimaryMatrix:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    layoutRect.SetRect( 
                            KQvgaLscPMLeft,
                            KQvgaLscPMTop,
                            KQvgaLscPMRight,
                            KQvgaLscPMBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    layoutRect.SetRect( 
                            KQvgaPrtPMLeft,
                            KQvgaPrtPMTop,
                            KQvgaPrtPMRight,
                            KQvgaPrtPMBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Secondary Matrix
        case ESecondaryMatrix:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    layoutRect.SetRect( 
                            KQvgaLscSMLeft,
                            KQvgaLscSMTop,
                            KQvgaLscSMRight,
                            KQvgaLscSMBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    layoutRect.SetRect( 
                            KQvgaPrtSMLeft,
                            KQvgaPrtSMTop,
                            KQvgaPrtSMRight,
                            KQvgaPrtSMBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Scorekeeper
        case EScorekeeper:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    layoutRect.SetRect( 
                            KQvgaLscScorekeeperLeft,
                            KQvgaLscScorekeeperTop,
                            KQvgaLscScorekeeperRight,
                            KQvgaLscScorekeeperBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    layoutRect.SetRect( 
                            KQvgaPrtScorekeeperLeft,
                            KQvgaPrtScorekeeperTop,
                            KQvgaPrtScorekeeperRight,
                            KQvgaPrtScorekeeperBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        default:
            break;
        }
    return layoutRect;
    }

// ----------------------------------------------------------------------------
// CTe2LayoutManager::LayoutRect
// ----------------------------------------------------------------------------
//
CTe2LayoutManager::CTe2LayoutManager()
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CTe2LayoutManager::ConstructL
// ----------------------------------------------------------------------------
//
void CTe2LayoutManager::ConstructL()
    { // No implementation required.
    }

// End of File
