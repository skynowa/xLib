/**
 * \file  Utils.inl
 * \brief functions like macros
 */


#include "Utils.h"

#if xENV_UNIX
	#include <xLib/Fs/FileInfo.h>
	#include <xLib/Fs/Path.h>
#endif

namespace xl::core
{

//-------------------------------------------------------------------------------------------------
#if xENV_UNIX

/* static */
std::tstring_t
Utils::readSymLink(
	std::ctstring_t &a_symLinkPath
)
{
    std::string asRv;

    bool_t bRv = FileInfo(a_symLinkPath).isExists();
    xCHECK_RET(!bRv, std::tstring_t());

    ssize_t readed {- 1};
    asRv.resize( Path::maxSize() );

    for ( ; ; ) {
        readed = ::readlink(xT2A(a_symLinkPath).c_str(), &asRv.at(0), asRv.size() *
            sizeof(std::string::value_type));
        xCHECK_DO(readed == ssize_t(- 1), break);	// TODO: test - add ??
        xCHECK_DO(asRv.size() * sizeof(std::string::value_type) > static_cast<size_t>(readed), break);

        asRv.resize(asRv.size() * 2);
    }

    asRv.resize( static_cast<std::size_t>(readed) );

    return xA2T(asRv);
}

#endif
//-------------------------------------------------------------------------------------------------

} // namespace
