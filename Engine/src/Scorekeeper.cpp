/* ====================================================================
 * File: Scorekeeper.cpp
 * Created: 06/16/09
 * Modified: 06/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "Scorekeeper.h"
#include "EngineCommon.h"
#include "AquaticData.h"
#include "ScaLogger.h"

// CONSTANTS
const TInt KScoreScallop = 10;
const TInt KScoreStarFish = 10;
const TInt KScoreTurtle = 30;
const TInt KScoreShark = 10;
const TInt KScoreOctopus = 15;
const TInt KScoreCuttleFish = 20;
const TInt KScoreSeaCrab = 25;
const TInt KScoreJellyfish = 10;

const TInt KNumOneAquatics = 1;
const TInt KNumTwoAquatics = 2;
const TInt KNumThreeAquatics = 3;
const TInt KNumFourAquatics = 4;
const TInt KNumFiveAquatics = 5;
const TInt KNumSixAquatics = 6;
const TInt KNumSevenAquatics = 7;
const TInt KNumEightAquatics = 8;
const TInt KNumNineAquatics = 9;

const TInt KBounsOneAquatics = 0;
const TInt KBounsTwoAquatics = 0;
const TInt KBounsThreeAquatics = 0;
const TInt KBounsFourAquatics = 0;
const TInt KBounsFiveAquatics = 0;
const TInt KBounsSixAquatics = 30;
const TInt KBounsSevenAquatics = 60;
const TInt KBounsEightAquatics = 80;
const TInt KBounsNineAquatics = 100;

const TInt KFullFuncKeyNumber = 5;
const TInt KEmptyFuncKeyNumber = 0;

const TInt KExpireDelayTimeout = 0;
const TInt KExpireOneSecTimeout = 1000000;

const TInt KMaxProgressValue = 10;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CScorekeeper::~CScorekeeper
// ----------------------------------------------------------------------------
//
CScorekeeper::~CScorekeeper()
    {
    FUNC_LOG;
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;   
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::SetupLevel
// ----------------------------------------------------------------------------
//
void CScorekeeper::SetupLevel( const TLevelData& aLevel )
    {
    FUNC_LOG;
    iLevel = aLevel;
    Clear();
    UpdateAll();
    TInt timeout = KExpireOneSecTimeout * 
            ( iLevel.iTime / KMaxProgressValue );
    iPeriodic->Cancel();
    iPeriodic->Start(
            KExpireDelayTimeout,
            timeout,
            TCallBack( TimerCallback, this ) );
    }

// ----------------------------------------------------------------------------
// CScorekeeper::LevelID
// ----------------------------------------------------------------------------
//
TInt CScorekeeper::Level() const
    {
    FUNC_LOG;
    return iLevel.iLevelID;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::Score
// ----------------------------------------------------------------------------
//
TInt CScorekeeper::Score() const
    {
    FUNC_LOG;
    return iLevelScore;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::Bonus
// ----------------------------------------------------------------------------
//
TInt CScorekeeper::Bonus() const
    {
    FUNC_LOG;
    return iLevelBonus;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::FuncKey
// ----------------------------------------------------------------------------
//
TInt CScorekeeper::FuncKey() const
    {
    FUNC_LOG;
    return iFuncKeyNum;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::Progress
// ----------------------------------------------------------------------------
//
TInt CScorekeeper::Progress() const
        {
        FUNC_LOG;
        return iLevelTime;
        }

// ----------------------------------------------------------------------------
// CScorekeeper::Prompt
// ----------------------------------------------------------------------------
//
const TDesC* CScorekeeper::Prompt() const
        {
        FUNC_LOG;
        return &iLevel.iPrompt;
        }

// ----------------------------------------------------------------------------
// CScorekeeper::DismissL
// ----------------------------------------------------------------------------
//
void CScorekeeper::Dismiss( const RArray<TAquaticData>& aList )
    {
    FUNC_LOG;
    TInt score( 0 ), bonus( 0 );
    TInt count = aList.Count();
    for ( TInt ix = 0; ix < count; ix++ )
        {
        switch ( aList[ ix ].Type() )
            {
            case EBlueScallop: // fall through
            case EDarkBlueScallop: // fall through
            case EGreenScallop: // fall through
            case EDarkGreenScallop: // fall through
            case ERedScallop: // fall through
            case EMulberryScallop: // fall through
            case EOrangeScallop: // fall through
            case EYellowScallop: // fall through
                score += KScoreScallop;
                break;
            case EStarFish:
                score += KScoreStarFish;
                break;
            case ETurtle:
                score += KScoreTurtle;
                break;
            case EShark:
                score += KScoreShark;
                break;
            case EOctopus:
                score += KScoreOctopus;
                break;
            case ECuttleFish:
                score += KScoreCuttleFish;
                break;
            case ESeaCrab:
                score += KScoreSeaCrab;
                break;
            case EJellyfish:
                score += KScoreJellyfish;
                break;
            default:
                break;
            }
        }
    iLevelScore += score;
    iObserver.StateChanged( EScorekeeperScoreUpdated );
    MakeBonus( count );
    iObserver.StateChanged( EScorekeeperBonusUpdated );

    if ( iLevelScore + iLevelBonus >= iLevel.iPassScore )
        {
        iCompletedTotalScore += iLevelScore;
        iCompletedTotalScore += iLevelBonus;
        iCompletedTotalScore += iLevel.iPassScore;
        Store();
        iObserver.StateChanged( EScorekeeperLevelCompleted );
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::Clear
// ----------------------------------------------------------------------------
//
void CScorekeeper::Clear()
    {
    FUNC_LOG;
    iLevelScore = 0;
    iLevelBonus = 0;
    iLevelTime = 0;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::Start
// ----------------------------------------------------------------------------
//
void CScorekeeper::Start()
    {
    FUNC_LOG;
    if ( ! iPeriodic->IsActive() )
        {
        TInt timeout = KExpireOneSecTimeout * 
            ( iLevel.iTime / KMaxProgressValue );
        iPeriodic->Start(   
            KExpireDelayTimeout,
            timeout,
            TCallBack( TimerCallback, this ) 
            );
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::Stop
// ----------------------------------------------------------------------------
//
void CScorekeeper::Stop()
    {
    FUNC_LOG;
    if ( iPeriodic->IsActive() )
        {
        iPeriodic->Cancel();
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::IsFuncKeyFull
// ----------------------------------------------------------------------------
//
TBool CScorekeeper::IsFuncKeyFull() const
    {
    FUNC_LOG;
    return ( iFuncKeyNum == KFullFuncKeyNumber ) ? ETrue : EFalse;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::IsFuncKeyEmpty
// ----------------------------------------------------------------------------
//
TBool CScorekeeper::IsFuncKeyEmpty() const
    {
    FUNC_LOG;
    return ( iFuncKeyNum == KEmptyFuncKeyNumber ) ? ETrue : EFalse;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::FuncKeyType
// ----------------------------------------------------------------------------
//
TAquaticType CScorekeeper::FuncKeyType() const
    {
    FUNC_LOG;
    return iFuncKeyType;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::FuncKey
// ----------------------------------------------------------------------------
//
void CScorekeeper::FuncKey( const RArray<TAquaticData>& aList )
    {
    FUNC_LOG;
    TAquaticType comboType = ComboType( aList );
    if ( IsFuncKeyEmpty() )
        {
        iFuncKeyType = comboType;
        iFuncKeyNum = 1;
        iFuncKeyVar = 0;
        iObserver.StateChanged( EScorekeeperFuncKeyUpdated );
        }
    else
        {
        if ( comboType == iFuncKeyType )
            {
            if ( ! IsFuncKeyFull() )
                {
                iFuncKeyNum += 1;
                iFuncKeyVar += 1;
                iObserver.StateChanged( EScorekeeperFuncKeyUpdated );
                }
            }
        else
            {
            if ( iFuncKeyVar == 0 )
                {
                iFuncKeyType = comboType;
                iFuncKeyNum = 1;
                iObserver.StateChanged( EScorekeeperFuncKeyUpdated );
                }
            else
                {
                iFuncKeyVar -= 1;
                }
            }
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::ClearFuncKey
// ----------------------------------------------------------------------------
//
void CScorekeeper::ClearFuncKey()
    {
    FUNC_LOG;
    iFuncKeyNum = 0;
    iFuncKeyVar = 0;
    iFuncKeyType = EAquaticNull;
    iObserver.StateChanged( EScorekeeperFuncKeyUpdated );
    }

// ----------------------------------------------------------------------------
// CScorekeeper::ExpireL
// ----------------------------------------------------------------------------
//
void CScorekeeper::Expire()
    {
    FUNC_LOG;
    ++iLevelTime;
    iObserver.StateChanged( EScorekeeperProgressUpdated );
    if ( iLevelTime == KMaxProgressValue )
        {
        iPeriodic->Cancel();
        iObserver.StateChanged( EScorekeeperLevelExpired );
        }
    }

// ----------------------------------------------------------------------------
// CScorekeeper::CScorekeeper
// ----------------------------------------------------------------------------
//
CScorekeeper::CScorekeeper( MScorekeeperObserver& aObserver )
    : iObserver( aObserver ), iFuncKeyType( EAquaticNull )
    { // no implementation required
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::ConstructL
// ----------------------------------------------------------------------------
//
void CScorekeeper::ConstructL()
    {
    FUNC_LOG;
    Restore();
    iLevel.iLevelID = iCompletedLevelID;
    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    }

// ----------------------------------------------------------------------------
// CScorekeeper::MakeBonus
// ----------------------------------------------------------------------------
//
void CScorekeeper::MakeBonus( TInt aFactor )
    {
    FUNC_LOG;
    TInt bonus( 0 );
    switch ( aFactor )
        {
        case KNumOneAquatics:
        case KNumTwoAquatics:
        case KNumThreeAquatics:
        case KNumFourAquatics:
        case KNumFiveAquatics:
            break;
        case KNumSixAquatics:
            bonus += KBounsSixAquatics;
            break;
        case KNumSevenAquatics:
            bonus += KBounsSevenAquatics;
            break;
        case KNumEightAquatics:
            bonus += KBounsEightAquatics;
            break;
        case KNumNineAquatics:
            bonus += KBounsNineAquatics;
            break;
        default:
            break;
        }
    iLevelBonus += bonus;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::UpdateAll
// ----------------------------------------------------------------------------
//
void CScorekeeper::UpdateAll()
    {
    FUNC_LOG;
    iObserver.StateChanged( EScorekeeperLevelUpdated );
    iObserver.StateChanged( EScorekeeperScoreUpdated );
    iObserver.StateChanged( EScorekeeperBonusUpdated );
    iObserver.StateChanged( EScorekeeperProgressUpdated );
    iObserver.StateChanged( EScorekeeperPromptUpdated );
    }

// ----------------------------------------------------------------------------
// CScorekeeper::ComboType
// ----------------------------------------------------------------------------
//
TAquaticType CScorekeeper::ComboType( const RArray<TAquaticData>& aList ) const
    {
    FUNC_LOG;
    TAquaticType comboType( EAquaticNull );
    TInt count( aList.Count() );
    if ( count > 0 )
        {
        comboType = aList[ 0 ].Type();
        for ( TInt i =0; i < aList.Count(); i++ )
            {
            if ( comboType != aList[i].Type() )
                {
                comboType = EAquaticNull;
                break;
                }
            }
        }
    return comboType;
    }

// ----------------------------------------------------------------------------
// CScorekeeper::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CScorekeeper::TimerCallback( TAny* aPtr )
    {
    CScorekeeper* self = static_cast<CScorekeeper*> ( aPtr );
    self->Expire();
    return 0;
    }

// End of file
