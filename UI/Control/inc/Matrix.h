/* ====================================================================
 * File: Matrix.h
 * Created: 11/07/09
 * Modified: 11/07/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_MATRIX_H
#define C_MATRIX_H

// INCLUDE FILES
#include <coecntrl.h>
#include <EngineObserver.h>

// FORWARD DECLARATIONS
class CPeriodic;
class CBmpUtils;
class CGraphicsManager;
class CGraphicsLayer;
class CMatrixTaskScheduler;
class TAquaticData;

// CONSTANTS
const TInt KMaxTips = 16;

// CLASS DECLARATION

/**
* TZoom class
*
* @since S60 5.0
*/
class TZoom
        {
public: // Member data
        enum TZoomState
            {
            ESmallestToSmall, // smallest
            ESmallToNormal, // small
            ENormalToLarge, // normal
            ELargeToLargest, // large
            ELargestToLarge, // largest
            ELargeToNormal, // large
            ENormalToSmall, // normal
            ESmallToSmallest, // small
            EZoomStateCount // the count of zoom states
            } iZoomState;

public: // Constructor
        TZoom( TZoom::TZoomState aZoomState );

public: // New function
        void Next();
        };

/**
* MMatrixObserver class
*
* @since S60 5.0
*/
class MMatrixObserver
    {
public: // New functions
    virtual void ClickL( TInt aX, TInt aY ) = 0;
    virtual void DragL( TInt ax, TInt aY ) = 0;
    };

/**
* CMatrix class
*
* @since S60 5.0
*/
class CMatrix : public CCoeControl
    {
public: // friend class
    friend class CMatrixTask;

public: // Constructor and Destructor
    IMPORT_C static CMatrix* NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect );
    IMPORT_C virtual ~CMatrix();

public: // New Functions
    IMPORT_C void UpdateAquaticL( TAquaticAction aAction, const RArray<TAquaticData>& aAquatics );
    IMPORT_C void ShowPath( const RArray<TPoint>& aPath );
    IMPORT_C void ShowTips( TInt aValue );
    IMPORT_C void ClearPath();
    IMPORT_C void SetObserver( MMatrixObserver* aObserver );

    void DoTips();
    TBool IsShock() const;
    void Shock();
    void StartShockL();
    void StopShock();
    void Zoom();
    void StartZoomL();
    void StopZoom();

public: // from CCoeControl
    void SizeChanged();
    void HandlePointerEventL( const TPointerEvent& aPointerEvent );

private: // Constructor
    CMatrix( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // New functions
    void DrawBubbles( TBool aShock = EFalse );
    void CalcBubbleSize();
    static TInt TimerCallback( TAny* aPtr );
    static TInt TipsCallback( TAny* aPtr );
    TInt Rand( TInt aRange ) const;
    void ShockRect( TRect& aRect );
    void SetupZoom();
    void RomanceBubble( const TPoint& aBubble, TRgb aColor );

private: // Data members
    CGraphicsManager& iGraphicsManager;
    MMatrixObserver* iObserver; // Own.
    CGraphicsLayer* iPathLayer; // Own.
    CGraphicsLayer* iBubbleLayer; // Own.
    CGraphicsLayer* iAuqaticLayer; // Own.
    CGraphicsLayer* iEffectsLayer; // Own.
    CGraphicsLayer* iTipsLayer; // Own.
    CMatrixTaskScheduler* iScheduler; // Own.
    CBmpUtils* iBmpUtils; // Own.
    CPeriodic* iBubblePeriodic; // Own.
    CPeriodic* iTipsPeriodic; // Own.
    TInt iBubbleShockTimes;
    TSize iBubbleSize;
    TBool iShock;
    RArray<TZoom> iBubblesZoom;
    TPoint iDragPos;
    TPoint iTipsPos;
    TInt iTipsMoves;
    TBuf<KMaxTips> iTipsBuffer;
    TInt iDrag;
    };

#endif // C_MATRIX_H

// End of File
