/* ====================================================================
 * File: ResReader.cpp
 * Created: 10/28/09
 * Modified: 10/28/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <barsc.h>
#include "ResReader.h"

// CONSTANTS

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CResReader::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CResReader* CResReader::NewL( RFs& aFs, TFileName aFileName )
    {
    CResReader* self = new (ELeave) CResReader( aFs, aFileName );
    CleanupStack::PushL (self );
    self->ConstructL ();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CResReader::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CResReader::~CResReader()
    {
    delete iResData;
    }

// ----------------------------------------------------------------------------
// CResReader::ResourceData
// ----------------------------------------------------------------------------
//
EXPORT_C HBufC8* CResReader::ResourceData( TInt aResId )
    {
    RResourceFile resourceFile;
    resourceFile.OpenL ( iFs, iFileName );
    resourceFile.ConfirmSignatureL ();
    CleanupClosePushL( resourceFile );

    HBufC8* resourceData( NULL );

    resourceData = resourceFile.AllocReadLC ( aResId );
    
    if ( iResData )
        {
        delete iResData;
        iResData = NULL;
        }

    iResData =  HBufC8::NewL( resourceData->Length() );
    TPtr8 resData( iResData->Des() );
    resData.Copy( *resourceData );

    CleanupStack::PopAndDestroy( 2 ); // resourceData, resourceFile
    
    return iResData;
    }

// ----------------------------------------------------------------------------
// CResReader::CResReader
// ----------------------------------------------------------------------------
//
CResReader::CResReader( RFs& aFs, TFileName aFileName )
    : iFs( aFs ), iFileName( aFileName )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// CResReader::ConstructL
// ----------------------------------------------------------------------------
//
void CResReader::ConstructL()
    { // no implementation required
    }
    
// End of File
