/* ====================================================================
 * File: AudioUtils.h
 * Created: 05/22/09
 * Modified: 05/22/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_AUTILSUTILS_H
#define C_AUTILSUTILS_H

// INCLUDE FILES
#include <e32std.h>
#include <MdaAudioSamplePlayer.h>

// FORWARD DECLARATIONS

// CLASS DECLARATION
/**
* CAudioUtils class
*
* For handles creation and drawing of .bmp file.
*
* @since S60 3.1
*/
class CAudioUtils : public CBase, MMdaAudioPlayerCallback
    {
public: // Constructor and destructor
    IMPORT_C static CAudioUtils* NewL(const TDesC& aFileName);
    IMPORT_C virtual ~CAudioUtils();

public: // New functions
    IMPORT_C void Play();
    IMPORT_C void Stop();
    IMPORT_C void SetRepeat( TBool aRepeat );

private: // From base class MMdaAudioToneObserver
    void MapcInitComplete( TInt aError, const TTimeIntervalMicroSeconds& aDuration );
    void MapcPlayComplete( TInt aError );

private: // Constructor
    CAudioUtils();
    void ConstructL(const TDesC& aFileName);

private: // Data member
    CMdaAudioPlayerUtility* iPlayUtility;
    TBool iPlaying;
    TBool iPrepared;
    TBool iRepeat;
    };

#endif // C_AUTILSUTILS_H

// End of File
