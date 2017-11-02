/* ====================================================================
 * File: Icon.cpp
 * Created: 12/05/09
 * Modified: 12/05/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <BmpUtils.h>
#include <Icon.mbg>
#include "Icon.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KMbmIconFileName, "Z:\\resource\\apps\\icon.mbm" );
#else
_LIT( KMbmIconFileName, "\\resource\\apps\\icon.mbm" );
#endif // __WINS__

const TInt KInvalidBitmapIx = 0;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CIcon::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CIcon* CIcon::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CIcon* self = new (ELeave) CIcon( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CIcon::~CIcon
// ----------------------------------------------------------------------------
//
EXPORT_C CIcon::~CIcon()
    {
    delete iIconLayer;
    }

// ----------------------------------------------------------------------------
// CIcon::SetBitmap
// ----------------------------------------------------------------------------
//
EXPORT_C void CIcon::SetBitmap( CFbsBitmap* aBitmap )
    {
    iIconLayer->DrawBitmap( Rect(), aBitmap );
    }

// ----------------------------------------------------------------------------
// CIcon::SetBitmapL
// ----------------------------------------------------------------------------
//
EXPORT_C void CIcon::SetBitmapL( TInt aBitmapIx )
    {
    
    CBmpUtils* utils = CBmpUtils::NewL( 
            KMbmIconFileName, 
            EMbmIconClassic,
            EMbmIconLastElement 
            );
    CleanupStack::PushL( utils );
    
    CFbsBitmap* bitmap = utils->Bitmap( aBitmapIx );
    iIconLayer->DrawBitmap( Rect(), bitmap );
    
    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;
    }

// ----------------------------------------------------------------------------
// CIcon::SetMask
// ----------------------------------------------------------------------------
//
EXPORT_C void CIcon::SetMask( CFbsBitmap* aMask )
    {
    iIconLayer->DrawMask( Rect(), aMask );
    }

// ----------------------------------------------------------------------------
// CIcon::SetMaskL
// ----------------------------------------------------------------------------
//
EXPORT_C void CIcon::SetMaskL( TInt aMaskIx )
    {
    CBmpUtils* utils = CBmpUtils::NewL( 
            KMbmIconFileName, 
            EMbmIconClassic,
            EMbmIconLastElement 
            );
    CleanupStack::PushL( utils );
    
    CFbsBitmap* mask = utils->Bitmap( aMaskIx );
    iIconLayer->DrawMask( Rect(), mask );

    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;
    }

// ----------------------------------------------------------------------------
// CIcon::Clear
// ----------------------------------------------------------------------------
//
EXPORT_C void CIcon::Clear()
    {
    iIconLayer->Clear( Rect() );
    }

// ----------------------------------------------------------------------------
// CIcon::SetVisible
// ----------------------------------------------------------------------------
//
EXPORT_C void CIcon::SetVisible( TBool aVisible )
    {
    iIconLayer->SetVisible( aVisible );
    }

// ----------------------------------------------------------------------------
// CIcon::ResizeL
// ----------------------------------------------------------------------------
//
EXPORT_C void CIcon::ResizeL( const TRect& aRect )
    {
    if ( iIconLayer )
        {
        iGraphicsManager.UnregisterLayer( iIconLayer );
        delete iIconLayer;
        iIconLayer = NULL;
        }
    SetRect( aRect );
    iIconLayer = CGraphicsLayer::NewL( aRect, ECtrlBackground );
    iGraphicsManager.RegisterLayer( iIconLayer );
    }

// ----------------------------------------------------------------------------
// CIcon::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
EXPORT_C void CIcon::ConstructFromResourceL( TResourceReader& aReader )
    {
    TInt w = aReader.ReadInt32 ();
    TInt h = aReader.ReadInt32 ();

    CBmpUtils* utils = CBmpUtils::NewL( 
            KMbmIconFileName, 
            EMbmIconClassic,
            EMbmIconLastElement 
            );
    CleanupStack::PushL( utils );

    TInt bitmapIx = aReader.ReadInt32 ();
    TInt maskIx = aReader.ReadInt32 ();
    
    if ( bitmapIx != KInvalidBitmapIx && maskIx != KInvalidBitmapIx )
        {
        utils->SetSize( bitmapIx, TSize( w, h ) );
        CFbsBitmap* bitmap = utils->Bitmap( bitmapIx );
        iIconLayer->DrawBitmap( TRect( Rect().iTl, TSize( w, h ) ), bitmap );
        utils->SetSize( maskIx, TSize( w, h ) );
        CFbsBitmap* mask = utils->Bitmap( maskIx );
        iIconLayer->DrawMask( TRect( Rect().iTl, TSize( w, h ) ), mask );
        }

    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;
    }

// ----------------------------------------------------------------------------
// CIcon::CIcon
// ----------------------------------------------------------------------------
//
CIcon::CIcon( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CIcon::ConstructL
// ----------------------------------------------------------------------------
//
void CIcon::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    iIconLayer = CGraphicsLayer::NewL( aRect, ECtrlForeground );
    iGraphicsManager.RegisterLayer( iIconLayer );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// End of File
