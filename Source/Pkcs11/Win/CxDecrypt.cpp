/****************************************************************************
* Class name:  CxDecrypt
* Description: Pkcs11 decrypt
* File name:   CxDecrypt.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:11:10
*
*****************************************************************************/


#include <xLib/Pkcs11/CxDecrypt.h>

#include <xLib/Pkcs11/CxUtils.h>
#include <xLib/Filesystem/CxStdioFile.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxDecrypt ()
CxDecrypt::CxDecrypt(const CxPkcs11 &cPkcs11, const CxSession &cSession) :
    _m_bRes    (FALSE),
    _m_ulRes   (!CKR_OK),
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{
    //code
}
//---------------------------------------------------------------------------
//TODO: ~CxDecrypt ()
CxDecrypt::~CxDecrypt() {
    //code
}
//---------------------------------------------------------------------------
//TODO: bInit (initializes a decryption operation)
BOOL
CxDecrypt::bInit(
    CK_MECHANISM_PTR  pMechanism,  /* the decryption mechanism */
    CK_OBJECT_HANDLE  hKey         /* handle of decryption key */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_DecryptInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bMake (decrypts encrypted data in a single part)
BOOL
CxDecrypt::bMake(
    CK_BYTE_PTR       pEncryptedData,     /* ciphertext */
    CK_ULONG          ulEncryptedDataLen, /* ciphertext length */
    CK_BYTE_PTR       pData,              /* gets plaintext */
    CK_ULONG_PTR      pulDataLen          /* gets p-text size */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_Decrypt(_m_hSession, pEncryptedData, ulEncryptedDataLen, pData, pulDataLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bUpdate (continues a multiple-part decryption operation)
BOOL
CxDecrypt::bUpdate(
    CK_BYTE_PTR       pEncryptedPart,      /* encrypted data */
    CK_ULONG          ulEncryptedPartLen,  /* input length */
    CK_BYTE_PTR       pPart,               /* gets plaintext */
    CK_ULONG_PTR      pulPartLen           /* p-text size */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_DecryptUpdate(_m_hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bFinal (finishes a multiple-part decryption operation)    
BOOL
CxDecrypt::bFinal(
    CK_BYTE_PTR       pLastPart,      /* gets plaintext */
    CK_ULONG_PTR      pulLastPartLen  /* p-text size */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_DecryptFinal(_m_hSession, pLastPart, pulLastPartLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bDigestUpdate (continues a multiple-part decryption and digesting operation)
BOOL
CxDecrypt::bDigestUpdate(
    CK_BYTE_PTR       pEncryptedPart,      /* ciphertext */
    CK_ULONG          ulEncryptedPartLen,  /* ciphertext length */
    CK_BYTE_PTR       pPart,               /* gets plaintext */
    CK_ULONG_PTR      pulPartLen           /* gets plaintext len */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_DecryptDigestUpdate(_m_hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------
//TODO: bVerifyUpdate (continues a multiple-part decryption and verify operation)
BOOL
CxDecrypt::bVerifyUpdate(
    CK_BYTE_PTR       pEncryptedPart,      /* ciphertext */
    CK_ULONG          ulEncryptedPartLen,  /* ciphertext length */
    CK_BYTE_PTR       pPart,               /* gets plaintext */
    CK_ULONG_PTR      pulPartLen           /* gets p-text length */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_DecryptVerifyUpdate(_m_hSession, pEncryptedPart, ulEncryptedPartLen, pPart, pulPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
}
//---------------------------------------------------------------------------

/****************************************************************************
*    Public utils                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: bMakeFile ()
BOOL
CxDecrypt::bMakeFile(const tString &csInFilePath, const tString &csOutFilePath, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey) {
    /*DEBUG*/xASSERT_RET(false == csInFilePath.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(false == csOutFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pMechanism,            FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != hKey,                  FALSE);

    //-------------------------------------
    //������ ����-����� � �����
    uString usEncryptedData;        //����-������
    
    {
        CxStdioFile sfFileRaw;
        
        _m_bRes = sfFileRaw.bOpen(csInFilePath, CxStdioFile::omBinRead, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _m_bRes = sfFileRaw.bRead(&usEncryptedData);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }        
    
    //-------------------------------------
    //������������ ������
    ULONG ulPadSize = 128;  //��� DES 64 ����
    ULONG ulOffset  = 0;
    ULONG ulOffset2 = 0;
    ULONG ulResDecryptSize = 0;

      ////CK_BYTE  usDecryptedData[128]   = {0}; 
    const ULONG          g_culBuffSize    = 8192 * 4;  //FIX_ME:    
    uString  usDecryptedData;    usDecryptedData.resize(g_culBuffSize);     
    CK_ULONG usDecryptedDataSize = g_culBuffSize;

    {
        for (ulOffset = 0; ulOffset < usEncryptedData.size()/*ulResEncryptSize*//*usRawData.size()*/; ulOffset += ulPadSize) {
            _m_bRes = bInit(pMechanism, hKey);
            xCHECK_RET(FALSE == _m_bRes, FALSE);

            _m_bRes = bMake(&usEncryptedData[0] + ulOffset, ulPadSize, &usDecryptedData[0] + ulOffset2, &usDecryptedDataSize);
            xCHECK_RET(FALSE == _m_bRes, FALSE);

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
        CxStdioFile sfFileDecrypt;

        _m_bRes = sfFileDecrypt.bOpen(csOutFilePath, CxStdioFile::omBinWrite, TRUE);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _m_bRes = sfFileDecrypt.bWrite(usDecryptedData);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }

    return TRUE;
}
//---------------------------------------------------------------------------



/****************************************************************************
*    Private methods                                                         
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
