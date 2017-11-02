/* ====================================================================
 * File: ScaDocument.h
 * Created: 10/23/09
 * Modified:
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_SCADOCUMENT_H
#define C_SCADOCUMENT_H

// INCLUDE FILES
#include <akndoc.h>

// FORWARD REFERENCES
class CScaAppUi;
class CAknApplication;


// CLASS DECLARATION
/**
* CScaDocument class
*
* Discussion An instance of class CScaDocument is the Document part of
* the AVKON application framework for the Tetris example application.
*
* @since S60 5.0
*/
class CScaDocument : public CAknDocument
    {
public: // Constructor and destructor

    static CScaDocument* NewL( CEikApplication& aApp );
    static CScaDocument* NewLC( CEikApplication& aApp );
    ~CScaDocument();

public: // from base class CAknDocument
    CEikAppUi* CreateAppUiL();

private: // Constructor
    void ConstructL();
    CScaDocument( CEikApplication& aApp );
    };


#endif // C_SCADOCUMENT_H

// End of File
