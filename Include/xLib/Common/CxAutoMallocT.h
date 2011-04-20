/****************************************************************************
* Class name:  CxAutoMallocT
* Description: test CxAutoMallocT
* File name:   CxAutoMallocT.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     17.05.2009 17:20:09
*
*****************************************************************************/

/*
Usage:

    PSP_DEVICE_INTERFACE_DETAIL_DATA pData = (PSP_DEVICE_INTERFACE_DETAIL_DATA)malloc(ulBytesReturned);
    ...
    free(pData);

    CxAutoMallocT<PSP_DEVICE_INTERFACE_DETAIL_DATA> diddDeviceInterfaceDetailData((size_t)ulBytesReturned);
*/

#ifndef xLib_Common_CxMallocH
#define xLib_Common_CxMallocH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
template<class PtrT>
class CxAutoMallocT : public CxNonCopyable {
    public:
             CxAutoMallocT(const std::size_t cuiSize);
            ~CxAutoMallocT();

        PtrT pGetPtr      ();
            
    private:
        PtrT _m_pDataT;
};
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//DONE: CxAutoMallocT (construcor)
template<class PtrT>
CxAutoMallocT<PtrT>::CxAutoMallocT(const std::size_t cuiSize) :
    _m_pDataT(NULL)
{
    /*DEBUG*/xASSERT_DO(NULL == _m_pDataT, return);
    /*DEBUG*/// cuiSize - n/a

    _m_pDataT = static_cast<PtrT>( malloc(cuiSize) );
    /*DEBUG*/xASSERT(NULL != _m_pDataT);        //MessageBox(0, "Constructor", "", MB_OK);
}
//---------------------------------------------------------------------------
//DONE: ~CxAutoMallocT (destructor)
template<class PtrT>
CxAutoMallocT<PtrT>::~CxAutoMallocT() {
    /*DEBUG*/xASSERT_DO(NULL != _m_pDataT, return);

    if (NULL != _m_pDataT) {
        free(_m_pDataT);    
        _m_pDataT = NULL;                            //MessageBox(0, "Destructor", "", MB_OK);
    }
}
//---------------------------------------------------------------------------
//DONE: pGetPtr (get pointer)
template<class PtrT>
PtrT
CxAutoMallocT<PtrT>::pGetPtr() {
    /*DEBUG*/xASSERT_RET(NULL != _m_pDataT, NULL);

    return _m_pDataT; 
}
//---------------------------------------------------------------------------
#endif    //xLib_Common_CxMallocH
