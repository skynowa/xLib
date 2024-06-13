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
void *
parseSymbolOffset(
	char *frame
)
{
	char        *p_symbol {};
	std::size_t  nn_symbol {};
	char        *p_offset {};
	std::size_t  nn_offset {};

	// Read symbol and offset, for example:
	//      /tools/backtrace(foo+0x1820) [0x555555555820]
	for (char *p = frame; *p; ++ p) {
		if (*p == '(') {
			p_symbol = p + 1;
		}
		else if (*p == '+') {
			if (p_symbol) {
				nn_symbol = p - p_symbol;
			}

			p_offset = p + 1;
		}
		else if (*p == ')') {
			if (p_offset) {
				nn_offset = p - p_offset;
			}
		}
	}

	if (!nn_symbol &&
		!nn_offset)
	{
		return nullptr;
	}

	// Convert offset(0x1820) to pointer, such as 0x1820.
	char tmp[128] {};
	if (!nn_offset ||
		nn_offset >= sizeof(tmp))
	{
		return nullptr;
	}

	int r0 = EOF;
	void* offset {};
	tmp[nn_offset] = 0;
	if ((r0 = sscanf(strncpy(tmp, p_offset, nn_offset), "%p", &offset)) == EOF) {
		return nullptr;
	}

	// Covert symbol(foo) to offset, such as 0x2fba.
	if (!nn_symbol ||
		nn_symbol >= sizeof(tmp))
	{
		return offset;
	}

	void *object_file {};
	if ((object_file = ::dlopen(nullptr, RTLD_LAZY)) == nullptr) {
		return offset;
	}

	void *address {};
	tmp[nn_symbol] = 0;
	if ((address = ::dlsym(object_file, strncpy(tmp, p_symbol, nn_symbol))) == nullptr) {
		::dlclose(object_file);
		return offset;
	}

	Dl_info symbol_info {};
	if ((r0 = ::dladdr(address, &symbol_info)) == 0) {
		::dlclose(object_file);
		return offset;
	}

	::dlclose(object_file);

	return
		reinterpret_cast<void*>(
			reinterpret_cast<std::uintptr_t>(symbol_info.dli_saddr) -
			reinterpret_cast<std::uintptr_t>(symbol_info.dli_fbase) +
			reinterpret_cast<std::uintptr_t>(offset)
		);
}
//-------------------------------------------------------------------------------------------------
void_t
StackTrace::_get_impl(
    std::vector<std::vec_tstring_t> *out_stack
) const
{
    xCHECK_DO(out_stack == nullptr, return);

    std::vector<std::vec_tstring_t> stack;
    std::ctstring_t                 dataNotFound = xT("[???]");

#if cmEXECINFO_FOUND
    void_t *stackBuff[_framesMax + 1] {};

    int_t framesNum = ::backtrace(stackBuff, static_cast<int_t>(_framesMax));
    xCHECK_DO(framesNum <= 0, return);

    char **symbols = ::backtrace_symbols(stackBuff, framesNum);
    xCHECK_DO(symbols == nullptr, return);

    for (int_t i = _data.skipFramesNum; i < framesNum; ++ i) {
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
            const char *symbolName {};
            int_t       status     {-1};

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

		#define _xOPTION_ADDR2LINE 0

		#if _xOPTION_ADDR2LINE
			void *frame = ::parseSymbolOffset(it_symbol);

			std::tstring_t _filePath;
			std::tstring_t _functionName;
			ulong_t        _sourceLine {};
			{
				_addr2Line(dlinfo.dli_saddr, &_filePath, &_functionName, &_sourceLine);
				xUNUSED(_functionName);

			#if 1
				Cout() << xTRACE_VAR(it_symbol);
				Cout() << xTRACE_VAR(frame);
				Cout() << xTRACE_VAR(dlinfo.dli_saddr);
				Cout() << xTRACE_VAR(_filePath);
				Cout() << xTRACE_VAR_2(symbolName, _functionName);
				Cout() << xTRACE_VAR(_sourceLine);
				Cout() << "-----------------------------------";
			#endif
			}
		#endif

            modulePath   = (dlinfo.dli_fname == nullptr) ? dataNotFound : xA2T(dlinfo.dli_fname);
		#if _xOPTION_ADDR2LINE
			filePath     = _filePath.empty()             ? dataNotFound : _filePath;
			fileLine     = String::cast(_sourceLine);
		#endif
            byteOffset   = Format::str(xT("{}"), static_cast<void_t *>(dlinfo.dli_saddr));
            functionName = (symbolName == nullptr) ? dataNotFound : xA2T(symbolName);

            Utils::bufferFreeT(demangleName);
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

    Utils::bufferFreeT(symbols);

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
