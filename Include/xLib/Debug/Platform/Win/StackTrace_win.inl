/**
 * \file   StackTrace.h
 * \brief  stackrace of the caller function
 */


#if   xCOMPILER_MINGW
    // TODO: [skynowa] StackTrace - includes
#elif xCOMPILER_MS
    #ifdef xUNICODE
        #define DBGHELP_TRANSLATE_TCHAR 1
    #endif

    #include <DbgHelp.h>
#endif


namespace xl::debug
{

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
    xCHECK_DO(a_stack == nullptr, return);

    std::vector<std::vec_tstring_t> stack;
    std::ctstring_t                 dataNotFound = xT("[???]");

#if   xCOMPILER_MINGW
    // TODO: [skynowa] StackTrace::_get()
#elif xCOMPILER_MS
    void_t      *stackBuff[_frames_max + 1] {};
    SYMBOL_INFO *symbol                     {};
    HANDLE       process                    {};

    process = ::GetCurrentProcess();

    BOOL blRv = ::SymInitialize(process, nullptr, TRUE);
    xCHECK_DO(blRv == FALSE, return);

    ushort_t framesNum = ::CaptureStackBackTrace(0UL, _frames_max, stackBuff, nullptr);
    xCHECK_DO(framesNum == 0U, return);

    symbol = new (std::nothrow) SYMBOL_INFO[sizeof(SYMBOL_INFO) + (255UL + 1) * sizeof(tchar_t)];
    STD_VERIFY(symbol != nullptr);
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen   = 255UL;

    for (ushort_t i = _data._skipFramesNum; i < framesNum; ++ i) {
        std::tstring_t modulePath;
        std::tstring_t filePath;
        std::tstring_t fileLine;
        std::tstring_t byteOffset;
        std::tstring_t functionName;

        // modulePath
        {
            IMAGEHLP_MODULE64 miModuleInfo {};
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
            DWORD           displacement {};
            IMAGEHLP_LINE64 imagehlpLine {};
            imagehlpLine.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

            blRv = ::SymGetLineFromAddr64(process, reinterpret_cast<DWORD64>( stackBuff[i] ),
                &displacement, &imagehlpLine);
            if (blRv == FALSE) {
                filePath = dataNotFound;
                fileLine = dataNotFound;
            } else {
                filePath = imagehlpLine.FileName;
                fileLine = String::cast(imagehlpLine.LineNumber);
            }
        }

        // byteOffset, functionName
        {
            blRv = ::SymFromAddr(process, reinterpret_cast<DWORD64>( stackBuff[i] ), nullptr,
                symbol);
            if (blRv == FALSE) {
                byteOffset   = Format::str(xT("{}"), static_cast<void_t *>(nullptr));
                functionName = dataNotFound;
            } else {
                byteOffset   = Format::str(xT("{}"), static_cast<void_t *>(symbol->Address));
                functionName = std::tstring_t(symbol->Name);
            }
        }

        // swap file paths
        if (_isWrapFilePaths) {
            modulePath = Path(modulePath).fileName();
            filePath   = Path(filePath).fileName();
        }

        // disable function params
        if (_isFuncParamsDisable) {
            std::csize_t pos1 = functionName.find(xT("("));
            std::csize_t pos2 = functionName.find(xT(")"));

            if (pos1 != std::tstring_t::npos && pos2 != std::tstring_t::npos) {
                STD_VERIFY(pos1 < pos2);

                functionName = functionName.substr(0, pos1 + 1) + functionName.substr(pos2);
            }
        }

        // out
        {
            std::vec_tstring_t stackLine
			{
				modulePath,
				filePath,
				fileLine,
				byteOffset,
				functionName
			};

            stack.push_back(stackLine);
        }
    } // for (framesNum)

    xARRAY_DELETE(symbol);

    (void_t)::SymCleanup(process); process = nullptr;
#endif

    // out
    a_stack->swap(stack);
}
//-------------------------------------------------------------------------------------------------

} // namespace
