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
class CxException {
    public:
                           CxException  ();
        virtual           ~CxException  ();

        const tString &    sGetWhat     () const;
        tString            sGetReport   ();

        template<class T>
        CxException &      operator <<  (const T &cMessageT);

    private:
        tString            _m_sMsg;

};
//---------------------------------------------------------------------------
#include <Common/CxException.inl>
//---------------------------------------------------------------------------
#define xTRY try

#define xCATCH_ALL \
    catch (const CxException &e) { \
        /*DEBUG*/xASSERT_MSG_RET(FALSE, e.sGetWhat(), FALSE); \
    } \
    catch (const std::exception &cexE) { \
        std::string asMsg = cexE.what(); \
                                         \
        /*DEBUG*/xASSERT_MSG_RET(FALSE, xS2TS(asMsg), FALSE); \
    } \
    catch (...) { \
        /*DEBUG*/xASSERT_MSG_RET(FALSE, xT("unknown error"), FALSE); \
    }
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxExceptionH
