/* ====================================================================
 * File: AquaticData.inl
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// TAquaticData::TAquaticData
// ----------------------------------------------------------------------------
//
TAquaticData::TAquaticData()  : iType( EAquaticNull ),
    iPos( EUninitialized, EUninitialized ), iMature( EFalse )
    { // no implementation required
    }

// ----------------------------------------------------------------------------
// TAquaticData::TAquaticData
// ----------------------------------------------------------------------------
//
inline TAquaticData::TAquaticData( TAquaticType aType )
    : iType( aType ),
    iPos( EUninitialized, EUninitialized ),
    iMature( EFalse )
    { // no implementation required 
    }

// ----------------------------------------------------------------------------
// TAquaticData::TAquaticData
// ----------------------------------------------------------------------------
//
inline TAquaticData::TAquaticData( TAquaticType aType, TInt aX, TInt aY )
    : iType( aType ), iPos( aX, aY ), iMature( EFalse )
    {  // no implementation required 
    }

// ----------------------------------------------------------------------------
// TAquaticData::TAquaticData
// ----------------------------------------------------------------------------
//
inline TAquaticData::TAquaticData( TAquaticType aType, const TPoint& aPos )
    : iType( aType ), iPos( aPos ), iMature( EFalse )
    {  // no implementation required 
    }

// ----------------------------------------------------------------------------
// TAquaticData::TAquaticData
// ----------------------------------------------------------------------------
//
inline TAquaticData::TAquaticData( const TAquaticData& aAquaticData )
    : iType( aAquaticData.Type() ),
    iPos( aAquaticData.Position() ),
    iMature( aAquaticData.IsMature() )
    {  // no implementation required 
    }

// ----------------------------------------------------------------------------
// TAquaticData::operator==
// ----------------------------------------------------------------------------
//
inline TBool TAquaticData::operator==( const TAquaticData& aAquaticData ) const
    {
    TBool retVal( EFalse );
    if ( ( aAquaticData.Type() == iType )
        && ( aAquaticData.Position() == iPos )
        && ( aAquaticData.IsMature() == iMature ) )
        {
        retVal = ETrue;
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// TAquaticData::operator!=
// ----------------------------------------------------------------------------
//
inline TBool TAquaticData::operator!=( const TAquaticData& aAquaticData ) const
    {
    return ( *this == aAquaticData ) ? ETrue : EFalse ;
    }

// ----------------------------------------------------------------------------
// TAquaticData::SetXY
// ----------------------------------------------------------------------------
//
inline void TAquaticData::SetXY( TInt aX, TInt aY )
    {
    iPos.SetXY( aX, aY );
    }

// ----------------------------------------------------------------------------
// TAquaticData::SetXY
// ----------------------------------------------------------------------------
//
inline void TAquaticData::SetXY( const TPoint& aPos )
    {
    iPos = aPos;
    }

// ----------------------------------------------------------------------------
// TAquaticData::SetType
// ----------------------------------------------------------------------------
//
inline void TAquaticData::SetType( TAquaticType aType )
    {
    iType = aType;
    }

// ----------------------------------------------------------------------------
// TAquaticData::SetType
// ----------------------------------------------------------------------------
//
void TAquaticData::SetMature()
    {
    iMature = ETrue;
    }

// ----------------------------------------------------------------------------
// TAquaticData::Type
// ----------------------------------------------------------------------------
//
inline TAquaticType TAquaticData::Type() const
    {
    return iType;
    }

// ----------------------------------------------------------------------------
// TAquaticData::Position
// ----------------------------------------------------------------------------
//
inline TPoint TAquaticData::Position() const
    {
    return iPos;
    }

// ----------------------------------------------------------------------------
// TAquaticData::Position
// ----------------------------------------------------------------------------
//
TBool TAquaticData::IsMature() const
    {
    return iMature;
    }

// ----------------------------------------------------------------------------
// TAquaticData::IsNull
// ----------------------------------------------------------------------------
//
inline TBool TAquaticData::IsNull() const
    {
    TBool retVal( EFalse );
    if ( iType == EAquaticNull )
        {
        retVal = ETrue;
        }
    return retVal;
    }

// ----------------------------------------------------------------------------
// TAquaticData::InternalizeL
// ----------------------------------------------------------------------------
//
void TAquaticData::InternalizeL( RReadStream& aRStream )
    {
    iType = static_cast<TAquaticType>( aRStream.ReadInt8L() );
    iMature = static_cast<TBool>( aRStream.ReadInt8L() );
    iPos.iX = static_cast<TInt>( aRStream.ReadInt32L() );
    iPos.iY = static_cast<TInt>( aRStream.ReadInt32L() );
    }

// ----------------------------------------------------------------------------
// TAquaticData::ExternalizeL
// ----------------------------------------------------------------------------
//
void TAquaticData::ExternalizeL( RWriteStream& aWStream ) const
    {
    aWStream.WriteInt8L( iType );
    aWStream.WriteInt8L( iMature );
    aWStream.WriteInt32L( iPos.iX );
    aWStream.WriteInt32L( iPos.iY );
    }

// End of file
