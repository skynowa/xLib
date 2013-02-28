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

/*******************************************************************************
*    public
*
*******************************************************************************/

//------------------------------------------------------------------------------
CxDecrypt::CxDecrypt(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.funcList()),
    _m_hSession(a_cSession.handle())
{

}
//------------------------------------------------------------------------------
/* virtual */
CxDecrypt::~CxDecrypt() {

}
//------------------------------------------------------------------------------
void
CxDecrypt::init(
    CK_MECHANISM_PTR a_pMechanism,  ///< the decryption mechanism
    CK_OBJECT_HANDLE a_hKey         ///< handle of decryption key
)
{


    CK_RV ulRv = _m_pFunc->C_DecryptInit(_m_hSession, a_pMechanism, a_hKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void
CxDecrypt::make(
    CK_BYTE_PTR  a_pEncryptedData,     ///< ciphertext
    CK_ULONG     a_ulEncryptedDataLen, ///< ciphertext length
    CK_BYTE_PTR  a_pData,              ///< gets plaintext
    CK_ULONG_PTR a_pulDataLen          ///< gets p-text size
)
{


    CK_RV ulRv = _m_pFunc->C_Decrypt(_m_hSession, a_pEncryptedData, a_ulEncryptedDataLen, a_pData, a_pulDataLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void
CxDecrypt::update(
    CK_BYTE_PTR  a_pEncryptedPart,      ///< encrypted data
    CK_ULONG     a_ulEncryptedPartLen,  ///< input length
    CK_BYTE_PTR  a_pPart,               ///< gets plaintext
    CK_ULONG_PTR a_pulPartLen           ///< p-text size
)
{


    CK_RV ulRv = _m_pFunc->C_DecryptUpdate(_m_hSession, a_pEncryptedPart, a_ulEncryptedPartLen, a_pPart, a_pulPartLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void
CxDecrypt::final(
    CK_BYTE_PTR  a_pLastPart,      ///< gets plaintext
    CK_ULONG_PTR a_pulLastPartLen  ///< p-text size
)
{


    CK_RV ulRv = _m_pFunc->C_DecryptFinal(_m_hSession, a_pLastPart, a_pulLastPartLen );
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void
CxDecrypt::digestUpdate(
    CK_BYTE_PTR  a_pEncryptedPart,      ///< ciphertext
    CK_ULONG     a_ulEncryptedPartLen,  ///< ciphertext length
    CK_BYTE_PTR  a_pPart,               ///< gets plaintext
    CK_ULONG_PTR a_pulPartLen           ///< gets plaintext len
)
{


    CK_RV ulRv = _m_pFunc->C_DecryptDigestUpdate(_m_hSession, a_pEncryptedPart, a_ulEncryptedPartLen, a_pPart, a_pulPartLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void
CxDecrypt::verifyUpdate(
    CK_BYTE_PTR  a_pEncryptedPart,      ///< ciphertext
    CK_ULONG     a_ulEncryptedPartLen,  ///< ciphertext length
    CK_BYTE_PTR  a_pPart,               ///< gets plaintext
    CK_ULONG_PTR a_pulPartLen           ///< gets p-text length
)
{


    CK_RV ulRv = _m_pFunc->C_DecryptVerifyUpdate(_m_hSession, a_pEncryptedPart, a_ulEncryptedPartLen, a_pPart, a_pulPartLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    Public utils
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CxDecrypt::makeFile(
    std::ctstring_t &a_csInFilePath,
    std::ctstring_t &a_csOutFilePath,
    CK_MECHANISM_PTR      a_pMechanism,
    CK_OBJECT_HANDLE      a_hKey
)
{
    xTEST_EQ(false, a_csInFilePath.empty());
    xTEST_EQ(false, a_csOutFilePath.empty());
    xTEST_PTR(a_pMechanism);
    xTEST_DIFF(0UL, a_hKey);

    //-------------------------------------
    //������ ����-����� � �����
    std::ustring_t usEncryptedData;

    {
        CxFile sfFileRaw;

        sfFileRaw.create(a_csInFilePath, CxFile::omBinRead, true);
        sfFileRaw.read(&usEncryptedData);
    }

    //-------------------------------------
    //������������ ������
    ulong_t ulPadSize        = 128;  //��� DES 64 ����
    ulong_t ulOffset         = 0;
    ulong_t ulOffset2        = 0;
    ulong_t ulResDecryptSize = 0;

    ////CK_BYTE  usDecryptedData[128]   = {0};
    culong_t  g_culBuffSize       = 8192 * 4;  //FIX_ME:
    std::ustring_t usDecryptedData;    usDecryptedData.resize(g_culBuffSize);
    CK_ULONG     usDecryptedDataSize = g_culBuffSize;

    {
        for (ulOffset = 0; ulOffset < usEncryptedData.size()/*ulResEncryptSize*//*usRawData.size()*/; ulOffset += ulPadSize) {
            init(a_pMechanism, a_hKey);
            make(&usEncryptedData[0] + ulOffset, ulPadSize, &usDecryptedData[0] + ulOffset2, &usDecryptedDataSize);

            ulOffset2 += usDecryptedDataSize;
        }
        ulResDecryptSize = ulOffset2;
    }
    usDecryptedData.resize(ulResDecryptSize/*usDecryptedDataSize*/);

    //-------------------------------------
    //check that we are back where we started
    ////xTEST_EQ(true, usRawData == usDecryptedData);
    ////xTEST_EQ(usRawData.size(), usDecryptedData.size());
    ////std::cout << &usDecryptedData[0] << std::endl;

    //-------------------------------------
    //������ ������ � ����
    {
        CxFile sfFileDecrypt;

        sfFileDecrypt.create(a_csOutFilePath, CxFile::omBinWrite, true);
        sfFileDecrypt.write(usDecryptedData);
    }
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
