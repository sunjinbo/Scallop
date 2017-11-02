/* ====================================================================
 * File: ScaLayoutManager.h
 * Created: 11/03/09
 * Modified: 11/03/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCALAYOUTMANAGER_H
#define C_SCALAYOUTMANAGER_H

// INCLUDE FILES
#include <e32base.h>
#include "ScaLayoutValues.h"

// FORWARD DECLARATIONS
class TAknLayoutRect;

// CLASS DECLARATION
/**
* CScaLayoutManager class
*
* @since S60 5.0
*/
class CScaLayoutManager : public CBase
    {
public: // Constructor and Destructor
    static CScaLayoutManager* NewL();
    virtual ~CScaLayoutManager();    

public: // New functions
    void ResolutionChanged( TOrientation aOrientation = EAutomatic );
    void LayoutRect( TComponent aComponent, TRect& rect ) const;

protected: // Constructor
    CScaLayoutManager();
    void ConstructL();

private: // Data members
    TResolution iResolution;

    };

#endif // C_SCALAYOUTMANAGER_H

// End of File
