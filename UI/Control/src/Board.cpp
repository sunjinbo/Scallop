/* ====================================================================
 * File: Board.cpp
 * Created: 12/05/09
 * Modified: 12/05/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsread.h>
#include <BmpUtils.h>
#include <Board.mbg>
#include "Board.h"
#include "GraphicsManager.h"
#include "GraphicsLayer.h"

// CONSTANTS
#if defined( __WINS__ )
_LIT( KMbmBoardFileName, "Z:\\resource\\apps\\board.mbm" );
#else
_LIT( KMbmBoardFileName, "\\resource\\apps\\board.mbm" );
#endif // __WINS__

const TInt KInvalidBitmapIx = 0;

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CBoard::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CBoard* CBoard::NewL( CGraphicsManager& aGraphicsManager, const TRect& aRect )
    {
    CBoard* self = new (ELeave) CBoard( aGraphicsManager );
    CleanupStack::PushL (self );
    self->ConstructL ( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CBoard::~CBoard
// ----------------------------------------------------------------------------
//
EXPORT_C CBoard::~CBoard()
    {
    delete iBoardLayer;
    }

// ----------------------------------------------------------------------------
// CBoard::SetBitmap
// ----------------------------------------------------------------------------
//
EXPORT_C void CBoard::SetBitmap( CFbsBitmap* aBitmap )
    {
    iBoardLayer->DrawBitmap( Rect(), aBitmap );
    }

// ----------------------------------------------------------------------------
// CBoard::SetBitmapL
// ----------------------------------------------------------------------------
//
EXPORT_C void CBoard::SetBitmapL( TInt aBitmapIx )
    {
    
    CBmpUtils* utils = CBmpUtils::NewL( 
            KMbmBoardFileName, 
            EMbmBoardBar,
            EMbmBoardLastElement 
            );
    CleanupStack::PushL( utils );
    
    CFbsBitmap* bitmap = utils->Bitmap( aBitmapIx );
    iBoardLayer->DrawBitmap( Rect(), bitmap );
    
    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;
    }

// ----------------------------------------------------------------------------
// CBoard::SetMask
// ----------------------------------------------------------------------------
//
EXPORT_C void CBoard::SetMask( CFbsBitmap* aMask )
    {
    iBoardLayer->DrawMask( Rect(), aMask );
    }

// ----------------------------------------------------------------------------
// CBoard::SetMaskL
// ----------------------------------------------------------------------------
//
EXPORT_C void CBoard::SetMaskL( TInt aMaskIx )
    {
    CBmpUtils* utils = CBmpUtils::NewL( 
            KMbmBoardFileName, 
            EMbmBoardBar,
            EMbmBoardLastElement 
            );
    CleanupStack::PushL( utils );
    
    CFbsBitmap* mask = utils->Bitmap( aMaskIx );
    iBoardLayer->DrawMask( Rect(), mask );

    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;
    }

// ----------------------------------------------------------------------------
// CBoard::Clear
// ----------------------------------------------------------------------------
//
EXPORT_C void CBoard::Clear()
    {
    iBoardLayer->Clear( Rect() );
    }

// ----------------------------------------------------------------------------
// CBoard::SetVisible
// ----------------------------------------------------------------------------
//
EXPORT_C void CBoard::SetVisible( TBool aVisible )
    {
    iBoardLayer->SetVisible( aVisible );
    }

// ----------------------------------------------------------------------------
// CBoard::ResizeL
// ----------------------------------------------------------------------------
//
EXPORT_C void CBoard::ResizeL( const TRect& aRect )
    {
    if ( iBoardLayer )
        {
        iGraphicsManager.UnregisterLayer( iBoardLayer );
        delete iBoardLayer;
        iBoardLayer = NULL;
        }
    SetRect( aRect );
    iBoardLayer = CGraphicsLayer::NewL( aRect, ECtrlBackground );
    iGraphicsManager.RegisterLayer( iBoardLayer );
    }

// ----------------------------------------------------------------------------
// CBoard::ConstructFromResourceL
// ----------------------------------------------------------------------------
//
EXPORT_C void CBoard::ConstructFromResourceL( TResourceReader& aReader )
    {
    TInt w = aReader.ReadInt32 ();
    TInt h = aReader.ReadInt32 ();

    CBmpUtils* utils = CBmpUtils::NewL( 
            KMbmBoardFileName, 
            EMbmBoardBar,
            EMbmBoardLastElement 
            );
    CleanupStack::PushL( utils );

    TInt bitmapIx = aReader.ReadInt32 ();
    TInt maskIx = aReader.ReadInt32 ();
    
    if ( bitmapIx != KInvalidBitmapIx && maskIx != KInvalidBitmapIx )
        {
        utils->SetSize( bitmapIx, TSize( w, h ) );
        CFbsBitmap* bitmap = utils->Bitmap( bitmapIx );
        iBoardLayer->DrawBitmap( TRect( Rect().iTl, TSize( w, h ) ), bitmap );
        utils->SetSize( maskIx, TSize( w, h ) );
        CFbsBitmap* mask = utils->Bitmap( maskIx );
        iBoardLayer->DrawMask( TRect( Rect().iTl, TSize( w, h ) ), mask );
        }

    CleanupStack::Pop( utils );
    delete utils;
    utils = NULL;
    }

// ----------------------------------------------------------------------------
// CBoard::CBoard
// ----------------------------------------------------------------------------
//
CBoard::CBoard( CGraphicsManager& aGraphicsManager )
    : iGraphicsManager( aGraphicsManager )
    { // No implementation required.
    }

// ----------------------------------------------------------------------------
// CBoard::ConstructL
// ----------------------------------------------------------------------------
//
void CBoard::ConstructL( const TRect& aRect )
    {
    // Create a window for this application view
    CreateWindowL();

    // Set the windows size
    SetRect( aRect );

    iBoardLayer = CGraphicsLayer::NewL( aRect, ECtrlBackground );
    iGraphicsManager.RegisterLayer( iBoardLayer );

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// End of File
