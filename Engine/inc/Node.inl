/* ====================================================================
 * File: Node.inl
 * Created: 09/09/09
 * Modified: 09/09/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// TNode::TNode
// ----------------------------------------------------------------------------
//
TNode::TNode()  : iG( EUninitialized ), iH( EUninitialized ),
    iPos( EUninitialized, EUninitialized ), 
    iParent( EUninitialized, EUninitialized )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// TNode::TNode
// ----------------------------------------------------------------------------
//
inline TNode::TNode( const TPoint& aPos )
    : iG( EUninitialized ), iH( EUninitialized ),
    iPos( aPos ),
    iParent( EUninitialized, EUninitialized )
    { // no implementation required 
    }

// ----------------------------------------------------------------------------
// TNode::TNode
// ----------------------------------------------------------------------------
//
inline TNode::TNode( TInt aX, TInt aY )
    : iG( EUninitialized ), iH( EUninitialized ),
    iPos( aX, aY ),
    iParent( EUninitialized, EUninitialized )
    {  // no implementation required 
    }

// ----------------------------------------------------------------------------
// TNode::operator==
// ----------------------------------------------------------------------------
//
inline TBool TNode::operator==( const TNode& aNode ) const
    {
    TBool retVal( EFalse );
    if ( aNode.Position() == iPos )
        {
        retVal = ETrue;
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// TNode::operator!=
// ----------------------------------------------------------------------------
//
inline TBool TNode::operator!=( const TNode& aNode ) const
    {
    return ( *this == aNode ) ? ETrue : EFalse ;
    }

// ----------------------------------------------------------------------------
// TNode::Position
// ----------------------------------------------------------------------------
//
inline TPoint TNode::Position() const
    {
    return iPos;
    }

// ----------------------------------------------------------------------------
// TNode::Parent
// ----------------------------------------------------------------------------
//
inline TPoint TNode::Parent() const
    {
    return iParent;
    }

// ----------------------------------------------------------------------------
// TNode::SetParent
// ----------------------------------------------------------------------------
//
inline void TNode::SetParent( const TPoint& aParent )
    {
    iParent = aParent;
    }

// ----------------------------------------------------------------------------
// TNode::G
// ----------------------------------------------------------------------------
//
inline TInt TNode::G() const
    {
    return iG;
    }

// ----------------------------------------------------------------------------
// TNode::SetG
// ----------------------------------------------------------------------------
//
void TNode::SetG( TInt aG )
    {
    iG = aG;
    }

// ----------------------------------------------------------------------------
// TNode::H
// ----------------------------------------------------------------------------
//
inline TInt TNode::H() const
    {
    return iH;
    }

// ----------------------------------------------------------------------------
// TNode::SetH
// ----------------------------------------------------------------------------
//
void TNode::SetH( TInt aH )
    {
    iH = aH;
    }

// ----------------------------------------------------------------------------
// TNode::F
// ----------------------------------------------------------------------------
//
inline TInt TNode::F() const
    {
    return iG + iH;
    }

// ----------------------------------------------------------------------------
// TNode::Match
// ----------------------------------------------------------------------------
//
TBool TNode::Match( const TNode& aFirst, const TNode& aSecond )
    {
    if ( aFirst == aSecond )
        return ETrue;
    else
        return EFalse;
    }

// End of file
