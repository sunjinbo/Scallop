/* ====================================================================
 * File: ScaTest.pan
 * Created: 08/17/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __SCATEST_PAN__
#define __SCATEST_PAN__

/** ScaTest application panic codes */
enum TScaTestPanics 
    {
    EScaTestBasicUi = 1
    // add further panics here
    };

inline void Panic(TScaTestPanics aReason)
    {
	_LIT(applicationName,"ScaTest");
    User::Panic(applicationName, aReason);
    }

#endif // __SCATEST_PAN__
