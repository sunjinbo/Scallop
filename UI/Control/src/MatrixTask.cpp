/* ====================================================================
 * File: MatrixTask.cpp
 * Created: 11/07/09
 * Modified: 11/10/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <matrix.mbg>
#include <BmpUtils.h>
#include "MatrixTask.h"
#include "Matrix.h"
#include "MatrixTaskObserver.h"
#include "GraphicsLayer.h"

// CONSTANTS
const TInt KMatrixMoveTimeout = 250000;
const TInt KMatrixGradientTimeout = 250000;
const TInt KMatrixGradients = 4; // 0<->64<->128<->192<->255
const TInt KScallopMargin = 0;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CMatrixTask::NewL
// ----------------------------------------------------------------------------
//
CMatrixTask* CMatrixTask::NewL( CMatrix& aMatrix, MMatrixTaskObserver& aObserver )
    {
    CMatrixTask* self = new (ELeave) CMatrixTask( aMatrix, aObserver );
    CleanupStack::PushL (self );
    self->ConstructL();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CMatrixTask::~CMatrixTask
// ----------------------------------------------------------------------------
//
CMatrixTask::~CMatrixTask()
    {
    Cancel();
    iArray.Close();
    }

// ----------------------------------------------------------------------------
// CMatrixTask::SetType
// ----------------------------------------------------------------------------
//
void CMatrixTask::SetType( TTaskType aType )
    {
    iType = aType;
    }

// ----------------------------------------------------------------------------
// CMatrixTask::Append
// ----------------------------------------------------------------------------
//
void CMatrixTask::Append( const TAquaticData& aAquatic )
    {
    if ( ! IsActive() )
        {
        iArray.Append( aAquatic );
        }
    }

// ----------------------------------------------------------------------------
// CMatrixTask::Append
// ----------------------------------------------------------------------------
//
void CMatrixTask::Append( const RArray<TAquaticData>& aArray )
    {
    if ( ! IsActive() )
        {
        for ( TInt ix = 0; ix < aArray.Count(); ix++ )
            {
            iArray.Append( aArray[ ix ] );
            }
        }
    }

// ----------------------------------------------------------------------------
// CMatrixTask::DoTask
// ----------------------------------------------------------------------------
//
void CMatrixTask::DoTask()
    {
    if ( ! IsActive() )
        {
        switch( iType )
            {
            case EDraw:
                {
                DoDraw();
                iObserver.TaskCompleted();
                }
                break;
            case ERemove:
                {
                DoRemove();
                iObserver.TaskCompleted();
                }
                break;
            case EMove:
                {
                TInt count( iArray.Count() );
                RemoveAquatic( iArray[ count - 1 ] );
                iMoves = count;
                CTimer::After( KMatrixMoveTimeout );
                }
                break;
            case ESelect:
                {
                iMatrix.RomanceBubble( iArray[0].Position(), KRgbRed );
                iObserver.TaskCompleted();
                }
                break;
            case EUnselect:
                {
                iObserver.TaskCompleted();
                }
                break;
            case EDarken:
                {
                iGradients = EGs255;
                CTimer::After( KMatrixGradientTimeout );
                }
                break;
            case ELighten:
                {
                iGradients = EGs0;
                CTimer::After( KMatrixGradientTimeout );
                }
                break;
            case EBlasting:
                { // no implementation required.
                }
                break;
            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// CMatrixTask::CMatrixTask
// ----------------------------------------------------------------------------
//
CMatrixTask::CMatrixTask( CMatrix& aMatrix, MMatrixTaskObserver& aObserver )
    : CTimer( EPriorityStandard ), iMatrix( aMatrix ), iObserver( aObserver )
    {
    CActiveScheduler::Add( this );
    }

// ----------------------------------------------------------------------------
// CMatrixTask::ConstructL
// ----------------------------------------------------------------------------
//
void CMatrixTask::ConstructL()
    {
    CTimer::ConstructL();
    }

// ----------------------------------------------------------------------------
// CMatrixTask::RunL
// ----------------------------------------------------------------------------
//
void CMatrixTask::RunL()
    {
    if ( iStatus == KErrNone )
        {
        switch ( iType )
            {
            case EDraw: // flowthru
            case ERemove: // flowthru
                break;
            case EMove:
                {
                if ( --iMoves > 0 )
                    {
                    DoMove();
                    CTimer::After( KMatrixMoveTimeout );
                    }
                else
                    {
                    iMatrix.iEffectsLayer->Clear();
                    DrawAquatic( iArray[0] );
                    iObserver.TaskCompleted();
                    }
                }
                break;
            case EDarken:
                {
                if ( --iGradients < EGs0 )
                    {
                    iObserver.TaskCompleted();
                    }
                else
                    {
                    DoDraw( (TGrayScale)iGradients );
                    CTimer::After( KMatrixGradientTimeout );
                    }
                }
                break;
           case ELighten:
                {
                if ( ++iGradients > EGs255 )
                    {
                    iObserver.TaskCompleted();
                    }
                else
                    {
                    DoDraw( (TGrayScale)iGradients );
                    CTimer::After( KMatrixGradientTimeout );
                    }
                }
                break;
            case EBlasting: 
                // flowthru
            default:
                break;
            }
        }
    }

// ----------------------------------------------------------------------------
// CMatrixTask::DoDraw
// ----------------------------------------------------------------------------
//
void CMatrixTask::DoDraw( TGrayScale aGs )
    {
    for ( TInt ix = 0; ix < iArray.Count(); ix++ )
        {
        DrawAquatic( iArray[ ix ], aGs );
        }
    }

// ----------------------------------------------------------------------------
// CMatrixTask::DoRemove
// ----------------------------------------------------------------------------
//
void CMatrixTask::DoRemove()
    {
    for ( TInt ix = 0; ix < iArray.Count(); ix++ )
        {
        RemoveAquatic( iArray[ ix ] );
        }
    }

// ----------------------------------------------------------------------------
// CMatrixTask::DoMove
// ----------------------------------------------------------------------------
//
void CMatrixTask::DoMove()
    {
    TAquaticData aquatic( iArray[ iMoves ] );
    TInt bmpIx(0), maskIx(0);
    switch( aquatic.Type() )
        {
        case EBlueScallop:
            {
            bmpIx = EMbmMatrixBluescallop_matured;
            maskIx = EMbmMatrixScallop_matured_mask;
            }
            break;
        case EDarkBlueScallop:
            {
            bmpIx = EMbmMatrixDarkbluescallop_matured;
            maskIx = EMbmMatrixScallop_matured_mask;
            }
            break;
        case EGreenScallop:
            {
            bmpIx = EMbmMatrixGreenscallop_matured;
            maskIx = EMbmMatrixScallop_matured_mask;
            }
            break;
        case EDarkGreenScallop:
            {
            bmpIx = EMbmMatrixDarkgreenscallop_matured;
            maskIx = EMbmMatrixScallop_matured_mask;
            }
            break;
        case ERedScallop:
            {
            bmpIx = EMbmMatrixRedscallop_matured;
            maskIx = EMbmMatrixScallop_matured_mask;
            }
            break;
        case EMulberryScallop:
            {
            bmpIx = EMbmMatrixMulberryscallop_matured;
            maskIx = EMbmMatrixScallop_matured_mask;
            }
            break;
        case EOrangeScallop:
            {
            bmpIx = EMbmMatrixOrangescallop_matured;
            maskIx = EMbmMatrixScallop_matured_mask;
            }
            break;
        case EYellowScallop:
            {
            bmpIx = EMbmMatrixYellowscallop_matured;
            maskIx = EMbmMatrixScallop_matured_mask;
            }
            break;
        case EStarFish: // fall through
        case ETurtle: // fall through
        case EShark: // fall through
        case EOctopus: // fall through
        case ECuttleFish: // fall through
        case ESeaCrab: // fall through
        case EJellyfish: // fall through
            {
            bmpIx = EMbmMatrixBluescallop_matured;
            maskIx = EMbmMatrixScallop_matured_mask;
            }
            break;
        default:
            break;
        }
    
    TRect rect( iMatrix.Rect() );
    TSize theScallopSize( iMatrix.iBubbleSize );
    TPoint theScallopPosition;
    
    theScallopPosition.iX = theScallopSize.iWidth * aquatic.Position().iX + rect.iTl.iX;
    theScallopPosition.iY = theScallopSize.iHeight * aquatic.Position().iY + rect.iTl.iY;
    TRect theRect( theScallopPosition, theScallopSize );
    theRect.Shrink( KScallopMargin, KScallopMargin );

    iMatrix.iEffectsLayer->Clear();
    iMatrix.iEffectsLayer->DrawBitmap( 
                theRect, 
                iMatrix.iBmpUtils->Bitmap( bmpIx ) 
                );
    iMatrix.iEffectsLayer->DrawMask( 
                theRect,
                iMatrix.iBmpUtils->Bitmap( maskIx ) 
                );
    }

// ----------------------------------------------------------------------------
// CMatrixTask::DrawAquatics
// ----------------------------------------------------------------------------
//
void CMatrixTask::DrawAquatic( const TAquaticData& aAquatic, TGrayScale aGs )
    {
    TInt bmpIx(0), maskIx(0);

    // bitmap
    switch( aAquatic.Type() )
        {
        case EBlueScallop:
            {
            if ( aAquatic.IsMature() )
                {
                bmpIx = EMbmMatrixBluescallop_matured;
                }
            else
                {
                bmpIx = EMbmMatrixBluescallop_unmatured;
                }
            }
            break;
        case EDarkBlueScallop:
            {
            if ( aAquatic.IsMature() )
                {
                bmpIx = EMbmMatrixDarkbluescallop_matured;
                }
            else
                {
                bmpIx = EMbmMatrixDarkbluescallop_unmatured;
                }
            }
            break;
        case EGreenScallop:
            {
            if ( aAquatic.IsMature() )
                {
                bmpIx = EMbmMatrixGreenscallop_matured;
                }
            else
                {
                bmpIx = EMbmMatrixGreenscallop_unmatured;
                }
            }
            break;
        case EDarkGreenScallop:
            {
            if ( aAquatic.IsMature() )
                {
                bmpIx = EMbmMatrixDarkgreenscallop_matured;
                }
            else
                {
                bmpIx = EMbmMatrixDarkgreenscallop_unmatured;
                }
            }
            break;
        case ERedScallop:
            {
            if ( aAquatic.IsMature() )
                {
                bmpIx = EMbmMatrixRedscallop_matured;
                }
            else
                {
                bmpIx = EMbmMatrixRedscallop_unmatured;
                }
            }
            break;
        case EMulberryScallop:
            {
            if ( aAquatic.IsMature() )
                {
                bmpIx = EMbmMatrixMulberryscallop_matured;
                }
            else
                {
                bmpIx = EMbmMatrixMulberryscallop_unmatured;
                }
            }
            break;
        case EOrangeScallop:
            {
            if ( aAquatic.IsMature() )
                {
                bmpIx = EMbmMatrixOrangescallop_matured;
                }
            else
                {
                bmpIx = EMbmMatrixOrangescallop_unmatured;
                }
            }
            break;
        case EYellowScallop:
            {
            if ( aAquatic.IsMature() )
                {
                bmpIx = EMbmMatrixYellowscallop_matured;
                }
            else
                {
                bmpIx = EMbmMatrixYellowscallop_unmatured;
                }
            }
            break;
        case EStarFish: // flowthru
        case ETurtle: // flowthru
        case EShark: // flowthru
        case EOctopus: // flowthru
        case ECuttleFish: // flowthru
        case ESeaCrab: // flowthru
        case EJellyfish: // flowthru
            {
            if ( aAquatic.IsMature() )
                {
                bmpIx = EMbmMatrixBluescallop_matured;
                }
            else
                {
                bmpIx = EMbmMatrixBluescallop_unmatured;
                }
            }
            break;
        default:
            break;
        }

    // mask
    switch ( aGs )
        {
        case EGs0:
            {
            if ( aAquatic.IsMature() )
                {
                maskIx = EMbmMatrixScallop_matured_mask;
                }
            else
                {
                maskIx = EMbmMatrixScallop_unmatured_mask;
                }
            }
            break;
        case EGs64:
            {
            if ( aAquatic.IsMature() )
                {
                maskIx = EMbmMatrixScallop_matured_g64_mask;
                }
            else
                {
                maskIx = EMbmMatrixScallop_unmatured_g64_mask;
                }
            }
            break;
        case EGs128:
            {
            if ( aAquatic.IsMature() )
                {
                maskIx = EMbmMatrixScallop_matured_g128_mask;
                }
            else
                {
                maskIx = EMbmMatrixScallop_unmatured_g128_mask;
                }
            }
            break;
        case EGs192:
            {
            if ( aAquatic.IsMature() )
                {
                maskIx = EMbmMatrixScallop_matured_g192_mask;
                }
            else
                {
                maskIx = EMbmMatrixScallop_unmatured_g192_mask;
                }
            }
            break;
        case EGs255:
            {
            if ( aAquatic.IsMature() )
                {
                maskIx = EMbmMatrixScallop_matured_g255_mask;
                }
            else
                {
                maskIx = EMbmMatrixScallop_unmatured_g255_mask;
                }
            }
            break;
        default:
            break;
        }

    TRect rect( iMatrix.Rect() );
    TSize theScallopSize( iMatrix.iBubbleSize );
    TPoint theScallopPosition;
    theScallopPosition.iX = theScallopSize.iWidth * aAquatic.Position().iX + rect.iTl.iX;
    theScallopPosition.iY = theScallopSize.iHeight * aAquatic.Position().iY + rect.iTl.iY;
    TRect theRect( theScallopPosition, theScallopSize );
    theRect.Shrink( KScallopMargin, KScallopMargin );

    iMatrix.iAuqaticLayer->DrawBitmap( 
                theRect, 
                iMatrix.iBmpUtils->Bitmap( bmpIx ) 
                );
    iMatrix.iAuqaticLayer->DrawMask( 
                theRect,
                iMatrix.iBmpUtils->Bitmap( maskIx ) 
                );
    }

// ----------------------------------------------------------------------------
// CMatrixTask::RemoveAquatic
// ----------------------------------------------------------------------------
//
void CMatrixTask::RemoveAquatic( const TAquaticData& aAquatic )
    {
    TRect rect( iMatrix.Rect() );
    TSize theScallopSize( iMatrix.iBubbleSize );
    TPoint theScallopPosition;
    theScallopPosition.iX = theScallopSize.iWidth * aAquatic.Position().iX;
    theScallopPosition.iY = theScallopSize.iHeight * aAquatic.Position().iY;
    TRect theRect( theScallopPosition, theScallopSize );
    theRect.Shrink( KScallopMargin, KScallopMargin );
    iMatrix.iAuqaticLayer->Clear( theRect );
    }

// End of File
