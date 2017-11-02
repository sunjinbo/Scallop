/* ====================================================================
 * File: GameLevel.cpp
 * Created: 09/16/09
 * Modified: 09/16/09
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <s32file.h>
#include <AknUtils.h>
#include <barsread.h>
#include <coemain.h>
#include <coeutils.h>
#include "GameLevel.h"
#include "Aquatic.hrh"
#include "AquaticData.h"
#include "PathRepository.h"
#include "ScaLogger.h"

// CONSTANTS
_LIT( KLevelFileNameHead, "l" );

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CGameLevel::NewL
// ----------------------------------------------------------------------------
//
CGameLevel* CGameLevel::NewL( TResourceReader& aReader, MPathRepository& aRep )
    {
    CGameLevel* self = CGameLevel::NewLC( aReader, aRep );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CGameLevel::NewLC
// ----------------------------------------------------------------------------
//
CGameLevel* CGameLevel::NewLC( TResourceReader& aReader, MPathRepository& aRep )
    {
    CGameLevel* self = new (ELeave) CGameLevel( aRep );
    CleanupStack::PushL( self );
    self->ConstructL( aReader );
    return self;
    }

// ----------------------------------------------------------------------------
// CGameLevel::Compare
// ----------------------------------------------------------------------------
//
TInt CGameLevel::Compare( const CGameLevel& aFirst, const CGameLevel& aSecond )
    {
     if ( aFirst.Id() > aSecond.Id() )
      return 1; 
     if ( aFirst.Id() < aSecond.Id() )
      return -1;
    return 0;
    }

// ----------------------------------------------------------------------------
// CGameLevel::~CGameLevel
// ----------------------------------------------------------------------------
//
CGameLevel::~CGameLevel()
    {
    FUNC_LOG;
    delete iType;
    delete iPrompt;
    }

// ----------------------------------------------------------------------------
// CGameLevel::Id
// ----------------------------------------------------------------------------
//
TInt CGameLevel::Id() const
    {
    FUNC_LOG;
    return iId;
    }

// ----------------------------------------------------------------------------
// CGameLevel::Time
// ----------------------------------------------------------------------------
//
TInt CGameLevel::Time() const
    {
    FUNC_LOG;
    return iTime;
    }

// ----------------------------------------------------------------------------
// CGameLevel::Score
// ----------------------------------------------------------------------------
//
TInt CGameLevel::Score() const
    {
    FUNC_LOG;
    return iScore;
    }

// ----------------------------------------------------------------------------
// CGameLevel::Bonus
// ----------------------------------------------------------------------------
//
TInt CGameLevel::Bonus() const
    {
    FUNC_LOG;
    return iBonus;
    }

// ----------------------------------------------------------------------------
// CGameLevel::GetAvailableType
// ----------------------------------------------------------------------------
//
void CGameLevel::GetAvailableType( RArray<TAquaticType>& aList )
    {
    FUNC_LOG;
    const TChar KCharSeparator = ',';
    iLexIsValid = ETrue;
    iLex.Assign( *iType );
    while( ! iLex.Eos() && iLexIsValid )
        {           
        SkipChar( KCharSeparator );
        TInt code = ReadCode();

        if ( iLexIsValid )
            {
            aList.Append( ( TAquaticType )code );
            }
        }
    }

// ----------------------------------------------------------------------------
// CGameLevel::Prompt
// ----------------------------------------------------------------------------
//
const TDesC* CGameLevel::Prompt() const
    {
    FUNC_LOG;
    return iPrompt;
    }

// ----------------------------------------------------------------------------
// CGameLevel::GetAquaticDataL
// ----------------------------------------------------------------------------
//
void CGameLevel::GetAquaticDataL( RArray<TAquaticData>& aList )
    {
    TFileName fileName;
    TBuf<256> path;
    iRepository.GetPath( path );
    fileName.Append( path );
    fileName.Append( KLevelFileNameHead );
    fileName.AppendNum( iId );
 
    if ( ConeUtils::FileExists( fileName ) )
        {
        RFile file;
        CleanupClosePushL( file );
        User::LeaveIfError( file.Open( iFs, fileName, EFileRead ) );
        RFileReadStream frs( file );
        CleanupClosePushL( frs );
        TInt count = frs.ReadInt32L();
        for ( TInt ix = 0; ix < count; ix++ )
            {
            TAquaticData aquatic;
            aquatic.InternalizeL( frs );
            aList.Append( aquatic );
            }
        CleanupStack::PopAndDestroy( &frs );
        file.Close();
        CleanupStack::PopAndDestroy( &file );
        }
    else 
        {
        User::Leave( KErrPathNotFound );
        }
    }

// ----------------------------------------------------------------------------
// CGameLevel::CGameLevel
// ----------------------------------------------------------------------------
//
CGameLevel::CGameLevel( MPathRepository& aRep )
    : iFs( CCoeEnv::Static()->FsSession() ), 
    iRepository( aRep ), iLexIsValid ( EFalse )
    { // no implementation required.
    FUNC_LOG;
    }

// ----------------------------------------------------------------------------
// CGameLevel::ConstructL
// ----------------------------------------------------------------------------
//
void CGameLevel::ConstructL( TResourceReader& aReader )
    {
    FUNC_LOG;
    iId = aReader.ReadUint8();
    iTime = aReader.ReadUint16();
    iScore = aReader.ReadUint16();
    iBonus = aReader.ReadUint16();
    iType = aReader.ReadHBufCL();
    iPrompt = aReader.ReadHBufCL();
    }

// ----------------------------------------------------------------------------
// CGameLevel::SkipChar
// ----------------------------------------------------------------------------
//
void CGameLevel::SkipChar( TChar aChar )
    {
    FUNC_LOG;
    iLex.SkipSpaceAndMark();
    if ( iLex.Peek() == aChar )
        {
        iLex.Inc();
        }
    iLex.SkipSpaceAndMark();
    }

// ----------------------------------------------------------------------------
// CGameLevel::ReadCode
// ----------------------------------------------------------------------------
//
TInt CGameLevel::ReadCode()
    {
    FUNC_LOG;
    TInt code;

    iLex.Mark();
    while ( iLex.Peek().IsDigit() )
        {
        iLex.Inc();
        }

    TPtrC codeToken = iLex.MarkedToken();
    TLex codeLex( codeToken );
    if ( codeLex.Val( code ) != KErrNone )
        {
        iLexIsValid = EFalse;
        }

    return code;
    }

// End of file
