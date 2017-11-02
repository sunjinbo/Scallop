/* ====================================================================
 * File: ScaLayoutManager.cpp
 * Created: 11/03/09
 * Modified: 12/25/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <AknUtils.h>
#include <e32property.h>
#include "ScaLayoutManager.h"
#include "ScaLogger.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScaLayoutManager::NewL
// ----------------------------------------------------------------------------
//
CScaLayoutManager* CScaLayoutManager::NewL()
    {
    CScaLayoutManager* self = new (ELeave) CScaLayoutManager;
    CleanupStack::PushL (self );
    self->ConstructL ();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CScaLayoutManager::~CScaLayoutManager
// ----------------------------------------------------------------------------
//
CScaLayoutManager::~CScaLayoutManager()
    { // No implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaLayoutManager::ResolutionChanged
//
// Function can be used to update internal resolution value.
// Typically called by container in startup,
// and when dynamic layout variant switch has occured.
//
// ----------------------------------------------------------------------------
//
void CScaLayoutManager::ResolutionChanged( TOrientation aOrientation )
    {
    FUNC_LOG;
    INFO_1( "The current orientation is %d", aOrientation );
    // Get screen parameters for solving layout
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );
    TInt w = screenRect.Width();
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
// CScaLayoutManager::LayoutRect
// LayoutRect should be called from control's SizeChanged() method.
// ----------------------------------------------------------------------------
//
void CScaLayoutManager::LayoutRect( TComponent aComponent, TRect& aRect ) const
    {
    FUNC_LOG;
    switch ( aComponent )
        {
        // Welcome
        case EWelcome:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscWelcomeLeft,
                            KQvgaLscWelcomeTop,
                            KQvgaLscWelcomeRight,
                            KQvgaLscWelcomeBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtWelcomeLeft,
                            KQvgaPrtWelcomeTop,
                            KQvgaPrtWelcomeRight,
                            KQvgaPrtWelcomeBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Brand
        case EBrand:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscBrandLeft,
                            KQvgaLscBrandTop,
                            KQvgaLscBrandRight,
                            KQvgaLscBrandBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtBrandLeft,
                            KQvgaPrtBrandTop,
                            KQvgaPrtBrandRight,
                            KQvgaPrtBrandBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Start
        case EStart:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscStartLeft,
                            KQvgaLscStartTop,
                            KQvgaLscStartRight,
                            KQvgaLscStartBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtStartLeft,
                            KQvgaPrtStartTop,
                            KQvgaPrtStartRight,
                            KQvgaPrtStartBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Option
        case EOption:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscOptionLeft,
                            KQvgaLscOptionTop,
                            KQvgaLscOptionRight,
                            KQvgaLscOptionBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtOptionLeft,
                            KQvgaPrtOptionTop,
                            KQvgaPrtOptionRight,
                            KQvgaPrtOptionBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Record
        case ERecord:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscRecordLeft,
                            KQvgaLscRecordTop,
                            KQvgaLscRecordRight,
                            KQvgaLscRecordBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtRecordLeft,
                            KQvgaPrtRecordTop,
                            KQvgaPrtRecordRight,
                            KQvgaPrtRecordBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Help
        case EHelp:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpLeft,
                            KQvgaLscHelpTop,
                            KQvgaLscHelpRight,
                            KQvgaLscHelpBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpLeft,
                            KQvgaPrtHelpTop,
                            KQvgaPrtHelpRight,
                            KQvgaPrtHelpBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Quit
        case EQuit:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscQuitLeft,
                            KQvgaLscQuitTop,
                            KQvgaLscQuitRight,
                            KQvgaLscQuitBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtQuitLeft,
                            KQvgaPrtQuitTop,
                            KQvgaPrtQuitRight,
                            KQvgaPrtQuitBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Matrix
        case EMatrix:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscMatrixLeft,
                            KQvgaLscMatrixTop,
                            KQvgaLscMatrixRight,
                            KQvgaLscMatrixBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtMatrixLeft,
                            KQvgaPrtMatrixTop,
                            KQvgaPrtMatrixRight,
                            KQvgaPrtMatrixBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Masking
        case EMasking:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscMaskingLeft,
                            KQvgaLscMaskingTop,
                            KQvgaLscMaskingRight,
                            KQvgaLscMaskingBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtMaskingLeft,
                            KQvgaPrtMaskingTop,
                            KQvgaPrtMaskingRight,
                            KQvgaPrtMaskingBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Level
        case ELevel:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscLevelLeft,
                            KQvgaLscLevelTop,
                            KQvgaLscLevelRight,
                            KQvgaLscLevelBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtLevelLeft,
                            KQvgaPrtLevelTop,
                            KQvgaPrtLevelRight,
                            KQvgaPrtLevelBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Score
        case EScore:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscScoreLeft,
                            KQvgaLscScoreTop,
                            KQvgaLscScoreRight,
                            KQvgaLscScoreBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtScoreLeft,
                            KQvgaPrtScoreTop,
                            KQvgaPrtScoreRight,
                            KQvgaPrtScoreBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Bonus
        case EBonus:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscBonusLeft,
                            KQvgaLscBonusTop,
                            KQvgaLscBonusRight,
                            KQvgaLscBonusBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtBonusLeft,
                            KQvgaPrtBonusTop,
                            KQvgaPrtBonusRight,
                            KQvgaPrtBonusBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Progress
        case EProgress:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscProgressLeft,
                            KQvgaLscProgressTop,
                            KQvgaLscProgressRight,
                            KQvgaLscProgressBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtProgressLeft,
                            KQvgaPrtProgressTop,
                            KQvgaPrtProgressRight,
                            KQvgaPrtProgressBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // FuncKey
        case EFuncKey:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscFuncKeyLeft,
                            KQvgaLscFuncKeyTop,
                            KQvgaLscFuncKeyRight,
                            KQvgaLscFuncKeyBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtFuncKeyLeft,
                            KQvgaPrtFuncKeyTop,
                            KQvgaPrtFuncKeyRight,
                            KQvgaPrtFuncKeyBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // InfoComponent
        case EInfoComponent:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscInfoComponentLeft,
                            KQvgaLscInfoComponentTop,
                            KQvgaLscInfoComponentRight,
                            KQvgaLscInfoComponentBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtInfoComponentLeft,
                            KQvgaPrtInfoComponentTop,
                            KQvgaPrtInfoComponentRight,
                            KQvgaPrtInfoComponentBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // SoundBoard
        case ESoundBoard:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscSoundBoardLeft,
                            KQvgaLscSoundBoardTop,
                            KQvgaLscSoundBoardRight,
                            KQvgaLscSoundBoardBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtSoundBoardLeft,
                            KQvgaPrtSoundBoardTop,
                            KQvgaPrtSoundBoardRight,
                            KQvgaPrtSoundBoardBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // SoundTitle
        case ESoundTitle:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscSoundTitleLeft,
                            KQvgaLscSoundTitleTop,
                            KQvgaLscSoundTitleRight,
                            KQvgaLscSoundTitleBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtSoundTitleLeft,
                            KQvgaPrtSoundTitleTop,
                            KQvgaPrtSoundTitleRight,
                            KQvgaPrtSoundTitleBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // SoundProgress
        case ESoundProgress:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscSoundProgressLeft,
                            KQvgaLscSoundProgressTop,
                            KQvgaLscSoundProgressRight,
                            KQvgaLscSoundProgressBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtSoundProgressLeft,
                            KQvgaPrtSoundProgressTop,
                            KQvgaPrtSoundProgressRight,
                            KQvgaPrtSoundProgressBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // ModeTitleBoard
        case EModeTitleBoard:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscModeTitleBoardLeft,
                            KQvgaLscModeTitleBoardTop,
                            KQvgaLscModeTitleBoardRight,
                            KQvgaLscModeTitleBoardBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtModeTitleBoardLeft,
                            KQvgaPrtModeTitleBoardTop,
                            KQvgaPrtModeTitleBoardRight,
                            KQvgaPrtModeTitleBoardBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // ModeTitle
        case EModeTitle:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscModeTitleLeft,
                            KQvgaLscModeTitleTop,
                            KQvgaLscModeTitleRight,
                            KQvgaLscModeTitleBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtModeTitleLeft,
                            KQvgaPrtModeTitleTop,
                            KQvgaPrtModeTitleRight,
                            KQvgaPrtModeTitleBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // ModeName
        case EModeName:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscModeNameLeft,
                            KQvgaLscModeNameTop,
                            KQvgaLscModeNameRight,
                            KQvgaLscModeNameBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtModeNameLeft,
                            KQvgaPrtModeNameTop,
                            KQvgaPrtModeNameRight,
                            KQvgaPrtModeNameBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // ModeBack
        case EModeBack:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscModeBackLeft,
                            KQvgaLscModeBackTop,
                            KQvgaLscModeBackRight,
                            KQvgaLscModeBackBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtModeBackLeft,
                            KQvgaPrtModeBackTop,
                            KQvgaPrtModeBackRight,
                            KQvgaPrtModeBackBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // ModeForward
        case EModeForward:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscModeForwardLeft,
                            KQvgaLscModeForwardTop,
                            KQvgaLscModeForwardRight,
                            KQvgaLscModeForwardBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtModeForwardLeft,
                            KQvgaPrtModeForwardTop,
                            KQvgaPrtModeForwardRight,
                            KQvgaPrtModeForwardBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }
        // ModeBoard
        case EModeBoard:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscModeBoardLeft,
                            KQvgaLscModeBoardTop,
                            KQvgaLscModeBoardRight,
                            KQvgaLscModeBoardBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtModeBoardLeft,
                            KQvgaPrtModeBoardTop,
                            KQvgaPrtModeBoardRight,
                            KQvgaPrtModeBoardBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // ModeDetails
        case EModeDetails:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscModeDetailsLeft,
                            KQvgaLscModeDetailsTop,
                            KQvgaLscModeDetailsRight,
                            KQvgaLscModeDetailsBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtModeDetailsLeft,
                            KQvgaPrtModeDetailsTop,
                            KQvgaPrtModeDetailsRight,
                            KQvgaPrtModeDetailsBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // ModePicture
        case EModePicture:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscModePictureLeft,
                            KQvgaLscModePictureTop,
                            KQvgaLscModePictureRight,
                            KQvgaLscModePictureBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtModePictureLeft,
                            KQvgaPrtModePictureTop,
                            KQvgaPrtModePictureRight,
                            KQvgaPrtModePictureBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // ModeCheckbox
        case EModeCheckbox:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscModeCheckboxLeft,
                            KQvgaLscModeCheckboxTop,
                            KQvgaLscModeCheckboxRight,
                            KQvgaLscModeCheckboxBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtModeCheckboxLeft,
                            KQvgaPrtModeCheckboxTop,
                            KQvgaPrtModeCheckboxRight,
                            KQvgaPrtModeCheckboxBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }
            
        // HelpTitleBoard
        case EHelpTitleBoard:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpTitleBoardLeft,
                            KQvgaLscHelpTitleBoardTop,
                            KQvgaLscHelpTitleBoardRight,
                            KQvgaLscHelpTitleBoardBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpTitleBoardLeft,
                            KQvgaPrtHelpTitleBoardTop,
                            KQvgaPrtHelpTitleBoardRight,
                            KQvgaPrtHelpTitleBoardBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // HelpTitle
        case EHelpTitle:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpTitleLeft,
                            KQvgaLscHelpTitleTop,
                            KQvgaLscHelpTitleRight,
                            KQvgaLscHelpTitleBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpTitleLeft,
                            KQvgaPrtHelpTitleTop,
                            KQvgaPrtHelpTitleRight,
                            KQvgaPrtHelpTitleBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // HelpBack
        case EHelpBack:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpBackLeft,
                            KQvgaLscHelpBackTop,
                            KQvgaLscHelpBackRight,
                            KQvgaLscHelpBackBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpBackLeft,
                            KQvgaPrtHelpBackTop,
                            KQvgaPrtHelpBackRight,
                            KQvgaPrtHelpBackBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // HelpForward
        case EHelpForward:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpForwardLeft,
                            KQvgaLscHelpForwardTop,
                            KQvgaLscHelpForwardRight,
                            KQvgaLscHelpForwardBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpForwardLeft,
                            KQvgaPrtHelpForwardTop,
                            KQvgaPrtHelpForwardRight,
                            KQvgaPrtHelpForwardBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // HelpBoard
        case EHelpBoard:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpBoardLeft,
                            KQvgaLscHelpBoardTop,
                            KQvgaLscHelpBoardRight,
                            KQvgaLscHelpBoardBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpBoardLeft,
                            KQvgaPrtHelpBoardTop,
                            KQvgaPrtHelpBoardRight,
                            KQvgaPrtHelpBoardBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // HelpFirstText
        case EHelpFirstText:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpFirstTextLeft,
                            KQvgaLscHelpFirstTextTop,
                            KQvgaLscHelpFirstTextRight,
                            KQvgaLscHelpFirstTextBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpFirstTextLeft,
                            KQvgaPrtHelpFirstTextTop,
                            KQvgaPrtHelpFirstTextRight,
                            KQvgaPrtHelpFirstTextBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // HelpFirstPicture
        case EHelpFirstPicture:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpFirstPictureLeft,
                            KQvgaLscHelpFirstPictureTop,
                            KQvgaLscHelpFirstPictureRight,
                            KQvgaLscHelpFirstPictureBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpFirstPictureLeft,
                            KQvgaPrtHelpFirstPictureTop,
                            KQvgaPrtHelpFirstPictureRight,
                            KQvgaPrtHelpFirstPictureBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // HelpSecondText
        case EHelpSecondText:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpSecondTextLeft,
                            KQvgaLscHelpSecondTextTop,
                            KQvgaLscHelpSecondTextRight,
                            KQvgaLscHelpSecondTextBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpSecondTextLeft,
                            KQvgaPrtHelpSecondTextTop,
                            KQvgaPrtHelpSecondTextRight,
                            KQvgaPrtHelpSecondTextBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // HelpSecondPicture
        case EHelpSecondPicture:
            {
            switch ( iResolution )
                {
                case EQvgaLandscape:
                    {
                    aRect.SetRect( 
                            KQvgaLscHelpSecondPictureLeft,
                            KQvgaLscHelpSecondPictureTop,
                            KQvgaLscHelpSecondPictureRight,
                            KQvgaLscHelpSecondPictureBottom );
                    break;
                    }
                case EQvgaPortrait:
                    {
                    aRect.SetRect( 
                            KQvgaPrtHelpSecondPictureLeft,
                            KQvgaPrtHelpSecondPictureTop,
                            KQvgaPrtHelpSecondPictureRight,
                            KQvgaPrtHelpSecondPictureBottom );
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
    }

// ----------------------------------------------------------------------------
// CScaLayoutManager::LayoutRect
// ----------------------------------------------------------------------------
//
CScaLayoutManager::CScaLayoutManager()
    { // No implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScaLayoutManager::ConstructL
// ----------------------------------------------------------------------------
//
void CScaLayoutManager::ConstructL()
    { // No implementation required.
    FUNC_LOG;
    }

// End of File
