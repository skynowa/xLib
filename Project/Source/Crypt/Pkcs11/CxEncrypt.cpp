/**
 * \file  CxEncrypt.cpp
 * \brief Pkcs11 encrypt
 */


#include <xLib/Crypt/Pkcs11/CxEncrypt.h>

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
CxEncrypt::CxEncrypt(
    const CxPkcs11  &a_cPkcs11,
    const CxSession &a_cSession
) :
    _m_pFunc   (a_cPkcs11.funcList()),
    _m_hSession(a_cSession.handle())
{

}
//------------------------------------------------------------------------------
/* virtual */
CxEncrypt::~CxEncrypt() {

}
//------------------------------------------------------------------------------
void
CxEncrypt::init(
    CK_MECHANISM_PTR a_pMechanism,  ///< the encryption mechanism
    CK_OBJECT_HANDLE a_hKey         ///< handle of encryption key
)
{


    CK_RV ulRv = _m_pFunc->C_EncryptInit(_m_hSession, a_pMechanism, a_hKey);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void
CxEncrypt::make(
    CK_BYTE_PTR  a_pData,               ///< the plaintext data
    CK_ULONG     a_ulDataLen,           ///< bytes of plaintext
    CK_BYTE_PTR  a_pEncryptedData,      ///< gets ciphertext
    CK_ULONG_PTR a_pulEncryptedDataLen  ///< gets c-text size
)
{


    CK_RV ulRv = _m_pFunc->C_Encrypt(_m_hSession, a_pData, a_ulDataLen, a_pEncryptedData, a_pulEncryptedDataLen  );
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void
CxEncrypt::update(
    CK_BYTE_PTR  a_pPart,              ///< the plaintext data
    CK_ULONG     a_ulPartLen,          ///< plaintext data len
    CK_BYTE_PTR  a_pEncryptedPart,     ///< gets ciphertext
    CK_ULONG_PTR a_pulEncryptedPartLen ///< gets c-text size
)
{


    CK_RV ulRv = _m_pFunc->C_EncryptUpdate(_m_hSession, a_pPart, a_ulPartLen, a_pEncryptedPart, a_pulEncryptedPartLen);
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------
void
CxEncrypt::final(
    CK_BYTE_PTR  a_pLastEncryptedPart,      ///< last c-text
    CK_ULONG_PTR a_pulLastEncryptedPartLen  ///< gets last size
)
{


    CK_RV ulRv = _m_pFunc->C_EncryptFinal(_m_hSession, a_pLastEncryptedPart, a_pulLastEncryptedPartLen );
    xTEST_MSG_EQ(ulong_t(CKR_OK), ulRv, CxPkcs11::errorStr(ulRv));
}
//------------------------------------------------------------------------------


/*******************************************************************************
*    Public utils
*
*******************************************************************************/

//------------------------------------------------------------------------------
void
CxEncrypt::makeFile(
    const std::tstring_t &a_csInFilePath,
    const std::tstring_t &a_csOutFilePath,
    CK_MECHANISM_PTR      a_pMechanism,
    CK_OBJECT_HANDLE      a_hKey
)
{
    xTEST_EQ(false, a_csInFilePath.empty());
    xTEST_EQ(false, a_csOutFilePath.empty());
    xTEST_PTR(a_pMechanism);
    xTEST_DIFF(0UL, a_hKey);

    //-------------------------------------
    //������ ����� � �����
    std::ustring_t usPlainData;

    {
        CxFile sfFileRaw;

        sfFileRaw.create(a_csInFilePath, CxFile::omBinRead, true);
        sfFileRaw.read(&usPlainData);
    }

    //-------------------------------------
    //���������� ������
    ulong_t ulPadSize  = 128 - 11;  //��� RSA 117-����.����� �����, 128-������������� ����
    ulong_t ulOffset   = 0;
    ulong_t ulOffset2  = 0;
    ulong_t ulResEncryptSize = 0;

    ////CK_BYTE  usEncryptedData[128]  = {0};
    culong_t          g_culBuffSize    = 8192 * 4;  //FIX_ME:
    std::ustring_t  usEncryptedData;    usEncryptedData.resize(g_culBuffSize);
    CK_ULONG usEncryptedDataSize = g_culBuffSize;

    {
        ulong_t uiDataSize = static_cast<ulong_t>( usPlainData.size() );
        for (ulOffset = 0; ulOffset < uiDataSize; ulOffset += ulPadSize) {
            //������� ������
            if (ulPadSize > (uiDataSize - ulOffset)) {
                ulPadSize = uiDataSize - ulOffset;
            }

            init(a_pMechanism, a_hKey);
            make(&usPlainData[0] + ulOffset, ulPadSize, &usEncryptedData[0] + ulOffset2, &usEncryptedDataSize);

            ulOffset2 += usEncryptedDataSize;
        }
        ulResEncryptSize = ulOffset2;
    }
    usEncryptedData.resize(ulResEncryptSize);


    //-------------------------------------
    //������ ����-������ � ����
    {
        CxFile sfFileEncrypt;

        sfFileEncrypt.create(a_csOutFilePath, CxFile::omBinWrite, true);
        sfFileEncrypt.write(usEncryptedData);
    }
}
//------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)

#endif
