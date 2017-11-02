/* ====================================================================
 * File: ScaEngine.pan
 * Created: 08/16/09
 * Modified: 08/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef SCAENGINE_PAN
#define SCAENGINE_PAN

#include <e32std.h>

/* ScaEngine dll panic codes */
enum TEnginePanics 
    {
    EEngineNullPointer = 0xFF, // 255
    EEngineInvalidCommand, // 256
    EEngineInvalidParam, //257
    EEngineInvalidIndex, //258
    EEngineInvalidCount
    };

inline void Panic( TEnginePanics aReason )
    {
    _LIT( KScaEngineName, "ScaEngine" );
    User::Panic( KScaEngineName, aReason );
    }

#endif // SCAENGINE_PAN

// End of file
