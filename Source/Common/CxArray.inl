/****************************************************************************
* Class name:  CxArray
* Description: fixed-size array
* File name:   CxArray.cpp
* Compilers:   Visual C++ 2010 
* String type: Ansi, Unicode
* Libraries:   WinAPI, Stl, XLib
* Author:      Alca
* E-mail:      dr.web.agent@gmail.com
* Created:     28.03.2011 14:40:50
* Version:     1.0.0.0 Debug
*
*****************************************************************************/


/****************************************************************************
*    Public
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
//TODO: CxArray (constructor)
//template<class TypeT, std::size_t uiNumT>
//CxArray<TypeT, uiNumT>::CxArray(size_t uiSize) {
//    //vClear();
//}
////---------------------------------------------------------------------------
////TODO: ~CxArray (destructor)
///*virtual*/
//template<class TypeT, std::size_t uiNumT>
//CxArray<TypeT, uiNumT>::~CxArray() {
//
//}

////---------------------------------------------------------------------------
////DONE: operator[]
//template <class TypeT, std::size_t uiNumT>
//const TypeT &
//CxArray<TypeT, uiNumT>::operator[] (size_t uiIndex) const {
//    /*DEBUG*/xASSERT(uiIndex < uiNumT);
//
//    return tArray[uiIndex];
//}
////---------------------------------------------------------------------------
////DONE: operator[]
//template <class TypeT, std::size_t uiNumT>
//TypeT &
//CxArray<TypeT, uiNumT>::operator[] (size_t uiIndex) {
//    /*DEBUG*/xASSERT(uiIndex < uiNumT);
//
//    return tArray[uiIndex];
//}
////---------------------------------------------------------------------------
////DONE: uiGetSize (get size)
//template <class TypeT, std::size_t uiNumT>
//size_t
//CxArray<TypeT, uiNumT>::uiGetSize() {
//   /*DEBUG*/xASSERT_RET(xARRAY_SIZE(tArray) == uiNumT, 0);
//
//    return uiNumT;
//}
////---------------------------------------------------------------------------
////DONE: bClear (clear)
//template<class TypeT, std::size_t uiNumT>
//BOOL
//CxArray<TypeT, uiNumT>::bClear() {
//    /*DEBUG*/
//
//    VOID *pvRes = memset((VOID *)&tArray[0], 0, sizeof(tArray));
//    /*DEBUG*/xASSERT_RET(NULL != pvRes, FALSE);
//
//    return TRUE;
//}
//---------------------------------------------------------------------------






/****************************************************************************
*    Private
*                                                                            
*****************************************************************************/

//---------------------------------------------------------------------------
