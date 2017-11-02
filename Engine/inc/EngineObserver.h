/* ====================================================================
 * File: EngineObserver.h
 * Created: 06/13/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_ENGINEOBSERVER_H
#define M_ENGINEOBSERVER_H

// INCLUDE FILES
#include <e32cmn.h>
#include "AquaticData.h"

// ENUMERATES

// Engine states
enum TEngineAction
    {
    EEngineActionStart,
    EEngineActionPause,
    EEngineActionStop,
    EEngineActionLevelExpired,
    EEngineActionLevelFailed,
    EEngineActionGameOver
    };

// Aquatic states
enum TAquaticAction
    {
    EAquaticActionBorn = 0,
    EAquaticActionMatured,
    EAquaticActionMoved,
    EAquaticActionChanged,
    EAquaticActionReleased,
    EAquaticActionUpdated,
    EAquaticActionSelected,
    EAquaticActionUnselected
    };

// Path states
enum TPathAction
    {
    EPathActionDisplayed,
    EPathActionDisappeared
    };

// Scorekeeper states
enum TScorekeeperAction
    {
    EScorekeeperActionLevel,
    EScorekeeperActionScore,
    EScorekeeperActionBonus,
    EScorekeeperActionMoves,
    EScorekeeperActionProgress
    };
    

// CLASS DECLARATION

/**
* MEngineObserver class
*
* @since S60 5.0
*/
class MEngineObserver
    {
public: // Called when game engine state changes and observer needs to be notified.
    virtual void StateChanged( TEngineAction aAction ) = 0;
    virtual void AuqaticChanged( TAquaticAction aAction, const RArray<TAquaticData>& aList ) = 0;
    virtual void PathChanged( TPathAction aAction, const RArray<TPoint>& aList ) = 0;
    virtual void ScorekeeperChanged( TScorekeeperAction aAction, TInt aValue ) = 0;
    virtual void PromptChanged( const TDesC& aText ) = 0;
    virtual void FuncKeyChanged( TAquaticType aType, TInt aValue ) = 0;
    };

#endif // M_ENGINEOBSERVER_H

// End of file
