/**
 * \file  CxEncrypt.cpp
 * \brief Pkcs11 encrypt
 */


#include <xLib/Crypt/Pkcs11/CxEncrypt.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>
#include <xLib/Crypt/Pkcs11/CxUtils.h>
#include <xLib/Filesystem/CxFile.h>


#if xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxEncrypt::CxEncrypt(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.pGetFuncList()),
    _m_hSession(a_cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxEncrypt::~CxEncrypt() {

}
//---------------------------------------------------------------------------
bool
CxEncrypt::bInit(
    CK_MECHANISM_PTR a_pMechanism,  ///< the encryption mechanism
    CK_OBJECT_HANDLE a_hKey         ///< handle of encryption key
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_EncryptInit(_m_hSession, a_pMechanism, a_hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxEncrypt::bMake(
    CK_BYTE_PTR  a_pData,               ///< the plaintext data
    CK_ULONG     a_ulDataLen,           ///< bytes of plaintext
    CK_BYTE_PTR  a_pEncryptedData,      ///< gets ciphertext
    CK_ULONG_PTR a_pulEncryptedDataLen  ///< gets c-text size
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_Encrypt(_m_hSession, a_pData, a_ulDataLen, a_pEncryptedData, a_pulEncryptedDataLen  );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxEncrypt::bUpdate(
    CK_BYTE_PTR  a_pPart,              ///< the plaintext data
    CK_ULONG     a_ulPartLen,          ///< plaintext data len
    CK_BYTE_PTR  a_pEncryptedPart,     ///< gets ciphertext
    CK_ULONG_PTR a_pulEncryptedPartLen ///< gets c-text size
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_EncryptUpdate(_m_hSession, a_pPart, a_ulPartLen, a_pEncryptedPart, a_pulEncryptedPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxEncrypt::bFinal(
    CK_BYTE_PTR  a_pLastEncryptedPart,      ///< last c-text
    CK_ULONG_PTR a_pulLastEncryptedPartLen  ///< gets last size
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_EncryptFinal(_m_hSession, a_pLastEncryptedPart, a_pulLastEncryptedPartLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRv, CxUtils::sErrorStr(ulRv).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Public utils
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxEncrypt::bMakeFile(
    const std::tstring_t &a_csInFilePath,
    const std::tstring_t &a_csOutFilePath,
    CK_MECHANISM_PTR      a_pMechanism,
    CK_OBJECT_HANDLE      a_hKey
)
{
    /*DEBUG*/xASSERT_RET(false == a_csInFilePath.empty(),  false);
    /*DEBUG*/xASSERT_RET(false == a_csOutFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != a_pMechanism,            false);
    /*DEBUG*/xASSERT_RET(NULL  != a_hKey,                  false);

    //-------------------------------------
    //������ ����� � �����
    bool         bRv        = false;
    std::ustring_t usPlainData;

    {
        CxFile sfFileRaw;

        bRv = sfFileRaw.bCreate(a_csInFilePath, CxFile::omBinRead, true);
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        bRv = sfFileRaw.bRead(&usPlainData);
        /*DEBUG*/xASSERT_RET(true == bRv, false);
    }

    //-------------------------------------
    //���������� ������
    ulong_t ulPadSize  = 128 - 11;  //��� RSA 117-����.����� �����, 128-������������� ����
    ulong_t ulOffset   = 0;
    ulong_t ulOffset2  = 0;
    ulong_t ulResEncryptSize = 0;

    ////CK_BYTE  usEncryptedData[128]  = {0};
    const ulong_t          g_culBuffSize    = 8192 * 4;  //FIX_ME:
    std::ustring_t  usEncryptedData;    usEncryptedData.resize(g_culBuffSize);
    CK_ULONG usEncryptedDataSize = g_culBuffSize;

    {
        size_t uiDataSize = usPlainData.size();
        for (ulOffset = 0; ulOffset < uiDataSize; ulOffset += ulPadSize) {
            //������� ������
            if (ulPadSize > (uiDataSize - ulOffset)) {
                ulPadSize = uiDataSize - ulOffset;
            }

            bRv = bInit(a_pMechanism, a_hKey);
            xCHECK_RET(false == bRv, false);

            bRv = bMake(&usPlainData[0] + ulOffset, ulPadSize, &usEncryptedData[0] + ulOffset2, &usEncryptedDataSize);
            xCHECK_RET(false == bRv, false);

            ulOffset2 += usEncryptedDataSize;
        }
        ulResEncryptSize = ulOffset2;
    }
    usEncryptedData.resize(ulResEncryptSize);


    //-------------------------------------
    //������ ����-������ � ����
    {
        CxFile sfFileEncrypt;

        bRv = sfFileEncrypt.bCreate(a_csOutFilePath, CxFile::omBinWrite, true);
        /*DEBUG*/xASSERT_RET(true == bRv, false);

        bRv = sfFileEncrypt.bWrite(usEncryptedData);
        /*DEBUG*/xASSERT_RET(true == bRv, false);
    }

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
