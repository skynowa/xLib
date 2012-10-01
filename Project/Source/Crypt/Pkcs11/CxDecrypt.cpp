/**
 * \file  CxDecrypt.cpp
 * \brief Pkcs11 decrypt
 */


#include <xLib/Crypt/Pkcs11/CxDecrypt.h>

#include <xLib/Crypt/Pkcs11/CxPkcs11.h>
#include <xLib/Crypt/Pkcs11/CxSession.h>
#include <xLib/Filesystem/CxFile.h>


#if   xOS_ENV_WIN

xNAMESPACE_BEGIN(NxLib)

/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxDecrypt::CxDecrypt(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/* virtual */
CxDecrypt::~CxDecrypt() {

}
//---------------------------------------------------------------------------
bool
CxDecrypt::bInit(
    CK_MECHANISM_PTR a_pMechanism,  ///< the decryption mechanism
    CK_OBJECT_HANDLE a_hKey         ///< handle of decryption key
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_DecryptInit(_m_hSession, a_pMechanism, a_hKey);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bMake(
    CK_BYTE_PTR  a_pEncryptedData,     ///< ciphertext
    CK_ULONG     a_ulEncryptedDataLen, ///< ciphertext length
    CK_BYTE_PTR  a_pData,              ///< gets plaintext
    CK_ULONG_PTR a_pulDataLen          ///< gets p-text size
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_Decrypt(_m_hSession, a_pEncryptedData, a_ulEncryptedDataLen, a_pData, a_pulDataLen);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bUpdate(
    CK_BYTE_PTR  a_pEncryptedPart,      ///< encrypted data
    CK_ULONG     a_ulEncryptedPartLen,  ///< input length
    CK_BYTE_PTR  a_pPart,               ///< gets plaintext
    CK_ULONG_PTR a_pulPartLen           ///< p-text size
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_DecryptUpdate(_m_hSession, a_pEncryptedPart, a_ulEncryptedPartLen, a_pPart, a_pulPartLen);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bFinal(
    CK_BYTE_PTR  a_pLastPart,      ///< gets plaintext
    CK_ULONG_PTR a_pulLastPartLen  ///< p-text size
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_DecryptFinal(_m_hSession, a_pLastPart, a_pulLastPartLen );
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bDigestUpdate(
    CK_BYTE_PTR  a_pEncryptedPart,      ///< ciphertext
    CK_ULONG     a_ulEncryptedPartLen,  ///< ciphertext length
    CK_BYTE_PTR  a_pPart,               ///< gets plaintext
    CK_ULONG_PTR a_pulPartLen           ///< gets plaintext len
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_DecryptDigestUpdate(_m_hSession, a_pEncryptedPart, a_ulEncryptedPartLen, a_pPart, a_pulPartLen);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bVerifyUpdate(
    CK_BYTE_PTR  a_pEncryptedPart,      ///< ciphertext
    CK_ULONG     a_ulEncryptedPartLen,  ///< ciphertext length
    CK_BYTE_PTR  a_pPart,               ///< gets plaintext
    CK_ULONG_PTR a_pulPartLen           ///< gets p-text length
)
{
    /*DEBUG*/

    CK_RV ulRv = _m_pFunc->C_DecryptVerifyUpdate(_m_hSession, a_pEncryptedPart, a_ulEncryptedPartLen, a_pPart, a_pulPartLen);
    /*DEBUG*/xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::sErrorStr(ulRv));

    return true;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Public utils
*
*****************************************************************************/

//---------------------------------------------------------------------------
bool
CxDecrypt::bMakeFile(
    const std::tstring_t &a_csInFilePath,
    const std::tstring_t &a_csOutFilePath,
    CK_MECHANISM_PTR      a_pMechanism,
    CK_OBJECT_HANDLE      a_hKey
)
{
    /*DEBUG*/xTEST_EQ(false, a_csInFilePath.empty());
    /*DEBUG*/xTEST_EQ(false, a_csOutFilePath.empty());
    /*DEBUG*/xTEST_PTR(a_pMechanism);
    /*DEBUG*/xTEST_PTR(a_hKey);

    //-------------------------------------
    //������ ����-����� � �����
    bool         bRv            = false;
    std::ustring_t usEncryptedData;

    {
        CxFile sfFileRaw;

        bRv = sfFileRaw.bCreate(a_csInFilePath, CxFile::omBinRead, true);
        /*DEBUG*/xTEST_EQ(true, bRv);

        bRv = sfFileRaw.bRead(&usEncryptedData);
        /*DEBUG*/xTEST_EQ(true, bRv);
    }

    //-------------------------------------
    //������������ ������
    ulong_t ulPadSize        = 128;  //��� DES 64 ����
    ulong_t ulOffset         = 0;
    ulong_t ulOffset2        = 0;
    ulong_t ulResDecryptSize = 0;

    ////CK_BYTE  usDecryptedData[128]   = {0};
    const ulong_t  g_culBuffSize       = 8192 * 4;  //FIX_ME:
    std::ustring_t usDecryptedData;    usDecryptedData.resize(g_culBuffSize);
    CK_ULONG     usDecryptedDataSize = g_culBuffSize;

    {
        for (ulOffset = 0; ulOffset < usEncryptedData.size()/*ulResEncryptSize*//*usRawData.size()*/; ulOffset += ulPadSize) {
            bRv = bInit(a_pMechanism, a_hKey);
            xCHECK_RET(false == bRv, false);

            bRv = bMake(&usEncryptedData[0] + ulOffset, ulPadSize, &usDecryptedData[0] + ulOffset2, &usDecryptedDataSize);
            xCHECK_RET(false == bRv, false);

            ulOffset2 += usDecryptedDataSize;
        }
        ulResDecryptSize = ulOffset2;
    }
    usDecryptedData.resize(ulResDecryptSize/*usDecryptedDataSize*/);

    //-------------------------------------
    //check that we are back where we started
    /*DEBUG*/////xASSERT(usRawData        == usDecryptedData);
    /*DEBUG*/////xASSERT(usRawData.size() == usDecryptedData.size());
    /*DEBUG*/////std::cout << &usDecryptedData[0] << std::endl;

    //-------------------------------------
    //������ ������ � ����
    {
        CxFile sfFileDecrypt;

        bRv = sfFileDecrypt.bCreate(a_csOutFilePath, CxFile::omBinWrite, true);
        /*DEBUG*/xTEST_EQ(true, bRv);

        bRv = sfFileDecrypt.bWrite(usDecryptedData);
        /*DEBUG*/xTEST_EQ(true, bRv);
    }

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
