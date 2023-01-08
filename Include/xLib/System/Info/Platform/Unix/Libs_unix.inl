/**
 * \file  Libs.inl
 * \brief system information
 *
 * \see   https://www.kernel.org/doc/Documentation/ABI/testing/sysfs-class-net
 */


namespace xl::system::info
{

//-------------------------------------------------------------------------------------------------
std::tstring_t
Libs::glibcVersion() const
{
    std::tstring_t version;
    {
    #if cmGNU_GET_LIBC_FOUND
        cchar_t *libc_version = ::gnu_get_libc_version();
        if (libc_version == nullptr) {
            version = Const::strUnknown();
        } else {
            version = xA2T(libc_version);
        }
    #else
        xBUILD_IMPL("Libs::glibcVersion()");
        version = Const::strUnknown();
    #endif
    }

    std::tstring_t release;
    {
    #if cmGNU_GET_LIBC_FOUND
        cchar_t *libc_release = ::gnu_get_libc_release();
        if (libc_release == nullptr) {
            release = Const::strUnknown();
        } else {
            release = xA2T(libc_release);
        }
    #else
        release = Const::strUnknown();
    #endif
    }

    std::ctstring_t sRv = version + Const::space() + release;

    return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
Libs::pthreadVersion() const
{
    std::tstring_t sRv;

#if cmCS_GNU_LIBPTHREAD_VERSION_FOUND
    std::string buff;

    std::size_t buffBytes;
    {
        buffBytes = ::confstr(_CS_GNU_LIBPTHREAD_VERSION, nullptr, 0);
        xCHECK_RET(buffBytes == 0, Const::strUnknown());

        buff.resize(buffBytes);
    }

    buffBytes = ::confstr(_CS_GNU_LIBPTHREAD_VERSION, &buff.at(0), buff.size());
    xCHECK_RET(buffBytes == 0, Const::strUnknown());

    // remove terminating null byte
    buff.resize(buffBytes - 1);

    sRv = xA2T(buff);
#else
    xBUILD_IMPL("Libs::pthreadVersion()");
    sRv = Const::strUnknown();
#endif

    return sRv;
}
//-------------------------------------------------------------------------------------------------

} // namespace
