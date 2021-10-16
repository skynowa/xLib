/**
 * \file  File.cpp
 * \brief File
 */


#include "File.h"

#include <xLib/Core/Locale.h>
#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/FileInfo.h>
#include <xLib/Fs/FileType.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Crypt/Random.h>
#include <xLib/Sync/Thread.h>

#if   xENV_WIN
    #include "Platform/Win/File_win.inl"
#elif xENV_UNIX
    #include "Platform/Unix/File_unix.inl"
#endif


namespace xl::fs
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
File::File(
	std::ctstring_t &a_filePath
) :
	_filePath(a_filePath)
{
}
//-------------------------------------------------------------------------------------------------
File::~File()
{
}
//-------------------------------------------------------------------------------------------------
void_t
File::remove() const
{
    FileInfo info(_filePath);
    xCHECK_DO(!info.isExists(), return);

    // TODO: [skynowa] maybe not work ?
    info.chmod(FileInfo::PermissionMode::Write);

    int_t iRv = xTREMOVE(_filePath.c_str());
    xTEST_DIFF(iRv, - 1);
    xTEST(!info.isExists());
}
//-------------------------------------------------------------------------------------------------
void_t
File::tryRemove(
    std::csize_t a_attempts,
    culong_t     a_timeoutMsec
) const
{
    xTEST_GR(a_attempts, size_t(0U));
    xTEST_NA(a_timeoutMsec);

    std::csize_t attemptsMax  {100};  // MAGIC_NUMBER: attemptsMax
    std::csize_t attemptsReal = (std::min)(a_attempts, attemptsMax);

    for (size_t i = 0; i < attemptsReal; ++ i) {
        xTRY {
            remove();
            xCHECK_DO(!FileInfo(_filePath).isExists(), break);
        }
        xCATCH_ALL

        Thread::currentSleep(a_timeoutMsec);
    }
}
//-------------------------------------------------------------------------------------------------
void_t
File::wipe(
    std::csize_t a_passes
) const
{
    xTEST_NA(a_passes);

    FileInfo info(_filePath);
    xCHECK_DO(!info.isExists(), return);

	// attributes - reset
	{
		FileType(_filePath).clear();
	}

	// content - reset
	if ( !info.isEmpty() ) {
		FileIO file(_filePath);
		file.open(FileIO::OpenMode::BinReadWrite);

		clonglong_t fileSize = file.size();
		if (fileSize > 0LL) {
			for (size_t p {}; p < a_passes; ++ p) {
				auto writer = [&](cuchar_t a_byte) -> void
				{
					file.setPosition(0L, FileIO::PointerPosition::Begin);

					for (longlong_t i {}; i < fileSize; ++ i) {
						std::csize_t uiRv = std::fwrite(&a_byte, 1, sizeof(a_byte), file.get().get());
						xTEST_EQ(uiRv, sizeof(a_byte));
					}

					file.flush();
				};

				// fill by 0x55 (01010101), 0xAA (10101010), random char
				cuchar_t bytes[] {0x55, 0xAA, NativeRandom().nextChar<uchar_t>()};

				for (const auto &it_byte : bytes) {
					writer(it_byte);
				}
			} // for (p)

			// truncate
			file.clear();
		} // if (fileSize)
	}

    // file time - reset
    info.resetTime();

    // file name - randomize
    std::tstring_t randFilePath;
    {
        std::tstring_t randFileName = String::cast( DateTime().current().toMsec() );

        std::random_device randDevice;
        std::mt19937       gen( randDevice() );

        std::shuffle(randFileName.begin(), randFileName.end(), gen);

        randFilePath = Path(_filePath).dir() + Const::slash() + randFileName;

        rename(randFilePath);
    }

	remove();
}
//-------------------------------------------------------------------------------------------------
void_t
File::unlink() const
{
    int_t iRv = xTUNLINK(_filePath.c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
File::rename(
    std::ctstring_t &a_filePathNew
) const
{
    xTEST(!a_filePathNew.empty());

    int_t iRv = xTRENAME(_filePath.c_str(), a_filePathNew.c_str());
    xTEST_DIFF(iRv, - 1);
}
//-------------------------------------------------------------------------------------------------
void_t
File::move(
    std::ctstring_t &a_dirPath
) const
{
    xTEST(!a_dirPath.empty());

    rename(Path(a_dirPath).slashAppend().str() + Path(_filePath).fileName());
}
//-------------------------------------------------------------------------------------------------
void_t
File::copy(
    std::ctstring_t &a_filePathTo,
    cbool_t          a_isFailIfExists
) const /* throw(Exception) */
{
    xTEST(!a_filePathTo.empty());
    xTEST_NA(a_isFailIfExists);

#if 1
	bool_t isCopyOk {true};

	// errors
	std::ctstring_t errorDestFileExists = xT("File - Destination file is exists");
	std::ctstring_t errorCopyFail       = xT("File - Copy fail");
	std::ctstring_t errorFilesDiffrent  = xT("File - Files are diffrent");

	xCHECK_DO(a_isFailIfExists && FileInfo(a_filePathTo).isExists(),
		xTHROW_REPORT(errorDestFileExists));

	// copy
	{
		FileIO fileFrom(_filePath);
		fileFrom.open(FileIO::OpenMode::BinReadOnly);

		FileIO fileTo(a_filePathTo);
		fileTo.open(FileIO::OpenMode::BinWrite);

		constexpr std::size_t buffSize       {1024};
		uchar_t               buff[buffSize] {};

		for ( ; !fileFrom.isEof(); ) {
			std::csize_t readed  = fileFrom.read(buff, buffSize);
			xCHECK_DO(0 >= readed, break);

			std::csize_t written = fileTo.write(buff, readed);
			xCHECK_DO(readed != written, isCopyOk = false; break);
		}
	}

	// checks
	{
		if (!isCopyOk) {
			File(a_filePathTo).remove();
			xTHROW_REPORT(errorCopyFail);
		}

		if (FileInfo(_filePath).size() != FileInfo(a_filePathTo).size()) {
			File(a_filePathTo).remove();
			xTHROW_REPORT(errorFilesDiffrent);
		}
	}
#else
    std::tifstream_t fileFrom(_filePath, std::ios::binary);
    std::tofstream_t fileTo(a_filePathTo, std::ios::binary);

    fileTo << fileFrom.rdbuf();
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
File::createSymlink(
	std::ctstring_t &a_filePathTo
) const
{
	_createSymlink_impl(a_filePathTo);
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: text
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
File::textRead(
    std::tstring_t *a_content
) const
{
    xTEST_PTR(a_content);

    std::tstring_t sRv;

    FileIO file(_filePath);
    file.open(FileIO::OpenMode::BinReadOnly);

    clonglong_t fileSize = file.size();
    xTEST_DIFF(fileSize, static_cast<longlong_t>(FileIO::PointerPosition::Error));
    xCHECK_DO(fileSize == 0LL, a_content->clear(); return);

    sRv.resize( static_cast<size_t>(fileSize) );

    std::csize_t readLen = file.read((void_t *)&sRv.at(0), sRv.size());
    xTEST_EQ(readLen, sRv.size());

    // out
    a_content->swap(sRv);
}
//-------------------------------------------------------------------------------------------------
void_t
File::textRead(
    std::vec_tstring_t *a_content
) const
{
    xTEST(FileInfo(_filePath).isExists());
    xTEST_PTR(a_content);

    std::tstring_t content;
    textRead(&content);

    std::vec_tstring_t vsRv;
    String::split(content, Const::nl(), &vsRv);

    // out
    a_content->swap(vsRv);
}
//-------------------------------------------------------------------------------------------------
void_t
File::textRead(
    std::ctstring_t    &a_separator,
    std::map_tstring_t *a_content
) const
{
    xTEST(FileInfo(_filePath).isExists());
    xTEST_PTR(a_content);

    // if file empty
    xCHECK_DO(FileInfo(_filePath).size() == 0L, a_content->clear(); return);

    std::locale::global( std::locale() );

    std::tifstream_t ifs(xT2A(_filePath));
    xTEST(!! ifs);
    xTEST(!ifs.fail());
    xTEST(ifs.good());
    xTEST(ifs.is_open());
    xTEST(!ifs.eof());

    std::map_tstring_t msRv;
    std::tstring_t     line;
    std::vec_tstring_t lines;

    for (size_t i = 0; !ifs.eof(); ++ i) {
        std::getline(ifs, line);
        line = String::trimRightChars(line, Const::eol());

        if ( line.empty() ) {
            auto prRv = msRv.insert( {Const::strEmpty(), Const::strEmpty()} );
            xTEST_NA(prRv);
        } else {
            String::split(line, a_separator, &lines);
            xTEST_EQ(lines.size(), size_t(2));

            auto prRv = msRv.insert( {lines.at(0), lines.at(1)} );
            xTEST_NA(prRv);
        }
    }

    // out
    a_content->swap(msRv);

#if xTODO
    bool_t             bRv {};
    std::map_tstring_t msRv;
    std::vec_tstring_t vsRv;

    bRv = textRead(filePath, &vsRv);
    xTEST_EQ(bRv, true);

    for (const auto it = vsRv.cbegin(); it != vsRv.cend(); ++ it) {
        std::vec_tstring_t lines;
        String::split(vsRv.at(0), separator, &lines);

        msRv.insert( {lines.at(0), lines.at(1)} );
    }

    // out
    content.swap(msRv);
#endif
}
//-------------------------------------------------------------------------------------------------
void_t
File::textWrite(
    std::ctstring_t   &a_content,
    FileIO::cOpenMode  a_mode
) const
{
    xTEST_NA(a_content);
    xTEST_NA(a_mode);

    FileIO file(_filePath);
    file.open(a_mode);

    xCHECK_DO(a_content.empty(), return);

    std::csize_t writeLen = file.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(writeLen, a_content.size());
}
//-------------------------------------------------------------------------------------------------
void_t
File::textWrite(
    std::cvec_tstring_t &a_content,
    FileIO::cOpenMode    a_mode
) const
{
    xTEST_NA(a_content);
    xTEST_NA(a_mode);

    std::ctstring_t &content = String::join(a_content, Const::nl());
    textWrite(content, a_mode);
}
//-------------------------------------------------------------------------------------------------
void_t
File::textWrite(
    std::ctstring_t     &a_separator,
    std::cmap_tstring_t &a_content,
    FileIO::cOpenMode    a_mode
) const
{
    xTEST(!_filePath.empty());
    xTEST(!a_separator.empty());
    xTEST_NA(a_content);
    xTEST_NA(a_mode);

    FileIO file(_filePath);
    file.open(a_mode);

    xCHECK_DO(a_content.empty(), return);

    for (const auto &[key, value] : a_content) {
        file.writeLine(key + a_separator + value);
    }
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*    public: bin
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
void_t
File::binRead(
    std::ustring_t *a_content
) const
{
    xTEST_PTR(a_content);

    FileIO file(_filePath);
    file.open(FileIO::OpenMode::BinReadOnly);

    clonglong_t fileSize = file.size();
    xTEST_DIFF(fileSize, static_cast<longlong_t>(FileIO::PointerPosition::Error));
    xCHECK_DO(fileSize == 0LL, a_content->clear(); return);

    std::ustring_t usRv;
    usRv.resize( static_cast<size_t>(fileSize) );

    std::csize_t readLen = file.read((void_t *)&usRv.at(0), usRv.size());
    xTEST_EQ(readLen, usRv.size());

    // out
    a_content->swap(usRv);
}
//-------------------------------------------------------------------------------------------------
void_t
File::binWrite(
    std::custring_t   &a_content,
    FileIO::cOpenMode  a_mode
) const
{
    xTEST_NA(a_content);

    FileIO file(_filePath);
    file.open(a_mode);

    xCHECK_DO(a_content.empty(), return);

    std::csize_t writeLen = file.write((void_t *)&a_content.at(0), a_content.size());
    xTEST_EQ(writeLen, a_content.size());
}
//-------------------------------------------------------------------------------------------------

} // namespace
