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
    std::vector<std::vec_tstring_t> *a_stack
) const
{
    xCHECK_DO(a_stack == nullptr, return);

    std::vector<std::vec_tstring_t> stack;
    std::ctstring_t                 dataNotFound = xT("[???]");

#if cmEXECINFO_FOUND
    void_t *stackBuff[_framesMax + 1] {};

    int_t framesNum = ::backtrace(stackBuff, static_cast<int_t>(_framesMax));
    xCHECK_DO(framesNum <= 0, return);

    char **symbols = ::backtrace_symbols(stackBuff, framesNum);
    xCHECK_DO(symbols == nullptr, return);

    for (int_t i = _data.skipFramesNum; i < framesNum; ++ i) {
        std::tstring_t modulePath;
        std::tstring_t filePath;
        std::tstring_t fileLine;
        std::tstring_t byteOffset;
        std::tstring_t functionName;

        Dl_info dlinfo {};

        int_t iRv = ::dladdr(stackBuff[i], &dlinfo);
        if (iRv == 0) {
            modulePath   = (dlinfo.dli_fname == nullptr) ? dataNotFound : xA2T(dlinfo.dli_fname);
            filePath     = dataNotFound;
            fileLine     = dataNotFound;
            byteOffset   = Format::str(xT("{}"), static_cast<void_t *>(nullptr));
            functionName = (symbols[i] == nullptr) ? dataNotFound : xA2T(symbols[i]);
        } else {
            const char *symbolName {};
            int_t       status     {};

            char *demangleName = abi::__cxa_demangle(dlinfo.dli_sname, nullptr, nullptr, &status);
            if (demangleName != nullptr &&
                status == 0)
            {
                symbolName = demangleName;
            } else {
                symbolName = dlinfo.dli_sname;
            }

		#if 0
			Cout() << xTRACE_VAR(status);
			Cout() << xTRACE_VAR(symbolName);
		#endif

            std::tstring_t _filePath;
            std::tstring_t _functionName;
            ulong_t        _sourceLine {};

            _addr2Line(dlinfo.dli_saddr, &_filePath, &_functionName, &_sourceLine);
            xUNUSED(_functionName);

		#if 0
			Cout() << xTRACE_VAR(dlinfo.dli_saddr);
			Cout() << xTRACE_VAR(_filePath);
			Cout() << xTRACE_VAR(_functionName);
			Cout() << xTRACE_VAR(_sourceLine);
		#endif

            modulePath   = (dlinfo.dli_fname == nullptr) ? dataNotFound : xA2T(dlinfo.dli_fname);
            filePath     = _filePath.empty()             ? dataNotFound : _filePath;
            fileLine     = String::cast(_sourceLine);
            byteOffset   = Format::str(xT("{}"), static_cast<void_t *>(dlinfo.dli_saddr));
            functionName = (symbolName == nullptr) ? dataNotFound : xA2T(symbolName);

            Utils::bufferFreeT(demangleName);
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

            if (pos1 != std::tstring_t::npos &&
                pos2 != std::tstring_t::npos)
            {
                xSTD_VERIFY(pos1 < pos2);

                functionName = functionName.substr(0, pos1 + 1) + functionName.substr(pos2);
            }
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
    std::tstring_t *out_filePath,
    std::tstring_t *out_functionName,
    ulong_t        *out_sourceLine
)
{
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

		/// Cout() << xTRACE_VAR(cmdLine);
	}

	auto pipe = autoPipe(cmdLine, "r");
	xTEST_PTR(pipe.get());

    // get function name
    {
        tchar_t buff[buffSize + 1] {};
        cptr_ctchar_t functionName = xTFGETS(buff, buffSize, pipe.get());

		if (functionName == nullptr) {
			out_functionName->assign( Const::strUnknown() );
		} else {
			out_functionName->assign(functionName);
		}
    }

    // get file and line
    {
        tchar_t buff[buffSize + 1] {};
        cptr_ctchar_t fileAndLine = xTFGETS(buff, buffSize, pipe.get());

		if (fileAndLine == nullptr) {
			*out_filePath   = Const::strUnknown();
			*out_sourceLine = 0UL;
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
			*out_sourceLine = String::cast<ulong_t>( line.at(1) );
		}
    }
#else
    xUNUSED(a_symbolAddress);

    *out_filePath     = Const::strUnknown();
    *out_functionName = Const::strUnknown();
    *out_sourceLine   = 0UL;
#endif
}
//-------------------------------------------------------------------------------------------------

} // namespace
