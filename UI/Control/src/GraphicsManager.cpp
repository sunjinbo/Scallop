/* ====================================================================
 * File: GraphicsManager.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "GraphicsManager.h"
#include "GraphicsLayer.h"
#include "GraphicsLayer.hrh"

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CGraphicsManager::NewL
// ----------------------------------------------------------------------------
//
CGraphicsManager* CGraphicsManager::NewL( const TRect& aRect )
    {
    CGraphicsManager* self = new (ELeave) CGraphicsManager;
    CleanupStack::PushL (self );
    self->ConstructL( aRect );
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::~CGraphicsManager
// ----------------------------------------------------------------------------
//
CGraphicsManager::~CGraphicsManager()
    {
    iGraphicsLayers.Close();
    delete iFoundationLayer;
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::Merge
// ----------------------------------------------------------------------------
//
void CGraphicsManager::Merge()
    {
    iFoundationLayer->Clear();
    for ( TInt i = 0; i < iGraphicsLayers.Count(); ++i )
        {

        if ( EFoundation != iGraphicsLayers[i]->LayerId()
            && iGraphicsLayers[i]->Visible() )
            {
            TRect rect( iGraphicsLayers[i]->Rect() );
            TPoint tl( rect.iTl );
            TSize size( rect.Size() );
            rect.SetRect( TPoint( 0, 0 ), size );

            iFoundationLayer->BitBltMasked( tl,
                                        iGraphicsLayers[ i ]->Bitmap(),
                                        rect,
                                        iGraphicsLayers[ i ]->Mask(),
                                        ETrue 
                                        );

            }
        }
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::Bitmap
// ----------------------------------------------------------------------------
//
CFbsBitmap* CGraphicsManager::Bitmap()
    {
    return iFoundationLayer->Bitmap();
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::Mask
// ----------------------------------------------------------------------------
//
CFbsBitmap* CGraphicsManager::Mask()
    {
    return iFoundationLayer->Mask();
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::SetRect
// ----------------------------------------------------------------------------
//
void CGraphicsManager::SetRect( const TRect& aRect )
    {
    TRAP_IGNORE ( CreateFoundationLayerL( aRect ) );
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::RegisterLayer
// ----------------------------------------------------------------------------
//
void CGraphicsManager::RegisterLayer( CGraphicsLayer* aLayer )
    {
    iGraphicsLayers.Append( aLayer );
    Sort();
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::UnregisterLayer
// ----------------------------------------------------------------------------
//
void CGraphicsManager::UnregisterLayer( CGraphicsLayer* aLayer )
    {
    TInt index;
    TRAPD( err, Find( aLayer, index ) );
    if ( err == KErrNone )
        {
        iGraphicsLayers.Remove( index );
        }
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::CGraphicsManager
// ----------------------------------------------------------------------------
//
CGraphicsManager::CGraphicsManager()
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::ConstructL
// ----------------------------------------------------------------------------
//
void CGraphicsManager::ConstructL( const TRect& aRect )
    {
    CreateFoundationLayerL( aRect );
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::Find
// ----------------------------------------------------------------------------
//
TInt CGraphicsManager::Find( CGraphicsLayer* aLayer, TInt& aIndex ) const
    {
    TInt retVal( KErrNotFound );
    for ( TInt i = 0; i < iGraphicsLayers.Count(); ++i )
        {
        if ( iGraphicsLayers[i] == aLayer )
            {
            aIndex = i;
            retVal = KErrNone;
            break;
            }
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// CGraphicsManager::CreateFoundationLayerL
// ----------------------------------------------------------------------------
//
void CGraphicsManager::CreateFoundationLayerL( const TRect& aRect )
    {
    if (  iFoundationLayer )
        {
        UnregisterLayer( iFoundationLayer );
        delete iFoundationLayer;
        iFoundationLayer = NULL;
        }
    iFoundationLayer = CGraphicsLayer::NewL( aRect, EFoundation );
    RegisterLayer( iFoundationLayer );

    }

// ----------------------------------------------------------------------------
// CGraphicsManager::Sort
// ----------------------------------------------------------------------------
//
void CGraphicsManager::Sort()
    {
    TLinearOrder<CGraphicsLayer> order( CGraphicsLayer::Compare );
    iGraphicsLayers.Sort( order );
    }

// End of File
