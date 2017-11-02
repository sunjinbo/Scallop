/* ====================================================================
 * File: MatrixTaskScheduler.cpp
 * Created: 04/19/09
 * Modified: 04/19/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "MatrixTaskScheduler.h"
#include "MatrixTask.h"

// CONSTANTS
const TInt KHeadIndex = 0;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CMatrixTaskScheduler::NewL
// ----------------------------------------------------------------------------
//
CMatrixTaskScheduler* CMatrixTaskScheduler::NewL()
    {
    CMatrixTaskScheduler* self = new (ELeave) CMatrixTaskScheduler;
    CleanupStack::PushL (self );
    self->ConstructL ();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CMatrixTaskScheduler::~CMatrixTaskScheduler
// ----------------------------------------------------------------------------
//
CMatrixTaskScheduler::~CMatrixTaskScheduler()
    {
    iTaskList.ResetAndDestroy();
    iTaskList.Close();
    }

// ----------------------------------------------------------------------------
// CMatrixTaskScheduler::AddTask
// ----------------------------------------------------------------------------
//
void CMatrixTaskScheduler::AddTask( CMatrixTask* aTask )
    {
    iTaskList.Append( aTask );
    if ( ! iRunning )
        {
        iRunning = ETrue;
        iTaskList[ KHeadIndex ]->DoTask();
        }
    }

// ----------------------------------------------------------------------------
// CMatrixTaskScheduler::Clear
// ----------------------------------------------------------------------------
//
void CMatrixTaskScheduler::Clear()
    {
    iTaskList.ResetAndDestroy();
    }

// ----------------------------------------------------------------------------
// CMatrixTaskScheduler::AllTasksCompleted
// ----------------------------------------------------------------------------
//
TBool CMatrixTaskScheduler::AllTasksCompleted() const
    {
    return iTaskList.Count() > 0 ? EFalse : ETrue;
    }

// ----------------------------------------------------------------------------
// CMatrixTaskScheduler::TaskCompleted
// ----------------------------------------------------------------------------
//
void CMatrixTaskScheduler::TaskCompleted()
    {
    CMatrixTask* task( iTaskList[ KHeadIndex ] );
    delete task;
    task = NULL;

    iTaskList.Remove( KHeadIndex );
    iTaskList.Compress();
    iRunning = EFalse;
    if ( iTaskList.Count() )
        {
        iTaskList[ KHeadIndex ]->DoTask();
        }
    }

// ----------------------------------------------------------------------------
// CMatrixTaskScheduler::CMatrixTaskScheduler
// ----------------------------------------------------------------------------
//
CMatrixTaskScheduler::CMatrixTaskScheduler()
    : iRunning( EFalse )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CMatrixTaskScheduler::CMatrixTaskScheduler
// ----------------------------------------------------------------------------
//
void CMatrixTaskScheduler::ConstructL()
    { // No implementation required.
    }

// End of File
