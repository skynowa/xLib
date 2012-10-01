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
        virtual               ~CxException ();
            ///< destructor

        const std::tstring_t & sGetWhat    () const;
            ///< get message
        template<class T>
        CxException &          operator << (const T &cMessageT);
            ///< put message

    private:
        std::tstring_t         _m_sMessage;
            ///< message
};

xNAMESPACE_END(NxLib)
//---------------------------------------------------------------------------
#include "CxException.inl"
//---------------------------------------------------------------------------
#define xTHROW \
            throw CxException
        ///< like throw

#define xTRY \
            try
        ///< like try

#define xCATCH_ALL \
            catch (const CxException &exExp) {      \
                xTEST_MSG_FAIL(exExp.sGetWhat());   \
            }                                       \
            catch (const std::exception &cexExp) {  \
                std::string asMsg = cexExp.what();  \
                xTEST_FAIL(xS2TS(asMsg));           \
            }                                       \
            catch (...) {                           \
                xTEST_FAIL(xT("unknown error"));    \
            }
        ///< catch CxException, std::exception and all other exceptions
//---------------------------------------------------------------------------
#endif //xLib_Debug_CxExceptionH
