/* ====================================================================
 * File: ScorekeeperObserver.h
 * Created: 06/16/09
 * Modified: 06/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef M_SCOREKEEPEROBSERVER_H
#define M_SCOREKEEPEROBSERVER_H

// INCLUDE FILE
#include <e32std.h>

// Enumeration for specifying, which tetrimino state chaged.
enum TScorekeeperState // for reporting to observer
    {
    EScorekeeperLevelUpdated = 0,
    EScorekeeperScoreUpdated,
    EScorekeeperBonusUpdated,
    EScorekeeperMovesUpdated,
    EScorekeeperFuncKeyUpdated,
    EScorekeeperProgressUpdated,
    EScorekeeperPromptUpdated,
    EScorekeeperLevelExpired,
    EScorekeeperLevelFailed,
    EScorekeeperLevelCompleted
    };

// CLASS DECLARATION
/**
* MScorekeeperObserver class
*
* @since S60 5.0
*/
class MScorekeeperObserver
    {
public:
    // Called when tetrimino state changes and observer needs to be notified.
    virtual void StateChanged( TScorekeeperState aNewState ) = 0;
    };

#endif // M_SCOREKEEPEROBSERVER_H

// End of file
