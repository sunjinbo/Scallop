/* ====================================================================
 * File: ScaLayoutValues.h
 * Created: 11/03/09
 * Modified: 12/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef LAYOUTMANAGERVALUES_H
#define LAYOUTMANAGERVALUES_H

// INCLUDE FILES
#include <avkon.hrh>

/////////////////////////////////////////////////////////////////////////////
//
// SUPPORTED UI RESOLUTIONS ARE:
//
// QVGA RESOLUTION PORTRAIT     360 x 640
// QVGA RESOLUTION LANDSCAPE    640 x 360
//
////////////////////////////////////////////////////////////////////////////

// Supported screen resolutions
enum TResolution
    {
    EQvgaPortrait,
    EQvgaLandscape,
    ENotSupported
    };

// Supported screen orientation
enum TOrientation
    {
    EAutomatic,
    EPortrait,
    ELandscape
    };

// Component enumerations
enum TComponent
    {
    EWelcome = 0, // welcome view
    EBrand,
    EStart, // menu view
    EOption,
    ERecord,
    EHelp,
    EQuit,
    EMatrix, // game view
    EMasking,
    ELevel,
    EScore,
    EBonus,
    EProgress,
    EFuncKey,
    EInfoComponent,
    ESoundBoard, // option view
    ESoundTitle,
    ESoundProgress,
    EModeTitleBoard,
    EModeTitle,
    EModeName,
    EModeBack,
    EModeForward,
    EModeBoard,
    EModeDetails,
    EModePicture,
    EModeCheckbox,
    EHelpTitleBoard, // help view
    EHelpTitle,
    EHelpBack,
    EHelpForward,
    EHelpBoard,
    EHelpFirstText,
    EHelpFirstPicture,
    EHelpSecondText,
    EHelpSecondPicture,
    EWebLink // about
    };

/////////////////////////////////////////////////////////////////////////////
//
// SCALLOP COMPONENTS VALUES
//
/////////////////////////////////////////////////////////////////////////////

// Screen
static const TInt KQvgaLandscapeWidth = 640;
static const TInt KQvgaLandscapeHeight = 360;

static const TInt KQvgaPortraitWidth = 360;
static const TInt KQvgaPortraitHeight = 640;


// Welcome
static const TInt KQvgaLscWelcomeLeft = 0;
static const TInt KQvgaLscWelcomeTop = 0;
static const TInt KQvgaLscWelcomeRight = 0;
static const TInt KQvgaLscWelcomeBottom = 0;
static const TInt KQvgaLscWelcomeWidth = 0;
static const TInt KQvgaLscWelcomeHeight = 0;

static const TInt KQvgaPrtWelcomeLeft = 120;
static const TInt KQvgaPrtWelcomeTop = 500;
static const TInt KQvgaPrtWelcomeRight = 240;
static const TInt KQvgaPrtWelcomeBottom = 530;
static const TInt KQvgaPrtWelcomeWidth = 120;
static const TInt KQvgaPrtWelcomeHeight = 30;


// Brand
static const TInt KQvgaLscBrandLeft = 0;
static const TInt KQvgaLscBrandTop = 0;
static const TInt KQvgaLscBrandRight = 0;
static const TInt KQvgaLscBrandBottom = 0;
static const TInt KQvgaLscBrandWidth = 0;
static const TInt KQvgaLscBrandHeight = 0;

static const TInt KQvgaPrtBrandLeft = 65;
static const TInt KQvgaPrtBrandTop = 200;
static const TInt KQvgaPrtBrandRight = 295;
static const TInt KQvgaPrtBrandBottom = 300;
static const TInt KQvgaPrtBrandWidth = 230;
static const TInt KQvgaPrtBrandHeight = 100;


// Start
static const TInt KQvgaLscStartLeft = 0;
static const TInt KQvgaLscStartTop = 0;
static const TInt KQvgaLscStartRight = 0;
static const TInt KQvgaLscStartBottom = 0;
static const TInt KQvgaLscStartWidth = 0;
static const TInt KQvgaLscStartHeight = 0;

static const TInt KQvgaPrtStartLeft = 1;
static const TInt KQvgaPrtStartTop = 101;
static const TInt KQvgaPrtStartRight = 359;
static const TInt KQvgaPrtStartBottom = 171;
static const TInt KQvgaPrtStartWidth = 358;
static const TInt KQvgaPrtStartHeight = 70;


// Option
static const TInt KQvgaLscOptionLeft = 0;
static const TInt KQvgaLscOptionTop = 0;
static const TInt KQvgaLscOptionRight = 0;
static const TInt KQvgaLscOptionBottom = 0;
static const TInt KQvgaLscOptionWidth = 0;
static const TInt KQvgaLscOptionHeight = 0;

static const TInt KQvgaPrtOptionLeft = 1;
static const TInt KQvgaPrtOptionTop = 173;
static const TInt KQvgaPrtOptionRight = 359;
static const TInt KQvgaPrtOptionBottom = 243;
static const TInt KQvgaPrtOptionWidth = 358;
static const TInt KQvgaPrtOptionHeight = 70;


// Record
static const TInt KQvgaLscRecordLeft = 0;
static const TInt KQvgaLscRecordTop = 0;
static const TInt KQvgaLscRecordRight = 0;
static const TInt KQvgaLscRecordBottom = 0;
static const TInt KQvgaLscRecordWidth = 0;
static const TInt KQvgaLscRecordHeight = 0;

static const TInt KQvgaPrtRecordLeft = 1;
static const TInt KQvgaPrtRecordTop = 245;
static const TInt KQvgaPrtRecordRight = 359;
static const TInt KQvgaPrtRecordBottom = 315;
static const TInt KQvgaPrtRecordWidth = 358;
static const TInt KQvgaPrtRecordHeight = 70;


// Help
static const TInt KQvgaLscHelpLeft = 0;
static const TInt KQvgaLscHelpTop = 0;
static const TInt KQvgaLscHelpRight = 0;
static const TInt KQvgaLscHelpBottom = 0;
static const TInt KQvgaLscHelpWidth = 0;
static const TInt KQvgaLscHelpHeight = 0;

static const TInt KQvgaPrtHelpLeft = 1;
static const TInt KQvgaPrtHelpTop = 317;
static const TInt KQvgaPrtHelpRight = 359;
static const TInt KQvgaPrtHelpBottom = 387;
static const TInt KQvgaPrtHelpWidth = 358;
static const TInt KQvgaPrtHelpHeight = 70;

// Quit
static const TInt KQvgaLscQuitLeft = 0;
static const TInt KQvgaLscQuitTop = 0;
static const TInt KQvgaLscQuitRight = 0;
static const TInt KQvgaLscQuitBottom = 0;
static const TInt KQvgaLscQuitWidth = 0;
static const TInt KQvgaLscQuitHeight = 0;

static const TInt KQvgaPrtQuitLeft = 1;
static const TInt KQvgaPrtQuitTop = 389;
static const TInt KQvgaPrtQuitRight = 359;
static const TInt KQvgaPrtQuitBottom = 459;
static const TInt KQvgaPrtQuitWidth = 358;
static const TInt KQvgaPrtQuitHeight = 70;


// Matrix
static const TInt KQvgaLscMatrixLeft = 0;
static const TInt KQvgaLscMatrixTop = 0;
static const TInt KQvgaLscMatrixRight = 0;
static const TInt KQvgaLscMatrixBottom = 0;
static const TInt KQvgaLscMatrixWidth = 0;
static const TInt KQvgaLscMatrixHeight = 0;

static const TInt KQvgaPrtMatrixLeft = 0;
static const TInt KQvgaPrtMatrixTop = 100;
static const TInt KQvgaPrtMatrixRight = 360;
static const TInt KQvgaPrtMatrixBottom = 460;
static const TInt KQvgaPrtMatrixWidth = 360;
static const TInt KQvgaPrtMatrixHeight = 360;


// Masking
static const TInt KQvgaLscMaskingLeft = 0;
static const TInt KQvgaLscMaskingTop = 0;
static const TInt KQvgaLscMaskingRight = 0;
static const TInt KQvgaLscMaskingBottom = 0;
static const TInt KQvgaLscMaskingWidth = 0;
static const TInt KQvgaLscMaskingHeight = 0;

static const TInt KQvgaPrtMaskingLeft = 0;
static const TInt KQvgaPrtMaskingTop = 100;
static const TInt KQvgaPrtMaskingRight = 360;
static const TInt KQvgaPrtMaskingBottom = 460;
static const TInt KQvgaPrtMaskingWidth = 360;
static const TInt KQvgaPrtMaskingHeight = 360;


// Level
static const TInt KQvgaLscLevelLeft = 0;
static const TInt KQvgaLscLevelTop = 0;
static const TInt KQvgaLscLevelRight = 0;
static const TInt KQvgaLscLevelBottom = 0;
static const TInt KQvgaLscLevelWidth = 0;
static const TInt KQvgaLscLevelHeight = 0;

static const TInt KQvgaPrtLevelLeft = 45;
static const TInt KQvgaPrtLevelTop = 0;
static const TInt KQvgaPrtLevelRight = 195;
static const TInt KQvgaPrtLevelBottom = 32;
static const TInt KQvgaPrtLevelWidth = 150;
static const TInt KQvgaPrtLevelHeight = 32;


// Score
static const TInt KQvgaLscScoreLeft = 0;
static const TInt KQvgaLscScoreTop = 0;
static const TInt KQvgaLscScoreRight = 0;
static const TInt KQvgaLscScoreBottom = 0;
static const TInt KQvgaLscScoreWidth = 0;
static const TInt KQvgaLscScoreHeight = 0;

static const TInt KQvgaPrtScoreLeft = 45;
static const TInt KQvgaPrtScoreTop = 33;
static const TInt KQvgaPrtScoreRight = 195;
static const TInt KQvgaPrtScoreBottom = 65;
static const TInt KQvgaPrtScoreWidth = 150;
static const TInt KQvgaPrtScoreHeight = 32;


// Bonus
static const TInt KQvgaLscBonusLeft = 0;
static const TInt KQvgaLscBonusTop = 0;
static const TInt KQvgaLscBonusRight = 0;
static const TInt KQvgaLscBonusBottom = 0;
static const TInt KQvgaLscBonusWidth = 0;
static const TInt KQvgaLscBonusHeight = 0;

static const TInt KQvgaPrtBonusLeft = 45;
static const TInt KQvgaPrtBonusTop = 66;
static const TInt KQvgaPrtBonusRight = 195;
static const TInt KQvgaPrtBonusBottom = 98;
static const TInt KQvgaPrtBonusWidth = 150;
static const TInt KQvgaPrtBonusHeight = 32;


// Progress
static const TInt KQvgaLscProgressLeft = 0;
static const TInt KQvgaLscProgressTop = 0;
static const TInt KQvgaLscProgressRight = 0;
static const TInt KQvgaLscProgressBottom = 0;
static const TInt KQvgaLscProgressWidth = 0;
static const TInt KQvgaLscProgressHeight = 0;

static const TInt KQvgaPrtProgressLeft = 2;
static const TInt KQvgaPrtProgressTop = 2;
static const TInt KQvgaPrtProgressRight = 41;
static const TInt KQvgaPrtProgressBottom = 98;
static const TInt KQvgaPrtProgressWidth = 42;
static const TInt KQvgaPrtProgressHeight = 99;


// FuncKey
static const TInt KQvgaLscFuncKeyLeft = 0;
static const TInt KQvgaLscFuncKeyTop = 0;
static const TInt KQvgaLscFuncKeyRight = 0;
static const TInt KQvgaLscFuncKeyBottom = 0;
static const TInt KQvgaLscFuncKeyWidth = 0;
static const TInt KQvgaLscFuncKeyHeight = 0;

static const TInt KQvgaPrtFuncKeyLeft = 2;
static const TInt KQvgaPrtFuncKeyTop = 462;
static const TInt KQvgaPrtFuncKeyRight = 81;
static const TInt KQvgaPrtFuncKeyBottom = 481;
static const TInt KQvgaPrtFuncKeyWidth = 80;
static const TInt KQvgaPrtFuncKeyHeight = 20;


// InfoComponent
static const TInt KQvgaLscInfoComponentLeft = 0;
static const TInt KQvgaLscInfoComponentTop = 0;
static const TInt KQvgaLscInfoComponentRight = 0;
static const TInt KQvgaLscInfoComponentBottom = 0;
static const TInt KQvgaLscInfoComponentWidth = 0;
static const TInt KQvgaLscInfoComponentHeight = 0;

static const TInt KQvgaPrtInfoComponentLeft = 0;
static const TInt KQvgaPrtInfoComponentTop = 483;
static const TInt KQvgaPrtInfoComponentRight = 360;
static const TInt KQvgaPrtInfoComponentBottom = 583;
static const TInt KQvgaPrtInfoComponentWidth = 360;
static const TInt KQvgaPrtInfoComponentHeight = 100;


// SoundBoard
static const TInt KQvgaLscSoundBoardLeft = 0;
static const TInt KQvgaLscSoundBoardTop = 0;
static const TInt KQvgaLscSoundBoardRight = 0;
static const TInt KQvgaLscSoundBoardBottom = 0;
static const TInt KQvgaLscSoundBoardWidth = 0;
static const TInt KQvgaLscSoundBoardHeight = 0;

static const TInt KQvgaPrtSoundBoardLeft = 2;
static const TInt KQvgaPrtSoundBoardTop = 102;
static const TInt KQvgaPrtSoundBoardRight = 358;
static const TInt KQvgaPrtSoundBoardBottom = 170;
static const TInt KQvgaPrtSoundBoardWidth = 356;
static const TInt KQvgaPrtSoundBoardHeight = 68;


// SoundTitle
static const TInt KQvgaLscSoundTitleLeft = 0;
static const TInt KQvgaLscSoundTitleTop = 0;
static const TInt KQvgaLscSoundTitleRight = 0;
static const TInt KQvgaLscSoundTitleBottom = 0;
static const TInt KQvgaLscSoundTitleWidth = 0;
static const TInt KQvgaLscSoundTitleHeight = 0;

static const TInt KQvgaPrtSoundTitleLeft = 70;
static const TInt KQvgaPrtSoundTitleTop = 114;
static const TInt KQvgaPrtSoundTitleRight = 142;
static const TInt KQvgaPrtSoundTitleBottom = 158;
static const TInt KQvgaPrtSoundTitleWidth = 72;
static const TInt KQvgaPrtSoundTitleHeight = 44;


// SoundProgress
static const TInt KQvgaLscSoundProgressLeft = 0;
static const TInt KQvgaLscSoundProgressTop = 0;
static const TInt KQvgaLscSoundProgressRight = 0;
static const TInt KQvgaLscSoundProgressBottom = 0;
static const TInt KQvgaLscSoundProgressWidth = 0;
static const TInt KQvgaLscSoundProgressHeight = 0;

static const TInt KQvgaPrtSoundProgressLeft = 150;
static const TInt KQvgaPrtSoundProgressTop = 114;
static const TInt KQvgaPrtSoundProgressRight = 290;
static const TInt KQvgaPrtSoundProgressBottom = 158;
static const TInt KQvgaPrtSoundProgressWidth = 140;
static const TInt KQvgaPrtSoundProgressHeight = 44;


// ModeTitleBoard
static const TInt KQvgaLscModeTitleBoardLeft = 0;
static const TInt KQvgaLscModeTitleBoardTop = 0;
static const TInt KQvgaLscModeTitleBoardRight = 0;
static const TInt KQvgaLscModeTitleBoardBottom = 0;
static const TInt KQvgaLscModeTitleBoardWidth = 0;
static const TInt KQvgaLscModeTitleBoardHeight = 0;

static const TInt KQvgaPrtModeTitleBoardLeft = 2;
static const TInt KQvgaPrtModeTitleBoardTop = 174;
static const TInt KQvgaPrtModeTitleBoardRight = 358;
static const TInt KQvgaPrtModeTitleBoardBottom = 242;
static const TInt KQvgaPrtModeTitleBoardWidth = 356;
static const TInt KQvgaPrtModeTitleBoardHeight = 68;


// ModeTitle
static const TInt KQvgaLscModeTitleLeft = 0;
static const TInt KQvgaLscModeTitleTop = 0;
static const TInt KQvgaLscModeTitleRight = 0;
static const TInt KQvgaLscModeTitleBottom = 0;
static const TInt KQvgaLscModeTitleWidth = 0;
static const TInt KQvgaLscModeTitleHeight = 0;

static const TInt KQvgaPrtModeTitleLeft = 70;
static const TInt KQvgaPrtModeTitleTop = 186;
static const TInt KQvgaPrtModeTitleRight = 142;
static const TInt KQvgaPrtModeTitleBottom = 230;
static const TInt KQvgaPrtModeTitleWidth = 72;
static const TInt KQvgaPrtModeTitleHeight = 44;


// ModeName
static const TInt KQvgaLscModeNameLeft = 0;
static const TInt KQvgaLscModeNameTop = 0;
static const TInt KQvgaLscModeNameRight = 0;
static const TInt KQvgaLscModeNameBottom = 0;
static const TInt KQvgaLscModeNameWidth = 0;
static const TInt KQvgaLscModeNameHeight = 0;

static const TInt KQvgaPrtModeNameLeft = 170;
static const TInt KQvgaPrtModeNameTop = 186;
static const TInt KQvgaPrtModeNameRight = 270;
static const TInt KQvgaPrtModeNameBottom = 230;
static const TInt KQvgaPrtModeNameWidth = 100;
static const TInt KQvgaPrtModeNameHeight = 44;


// ModeBack
static const TInt KQvgaLscModeBackLeft = 0;
static const TInt KQvgaLscModeBackTop = 0;
static const TInt KQvgaLscModeBackRight = 0;
static const TInt KQvgaLscModeBackBottom = 0;
static const TInt KQvgaLscModeBackWidth = 0;
static const TInt KQvgaLscModeBackHeight = 0;

static const TInt KQvgaPrtModeBackLeft = 152;
static const TInt KQvgaPrtModeBackTop = 199;
static const TInt KQvgaPrtModeBackRight = 170;
static const TInt KQvgaPrtModeBackBottom = 217;
static const TInt KQvgaPrtModeBackWidth = 18;
static const TInt KQvgaPrtModeBackHeight = 18;


// ModeForward
static const TInt KQvgaLscModeForwardLeft = 0;
static const TInt KQvgaLscModeForwardTop = 0;
static const TInt KQvgaLscModeForwardRight = 0;
static const TInt KQvgaLscModeForwardBottom = 0;
static const TInt KQvgaLscModeForwardWidth = 0;
static const TInt KQvgaLscModeForwardHeight = 0;

static const TInt KQvgaPrtModeForwardLeft = 270;
static const TInt KQvgaPrtModeForwardTop = 199;
static const TInt KQvgaPrtModeForwardRight = 288;
static const TInt KQvgaPrtModeForwardBottom = 217;
static const TInt KQvgaPrtModeForwardWidth = 18;
static const TInt KQvgaPrtModeForwardHeight = 18;


// ModeBoard
static const TInt KQvgaLscModeBoardLeft = 0;
static const TInt KQvgaLscModeBoardTop = 0;
static const TInt KQvgaLscModeBoardRight = 0;
static const TInt KQvgaLscModeBoardBottom = 0;
static const TInt KQvgaLscModeBoardWidth = 0;
static const TInt KQvgaLscModeBoardHeight = 0;

static const TInt KQvgaPrtModeBoardLeft = 2;
static const TInt KQvgaPrtModeBoardTop = 246;
static const TInt KQvgaPrtModeBoardRight = 358;
static const TInt KQvgaPrtModeBoardBottom = 458;
static const TInt KQvgaPrtModeBoardWidth = 356;
static const TInt KQvgaPrtModeBoardHeight = 212;


// ModeDetails
static const TInt KQvgaLscModeDetailsLeft = 0;
static const TInt KQvgaLscModeDetailsTop = 0;
static const TInt KQvgaLscModeDetailsRight = 0;
static const TInt KQvgaLscModeDetailsBottom = 0;
static const TInt KQvgaLscModeDetailsWidth = 0;
static const TInt KQvgaLscModeDetailsHeight = 0;

static const TInt KQvgaPrtModeDetailsLeft = 36;
static const TInt KQvgaPrtModeDetailsTop = 250;
static const TInt KQvgaPrtModeDetailsRight = 236;
static const TInt KQvgaPrtModeDetailsBottom = 384;
static const TInt KQvgaPrtModeDetailsWidth = 200;
static const TInt KQvgaPrtModeDetailsHeight = 134;


// ModePicture
static const TInt KQvgaLscModePictureLeft = 0;
static const TInt KQvgaLscModePictureTop = 0;
static const TInt KQvgaLscModePictureRight = 0;
static const TInt KQvgaLscModePictureBottom = 0;
static const TInt KQvgaLscModePictureWidth = 0;
static const TInt KQvgaLscModePictureHeight = 0;

static const TInt KQvgaPrtModePictureLeft = 244;
static const TInt KQvgaPrtModePictureTop = 246;
static const TInt KQvgaPrtModePictureRight = 331;
static const TInt KQvgaPrtModePictureBottom = 426;
static const TInt KQvgaPrtModePictureWidth = 110;
static const TInt KQvgaPrtModePictureHeight = 85;


// ModeCheckbox
static const TInt KQvgaLscModeCheckboxLeft = 0;
static const TInt KQvgaLscModeCheckboxTop = 0;
static const TInt KQvgaLscModeCheckboxRight = 0;
static const TInt KQvgaLscModeCheckboxBottom = 0;
static const TInt KQvgaLscModeCheckboxWidth = 0;
static const TInt KQvgaLscModeCheckboxHeight = 0;

static const TInt KQvgaPrtModeCheckboxLeft = 236;
static const TInt KQvgaPrtModeCheckboxTop = 432;
static const TInt KQvgaPrtModeCheckboxRight = 356;
static const TInt KQvgaPrtModeCheckboxBottom = 454;
static const TInt KQvgaPrtModeCheckboxWidth = 120;
static const TInt KQvgaPrtModeCheckboxHeight = 22;

// HelpTitleBoard
static const TInt KQvgaLscHelpTitleBoardLeft = 0;
static const TInt KQvgaLscHelpTitleBoardTop = 0;
static const TInt KQvgaLscHelpTitleBoardRight = 0;
static const TInt KQvgaLscHelpTitleBoardBottom = 0;
static const TInt KQvgaLscHelpTitleBoardWidth = 0;
static const TInt KQvgaLscHelpTitleBoardHeight = 0;

static const TInt KQvgaPrtHelpTitleBoardLeft = 2;
static const TInt KQvgaPrtHelpTitleBoardTop = 102;
static const TInt KQvgaPrtHelpTitleBoardRight = 358;
static const TInt KQvgaPrtHelpTitleBoardBottom = 170;
static const TInt KQvgaPrtHelpTitleBoardWidth = 356;
static const TInt KQvgaPrtHelpTitleBoardHeight = 68;

// HelpTitle
static const TInt KQvgaLscHelpTitleLeft = 0;
static const TInt KQvgaLscHelpTitleTop = 0;
static const TInt KQvgaLscHelpTitleRight = 0;
static const TInt KQvgaLscHelpTitleBottom = 0;
static const TInt KQvgaLscHelpTitleWidth = 0;
static const TInt KQvgaLscHelpTitleHeight = 0;

static const TInt KQvgaPrtHelpTitleLeft = 140;
static const TInt KQvgaPrtHelpTitleTop = 110;
static const TInt KQvgaPrtHelpTitleRight = 220;
static const TInt KQvgaPrtHelpTitleBottom = 162;
static const TInt KQvgaPrtHelpTitleWidth = 80;
static const TInt KQvgaPrtHelpTitleHeight = 52;


// HelpBack
static const TInt KQvgaLscHelpBackLeft = 0;
static const TInt KQvgaLscHelpBackTop = 0;
static const TInt KQvgaLscHelpBackRight = 0;
static const TInt KQvgaLscHelpBackBottom = 0;
static const TInt KQvgaLscHelpBackWidth = 0;
static const TInt KQvgaLscHelpBackHeight = 0;

static const TInt KQvgaPrtHelpBackLeft = 18;
static const TInt KQvgaPrtHelpBackTop = 118;
static const TInt KQvgaPrtHelpBackRight = 54;
static const TInt KQvgaPrtHelpBackBottom = 154;
static const TInt KQvgaPrtHelpBackWidth = 36;
static const TInt KQvgaPrtHelpBackHeight = 36;


// HelpForward
static const TInt KQvgaLscHelpForwardLeft = 0;
static const TInt KQvgaLscHelpForwardTop = 0;
static const TInt KQvgaLscHelpForwardRight = 0;
static const TInt KQvgaLscHelpForwardBottom = 0;
static const TInt KQvgaLscHelpForwardWidth = 0;
static const TInt KQvgaLscHelpForwardHeight = 0;

static const TInt KQvgaPrtHelpForwardLeft = 306;
static const TInt KQvgaPrtHelpForwardTop = 118;
static const TInt KQvgaPrtHelpForwardRight = 342;
static const TInt KQvgaPrtHelpForwardBottom = 154;
static const TInt KQvgaPrtHelpForwardWidth = 36;
static const TInt KQvgaPrtHelpForwardHeight = 36;


// HelpBoard
static const TInt KQvgaLscHelpBoardLeft = 0;
static const TInt KQvgaLscHelpBoardTop = 0;
static const TInt KQvgaLscHelpBoardRight = 0;
static const TInt KQvgaLscHelpBoardBottom = 0;
static const TInt KQvgaLscHelpBoardWidth = 0;
static const TInt KQvgaLscHelpBoardHeight = 0;

static const TInt KQvgaPrtHelpBoardLeft = 2;
static const TInt KQvgaPrtHelpBoardTop = 174;
static const TInt KQvgaPrtHelpBoardRight = 358;
static const TInt KQvgaPrtHelpBoardBottom = 458;
static const TInt KQvgaPrtHelpBoardWidth = 356;
static const TInt KQvgaPrtHelpBoardHeight = 284;


// HelpFirstText
static const TInt KQvgaLscHelpFirstTextLeft = 0;
static const TInt KQvgaLscHelpFirstTextTop = 0;
static const TInt KQvgaLscHelpFirstTextRight = 0;
static const TInt KQvgaLscHelpFirstTextBottom = 0;
static const TInt KQvgaLscHelpFirstTextWidth = 0;
static const TInt KQvgaLscHelpFirstTextHeight = 0;

static const TInt KQvgaPrtHelpFirstTextLeft = 190;
static const TInt KQvgaPrtHelpFirstTextTop = 182;
static const TInt KQvgaPrtHelpFirstTextRight = 350;
static const TInt KQvgaPrtHelpFirstTextBottom = 306;
static const TInt KQvgaPrtHelpFirstTextWidth = 160;
static const TInt KQvgaPrtHelpFirstTextHeight = 124;


// HelpFirstPicture
static const TInt KQvgaLscHelpFirstPictureLeft = 0;
static const TInt KQvgaLscHelpFirstPictureTop = 0;
static const TInt KQvgaLscHelpFirstPictureRight = 0;
static const TInt KQvgaLscHelpFirstPictureBottom = 0;
static const TInt KQvgaLscHelpFirstPictureWidth = 0;
static const TInt KQvgaLscHelpFirstPictureHeight = 0;

static const TInt KQvgaPrtHelpFirstPictureLeft = 10;
static const TInt KQvgaPrtHelpFirstPictureTop = 182;
static const TInt KQvgaPrtHelpFirstPictureRight = 170;
static const TInt KQvgaPrtHelpFirstPictureBottom = 306;
static const TInt KQvgaPrtHelpFirstPictureWidth = 160;
static const TInt KQvgaPrtHelpFirstPictureHeight = 124;


// HelpSecondText
static const TInt KQvgaLscHelpSecondTextLeft = 0;
static const TInt KQvgaLscHelpSecondTextTop = 0;
static const TInt KQvgaLscHelpSecondTextRight = 0;
static const TInt KQvgaLscHelpSecondTextBottom = 0;
static const TInt KQvgaLscHelpSecondTextWidth = 0;
static const TInt KQvgaLscHelpSecondTextHeight = 0;

static const TInt KQvgaPrtHelpSecondTextLeft = 10;
static const TInt KQvgaPrtHelpSecondTextTop = 326;
static const TInt KQvgaPrtHelpSecondTextRight = 170;
static const TInt KQvgaPrtHelpSecondTextBottom = 450;
static const TInt KQvgaPrtHelpSecondTextWidth = 160;
static const TInt KQvgaPrtHelpSecondTextHeight = 124;


// HelpSecondPicture
static const TInt KQvgaLscHelpSecondPictureLeft = 0;
static const TInt KQvgaLscHelpSecondPictureTop = 0;
static const TInt KQvgaLscHelpSecondPictureRight = 0;
static const TInt KQvgaLscHelpSecondPictureBottom = 0;
static const TInt KQvgaLscHelpSecondPictureWidth = 0;
static const TInt KQvgaLscHelpSecondPictureHeight = 0;

static const TInt KQvgaPrtHelpSecondPictureLeft = 190;
static const TInt KQvgaPrtHelpSecondPictureTop = 326;
static const TInt KQvgaPrtHelpSecondPictureRight = 350;
static const TInt KQvgaPrtHelpSecondPictureBottom = 450;
static const TInt KQvgaPrtHelpSecondPictureWidth = 160;
static const TInt KQvgaPrtHelpSecondPictureHeight = 124;


#endif // LAYOUTMANAGERVALUES_H

// End of File
