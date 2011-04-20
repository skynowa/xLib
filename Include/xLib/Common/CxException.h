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
class CxException : public std::exception {
    private:
        tString             _m_sMsg;

    public:
                            CxException ();
        virtual            ~CxException () throw();

        virtual const char *what        () const throw();

        template<class T>
        CxException &       operator << (const T &cValueT) {
            _m_sMsg.assign( CxString::lexical_cast(cValueT) );

            return *this;
        }
};
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxExceptionH
