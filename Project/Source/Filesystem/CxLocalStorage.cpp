/**
 * \file  CxLocalStorage.cpp
 * \brief ini
 */


#include <xLib/Filesystem/CxLocalStorage.h>

#include <xLib/Common/CxString.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Filesystem/CxDir.h>
#include <xLib/Filesystem/CxFile.h>


xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public: creation
*
*****************************************************************************/

//-------------------------------------------------------------------------
CxLocalStorage::CxLocalStorage() :
    _m_csSeparator(CxConst::xEQUAL),
    _m_csFileExt  (xT("ini")),
    _m_sFilePath  (),
    _m_msIni      ()
{
    xTEST_EQ(false, _m_csSeparator.empty());
    xTEST_EQ(false, _m_csFileExt.empty());
    xTEST_EQ(true,  _m_sFilePath.empty());

    vSetPath(CxPath::sSetExt( CxPath::sExe(), _m_csFileExt ));
}
//-------------------------------------------------------------------------
CxLocalStorage::CxLocalStorage(
    const std::tstring_t &csFilePath
) :
    _m_csSeparator(CxConst::xEQUAL),
    _m_csFileExt  (xT("ini")),
    _m_sFilePath  (),
    _m_msIni      ()
{
    xTEST_EQ(false, _m_csSeparator.empty());
    xTEST_EQ(false, _m_csFileExt.empty());
    xTEST_EQ(true,  _m_sFilePath.empty());
    xTEST_EQ(false, csFilePath.empty());

    vSetPath(CxPath::sSetExt( csFilePath, _m_csFileExt ));
}
//-------------------------------------------------------------------------
/* virtual */
CxLocalStorage::~CxLocalStorage() {

}
//-------------------------------------------------------------------------
void
CxLocalStorage::vCreateDefault(
    const std::tstring_t &csContent
) const
{
    xTEST_EQ(false, _m_sFilePath.empty());
    // csContent - n/a;

    CxFile::vTextWrite(_m_sFilePath, csContent);
}
//-------------------------------------------------------------------------
std::tstring_t
CxLocalStorage::sPath() const {
    xTEST_EQ(false, _m_sFilePath.empty());

    return _m_sFilePath;
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vSetPath(
    const std::tstring_t &csFilePath
)
{
    //_m_sFilePath - n/a
    xTEST_EQ(false, csFilePath.empty());

    CxDir::vCreateForce(CxPath::sDir(csFilePath));

    _m_sFilePath = csFilePath;
}
//---------------------------------------------------------------------------
TLocalStorage &
CxLocalStorage::cmsGet() {
    

    return _m_msIni;
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vFlush() const {
    

    CxFile::vTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vClear() {
    

    CxFile::vClear(_m_sFilePath);
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vDelete() {
    

    //file
    CxFile::vDelete(_m_sFilePath);

    //TLocalStorage
    _m_msIni.clear();
}
//---------------------------------------------------------------------------


/****************************************************************************
*    public: key
*
*****************************************************************************/

//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyIsExists(
    const std::tstring_t &csKey
) const
{
    xTEST_EQ(false, _m_sFilePath.empty());

    TLocalStorage mmsIni;

    CxFile::vTextRead(_m_sFilePath, _m_csSeparator, &mmsIni);

    xCHECK_RET(mmsIni.end() == mmsIni.find(csKey), false);

    return true;
}
//-------------------------------------------------------------------------
std::tstring_t
CxLocalStorage::sKeyReadString(
    const std::tstring_t &csKey,
    const std::tstring_t &csDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, csKey.empty());
    //csDefaultValue - n/a

    std::tstring_t sRv;

    _vRead(csKey, csDefaultValue, &sRv);

    return sRv;
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteString(
    const std::tstring_t &csKey,
    const std::tstring_t &csValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, csKey.empty());
    //csValue   - n/a

    _vWrite(csKey, csValue);
}
//---------------------------------------------------------------------------
long_t
CxLocalStorage::iKeyReadInt(
    const std::tstring_t &csKey,
    const long_t         &cliDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey         - n/a
    //iDefaultValue - n/a

    return CxString::string_cast<long_t>( sKeyReadString(csKey, CxString::string_cast(cliDefaultValue)) );
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteInt(
    const std::tstring_t &csKey,
    const long_t         &cliValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey     - n/a
    //iValue    - n/a

    vKeyWriteString(csKey, CxString::string_cast(cliValue));
}
//-------------------------------------------------------------------------
double
CxLocalStorage::dKeyReadFloat(
    const std::tstring_t &csKey,
    const double         &cdDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey         - n/a
    //dDefaultValue - n/a

    return CxString::string_cast<double>( sKeyReadString(csKey, CxString::string_cast(cdDefaultValue)) );
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteFloat(
    const std::tstring_t &csKey,
    const double         &cdValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey     - n/a
    //dValue    - n/a

    vKeyWriteString(csKey, CxString::string_cast(cdValue));
}
//-------------------------------------------------------------------------
bool
CxLocalStorage::bKeyReadBool(
    const std::tstring_t &csKey,
    const bool           &cbDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey         - n/a
    //bDefaultValue - n/a

    std::tstring_t sStr;

    sStr = sKeyReadString(csKey, CxString::sBoolToStr(cbDefaultValue));

    bool bRv = CxString::bStrToBool(sStr);
    

    return bRv;
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteBool(
    const std::tstring_t &csKey,
    const bool           &cbValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey     - n/a
    //bValue    - n/a

    std::tstring_t sValue;

    sValue = CxString::sBoolToStr(cbValue);

    vKeyWriteString(csKey, sValue);
}
//---------------------------------------------------------------------------
std::ustring_t
CxLocalStorage::usKeyReadBin(
    const std::tstring_t &csKey,
    const std::ustring_t &cusDefaultValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey          - n/a
    //cusDefaultValue - n/a

    std::tstring_t sRv;

    std::tstring_t sHexStr = sKeyReadString(csKey, std::tstring_t(cusDefaultValue.begin(), cusDefaultValue.end()));

    //sHexStr -> usRv
    sRv = CxString::string_cast(sHexStr, 16);

    return std::ustring_t(sRv.begin(), sRv.end());
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyWriteBin(
    const std::tstring_t &csKey,
    const std::ustring_t &cusValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    //csKey     - n/a
    //cusValue  - n/a

    //cusValue (std::ustring_t) -> sHexStr (std::tstring_t)
    std::tstring_t sHexStr;

    sHexStr = CxString::string_cast( std::tstring_t(cusValue.begin(), cusValue.end()), 16);

    vKeyWriteString(csKey, sHexStr);
}
//-------------------------------------------------------------------------
void
CxLocalStorage::vKeyClear(
    const std::tstring_t &csKey
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, csKey.empty());

    vKeyWriteString(csKey, std::tstring_t());
}
//---------------------------------------------------------------------------
void
CxLocalStorage::vKeyDelete(
   const std::tstring_t &csKey
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, csKey.empty());

    //read from file
    CxFile::vTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);

    xCHECK_DO(_m_msIni.end() == _m_msIni.find(csKey), return);

    //delete from TLocalStorage
    _m_msIni.erase(csKey);

    //write to file
    CxFile::vTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
}
//---------------------------------------------------------------------------


/****************************************************************************
*    private
*
*****************************************************************************/

//---------------------------------------------------------------------------
void
CxLocalStorage::_vRead(
    const std::tstring_t &csKey,
    const std::tstring_t &csDefaultValue,
    std::tstring_t       *psValue
)
{
    // csKey          - n/a
    // csDefaultValue - n/a
    xTEST_PTR(psValue);

    //read from file
    CxFile::vTextRead(_m_sFilePath, _m_csSeparator, &_m_msIni);

    //read to TLocalStorage
    TLocalStorage::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        _vWrite(csKey, csDefaultValue);

        (*psValue) = csDefaultValue;
    } else {
        (*psValue) = (*it).second;
    }
}
//---------------------------------------------------------------------------
void
CxLocalStorage::_vWrite(
    const std::tstring_t &csKey,
    const std::tstring_t &csValue
)
{
    xTEST_EQ(false, _m_sFilePath.empty());
    xTEST_EQ(false, csKey.empty());
    // csValue - n/a

    //write to TLocalStorage
    TLocalStorage::iterator it = _m_msIni.find(csKey);
    if (_m_msIni.end() == it) {
        _m_msIni.insert( std::pair<std::tstring_t, std::tstring_t>(csKey, csValue) );
    } else {
        (*it).second = csValue;
    }

    //write to file
    CxFile::vTextWrite(_m_sFilePath, _m_csSeparator, _m_msIni);
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
