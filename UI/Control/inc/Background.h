/* ====================================================================
 * File: Background.h
 * Created: 10/28/09
 * Modified: 11/24/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BACKGROUND_H
#define C_BACKGROUND_H

// INCLUDE FILES
#include <coecntrl.h>

// FORWARD DECLARATIONS
class CGraphicsManager;
class CGraphicsLayer;
class CPeriodic;
class CBmpUtils;

// CLASS DECLARATION
/**
* CBackground class
*
* @since S60 5.0
*/
class CBackground : public CCoeControl
    {
public: // Constructor and destructor

    static CBackground* NewL( 
            CGraphicsManager& aGraphicsManager,
            const TRect& aRect 
            );
    virtual ~CBackground();

public: // New function
    void ConstructFromResourceL( TResourceReader& aReader );
    void MoveFish();
    void MoveReef();
    void MoveJellyfish();
    void MoveShoal();

public: // from CCoeControl
    void SizeChanged();

private: // Constructor
    CBackground( CGraphicsManager& aGraphicsManager );
    void ConstructL( const TRect& aRect );

private: // New function
    static TInt FishCallback( TAny* aPtr );
    static TInt ReefCallback( TAny* aPtr );
    static TInt JellyfishCallback( TAny* aPtr );
    static TInt ShoalCallback( TAny* aPtr );
    void SetupWidget();
    TInt Rand( TInt aRange ) const;

private: // Member Data
    CGraphicsManager& iGraphicsManager; // Not own.
    CBmpUtils* iBmpUtils;
    CGraphicsLayer* iBackgroundLayer; // Own.
    CGraphicsLayer* iForegroundLayer; // Own.
    CGraphicsLayer* iForeground2Layer; // Own.
    CGraphicsLayer* iEffectsLayer; // Own.
    
    CPeriodic* iFishPeriodic; // Own.
    CPeriodic* iReefPeriodic; // Own.
    CPeriodic* iJellyfishPeriodic; // Own.
    CPeriodic* iShoalPeriodic; // Own.


    /**
    * Wiget's move state
    */
    enum TMoveState
        {
        EMoveEast = 0,
        EMoveNorth,
        EMoveSouth,
        EMoveWest,
        EMoveNorthwest,
        EMoveNortheast,
        EMoveSouthwest,
        EMoveSoutheast,
        EMoveCentral,
        EMoveStateLastElement
        };

    /**
    * TWidget class
    */
    class TWidget
        {
    public: // New functions
        void Next();
        TBool HitTest() const;
    private: // New function
        void DoNext( TPoint& aPosition ) const;

    public: // Member Data
        TRect iActiveRect;
        TSize iSize;
        TPoint iPosition;
        TMoveState iMoveState;
        CFbsBitmap* iBitmap; // Not own.
        CFbsBitmap* iMask; // Not own.
        };

    TBool iActiveFish;
    TWidget iRedFish;
    TWidget iYellowFish;
    TWidget iLeftReef;
    TWidget iRightReef;
    TWidget iJellyfish;
    TInt iJellyfishMoves;
    };

#endif // C_BACKGROUND_H

// End of File
