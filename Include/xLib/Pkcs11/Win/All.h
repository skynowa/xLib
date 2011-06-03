/****************************************************************************
* Class name:  All
* Description: all Pkcs11 classes
* File name:   All.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     01.03.2010 12:56:53
*
*****************************************************************************/


#ifndef xLib_Pkcs11_AllH
#define xLib_Pkcs11_AllH
//---------------------------------------------------------------------------
#include <xLib/Pkcs11/Win/Common.h>

#include <xLib/Pkcs11/Win/CxUtils.h>
#include <xLib/Pkcs11/Win/CxPkcs11.h>
#include <xLib/Pkcs11/Win/CxFunction.h>
#include <xLib/Pkcs11/Win/CxSlot.h>
#include <xLib/Pkcs11/Win/CxSession.h>
#include <xLib/Pkcs11/Win/CxLogin.h>
#include <xLib/Pkcs11/Win/CxInfo.h>
#if xTODO
    #include <xLib/Pkcs11/Win/CxeTokenInfo.h>
#endif
#include <xLib/Pkcs11/Win/CxPin.h>
#include <xLib/Pkcs11/Win/CxMechanism.h>
#include <xLib/Pkcs11/Win/CxObject.h>
#include <xLib/Pkcs11/Win/CxKey.h>
#include <xLib/Pkcs11/Win/CxEncrypt.h>
#include <xLib/Pkcs11/Win/CxDecrypt.h>
#include <xLib/Pkcs11/Win/CxDigest.h>
#include <xLib/Pkcs11/Win/CxSign.h>
#include <xLib/Pkcs11/Win/CxVerify.h>
//---------------------------------------------------------------------------
#endif    //xLib_Pkcs11_AllH
