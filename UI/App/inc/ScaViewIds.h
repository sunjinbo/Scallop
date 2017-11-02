/* ====================================================================
 * File: ScaViewIds.h
 * Created: 03/30/09
 * Modified: 03/30/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef SCAVIEWIDS_H
#define SCAVIEWIDS_H

//
// UID for the application, this should correspond to 
// the uid defined in the mmp file.
//
const TUid KUidScallopApp = { 0xe01ff1d2 };


///////////////////////////////////////////////////////////
// View IDs
///////////////////////////////////////////////////////////

// Welcome view
const TInt KScaWelcomeViewIdValue = 1;
const TUid KScaWelcomeViewId = { KScaWelcomeViewIdValue };

// Main view
const TInt KScaMenuViewIdValue = 2;
const TUid KScaMenuViewId = { KScaMenuViewIdValue };

// Game view
const TInt KScaGameViewIdValue = 3;
const TUid KScaGameViewId = { KScaGameViewIdValue };

// Help view
const TInt KScaHelpViewIdValue = 4;
const TUid KScaHelpViewId = { KScaHelpViewIdValue };

// About view
const TInt KScaAboutViewIdValue = 5;
const TUid KScaAboutViewId = { KScaAboutViewIdValue };

// Option view
const TInt KScaOptionViewIdValue = 6;
const TUid KScaOptionViewId = { KScaOptionViewIdValue };

// Record view
const TInt KScaRecordViewIdValue = 7;
const TUid KScaRecordViewId = { KScaRecordViewIdValue };

#endif // SCAVIEWIDS_H

// End of File
