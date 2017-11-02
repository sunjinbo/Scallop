/* ====================================================================
 * File: AquaticData.h
 * Created: 06/13/09
 * Modified: 06/13/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef T_AQUATICDATA_H
#define T_AQUATICDATA_H

// INCLUDE FILES
#include <e32std.h>
#include <s32strm.h>
#include "Aquatic.hrh"

// CLASS DECLARATION
/**
* TAquaticData class
*
* @since S60 5.0
*/
class TAquaticData
    {
public:
    enum TUninitialized { EUninitialized = -1 };
    inline TAquaticData();
    inline TAquaticData( TAquaticType aType );
    inline TAquaticData( TAquaticType aType, TInt aX, TInt aY );
    inline TAquaticData( TAquaticType aType, const TPoint& aPos );
    inline TAquaticData( const TAquaticData& aAquaticData );
    inline TBool operator == ( const TAquaticData& aAquaticData ) const;
    inline TBool operator != ( const TAquaticData& aAquaticData ) const;
    inline void SetXY( TInt aX, TInt aY );
    inline void SetXY( const TPoint& aPos );
    inline void SetType( TAquaticType aType );
    inline void SetMature();
    inline TAquaticType Type() const;
    inline TPoint Position() const;
    inline TBool IsMature() const;
    inline TBool IsNull() const;
    inline void InternalizeL( RReadStream& aRStream );
    inline void ExternalizeL( RWriteStream& aWStream ) const;

private: // Member data
    /**
    The aquatic type
    */
    TAquaticType iType;

    /**
    The x,y co-ordinate.
    */
    TPoint iPos;

    /**
    The mature, immature.
    */
    TBool iMature;

    };
#include "AquaticData.inl"

#endif // T_AQUATICDATA_H

// End of file
