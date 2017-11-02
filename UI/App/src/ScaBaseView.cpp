/* ====================================================================
 * File: ScaMenuView.cpp
 * Created: 10/23/09
 * Modified: 03/27/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <aknviewappui.h>
#include <aknconsts.h>
#include <akndef.h>
#include <aknutils.h>
#include <akntitle.h>
#include <barsread.h>

#include <Scallop.rsg>
#include "ScaBaseView.h"
#include "ScaAppUi.h"
#include "Scallop.hrh"
#include "ScaViewIds.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ---------------------------------------------------------------------------
// CScaBaseView::~CScaBaseView
// ---------------------------------------------------------------------------
// 
CScaBaseView::~CScaBaseView()
    { // No implementation required
    }

// ---------------------------------------------------------------------------
// CScaBaseView::HandleClientRectChange
//
// ---------------------------------------------------------------------------
//
void CScaBaseView::HandleClientRectChange()
    { // No implementation required
    }

// ---------------------------------------------------------------------------
// CScaBaseView::CScaBaseView
//
// ---------------------------------------------------------------------------
//
CScaBaseView::CScaBaseView( CScaAppUi& aAppUi )
    : iAppUi( aAppUi )
    { // No implementation required
    }

// End of File
