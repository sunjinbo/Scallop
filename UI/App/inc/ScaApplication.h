/* ====================================================================
 * File: ScaApplication.h
 * Created: 10/23/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCAAPPLICATION_H
#define C_SCAAPPLICATION_H

// INCLUDE FILES
#include <aknapp.h>

// CLASS DECLARATION
/**
* CScaApplication class
*
* Discussion An instance of CTetrisApplication is the application part of
* the AVKON application framework for the Tetris example application.
*
* @since S60 5.0
*/
class CScaApplication : public CAknApplication
    {
public: // from base class CAknApplication
    TUid AppDllUid() const;

protected: // from base class CAknApplication
    CApaDocument* CreateDocumentL();
    };

#endif // C_SCAAPPLICATION_H

// End of File
