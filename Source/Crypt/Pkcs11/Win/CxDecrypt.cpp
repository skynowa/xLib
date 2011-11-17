/**
 * \file  CxDecrypt.cpp
 * \brief Pkcs11 decrypt
 */


#include <xLib/Crypt/Pkcs11/Win/CxDecrypt.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>
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
BOOL
CxDecrypt::bInit(
    CK_MECHANISM_PTR pMechanism,  ///< the decryption mechanism
    CK_OBJECT_HANDLE hKey         ///< handle of decryption key
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDecrypt::bMake(
    CK_BYTE_PTR  pEncryptedData,     ///< ciphertext
    CK_ULONG     ulEncryptedDataLen, ///< ciphertext length
    CK_BYTE_PTR  pData,              ///< gets plaintext
    CK_ULONG_PTR pulDataLen          ///< gets p-text size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_Decrypt(_m_hSession, pEncryptedData, ulEncryptedDataLen, pData, pulDataLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDecrypt::bUpdate(
    CK_BYTE_PTR  pEncryptedPart,      ///< encrypted data
    CK_ULONG     ulEncryptedPartLen,  ///< input length
    CK_BYTE_PTR  pPart,               ///< gets plaintext
    CK_ULONG_PTR pulPartLen           ///< p-text size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptUpdate(_m_hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDecrypt::bFinal(
    CK_BYTE_PTR  pLastPart,      ///< gets plaintext
    CK_ULONG_PTR pulLastPartLen  ///< p-text size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptFinal(_m_hSession, pLastPart, pulLastPartLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDecrypt::bDigestUpdate(
    CK_BYTE_PTR  pEncryptedPart,      ///< ciphertext
    CK_ULONG     ulEncryptedPartLen,  ///< ciphertext length
    CK_BYTE_PTR  pPart,               ///< gets plaintext
    CK_ULONG_PTR pulPartLen           ///< gets plaintext len
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptDigestUpdate(_m_hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxDecrypt::bVerifyUpdate(
    CK_BYTE_PTR  pEncryptedPart,      ///< ciphertext
    CK_ULONG     ulEncryptedPartLen,  ///< ciphertext length
    CK_BYTE_PTR  pPart,               ///< gets plaintext
    CK_ULONG_PTR pulPartLen           ///< gets p-text length
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_DecryptVerifyUpdate(_m_hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------


/****************************************************************************
*    Public utils
*
*****************************************************************************/

//---------------------------------------------------------------------------
BOOL
CxDecrypt::bMakeFile(
    const std::string_t &csInFilePath,
    const std::string_t &csOutFilePath,
    CK_MECHANISM_PTR    pMechanism,
    CK_OBJECT_HANDLE    hKey
)
{
    /*DEBUG*/xASSERT_RET(false == csInFilePath.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(false == csOutFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pMechanism,            FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != hKey,                  FALSE);

    //-------------------------------------
    //������ ����-����� � �����
    BOOL         bRes            = FALSE;
    std::ustring usEncryptedData;

    {
        CxFile sfFileRaw;

        bRes = sfFileRaw.bCreate(csInFilePath, CxFile::omBinRead, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        bRes = sfFileRaw.bRead(&usEncryptedData);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    //-------------------------------------
    //������������ ������
    ULONG ulPadSize        = 128;  //��� DES 64 ����
    ULONG ulOffset         = 0;
    ULONG ulOffset2        = 0;
    ULONG ulResDecryptSize = 0;

    ////CK_BYTE  usDecryptedData[128]   = {0};
    const ULONG  g_culBuffSize       = 8192 * 4;  //FIX_ME:
    std::ustring usDecryptedData;    usDecryptedData.resize(g_culBuffSize);
    CK_ULONG     usDecryptedDataSize = g_culBuffSize;

    {
        for (ulOffset = 0; ulOffset < usEncryptedData.size()/*ulResEncryptSize*//*usRawData.size()*/; ulOffset += ulPadSize) {
            bRes = bInit(pMechanism, hKey);
            xCHECK_RET(FALSE == bRes, FALSE);

            bRes = bMake(&usEncryptedData[0] + ulOffset, ulPadSize, &usDecryptedData[0] + ulOffset2, &usDecryptedDataSize);
            xCHECK_RET(FALSE == bRes, FALSE);

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

        bRes = sfFileDecrypt.bCreate(csOutFilePath, CxFile::omBinWrite, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        bRes = sfFileDecrypt.bWrite(usDecryptedData);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
