/* ====================================================================
 * File: Node.h
 * Created: 09/09/09
 * Modified: 09/09/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef T_NODE_H
#define T_NODE_H

// INCLUDE FILES
#include <e32std.h>

// CLASS DECLARATION
/**
* TNode class
*
* @since S60 5.0
*/
class TNode
    {
public:
    enum TUninitialized { EUninitialized = -1 };
    inline TNode();
    inline TNode( const TPoint& aPos );
    inline TNode( TInt aX, TInt aY );
    inline TBool operator == ( const TNode& aNode ) const;
    inline TBool operator != ( const TNode& aNode ) const;
    inline TPoint Position() const;
    inline TPoint Parent() const;
    inline void SetParent( const TPoint& aParent );
    inline TInt G() const;
    inline void SetG( TInt aG );
    inline TInt H() const;
    inline void SetH( TInt aH );
    inline TInt F() const;
    static TBool Match( const TNode& aFirst, const TNode& aSecond );

private: // Member data
    TInt iG; // G cost
    TInt iH; // H cost
    TPoint iPos; // postion
    TPoint iParent; // parent node
    };

#include "Node.inl"

#endif // T_NODE_H

// End of file
