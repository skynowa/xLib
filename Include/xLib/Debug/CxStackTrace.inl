/**
 * \file   CxStackTrace.h
 * \brief  Print a demangled stack backtrace of the caller function to FILE* out
 */


#include <xLib/Core/CxConst.h>
#include <xLib/Core/CxString.h>
#include <xLib/Core/CxUtils.h>
#include <xLib/Filesystem/CxPath.h>
#include <xLib/Log/CxTracer.h>
#include <xLib/Debug/CxStdDebug.h>

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW
        // TODO:
    #elif xCOMPILER_MS || xCOMPILER_CODEGEAR
        #ifdef xUNICODE
            #define DBGHELP_TRANSLATE_TCHAR 1
        #endif

        #include <DbgHelp.h>
        #pragma comment(lib, "DbgHelp.Lib")
    #endif
#elif xOS_ENV_UNIX
    #if   xOS_LINUX
        #include <execinfo.h>
    #elif xOS_FREEBSD
        #include "CxExecInfo.h" // lib: -lexecinfo (FreeBSD)
    #endif

    #include <cxxabi.h>
#elif xOS_ENV_MAC
    #include <execinfo.h>   // lib: -lexecinfo
    #include <cxxabi.h>
#endif


xNAMESPACE_BEGIN(NxLib)

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline
CxStackTrace::CxStackTrace(
    std::ctstring_t &a_linePrefix,         /* = xT("\t") */
    std::ctstring_t &a_elementSeparator,   /* = xT("  ") */
    std::ctstring_t &a_lineSeparator,      /* = xT("\n") */
    cbool_t         &a_isWrapFilePaths,    /* = true */
    cbool_t         &a_isFuncParamsDisable /* = true */
) :
    _linePrefix         (a_linePrefix),
    _elementSeparator   (a_elementSeparator),
    _lineSeparator      (a_lineSeparator),
    _isWrapFilePaths    (a_isWrapFilePaths),
    _isFuncParamsDisable(a_isFuncParamsDisable)
{
}
//-------------------------------------------------------------------------------------------------
inline void_t
CxStackTrace::get(
    std::vector<std::vec_tstring_t> *a_stack
) const
{
    xCHECK_DO(NULL == a_stack, return);

    std::vector<std::vec_tstring_t> stack;
    std::ctstring_t                 dataNotFound = xT("[???]");

   /**
    * Skip 2 first elements of a real stack - it's a class internals:
    *   0  xLib_test  ??  0  0x46d314  NxLib::CxStackTrace::get() const
    *   1  xLib_test  ??  0  0x46e090  NxLib::CxStackTrace::toString()
    */
    std::csize_t posStackStart = 2;

#if   xOS_ENV_WIN
    #if   xCOMPILER_MINGW
        // TODO: CxStackTrace::get
    #elif xCOMPILER_MS || xCOMPILER_CODEGEAR
        void_t      *stackBuff[xSTACK_TRACE_FRAMES_MAX] = {0};
        SYMBOL_INFO *symbol                             = NULL;
        HANDLE       process                            = NULL;

        process = ::GetCurrentProcess();

        BOOL blRv = ::SymInitialize(process, NULL, TRUE);
        xCHECK_DO(FALSE == blRv, return);

        ushort_t framesNum = ::CaptureStackBackTrace(0UL, xSTACK_TRACE_FRAMES_MAX, stackBuff, NULL);
        xCHECK_DO(framesNum == 0U, return);

        symbol = new (std::nothrow) SYMBOL_INFO[sizeof(SYMBOL_INFO) + (255UL + 1) * sizeof(tchar_t)];
        xSTD_VERIFY(NULL != symbol);
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen   = 255UL;

        for (ushort_t i = 1U + posStackStart; i < framesNum; ++ i) {
            int_t          stackLineNum = 0;
            std::tstring_t modulePath;
            std::tstring_t filePath;
            std::tstring_t fileLine;
            std::tstring_t byteOffset;
            std::tstring_t functionName;

            // stackLineNum
            {
                stackLineNum = i;
            }

            // modulePath
            {
                IMAGEHLP_MODULE64 miModuleInfo = {0};
                miModuleInfo.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

                blRv = ::SymGetModuleInfo64(process, reinterpret_cast<DWORD64>( stackBuff[i] ),
                    &miModuleInfo);
                if (FALSE == blRv) {
                    modulePath = dataNotFound;
                } else {
                    modulePath = miModuleInfo.ImageName;
                }
            }

            // filePath, fileLine
            {
                DWORD           displacement = 0UL;
                IMAGEHLP_LINE64 imagehlpLine = {0};
                imagehlpLine.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

                blRv = ::SymGetLineFromAddr64(process, reinterpret_cast<DWORD64>( stackBuff[i] ),
                    &displacement, &imagehlpLine);
                if (FALSE == blRv) {
                    filePath = dataNotFound;
                    fileLine = dataNotFound;
                } else {
                    filePath = imagehlpLine.FileName;
                    fileLine = CxString::cast(imagehlpLine.LineNumber);
                }
            }

            // stackLineNum, byteOffset, functionName
            {
                blRv = ::SymFromAddr(process, reinterpret_cast<DWORD64>( stackBuff[i] ), NULL,
                    symbol);
                if (FALSE == blRv) {
                    byteOffset   = CxString::format(xT("%p"), ptrdiff_t(NULL));
                    functionName = dataNotFound;
                } else {
                    byteOffset   = CxString::format(xT("%p"), static_cast<ptrdiff_t>(symbol->Address));
                    functionName = std::tstring_t(symbol->Name);
                }
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

                if (std::tstring_t::npos != pos1 && std::tstring_t::npos != pos2) {
                    xSTD_VERIFY(pos1 < pos2);

                    functionName = functionName.substr(0, pos1 + 1) + functionName.substr(pos2);
                }
            }

            // out
            {
                std::vec_tstring_t stackLine;

                stackLine.push_back( CxString::cast(stackLineNum) );
                stackLine.push_back(modulePath);
                stackLine.push_back(filePath);
                stackLine.push_back(fileLine);
                stackLine.push_back(byteOffset);
                stackLine.push_back(functionName);

                stack.push_back(stackLine);
            }
        }

        xARRAY_DELETE(symbol);

        (void_t)::SymCleanup(process); process = NULL;
    #endif
#elif xOS_ENV_UNIX
    void_t *stackBuff[xSTACK_TRACE_FRAMES_MAX] = {0};

    int_t framesNum = ::backtrace(stackBuff, xSTACK_TRACE_FRAMES_MAX);
    xCHECK_DO(framesNum <= 0, return);

    tchar_t **symbols = ::backtrace_symbols(stackBuff, framesNum);
    xCHECK_DO(NULL == symbols, return);

    for (int_t i = 0 + posStackStart; i < framesNum; ++ i) {
        int_t          stackLineNum = 0;
        std::tstring_t modulePath;
        std::tstring_t filePath;
        std::tstring_t fileLine;
        std::tstring_t byteOffset;
        std::tstring_t functionName;

        Dl_info dlinfo;  xSTRUCT_ZERO(dlinfo);

        int_t iRv = ::dladdr(stackBuff[i], &dlinfo);
        if (0 == iRv) {
            stackLineNum = i;
            modulePath   = (NULL == dlinfo.dli_fname) ? dataNotFound : dlinfo.dli_fname;
            filePath     = dataNotFound;
            fileLine     = dataNotFound;
            byteOffset   = CxString::format(xT("%p"), ptrdiff_t(NULL));
            functionName = (NULL == symbols[i]) ? dataNotFound : symbols[i];
        } else {
            ctchar_t *symbolName = NULL;
            int_t     status     = - 1;

            tchar_t *demangleName = abi::__cxa_demangle(dlinfo.dli_sname, NULL, NULL, &status);
            if (NULL != demangleName && 0 == status) {
                symbolName = demangleName;
            } else {
                symbolName = dlinfo.dli_sname;
            }


            std::tstring_t _filePath;
            std::tstring_t _functionName;
            ulong_t        _sourceLine = 0U;

            _addr2Line(dlinfo.dli_saddr, &_filePath, &_functionName, &_sourceLine);
            xUNUSED(_functionName);

            stackLineNum = i;
            modulePath   = (NULL == dlinfo.dli_fname) ? dataNotFound : dlinfo.dli_fname;
            filePath     = _filePath.empty()          ? dataNotFound : _filePath;
            fileLine     = CxString::cast(_sourceLine);
            byteOffset   = CxString::format(xT("%p"), ptrdiff_t(dlinfo.dli_saddr));
            functionName = (NULL == symbolName) ? dataNotFound : symbolName;

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

            if (std::tstring_t::npos != pos1 && std::tstring_t::npos != pos2) {
                xSTD_VERIFY(pos1 < pos2);

                functionName = functionName.substr(0, pos1 + 1) + functionName.substr(pos2);
            }
        }

        // out
        {
            std::vec_tstring_t stackLine;

            stackLine.push_back( CxString::cast(stackLineNum) );
            stackLine.push_back(modulePath);
            stackLine.push_back(filePath);
            stackLine.push_back(fileLine);
            stackLine.push_back(byteOffset);
            stackLine.push_back(functionName);

            stack.push_back(stackLine);
        }
    } // for
#elif xOS_ENV_MAC
    xNOT_IMPLEMENTED
#endif

    a_stack->swap(stack);
}
//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxStackTrace::toString()
{
    std::tstring_t sRv;
    std::vector<std::vec_tstring_t> stack;

    get(&stack);
    sRv = _format(&stack);
    xCHECK_RET(sRv.empty(), CxConst::strUnknown());

    return sRv;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
inline std::tstring_t
CxStackTrace::_format(
    std::vector<std::vec_tstring_t> *a_stack
)
{
    xCHECK_RET(NULL == a_stack, std::tstring_t());

    std::tstring_t     sRv;
    std::csize_t       elementsNum = 6;
    std::vector<int_t> maxs(elementsNum, 0);

    // get elements max sizes
    for (size_t i = 0; i < elementsNum; ++ i) {
        xFOREACH_CONST(std::vector<std::vec_tstring_t>, it, *a_stack) {
            cint_t current = static_cast<int_t>( it->at(i).size() );
            xCHECK_DO(current > maxs[i], maxs[i] = current);
        }
    }

    // formatting
    xFOREACH_CONST(std::vector<std::vec_tstring_t>, it, *a_stack) {
        std::tstringstream_t stackLine;

        stackLine
            << _linePrefix
            << std::setw(maxs[0]) << std::right << it->at(0) << _elementSeparator
            << std::setw(maxs[1]) << std::left  << it->at(1) << _elementSeparator
            << std::setw(maxs[2]) << std::left  << it->at(2) << _elementSeparator
            << std::setw(maxs[3]) << std::right << it->at(3) << _elementSeparator
            << std::setw(maxs[4]) << std::left  << it->at(4) << _elementSeparator
            << std::setw(maxs[5]) << std::left  << it->at(5)
            << _lineSeparator;

        sRv.append(stackLine.str());
    }

    return sRv;
}
//-------------------------------------------------------------------------------------------------
#if !xOS_ENV_WIN

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
    xSTD_VERIFY(NULL != file);

    // get function name
    {
        tchar_t buff[1024 + 1] = {0};

        ctchar_t *functionName = std::fgets(buff, static_cast<int_t>( xARRAY_SIZE(buff) ), file);
        xSTD_VERIFY(NULL != functionName);

        (*a_functionName).assign(functionName);
    }

    // get file and line
    {
        tchar_t buff[1024 + 1] = {0};

        ctchar_t *fileAndLine = std::fgets(buff, static_cast<int_t>( xARRAY_SIZE(buff) ), file);
        xSTD_VERIFY(NULL != fileAndLine);

       /**
        * Parse that variants of fileAndLine string:
        *   - /home/skynowa/Projects/xLib/Build/Debug/../../../../Tests/Source/./Test.cpp:108
        *   - ??:0
        */
        std::vec_tstring_t line;

        CxString::split(fileAndLine, xT(":"), &line);
        xSTD_VERIFY(2U == line.size());

        // out
        xSTD_VERIFY(0 == std::feof(file));

        *a_filePath   = line.at(0);
        *a_sourceLine = CxString::cast<ulong_t>( line.at(1) );
    }

    int_t iRv = ::pclose(file);   file = NULL;
    xSTD_VERIFY(- 1 != iRv);
}

#endif  // xOS_ENV_UNIX
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END(NxLib)
