/* ====================================================================
 * File: AudioUtils.cpp
 * Created: 05/22/09
 * Modified: 05/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <MdaAudioTonePlayer.h>
#include <eikmenup.h>
#include "AudioUtils.h"

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CAudioUtils::NewL
// ----------------------------------------------------------------------------
//
EXPORT_C CAudioUtils* CAudioUtils::NewL( const TDesC& aFileName )
    {
    CAudioUtils* self = new (ELeave) CAudioUtils;
    CleanupStack::PushL( self );
    self->ConstructL( aFileName );
    CleanupStack::Pop( self );  
    return self;
    }

// ----------------------------------------------------------------------------
// CAudioUtils::~CAudioUtils
// ----------------------------------------------------------------------------
//
EXPORT_C CAudioUtils::~CAudioUtils()
    {
    if( iPlayUtility )
        {
        iPlayUtility->Stop();
        iPlayUtility->Close();
        }
    delete iPlayUtility;
    }
    
// ----------------------------------------------------------------------------
// CAudioUtils::Play
// ----------------------------------------------------------------------------
//
EXPORT_C void CAudioUtils::Play()
    {
    if ( iPrepared )
        {
        iPlayUtility->Play();
        iPlaying = ETrue;
        }
    }

// ----------------------------------------------------------------------------
// CAudioUtils::Stop
// ----------------------------------------------------------------------------
//
EXPORT_C void CAudioUtils::Stop()
    {
    iPlayUtility->Stop();
    iPlaying = EFalse;
    }

// ----------------------------------------------------------------------------
// CAudioUtils::SetRepeat
// ----------------------------------------------------------------------------
//
EXPORT_C void CAudioUtils::SetRepeat( TBool aRepeat )
    {
    iRepeat = aRepeat;
    }

// ----------------------------------------------------------------------------
// CAudioUtils::MapcPlayComplete
// ----------------------------------------------------------------------------
//
void CAudioUtils::MapcPlayComplete(TInt /*aError*/)
    {
    iPlaying = EFalse;
    if ( iRepeat )
        {
        Play();
        }
    }

// ----------------------------------------------------------------------------
// CAudioUtils::MapcInitComplete
// ----------------------------------------------------------------------------
//
void CAudioUtils::MapcInitComplete( TInt aError, const TTimeIntervalMicroSeconds& /*aDuration*/ )	
    {
    if( aError == KErrNone )
        {
        iPrepared = ETrue;
        iPlayUtility->SetVolume( iPlayUtility->MaxVolume() );
        }
    }

// ----------------------------------------------------------------------------
// CAudioUtils::CAudioUtils
// ----------------------------------------------------------------------------
//
CAudioUtils::CAudioUtils()
    : iPlaying( EFalse ), iPrepared( EFalse )
    {  // No implementation required.
    }

// ----------------------------------------------------------------------------
// CAudioUtils::ConstructL
// ----------------------------------------------------------------------------
//
void CAudioUtils::ConstructL(const TDesC& aFileName)
    {
    iPlayUtility = CMdaAudioPlayerUtility::NewFilePlayerL( aFileName, *this );
    }

// End of File
