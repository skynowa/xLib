/****************************************************************************
* Class name:  CxException
* Description: exception
* File name:   CxException.h
* Author:      skynowa
* E-mail:      skynowa@gmail.com
* Created:     1 лют. 2011 11:13:48
*
*****************************************************************************/


#ifndef xLib_Debug_CxExceptionH
#define xLib_Debug_CxExceptionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxException :
    public std::exception

{
    public:
                           CxException  ();
        virtual           ~CxException  () throw();

        virtual const char* what() const throw();
        tString            sGetClassName() const throw();
        const tString &    sGetWhat     () const throw();
        const tString      sGetReport   ();

        template<class T>
        CxException &      operator <<  (const T &cValueT);

    private:
        tString            _m_sMsg;

};
//---------------------------------------------------------------------------
#include <Common/CxException.inl>
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxExceptionH
