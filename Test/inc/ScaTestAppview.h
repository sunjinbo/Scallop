/* ====================================================================
 * File: ScaTestAppView.h
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __SCATEST_APPVIEW_H__
#define __SCATEST_APPVIEW_H__

#include <coecntrl.h>

#include <EngineObserver.h>

class CFbsBitmap;
class CFbsBitmapDevice;
class CFbsBitGc;
class CPeriodic;
class CEngineBase;
class CClassicEngineFactory;
class CStrategyEngineFactory;
class CFont;
/*! 
  @class CScaTestAppView
  
  @discussion An instance of the Application View object for the ScaTest 
  example application
  */
class CScaTestAppView : public CCoeControl, public MEngineObserver
    {
public:

/*!
  @function NewL
   
  @discussion Create a CScaTestAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CScaTestAppView
  */
    static CScaTestAppView* NewL(const TRect& aRect);

/*!
  @function NewLC
   
  @discussion Create a CScaTestAppView object, which will draw itself to aRect
  @param aRect the rectangle this view will be drawn to
  @result a pointer to the created instance of CScaTestAppView
  */
    static CScaTestAppView* NewLC(const TRect& aRect);


/*!
  @function ~CScaTestAppView
  
  @discussion Destroy the object and release all memory objects
  */
     ~CScaTestAppView();
    
    
    void Start();
    void Stop();
    void Pause();
    void Resume();
    void Restart();
    void Refresh();
    void FuncKey();

public:  // from CCoeControl
/*!
  @function Draw
  
  @discussion Draw this CScaTestAppView to the screen
  @param aRect the rectangle of this view that needs updating
  */
    void Draw(const TRect& aRect) const;
  
    void HandlePointerEventL(const TPointerEvent& aPointerEvent);

private:
    void StateChanged( TEngineAction aAction );
    void AuqaticChanged( TAquaticAction aAction, const RArray<TAquaticData>& aList );
    void PathChanged( TPathAction aAction, const RArray<TPoint>& aList );
    void ScorekeeperChanged( TScorekeeperAction aAction, TInt aValue );
    void FuncKeyChanged( TAquaticType aType, TInt aValue );

private:

/*!
  @function ConstructL
  
  @discussion  Perform the second phase construction of a CScaTestAppView object
  @param aRect the rectangle this view will be drawn to
  */
    void ConstructL(const TRect& aRect);

/*!
  @function CScaTestAppView
  
  @discussion Perform the first phase of two phase construction 
  */
    CScaTestAppView();
    
private:
    static TInt TimerCallback( TAny* aPtr );
    void DoDraw();
    void DoFrame();
    void CreateBmpBufferL();
    void ReleaseBmpBuffer();
    void DrawGrids();
    void DrawBornGrids( const RArray<TAquaticData>& aList );
    void DrawMaturedGrids( const RArray<TAquaticData>& aList );
    void DrawMovedGrids( const RArray<TAquaticData>& aList );
    void DrawChangedGrids( const RArray<TAquaticData>& aList );
    void DrawReleasedGrids( const RArray<TAquaticData>& aList );
    void DrawUpdatedGrids( const RArray<TAquaticData>& aList );
    void DrawSelectedGrids( const RArray<TAquaticData>& aList );
    void DrawUnselectedGrids( const RArray<TAquaticData>& aList );
    
    void SetEdgeColor( TAquaticType aType );
    void SetZoneColor( TAquaticType aType );

    void DrawPath( const RArray<TPoint>& aList );
    void ClearPath( const RArray<TPoint>& aList );
    
    void DrawEdge( const TPoint& aPos, TRgb aColor );
    void ClearAllPath();
    
    void DrawScore( TInt aScore );
    void DrawBonus( TInt aBonus );
    void DrawLevel( TInt aLevel );
    
    void DrawFuncKey( TAquaticType aType, TInt aValue );

    void DrawBitmap();

private:
    CFbsBitmap* iBitmap;
    CFbsBitmapDevice* iBitmapDevice;
    CFbsBitGc* iBitmapGc;
    CPeriodic* iPeriodic;
    
    TInt iSquareSideLen;
    CEngineBase* iEngine;
    CClassicEngineFactory* iClassicEngineFactory;
    CStrategyEngineFactory* iStrategyEngineFactory;
    
    TPoint iDragPos;
    TInt iDrag;
    
    CFont* iFont;
    TPoint iScorePos;
    TPoint iBonusPos;
    TPoint iLevelPos;
    };


#endif // __SCATEST_APPVIEW_H__
