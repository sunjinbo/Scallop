/* ====================================================================
 * File: StarFish.h
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef STARFISH_H
#define STARFISH_H

// INCLUDE FILES
#include "Scallop.h"

// CLASS DECLARATION
/**
* CStarFish class
*
* @since S60 5.0
*/
class CStarFish : public CScallop
    {
public: // Constructor and Destructor
    static CStarFish* NewL( MAquaticObserver& aObserver, MAquaticHandler& aHandler );
    virtual ~CStarFish();
    virtual TBool operator ==( const CAquatic& anAquatic ) const;

protected: // Constructor
    CStarFish( MAquaticObserver& aObserver, MAquaticHandler& aHandler );
    void ConstructL();

private: // Member Data
    };

#endif // STARFISH_H


// End of file
