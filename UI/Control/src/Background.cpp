/* ====================================================================
 * File: Background.cpp
 * Created: 10/28/09
 * Modified: 11/24/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#if !defined(__WINS__)
#include <eikenv.h>
#include <eikappui.h>
#include <eikapp.h>
#endif // !defined( __WINS__ )
#include <barsread.h>
#include <BmpUtils.h>
#include <bak.mbg>
#include "Background.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"
#include "ScaLogger.h"

// CONSTANTS
const TInt KFishDelayTimeout = 0;
const TInt KFishFrameUpdateTimeout = 100000;
const TInt KJellyfishDelayTimeout = 0;
const TInt KJellyfishFrameUpdateTimeout = 250000;
const TInt KReefDelayTimeout = 0;
const TInt KReefFrameUpdateTimeout = 250000;
const TInt KProportionNumerator = 4;
const TInt KRedFishWidth = 80;
const TInt KRedFishHeight = 70;
const TInt KYellowFishWidth = 77;
const TInt KYellowFishHeight = 77;
const TInt KJellyfishWidth = 72;
const TInt KJellyfishHeight = 96;
const TInt KShoalWidth = 0;
const TInt KShoalHeight = 0;
const TInt KLeftReefWidth = 150;
const TInt KLeftReefHeight = 150;
const TInt KRightReefWidth = 156;
const TInt KRightReefHeight = 164;
const TInt KMoonWidth = 102;
const TInt KMoonHeight = 108;
const TInt KMaxJellyfishMoves = 30;
const TInt KReefMoves = 5;

#if defined( __WINS__ )
_LIT( KMbmBackgroundFileName, "Z:\\resource\\apps\\bak.mbm" );
#else
_LIT( KMbmBackgroundFileName, "\\resource\\apps\\bak.mbm" );
#endif // __WINS__

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CBackground::NewL
// ----------------------------------------------------------------------------
//
CBackground* CBackground::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CBackground* self = new (ELeave) CBackground( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CBackground::~CBackground
// ----------------------------------------------------------------------------
//
CBackground::~CBackground()
    {
    delete iBmpUtils;
    delete iBackgroundLayer;
    delete iForegroundLayer;
    delete iForeground2Layer;
    delete iEffectsLayer;
    
    if ( iFishPeriodic )
        {
        iFishPeriodic->Cancel();
        delete iFishPeriodic;
        }

    if ( iReefPeriodic )
        {
        iReefPeriodic->Cancel();
        delete iReefPeriodic;
        }
        
    if ( iJellyfishPeriodic )
        {
        iJellyfishPeriodic->Cancel();
        delete iJellyfishPeriodic;
        }
    }

// ----------------------------------------------------------------------------
// CBackground::ConstructBackgroundL
// ----------------------------------------------------------------------------
//
void CBackground::ConstructFromResourceL( TResourceReader& aReader )
    {
    FUNC_LOG;
    TInt32 bakIx = aReader.ReadInt32 ();
    iBmpUtils->SetSize( bakIx, Rect().Size() );
    CFbsBitmap* bak = iBmpUtils->Bitmap( bakIx );
    iBackgroundLayer->DrawBitmap( Rect(), bak );

    TInt32 maskIx = aReader.ReadInt32 ();
    iBmpUtils->SetSize( maskIx, Rect().Size() );
    CFbsBitmap* mask = iBmpUtils->Bitmap( maskIx );
    iBackgroundLayer->DrawMask( Rect(), mask );
    }

// ----------------------------------------------------------------------------
// CBackground::MoveFish
// ----------------------------------------------------------------------------
//
void CBackground::MoveFish()
    {
    if ( ! iActiveFish )
        {
        if ( iRedFish.HitTest() )
            {
            iRedFish.Next();
            iForeground2Layer->DrawBitmap( 
                TRect( iRedFish.iPosition, iRedFish.iSize ), 
                iRedFish.iBitmap 
                );
            iForeground2Layer->DrawMask( 
                TRect( iRedFish.iPosition, iRedFish.iSize ), 
                iRedFish.iMask
                );
            }
        else
            {
            iActiveFish = ETrue;
            iRedFish.iPosition.iX = iRedFish.iActiveRect.iTl.iX;
            iRedFish.iPosition.iY = iRedFish.iActiveRect.iTl.iY + 
                Rand( iRedFish.iActiveRect.Height() - iRedFish.iSize.iHeight );
            }
        }
    else //  iActiveFish
        {
        TRect yellowFish( iYellowFish.iPosition, iYellowFish.iSize );
        if ( iYellowFish.HitTest() )
            {
            iYellowFish.Next();
            iForeground2Layer->Clear();
            iForeground2Layer->DrawBitmap( 
                TRect( iYellowFish.iPosition, iYellowFish.iSize ), 
                iYellowFish.iBitmap 
                );
            iForeground2Layer->DrawMask( 
                TRect( iYellowFish.iPosition, iYellowFish.iSize ), 
                iYellowFish.iMask
                );
            }
        else
            {
            iActiveFish = EFalse;
            iYellowFish.iPosition.iX = iYellowFish.iActiveRect.iBr.iX - KYellowFishWidth;
            iYellowFish.iPosition.iY = iYellowFish.iActiveRect.iTl.iY + 
                Rand( iYellowFish.iActiveRect.Height() - iYellowFish.iSize.iHeight );
            }
        }
    }

// ----------------------------------------------------------------------------
// CBackground::MoveReef
// ----------------------------------------------------------------------------
//
void CBackground::MoveReef()
    {
    if ( iLeftReef.HitTest() )
        {
        iLeftReef.Next();
        iForegroundLayer->DrawBitmap( 
            TRect( iLeftReef.iPosition, iLeftReef.iSize ), 
            iLeftReef.iBitmap
            );
        iForegroundLayer->DrawMask( 
            TRect( iLeftReef.iPosition, iLeftReef.iSize ), 
            iLeftReef.iMask
            );
        }
    else
        {
        iLeftReef.iMoveState = 
            ( iLeftReef.iMoveState == EMoveNorth ) ? EMoveSouth : EMoveNorth;
        }

    if ( iRightReef.HitTest() )
        {
        iRightReef.Next();
        iForegroundLayer->DrawBitmap( 
            TRect( iRightReef.iPosition, iRightReef.iSize ), 
            iRightReef.iBitmap 
            );
        iForegroundLayer->DrawMask( 
            TRect( iRightReef.iPosition, iRightReef.iSize ), 
            iRightReef.iMask
            );
        }
    else
        {
        iRightReef.iMoveState = 
            ( iRightReef.iMoveState == EMoveNorth ) ? EMoveSouth : EMoveNorth;
        }
    }

// ----------------------------------------------------------------------------
// CBackground::MoveJellyfish
// ----------------------------------------------------------------------------
//
void CBackground::MoveJellyfish()
    {
    if ( iJellyfish.HitTest() && iJellyfishMoves != 0 )
        {
        iJellyfishMoves--;
        iJellyfish.Next();
        iEffectsLayer->Clear();
        if ( iJellyfish.iMoveState != EMoveCentral )
            {
            iEffectsLayer->DrawBitmap( 
                TRect( iJellyfish.iPosition, iJellyfish.iSize ), 
                iJellyfish.iBitmap
                );
            }
        else
            {
            iEffectsLayer->DrawBitmap( 
                TRect( iJellyfish.iPosition, iJellyfish.iSize ), 
                iBmpUtils->Bitmap( EMbmBakJellyfish_close_eye )
                );
            }

        iEffectsLayer->DrawMask( 
            TRect( iJellyfish.iPosition, iJellyfish.iSize ), 
            iJellyfish.iMask
            );
        }
    else
        {
        iJellyfishMoves = KMaxJellyfishMoves;
        iJellyfish.iMoveState = 
            ( TMoveState )Rand( EMoveStateLastElement );
        }
    }

// ----------------------------------------------------------------------------
// CBackground::MoveShoal
// ----------------------------------------------------------------------------
//
void CBackground::MoveShoal()
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CBackground::SizeChanged
// ----------------------------------------------------------------------------
//
void CBackground::SizeChanged()
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CBackground::CBackground
// ----------------------------------------------------------------------------
//
CBackground::CBackground( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CBackground::ConstructL
// ----------------------------------------------------------------------------
//
void CBackground::ConstructL( const TRect& aRect )
    {
    FUNC_LOG;
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );
    
    TFileName fileName;

#if !defined( __WINS__ )
    TParse parse;
    parse.Set( iEikonEnv->EikAppUi()->Application()->AppFullName(), NULL, NULL );
    fileName.Append( parse.Drive() );
#endif // !defined( __WINS__ )

    fileName.Append( KMbmBackgroundFileName );
    INFO( "Create a instance of CBmpUtils class and loading bitmap files" );
    INFO_1( "fileName = %S", &fileName );
    iBmpUtils = CBmpUtils::NewL( 
                    fileName,
                    EMbmBakBak, 
                    EMbmBakLastElement 
                    );
    INFO( "Done!!!" );

    // Setup widgets
    SetupWidget();

    iBackgroundLayer = CGraphicsLayer::NewL( aRect, EBakBackground );
    iGraphicsManager.RegisterLayer( iBackgroundLayer );
    iForegroundLayer = CGraphicsLayer::NewL( aRect, EBakForeground );
    iGraphicsManager.RegisterLayer( iForegroundLayer );
    iForeground2Layer = CGraphicsLayer::NewL( aRect, EBakForeground );
    iGraphicsManager.RegisterLayer( iForeground2Layer );
    iEffectsLayer = CGraphicsLayer::NewL( aRect, EBakEffects );
    iGraphicsManager.RegisterLayer( iEffectsLayer );

    iFishPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iFishPeriodic->Cancel();
    iFishPeriodic->Start(
            KFishDelayTimeout,
            KFishFrameUpdateTimeout,
            TCallBack( FishCallback, this )
            );

    iReefPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iReefPeriodic->Cancel();
    
    iReefPeriodic->Start(
            KReefDelayTimeout,
            KReefFrameUpdateTimeout,
            TCallBack( ReefCallback, this )
            );
    
    iJellyfishPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iJellyfishPeriodic->Cancel();
    iJellyfishPeriodic->Start(
            KJellyfishDelayTimeout,
            KJellyfishFrameUpdateTimeout,
            TCallBack( JellyfishCallback, this )
            );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ----------------------------------------------------------------------------
// CBackground::FishCallback
// ----------------------------------------------------------------------------
//
TInt CBackground::FishCallback( TAny* aPtr )
    {
    CBackground* self = static_cast<CBackground*> ( aPtr );
    self->MoveFish();
    return 0;
    }

// ----------------------------------------------------------------------------
// CBackground::ReefCallback
// ----------------------------------------------------------------------------
//
TInt CBackground::ReefCallback( TAny* aPtr )
    {
    CBackground* self = static_cast<CBackground*> ( aPtr );
    self->MoveReef();
    return 0;
    }

// ----------------------------------------------------------------------------
// CBackground::JellyfishCallback
// ----------------------------------------------------------------------------
//
TInt CBackground::JellyfishCallback( TAny* aPtr )
    {
    CBackground* self = static_cast<CBackground*> ( aPtr );
    self->MoveJellyfish();
    return 0;
    }

// ----------------------------------------------------------------------------
// CBackground::ShoalCallback
// ----------------------------------------------------------------------------
//
TInt CBackground::ShoalCallback( TAny* aPtr )
    {
    CBackground* self = static_cast<CBackground*> ( aPtr );
    self->MoveShoal();
    return 0;
    }

// ----------------------------------------------------------------------------
// CBackground::SetupWidget
// ----------------------------------------------------------------------------
//
void CBackground::SetupWidget()
    {
    TRect theRect( Rect() );
    
    // Red fish
    iRedFish.iActiveRect.iTl.iX = theRect.iTl.iX - KRedFishWidth;
    iRedFish.iActiveRect.iTl.iY = theRect.iTl.iY + theRect.Height() / KProportionNumerator;
    iRedFish.iActiveRect.iBr.iX = theRect.iBr.iX + KRedFishWidth;
    iRedFish.iActiveRect.iBr.iY = theRect.iBr.iY - theRect.Height() / KProportionNumerator;
    iRedFish.iSize.iWidth = KRedFishWidth;
    iRedFish.iSize.iHeight = KRedFishHeight;

    iRedFish.iPosition.iX = iRedFish.iActiveRect.iTl.iX + 
        Rand( iRedFish.iActiveRect.Width() - iRedFish.iSize.iWidth );
    iRedFish.iPosition.iY = iRedFish.iActiveRect.iTl.iY + 
        Rand( iRedFish.iActiveRect.Height() - iRedFish.iSize.iHeight );

    iRedFish.iMoveState = EMoveEast;
    iRedFish.iBitmap = iBmpUtils->Bitmap( EMbmBakRedfish );
    iRedFish.iMask = iBmpUtils->Bitmap( EMbmBakRedfish_mask );

    // Yellow fish
    iYellowFish.iActiveRect.iTl.iX = theRect.iTl.iX - KYellowFishWidth;
    iYellowFish.iActiveRect.iTl.iY = theRect.iTl.iY + theRect.Height() / KProportionNumerator;
    iYellowFish.iActiveRect.iBr.iX = theRect.iBr.iX + KYellowFishWidth;
    iYellowFish.iActiveRect.iBr.iY = theRect.iBr.iY - theRect.Height() / KProportionNumerator;
    iYellowFish.iSize.iWidth = KYellowFishWidth;
    iYellowFish.iSize.iHeight = KYellowFishHeight;

    iYellowFish.iPosition.iX = iYellowFish.iActiveRect.iBr.iX - KYellowFishWidth;
    iYellowFish.iPosition.iY = iYellowFish.iActiveRect.iTl.iY + 
        Rand( iYellowFish.iActiveRect.Height() - iYellowFish.iSize.iHeight );

    iYellowFish.iMoveState = EMoveWest;
    iYellowFish.iBitmap = iBmpUtils->Bitmap( EMbmBakYellowfish );
    iYellowFish.iMask = iBmpUtils->Bitmap( EMbmBakYellowfish_mask );

    // Reef
    iLeftReef.iActiveRect.iTl.iX = theRect.iTl.iX;
    iLeftReef.iActiveRect.iTl.iY = theRect.iBr.iY - KLeftReefHeight;
    iLeftReef.iActiveRect.iBr.iX = theRect.iTl.iX + KLeftReefWidth;
    iLeftReef.iActiveRect.iBr.iY = theRect.iBr.iY + KReefMoves;
    iLeftReef.iSize.iWidth = KLeftReefWidth;
    iLeftReef.iSize.iHeight = KLeftReefHeight;

    iLeftReef.iPosition.iX = iLeftReef.iActiveRect.iTl.iX;
    iLeftReef.iPosition.iY = iLeftReef.iActiveRect.iTl.iY;

    iLeftReef.iMoveState = EMoveSouth;
    iLeftReef.iBitmap = iBmpUtils->Bitmap( EMbmBakLeftreef );
    iLeftReef.iMask = iBmpUtils->Bitmap( EMbmBakLeftreef_mask );

    iRightReef.iActiveRect.iTl.iX = theRect.iBr.iX - KRightReefWidth;
    iRightReef.iActiveRect.iTl.iY = theRect.iBr.iY - KRightReefHeight;
    iRightReef.iActiveRect.iBr.iX = theRect.iBr.iX;
    iRightReef.iActiveRect.iBr.iY = theRect.iBr.iY + KReefMoves;
    iRightReef.iSize.iWidth = KRightReefWidth;
    iRightReef.iSize.iHeight = KRightReefHeight;

    iRightReef.iPosition.iX = iRightReef.iActiveRect.iTl.iX;
    iRightReef.iPosition.iY = iRightReef.iActiveRect.iTl.iY;

    iRightReef.iMoveState = EMoveSouth;
    iRightReef.iBitmap = iBmpUtils->Bitmap( EMbmBakRightreef );
    iRightReef.iMask = iBmpUtils->Bitmap( EMbmBakRightreef_mask );

    // Jellyfish
    iJellyfish.iActiveRect.iTl.iX = theRect.iTl.iX;
    iJellyfish.iActiveRect.iTl.iY = theRect.iTl.iY+ theRect.Height() / KProportionNumerator;
    iJellyfish.iActiveRect.iBr.iX = theRect.iBr.iX;
    iJellyfish.iActiveRect.iBr.iY = theRect.iBr.iY - theRect.Height() / KProportionNumerator;
    iJellyfish.iSize.iWidth = KJellyfishWidth;
    iJellyfish.iSize.iHeight = KJellyfishHeight;

    iJellyfish.iPosition.iX = iJellyfish.iActiveRect.iTl.iX + 
        Rand( iJellyfish.iActiveRect.Width() - KJellyfishWidth );
    iJellyfish.iPosition.iY = iJellyfish.iActiveRect.iTl.iY + 
        Rand( iJellyfish.iActiveRect.Height() - KJellyfishHeight );

    iJellyfish.iMoveState = ( TMoveState )Rand( EMoveStateLastElement );
    iJellyfish.iBitmap = iBmpUtils->Bitmap( EMbmBakJellyfish );
    iJellyfish.iMask = iBmpUtils->Bitmap( EMbmBakJellyfish_mask );
    
    iJellyfishMoves = KMaxJellyfishMoves;
    }

// ----------------------------------------------------------------------------
// CBackground::Rand
// ----------------------------------------------------------------------------
//
TInt CBackground::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// ----------------------------------------------------------------------------
// CBackground::TWidget::Next
// ----------------------------------------------------------------------------
//
void CBackground::TWidget::Next()
    {
    DoNext( iPosition );
    }

// ----------------------------------------------------------------------------
// CBackground::TWidget::HitTest
// ----------------------------------------------------------------------------
//
TBool CBackground::TWidget::HitTest() const
    {
    TPoint thePosition( iPosition );
    DoNext( thePosition );
    TRect widgt( thePosition, iSize );
    if ( iActiveRect.Contains( widgt.iTl )
        && iActiveRect.Contains( TPoint( widgt.iBr.iX - 1, widgt.iBr.iY ) ) )
        {
        return ETrue;
        }
    else
        {
        return EFalse;
        }
    }

// ----------------------------------------------------------------------------
// CBackground::TWidget::DoNext
// ----------------------------------------------------------------------------
//
void CBackground::TWidget::DoNext( TPoint& aPosition ) const
    {
    switch( iMoveState )
        {
        case EMoveEast:
            aPosition.iX++;
            break;
        case EMoveNorth:
            aPosition.iY--;
            break;
        case EMoveSouth:
            aPosition.iY++;
            break;
        case EMoveWest:
            aPosition.iX--;
            break;
        case EMoveNorthwest:
            aPosition.iX--;
            aPosition.iY--;
            break;
        case EMoveNortheast:
            aPosition.iX++;
            aPosition.iY--;
            break;
        case EMoveSouthwest:
            aPosition.iX--;
            aPosition.iY++;
            break;
        case EMoveSoutheast:
            aPosition.iX++;
            aPosition.iY++;
            break;
        case EMoveCentral:
            break;
        default:
            break;
        }
    }

// End of File
