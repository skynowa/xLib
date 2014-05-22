/**
 * \file   CxStackTrace.h
 * \brief  stackrace of the caller function
 */


#if xHAVE_EXECINFO
    #include <execinfo.h> // lib: -lexecinfo (FreeBSD)
#endif

#include <cxxabi.h>


xNAMESPACE_BEGIN2(xlib, debug)

/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline void_t
CxStackTrace::_get_impl(
    std::vector<std::vec_tstring_t> *a_stack
) const
{
    xCHECK_DO(a_stack == xPTR_NULL, return);

    std::vector<std::vec_tstring_t> stack;
    std::ctstring_t                 dataNotFound = xT("[???]");

#if xHAVE_EXECINFO
    void_t *stackBuff[xSTACK_TRACE_FRAMES_MAX] = {0};

    int_t framesNum = ::backtrace(stackBuff, xSTACK_TRACE_FRAMES_MAX);
    xCHECK_DO(framesNum <= 0, return);

    tchar_t **symbols = ::backtrace_symbols(stackBuff, framesNum);
    xCHECK_DO(symbols == xPTR_NULL, return);

    for (int_t i = ::skipFramesNum; i < framesNum; ++ i) {
        std::tstring_t modulePath;
        std::tstring_t filePath;
        std::tstring_t fileLine;
        std::tstring_t byteOffset;
        std::tstring_t functionName;

        Dl_info dlinfo;  xSTRUCT_ZERO(dlinfo);

        int_t iRv = ::dladdr(stackBuff[i], &dlinfo);
        if (iRv == 0) {
            modulePath   = (dlinfo.dli_fname == xPTR_NULL) ? dataNotFound : dlinfo.dli_fname;
            filePath     = dataNotFound;
            fileLine     = dataNotFound;
            byteOffset   = CxString::format(xT("%p"), ptrdiff_t(xPTR_NULL));
            functionName = (symbols[i] == xPTR_NULL) ? dataNotFound : symbols[i];
        } else {
            ctchar_t *symbolName = xPTR_NULL;
            int_t     status     = - 1;

            tchar_t *demangleName = abi::__cxa_demangle(dlinfo.dli_sname, xPTR_NULL, xPTR_NULL, &status);
            if (demangleName != xPTR_NULL && status == 0) {
                symbolName = demangleName;
            } else {
                symbolName = dlinfo.dli_sname;
            }


            std::tstring_t _filePath;
            std::tstring_t _functionName;
            ulong_t        _sourceLine = 0U;

            _addr2Line(dlinfo.dli_saddr, &_filePath, &_functionName, &_sourceLine);
            xUNUSED(_functionName);

            modulePath   = (dlinfo.dli_fname == xPTR_NULL) ? dataNotFound : dlinfo.dli_fname;
            filePath     = _filePath.empty()          ? dataNotFound : _filePath;
            fileLine     = CxString::cast(_sourceLine);
            byteOffset   = CxString::format(xT("%p"), ptrdiff_t(dlinfo.dli_saddr));
            functionName = (symbolName == xPTR_NULL) ? dataNotFound : symbolName;

            xBUFF_FREE(demangleName);
        }

        // swap file paths
        if (_isWrapFilePaths) {
            modulePath = CxPath(modulePath).fileName();
            filePath   = CxPath(filePath).fileName();
        }

        // disable function params
        if (_isFuncParamsDisable) {
            std::csize_t pos1 = functionName.find(xT("("));
            std::csize_t pos2 = functionName.find(xT(")"));

            if (pos1 != std::tstring_t::npos && pos2 != std::tstring_t::npos) {
                _xVERIFY(pos1 < pos2);

                functionName = functionName.substr(0, pos1 + 1) + functionName.substr(pos2);
            }
        }

        // out
        {
            std::vec_tstring_t stackLine;
            stackLine.push_back(modulePath);
            stackLine.push_back(filePath);
            stackLine.push_back(fileLine);
            stackLine.push_back(byteOffset);
            stackLine.push_back(functionName);

            stack.push_back(stackLine);
        }
    } // for
#else
    #pragma message("xLib: CxStackTrace::_get() - n/a")
#endif // xHAVE_EXECINFO

    // out
    a_stack->swap(stack);
}
//-------------------------------------------------------------------------------------------------
/* static */
inline void_t
CxStackTrace::_addr2Line(
    cvoid_t        *a_symbolAddress,
    std::tstring_t *a_filePath,
    std::tstring_t *a_functionName,
    ulong_t        *a_sourceLine
)
{
    tchar_t cmdLine[1024 + 1] = {0};

#if xHAVE_ADDR2LINE
   /**
    * MAN: addr2line
    *   @<file>                Read options from <file>
    *   -b --target=<bfdname>  Set the binary file format
    *   -e --exe=<executable>  Set the input file name (default is a.out)
    *   -i --inlines           Unwind inlined functions
    *   -j --section=<name>    Read section-relative offsets instead of addresses
    *   -s --basenames         Strip directory names
    *   -f --functions         Show function names
    *   -C --demangle[=style]  Demangle function names
    *   -h --help              Display this information
    *   -v --version           Display the program's version
    */

    snprintf(cmdLine, xARRAY_SIZE(cmdLine) - 1,
        /* xT("addr2line -C -e %s -f -i %lx") */
        xT("addr2line -C -e %s -f %lx"),
        CxPath::exe().c_str(), reinterpret_cast<ptrdiff_t>(a_symbolAddress));

    FILE *file = ::popen(cmdLine, xT("r"));
    _xVERIFY(file != xPTR_NULL);

    // get function name
    {
        tchar_t buff[1024 + 1] = {0};

        ctchar_t *functionName = std::fgets(buff, static_cast<int_t>( xARRAY_SIZE(buff) ), file);
        _xVERIFY(functionName != xPTR_NULL);

        a_functionName->assign(functionName);
    }

    // get file and line
    {
        tchar_t buff[1024 + 1] = {0};

        ctchar_t *fileAndLine = std::fgets(buff, static_cast<int_t>( xARRAY_SIZE(buff) ), file);
        _xVERIFY(fileAndLine != xPTR_NULL);

       /**
        * Parse that variants of fileAndLine string:
        *   - /home/skynowa/Projects/xLib/Build/Debug/../../../../Tests/Source/./Test.inl:108
        *   - ??:0
        */
        std::vec_tstring_t line;

        CxString::split(fileAndLine, xT(":"), &line);
        _xVERIFY(line.size() == 2U);

        // out
        _xVERIFY(std::feof(file) == 0);

        *a_filePath   = line.at(0);
        *a_sourceLine = CxString::cast<ulong_t>( line.at(1) );
    }

    int_t iRv = ::pclose(file);   file = xPTR_NULL;
    _xVERIFY(iRv != - 1);
#else
    *a_filePath     = CxConst::strUnknown();
    *a_functionName = CxConst::strUnknown();
    *a_sourceLine   = CxConst::strUnknown();
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
