/**
 * \file  StackTrace_unix.inl
 * \brief stackrace of the caller function
 */


#include <xLib/Core/FormatC.h>
#include <xLib/Fs/Path.h>

#if cmEXECINFO_FOUND
    #include <execinfo.h> // lib: -lexecinfo (FreeBSD)
#endif

#include <cxxabi.h>


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

#if cmEXECINFO_FOUND
    std::ctstring_t dataNotFound = xT("[???]");

    void_t *stackBuff[_framesMax + 1] {};

    int_t framesNum = ::backtrace(stackBuff, static_cast<int_t>(_framesMax));
    xCHECK_DO(framesNum <= 0, return);

    char **symbols = ::backtrace_symbols(stackBuff, framesNum);
    xCHECK_DO(symbols == nullptr, return);

    for (int_t i = _option.skipFramesNum; i < framesNum; ++ i) {
        const char *it_symbol = symbols[i];

        std::tstring_t modulePath;
        std::tstring_t filePath;
        std::tstring_t fileLine;
        std::tstring_t byteOffset;
        std::tstring_t functionName;

        Dl_info dlinfo {};
        int_t iRv = ::dladdr(stackBuff[i], &dlinfo);
        if (iRv == 0) {
            modulePath   = dataNotFound;
            filePath     = dataNotFound;
            fileLine     = dataNotFound;
            byteOffset   = Format::str(xT("{}"), static_cast<void_t *>(nullptr));
            functionName = (it_symbol == nullptr) ? dataNotFound : xA2T(it_symbol);
        } else {
			struct Addr2LineData
			{
				std::tstring_t filePath;
				std::tstring_t functionName;
				std::tstring_t sourceLine;
			} data;

			_addr2Line(dlinfo.dli_saddr, &data.filePath, &data.functionName, &data.sourceLine);
			xUNUSED(data.functionName);

			modulePath   = (dlinfo.dli_fname == nullptr) ? dataNotFound : xA2T(dlinfo.dli_fname);
			filePath     = data.filePath;
			fileLine     = data.sourceLine;
			byteOffset   = Format::str(xT("{}"), static_cast<void_t *>(dlinfo.dli_saddr));
			functionName = xA2T( xl::demangleName(dlinfo.dli_sname) );

			if (0) {
				LogCout() << "-----------------------------------";
				LogCout() << xTRACE_VAR(it_symbol);
				LogCout() << xTRACE_VAR(dlinfo.dli_saddr);
				LogCout() << xTRACE_VAR(functionName);
				LogCout() << "";
				LogCout() << xTRACE_VAR(data.filePath);
				LogCout() << xTRACE_VAR(data.functionName);
				LogCout() << xTRACE_VAR(data.sourceLine);
				LogCout() << "-----------------------------------\n";
			}
        }

        // swap file paths
        if (_option.isWrapFilePaths) {
            _wrapFilePaths(&modulePath, &filePath);
        }

        // disable function params
        if (_option.isFuncArgsDisable) {
            _funcArgsDisable(&functionName);
        }

        // out
        {
            std::cvec_tstring_t stackLine
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

    Utils::bufferFreeT(symbols);
#else
    xBUILD_IMPL("StackTrace::_get()");
#endif // cmEXECINFO_FOUND

    // out
    out_stack->swap(stack);
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
StackTrace::_addr2Line(
    cptr_cvoid_t    a_symbolAddress,
    std::tstring_t *out_filePath,
    std::tstring_t *out_functionName,
    std::tstring_t *out_sourceLine
)
{
/**
 * TODO
 *
 * [ ] Process::execute()
 * [ ] SourceInfo
 */

#if cmADDR2LINE_FOUND || cmATOS_FOUND
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

    constexpr int_t buffSize {1024};

    std::tstring_t cmdLine;
	{
	#if   cmADDR2LINE_FOUND
		cmdLine = Format::str(xT("{} -e {} -f -C {}"), cmADDR2LINE_FILE_PATH, Path::exe().str(), a_symbolAddress);
	#elif cmATOS_FOUND
		cmdLine = FormatC::str(xT("%s -o %.256s %p"), cmATOS_FILE_PATH, Path::exe().str().c_str(), a_symbolAddress);
	#endif

		/// LogCout() << xTRACE_VAR(cmdLine);
	}

	auto pipe = autoPipe(cmdLine, "r");
	xTEST_PTR(pipe.get());

    // [out] out_functionName
    {
        tchar_t buff[buffSize + 1] {};
        cptr_ctchar_t functionName = xTFGETS(buff, buffSize, pipe.get());

		if (functionName == nullptr) {
			*out_functionName = Const::strUnknown();
		} else {
			// Fix EOL
			*out_functionName = String::removeEol(functionName);
		}
    }

    // [out] out_filePath, out_sourceLine
    {
        tchar_t buff[buffSize + 1] {};
        cptr_ctchar_t fileAndLine = xTFGETS(buff, buffSize, pipe.get());

		if (fileAndLine == nullptr) {
			*out_filePath   = Const::strUnknown();
			*out_sourceLine = Const::strUnknown();
		} else {
		   /**
			* Parse that variants of fileAndLine string:
			*   - /home/skynowa/Projects/xLib/Build/Debug/../../../../Tests/Source/./Test.inl:108
			*   - ??:0
			*/
			std::vec_tstring_t line;
			String::split(fileAndLine, xT(":"), &line);
			xSTD_VERIFY(line.size() == 2U);

			// out
			xSTD_VERIFY(std::feof(pipe.get()) == 0);

			*out_filePath   = line.at(0);
			*out_sourceLine = String::removeEol(line.at(1));
		}
    }
#else
    xUNUSED(a_symbolAddress);

    *out_filePath     = Const::strUnknown();
    *out_functionName = Const::strUnknown();
    *out_sourceLine   = Const::strUnknown();
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace
