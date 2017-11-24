/**
 * \file   StackTrace.h
 * \brief  stackrace of the caller function
 */


#if cmEXECINFO_FOUND
    #include <execinfo.h> // lib: -lexecinfo (FreeBSD)
#endif

#include <cxxabi.h>


xNAMESPACE_BEGIN2(xl, debug)

/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
StackTrace::_get_impl(
    std::vector<std::vec_tstring_t> *a_stack
) const
{
    xCHECK_DO(a_stack == xPTR_NULL, return);

    std::vector<std::vec_tstring_t> stack;
    std::ctstring_t                 dataNotFound = xT("[???]");

#if cmEXECINFO_FOUND
    void_t *stackBuff[xSTACK_TRACE_FRAMES_MAX] = {0};

    int_t framesNum = ::backtrace(stackBuff, xSTACK_TRACE_FRAMES_MAX);
    xCHECK_DO(framesNum <= 0, return);

    char **symbols = ::backtrace_symbols(stackBuff, framesNum);
    xCHECK_DO(symbols == xPTR_NULL, return);

    for (int_t i = _data.skipFramesNum; i < framesNum; ++ i) {
        std::tstring_t modulePath;
        std::tstring_t filePath;
        std::tstring_t fileLine;
        std::tstring_t byteOffset;
        std::tstring_t functionName;

        Dl_info dlinfo;  xSTRUCT_ZERO(dlinfo);

        int_t iRv = ::dladdr(stackBuff[i], &dlinfo);
        if (iRv == 0) {
            modulePath   = (dlinfo.dli_fname == xPTR_NULL) ? dataNotFound : xA2T(dlinfo.dli_fname);
            filePath     = dataNotFound;
            fileLine     = dataNotFound;
            byteOffset   = Format::str(xT("{}"), static_cast<void_t *>(xPTR_NULL));
            functionName = (symbols[i] == xPTR_NULL) ? dataNotFound : xA2T(symbols[i]);
        } else {
            const char *symbolName = xPTR_NULL;
            int_t       status     = - 1;

            char *demangleName = abi::__cxa_demangle(dlinfo.dli_sname, xPTR_NULL, xPTR_NULL, &status);
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

            modulePath   = (dlinfo.dli_fname == xPTR_NULL) ? dataNotFound : xA2T(dlinfo.dli_fname);
            filePath     = _filePath.empty()               ? dataNotFound : _filePath;
            fileLine     = String::cast(_sourceLine);
            byteOffset   = Format::str(xT("{}"), static_cast<void_t *>(dlinfo.dli_saddr));
            functionName = (symbolName == xPTR_NULL) ? dataNotFound : xA2T(symbolName);

            xBUFF_FREE(demangleName);
        }

        // swap file paths
        if (_data.isWrapFilePaths) {
            modulePath = Path(modulePath).fileName();
            filePath   = Path(filePath).fileName();
        }

        // disable function params
        if (_data.isFuncParamsDisable) {
            std::csize_t pos1 = functionName.find(xT("("));
            std::csize_t pos2 = functionName.find(xT(")"));

            if (pos1 != std::tstring_t::npos && pos2 != std::tstring_t::npos) {
                STD_VERIFY(pos1 < pos2);

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
    xBUILD_IMPL("StackTrace::_get()");
#endif // cmEXECINFO_FOUND

    // out
    a_stack->swap(stack);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StackTrace::_addr2Line(
    cptr_cvoid_t    a_symbolAddress,
    std::tstring_t *a_filePath,
    std::tstring_t *a_functionName,
    ulong_t        *a_sourceLine
)
{
#if cmADDR2LINE_FOUND
   /**
    * FAQ: addr2line
    *
    * @<file>                Read options from <file>
    * -a --addresses         Show addresses
    * -b --target=<bfdname>  Set the binary file format
    * -e --exe=<executable>  Set the input file name (default is a.out)
    * -i --inlines           Unwind inlined functions
    * -j --section=<name>    Read section-relative offsets instead of addresses
    * -p --pretty-print      Make the output easier to read for humans
    * -s --basenames         Strip directory names
    * -f --functions         Show function names
    * -C --demangle[=style]  Demangle function names
    * -h --help              Display this information
    * -v --version           Display the program's version
    */

    std::ctstring_t cmdLine = Format::str(
        xT("{} -e {} -f -C {}"), cmADDR2LINE_FILE_PATH, Path::exe(), a_symbolAddress);

    // TODO: [apple]
    //// sprintf(addr2line_cmd,"atos -o %.256s %p", program_name, addr);

    FILE *file = ::popen(xT2A(cmdLine).c_str(), "r");
    STD_VERIFY(file != xPTR_NULL);

    // get function name
    {
        tchar_t buff[1024 + 1] = {0};

        cptr_ctchar_t functionName = xTFGETS(buff, static_cast<int_t>( xARRAY_SIZE(buff) ), file);
        STD_VERIFY(functionName != xPTR_NULL);

        a_functionName->assign(functionName);
    }

    // get file and line
    {
        tchar_t buff[1024 + 1] = {0};

        cptr_ctchar_t fileAndLine = xTFGETS(buff, static_cast<int_t>( xARRAY_SIZE(buff) ), file);
        STD_VERIFY(fileAndLine != xPTR_NULL);

       /**
        * Parse that variants of fileAndLine string:
        *   - /home/skynowa/Projects/xLib/Build/Debug/../../../../Tests/Source/./Test.inl:108
        *   - ??:0
        */
        std::vec_tstring_t line;

        String::split(fileAndLine, xT(":"), &line);
        STD_VERIFY(line.size() == 2U);

        // out
        STD_VERIFY(std::feof(file) == 0);

        *a_filePath   = line.at(0);
        *a_sourceLine = String::cast<ulong_t>( line.at(1) );
    }

    int_t iRv = ::pclose(file);   file = xPTR_NULL;
    STD_VERIFY(iRv != - 1);
#else
    xUNUSED(a_symbolAddress);

    *a_filePath     = Const::strUnknown();
    *a_functionName = Const::strUnknown();
    *a_sourceLine   = 0UL;
#endif
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, debug)
