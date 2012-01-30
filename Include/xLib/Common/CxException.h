/**
 * \file  CxException.h
 * \brief exception
 */


#ifndef xLib_Debug_CxExceptionH
#define xLib_Debug_CxExceptionH
//---------------------------------------------------------------------------
#include <xLib/Common/xCommon.h>
//---------------------------------------------------------------------------
xNAMESPACE_BEGIN(NxLib)

class CxException
    /// exception
{
    public:
                              CxException ();
            ///< constructor
        virtual              ~CxException ();
            ///< destructor

        const std::tstring_t &sGetWhat    () const;
            ///< get message
        template<class T>
        CxException &         operator << (const T &cMessageT);
            ///< put message

    private:
        std::tstring_t        _m_sMsg;
            ///< message
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxException.inl"
//---------------------------------------------------------------------------
#define xTHROW \
    throw CxException() << "";


#define xTRY try
    ///< like try

#define xCATCH_ALL \
    catch (const CxException &e) { \
        /*DEBUG*/xASSERT_MSG_RET(false, e.sGetWhat(), false); \
    } \
    catch (const std::exception &cexE) { \
        std::string asMsg = cexE.what(); \
                                         \
        /*DEBUG*/xASSERT_MSG_RET(false, xS2TS(asMsg), false); \
    } \
    catch (...) { \
        /*DEBUG*/xASSERT_MSG_RET(false, xT("unknown error"), false); \
    }
    ///< catch CxException, std::exception and all other exceptions
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxExceptionH
