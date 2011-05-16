/****************************************************************************
* Class name:  CxEncrypt
* Description: Pkcs11 encrypt
* File name:   CxEncrypt.cpp
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 13:10:51
*
*****************************************************************************/


#include <xLib/Pkcs11/CxEncrypt.h>

#include <xLib/Pkcs11/CxUtils.h>
#include <xLib/Filesystem/CxStdioFile.h>


/****************************************************************************
*    Public methods                                                          
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxEncrypt ()
CxEncrypt::CxEncrypt(const CxPkcs11 &cPkcs11, const CxSession &cSession) :
    _m_bRes    (FALSE),
    _m_ulRes   (!CKR_OK),
    _m_pFunc   (cPkcs11.pGetFuncList()),
    _m_hSession(cSession.hGetHandle())
{
    //code
}
//---------------------------------------------------------------------------
//TODO: ~CxEncrypt ()
CxEncrypt::~CxEncrypt() {
    //code
}
//---------------------------------------------------------------------------
//TODO: bInit (initializes an encryption operation)
BOOL
CxEncrypt::bInit(
    CK_MECHANISM_PTR  pMechanism,  /* the encryption mechanism */
    CK_OBJECT_HANDLE  hKey         /* handle of encryption key */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_EncryptInit(_m_hSession, pMechanism, hKey);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: bMake (encrypts single-part data)
BOOL
CxEncrypt::bMake(
    CK_BYTE_PTR       pData,               /* the plaintext data */
    CK_ULONG          ulDataLen,           /* bytes of plaintext */
    CK_BYTE_PTR       pEncryptedData,      /* gets ciphertext */
    CK_ULONG_PTR      pulEncryptedDataLen  /* gets c-text size */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_Encrypt(_m_hSession, pData, ulDataLen, pEncryptedData, pulEncryptedDataLen  );
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: bUpdate (continues a multiple-part encryption operation)
BOOL
CxEncrypt::bUpdate(
    CK_BYTE_PTR       pPart,              /* the plaintext data */
    CK_ULONG          ulPartLen,          /* plaintext data len */
    CK_BYTE_PTR       pEncryptedPart,     /* gets ciphertext */
    CK_ULONG_PTR      pulEncryptedPartLen /* gets c-text size */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_EncryptUpdate(_m_hSession, pPart, ulPartLen, pEncryptedPart, pulEncryptedPartLen);
    /*DEBUG*/xASSERT_MSG_RET(CKR_OK == _m_ulRes, CxUtils::sErrorStr(_m_ulRes).c_str(), FALSE);

    return TRUE;
} 
//---------------------------------------------------------------------------
//TODO: bFinal (finishes a multiple-part encryption operation)
BOOL
CxEncrypt::bFinal(
    CK_BYTE_PTR       pLastEncryptedPart,      /* last c-text */
    CK_ULONG_PTR      pulLastEncryptedPartLen  /* gets last size */
)
{
    /*DEBUG*/

    _m_ulRes = _m_pFunc->C_EncryptFinal(_m_hSession, pLastEncryptedPart, pulLastEncryptedPartLen );
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
CxEncrypt::bMakeFile(const tString &csInFilePath, const tString &csOutFilePath, CK_MECHANISM_PTR pMechanism, CK_OBJECT_HANDLE hKey) {
    /*DEBUG*/xASSERT_RET(false == csInFilePath.empty(),  FALSE);
    /*DEBUG*/xASSERT_RET(false == csOutFilePath.empty(), FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != pMechanism,            FALSE);
    /*DEBUG*/xASSERT_RET(NULL  != hKey,                  FALSE);

    //-------------------------------------
    //������ ����� � �����
    uString usPlainData;        //����� ��� ����������
    
    {
        CxStdioFile sfFileRaw;
        
        _m_bRes = sfFileRaw.bOpen(csInFilePath, CxStdioFile::omBinRead);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _m_bRes = sfFileRaw.bRead(&usPlainData);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);
    }    
    
    //-------------------------------------
    //���������� ������
    ULONG ulPadSize  = 128 - 11;  //��� RSA 117-����.����� �����, 128-������������� ����
    ULONG ulOffset   = 0;
    ULONG ulOffset2  = 0;
    ULONG ulResEncryptSize = 0;

    ////CK_BYTE  usEncryptedData[128]  = {0}; 
    const ULONG          g_culBuffSize    = 8192 * 4;  //FIX_ME:
    uString  usEncryptedData;    usEncryptedData.resize(g_culBuffSize);     
    CK_ULONG usEncryptedDataSize = g_culBuffSize;
        
    {
        size_t uiDataSize = usPlainData.size();
        for (ulOffset = 0; ulOffset < uiDataSize; ulOffset += ulPadSize) {
            //������� ������
            if (ulPadSize > (uiDataSize - ulOffset)) {
                ulPadSize = uiDataSize - ulOffset;
            }

            _m_bRes = bInit(pMechanism, hKey);
            xCHECK_RET(FALSE == _m_bRes, FALSE);

            _m_bRes = bMake(&usPlainData[0] + ulOffset, ulPadSize, &usEncryptedData[0] + ulOffset2, &usEncryptedDataSize);
            xCHECK_RET(FALSE == _m_bRes, FALSE);
            
            ulOffset2 += usEncryptedDataSize;
        }
        ulResEncryptSize = ulOffset2;
    }
    usEncryptedData.resize(ulResEncryptSize);
    
    
    //-------------------------------------
    //������ ����-������ � ����
    {
        CxStdioFile sfFileEncrypt;

        _m_bRes = sfFileEncrypt.bOpen(csOutFilePath, CxStdioFile::omBinWrite);
        /*DEBUG*/xASSERT_RET(FALSE != _m_bRes, FALSE);

        _m_bRes = sfFileEncrypt.bWrite(usEncryptedData);
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
