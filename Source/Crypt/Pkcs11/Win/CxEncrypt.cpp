/**
 * \file  CxEncrypt.cpp
 * \brief Pkcs11 encrypt
 */


#include <xLib/Crypt/Pkcs11/Win/CxEncrypt.h>

#include <xLib/Crypt/Pkcs11/Win/CxUtils.h>
#include <xLib/Filesystem/CxFile.h>


#if defined(xOS_ENV_WIN)
/****************************************************************************
*    public
*
*****************************************************************************/

//---------------------------------------------------------------------------
CxEncrypt::CxEncrypt(
    const CxPkcs11  &cPkcs11,
    const CxSession &cSession
) :
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{

}
//---------------------------------------------------------------------------
/*virtual*/
CxEncrypt::~CxEncrypt() {

}
//---------------------------------------------------------------------------
BOOL
CxEncrypt::bInit(
    CK_MECHANISM_PTR pMechanism,  ///< the encryption mechanism
    CK_OBJECT_HANDLE hKey         ///< handle of encryption key
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_EncryptInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEncrypt::bMake(
    CK_BYTE_PTR  pData,               ///< the plaintext data
    CK_ULONG     ulDataLen,           ///< bytes of plaintext
    CK_BYTE_PTR  pEncryptedData,      ///< gets ciphertext
    CK_ULONG_PTR pulEncryptedDataLen  ///< gets c-text size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_Encrypt(_m_hSession, pData, ulDataLen, pEncryptedData, pulEncryptedDataLen  );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEncrypt::bUpdate(
    CK_BYTE_PTR  pPart,              ///< the plaintext data
    CK_ULONG     ulPartLen,          ///< plaintext data len
    CK_BYTE_PTR  pEncryptedPart,     ///< gets ciphertext
    CK_ULONG_PTR pulEncryptedPartLen ///< gets c-text size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_EncryptUpdate(_m_hSession, pPart, ulPartLen, pEncryptedPart, pulEncryptedPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == ulRes, CxUtils::sErrorStr(ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
BOOL
CxEncrypt::bFinal(
    CK_BYTE_PTR  pLastEncryptedPart,      ///< last c-text
    CK_ULONG_PTR pulLastEncryptedPartLen  ///< gets last size
)
{
    /*DEBUG*/

    CK_RV ulRes = _m_pFunc->C_EncryptFinal(_m_hSession, pLastEncryptedPart, pulLastEncryptedPartLen );
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
CxEncrypt::bMakeFile(
    const std::tstring &csInFilePath,
    const std::tstring &csOutFilePath,
    CK_MECHANISM_PTR    pMechanism,
    CK_OBJECT_HANDLE    hKey
)
{
    /*DEBUG*/xASSERT_RET(false == csInFilePath.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(false == csOutFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pMechanism,            FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != hKey,                  FALSE);

    //-------------------------------------
    //������ ����� � �����
    BOOL         bRes        = FALSE;
    std::ustring usPlainData;     

    {
        CxFile sfFileRaw;

        bRes = sfFileRaw.bCreate(csInFilePath, CxFile::omBinRead, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        bRes = sfFileRaw.bRead(&usPlainData);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    //-------------------------------------
    //���������� ������
    ULONG ulPadSize  = 128 - 11;  //��� RSA 117-����.����� �����, 128-������������� ����
    ULONG ulOffset   = 0;
    ULONG ulOffset2  = 0;
    ULONG ulResEncryptSize = 0;

    ////CK_BYTE  usEncryptedData[128]  = {0};
    const ULONG          g_culBuffSize    = 8192 * 4;  //FIX_ME:
    std::ustring  usEncryptedData;    usEncryptedData.resize(g_culBuffSize);
    CK_ULONG usEncryptedDataSize = g_culBuffSize;

    {
        size_t uiDataSize = usPlainData.size();
        for (ulOffset = 0; ulOffset < uiDataSize; ulOffset += ulPadSize) {
            //������� ������
            if (ulPadSize > (uiDataSize - ulOffset)) {
                ulPadSize = uiDataSize - ulOffset;
            }

            bRes = bInit(pMechanism, hKey);
            xCHECK_RET(FALSE == bRes, FALSE);

            bRes = bMake(&usPlainData[0] + ulOffset, ulPadSize, &usEncryptedData[0] + ulOffset2, &usEncryptedDataSize);
            xCHECK_RET(FALSE == bRes, FALSE);

            ulOffset2 += usEncryptedDataSize;
        }
        ulResEncryptSize = ulOffset2;
    }
    usEncryptedData.resize(ulResEncryptSize);


    //-------------------------------------
    //������ ����-������ � ����
    {
        CxFile sfFileEncrypt;

        bRes = sfFileEncrypt.bCreate(csOutFilePath, CxFile::omBinWrite, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);

        bRes = sfFileEncrypt.bWrite(usEncryptedData);
        /*DEBUG*/xASSERT_RET(FALSE != bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------
#endif
