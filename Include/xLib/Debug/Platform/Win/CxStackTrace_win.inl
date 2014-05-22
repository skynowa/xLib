/**
 * \file   CxStackTrace.h
 * \brief  stackrace of the caller function
 */


#if   xCOMPILER_MINGW
    // TODO: CxStackTrace - includes
#elif xCOMPILER_MS || xCOMPILER_CODEGEAR
    #ifdef xUNICODE
        #define DBGHELP_TRANSLATE_TCHAR 1
    #endif

    #include <DbgHelp.h>
    #pragma comment(lib, "DbgHelp.Lib")
#endif


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

#if   xCOMPILER_MINGW
    // TODO: CxStackTrace::_get()
#elif xCOMPILER_MS || xCOMPILER_CODEGEAR
    void_t      *stackBuff[xSTACK_TRACE_FRAMES_MAX] = {0};
    SYMBOL_INFO *symbol                             = xPTR_NULL;
    HANDLE       process                            = xPTR_NULL;

    process = ::GetCurrentProcess();

    BOOL blRv = ::SymInitialize(process, xPTR_NULL, TRUE);
    xCHECK_DO(blRv == FALSE, return);

    ushort_t framesNum = ::CaptureStackBackTrace(0UL, xSTACK_TRACE_FRAMES_MAX, stackBuff, xPTR_NULL);
    xCHECK_DO(framesNum == 0U, return);

    symbol = new (std::nothrow) SYMBOL_INFO[sizeof(SYMBOL_INFO) + (255UL + 1) * sizeof(tchar_t)];
    _xVERIFY(symbol != xPTR_NULL);
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen   = 255UL;

    for (ushort_t i = ::skipFramesNum; i < framesNum; ++ i) {
        std::tstring_t modulePath;
        std::tstring_t filePath;
        std::tstring_t fileLine;
        std::tstring_t byteOffset;
        std::tstring_t functionName;

        // modulePath
        {
            IMAGEHLP_MODULE64 miModuleInfo = {0};
            miModuleInfo.SizeOfStruct = sizeof(IMAGEHLP_MODULE64);

            blRv = ::SymGetModuleInfo64(process, reinterpret_cast<DWORD64>( stackBuff[i] ),
                &miModuleInfo);
            if (blRv == FALSE) {
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
            if (blRv == FALSE) {
                filePath = dataNotFound;
                fileLine = dataNotFound;
            } else {
                filePath = imagehlpLine.FileName;
                fileLine = CxString::cast(imagehlpLine.LineNumber);
            }
        }

        // byteOffset, functionName
        {
            blRv = ::SymFromAddr(process, reinterpret_cast<DWORD64>( stackBuff[i] ), xPTR_NULL,
                symbol);
            if (blRv == FALSE) {
                byteOffset   = CxString::format(xT("%p"), ptrdiff_t(xPTR_NULL));
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
    }

    xARRAY_DELETE(symbol);

    (void_t)::SymCleanup(process); process = xPTR_NULL;
#endif

    // out
    a_stack->swap(stack);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xlib, debug)
