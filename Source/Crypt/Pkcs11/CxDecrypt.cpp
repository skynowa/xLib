/**
 * \file  CxDecrypt.cpp
 * \brief Pkcs11 decrypt
 */


#include <xLib/Crypt/Pkcs11/CxDecrypt.h>

#include <xLib/Crypt/Pkcs11/CxUtils.h>
#include <xLib/Filesystem/CxFile.h>


#if xOS_ENV_WIN

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
/*virtual*/
CxDecrypt::~CxDecrypt() {

}
//---------------------------------------------------------------------------
bool
CxDecrypt::bInit(
    CK_MECHANISM_PTR pMechanism,  ///< the decryption mechanism
    CK_OBJECT_HANDLE hKey         ///< handle of decryption key
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bMake(
    CK_BYTE_PTR  pEncryptedData,     ///< ciphertext
    CK_ULONG     ulEncryptedDataLen, ///< ciphertext length
    CK_BYTE_PTR  pData,              ///< gets plaintext
    CK_ULONG_PTR pulDataLen          ///< gets p-text size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_Decrypt(_m_hSession, pEncryptedData, ulEncryptedDataLen, pData, pulDataLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bUpdate(
    CK_BYTE_PTR  pEncryptedPart,      ///< encrypted data
    CK_ULONG     ulEncryptedPartLen,  ///< input length
    CK_BYTE_PTR  pPart,               ///< gets plaintext
    CK_ULONG_PTR pulPartLen           ///< p-text size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptUpdate(_m_hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bFinal(
    CK_BYTE_PTR  pLastPart,      ///< gets plaintext
    CK_ULONG_PTR pulLastPartLen  ///< p-text size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptFinal(_m_hSession, pLastPart, pulLastPartLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bDigestUpdate(
    CK_BYTE_PTR  pEncryptedPart,      ///< ciphertext
    CK_ULONG     ulEncryptedPartLen,  ///< ciphertext length
    CK_BYTE_PTR  pPart,               ///< gets plaintext
    CK_ULONG_PTR pulPartLen           ///< gets plaintext len
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptDigestUpdate(_m_hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

    return true;
}
//---------------------------------------------------------------------------
bool
CxDecrypt::bVerifyUpdate(
    CK_BYTE_PTR  pEncryptedPart,      ///< ciphertext
    CK_ULONG     ulEncryptedPartLen,  ///< ciphertext length
    CK_BYTE_PTR  pPart,               ///< gets plaintext
    CK_ULONG_PTR pulPartLen           ///< gets p-text length
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptVerifyUpdate(_m_hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), false);

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
    const std::tstring_t &csInFilePath,
    const std::tstring_t &csOutFilePath,
    CK_MECHANISM_PTR    pMechanism,
    CK_OBJECT_HANDLE    hKey
)
{
    /*DEBUG*/xASSERT_RET(false == csInFilePath.empty(),  false);
    /*DEBUG*/xASSERT_RET(false == csOutFilePath.empty(), false);
    /*DEBUG*/xASSERT_RET(NULL  != pMechanism,            false);
    /*DEBUG*/xASSERT_RET(NULL  != hKey,                  false);

    //-------------------------------------
    //������ ����-����� � �����
    bool         bRes            = false;
    std::ustring_t usEncryptedData;

    {
        CxFile sfFileRaw;

        bRes = sfFileRaw.bCreate(csInFilePath, CxFile::omBinRead, true);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        bRes = sfFileRaw.bRead(&usEncryptedData);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
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
            bRes = bInit(pMechanism, hKey);
            xCHECK_RET(false == bRes, false);

            bRes = bMake(&usEncryptedData[0] + ulOffset, ulPadSize, &usDecryptedData[0] + ulOffset2, &usDecryptedDataSize);
            xCHECK_RET(false == bRes, false);

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

        bRes = sfFileDecrypt.bCreate(csOutFilePath, CxFile::omBinWrite, true);
        /*DEBUG*/xASSERT_RET(true == bRes, false);

        bRes = sfFileDecrypt.bWrite(usDecryptedData);
        /*DEBUG*/xASSERT_RET(true == bRes, false);
    }

    return true;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
