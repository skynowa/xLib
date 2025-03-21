/**
 * \file  StackTrace_win.inl
 * \brief Stackrace of the caller function
 */


namespace xl::debug
{

/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
StackTrace::_get_impl(
    std::vector<std::vec_tstring_t> *out_stack
) const
{
    xCHECK_DO(out_stack == nullptr, return);

    std::vector<std::vec_tstring_t> stack;
    std::ctstring_t                 dataNotFound = xT("[???]");

#if   xCOMPILER_MINGW
    // TODO: [skynowa] StackTrace::_get()
#elif xCOMPILER_MS
    void_t      *stackBuff[_framesMax + 1] {};
    SYMBOL_INFO *symbol                    {};
    HANDLE       process                   {};

    process = ::GetCurrentProcess();

    BOOL blRv = ::SymInitialize(process, nullptr, TRUE);
    xCHECK_DO(blRv == FALSE, return);

    ushort_t framesNum = ::CaptureStackBackTrace(0UL, _framesMax, stackBuff, nullptr);
    xCHECK_DO(framesNum == 0U, return);

    symbol = new (std::nothrow) SYMBOL_INFO[sizeof(SYMBOL_INFO) + (255UL + 1) * sizeof(tchar_t)];
    xSTD_VERIFY(symbol != nullptr);
    symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
    symbol->MaxNameLen   = 255UL;

    for (int_t i = _data.skipFramesNum; i < framesNum; ++ i) {
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
                byteOffset   = Format::str(xT("{}"), reinterpret_cast<void_t *>(symbol->Address));
                functionName = xA2T( xl::demangleName(symbol->Name) );
            }
        }

        // swap file paths
        if (_data.isWrapFilePaths) {
            _wrapFilePaths(&modulePath, &filePath);
        }

        // disable function params
        if (_data.isFuncArgsDisable) {
        	_funcArgsDisable(&functionName);
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

    delete[] symbol;    // TODO: delete - review

    (void_t)::SymCleanup(process); process = nullptr;
#endif

    // out
    out_stack->swap(stack);
}
//-------------------------------------------------------------------------------------------------

} // namespace
