/**
 * \file  CxException.h
 * \brief exception
 */


#ifndef xLib_Debug_CxExceptionH
#define xLib_Debug_CxExceptionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
class CxException {
    public:
                           CxException  ();
            ///< constructor
        virtual           ~CxException  ();
            ///< destructor

        const std::tstring &    sGetWhat     () const;
            ///< get message
        template<class T>
        CxException &      operator <<  (const T &cMessageT);
            ///< put message

    private:
        std::tstring            _m_sMsg;
            ///< message
};
//---------------------------------------------------------------------------
#include <Common/CxException.inl>
//---------------------------------------------------------------------------
#define xTRY try
    ///< like try

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
    ///< catch CxException, std::exception and all other exceptions
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxExceptionH
