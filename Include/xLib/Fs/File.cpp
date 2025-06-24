/**
 * \file  File.cpp
 * \brief File
 */


#include "File.h"

#include <xLib/Core/String.h>
#include <xLib/Core/DateTime.h>
#include <xLib/Fs/Path.h>
#include <xLib/Fs/FileType.h>
#include <xLib/Debug/Exception.h>
#include <xLib/Crypt/Random.h>
#include <xLib/Sync/ThreadCurrent.h>

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
File::File(
	const FileInfo &a_fileInfo
) :
	_filePath( a_fileInfo.path() )
{
}
//-------------------------------------------------------------------------------------------------
File::~File()
{
}
//-------------------------------------------------------------------------------------------------
void_t
File::clear() const
{
    FileInfo info(_filePath);
    xCHECK_DO(!info.isExists(), return);

    // Write, clear
    {
        FileIO file(_filePath);
        file.open(FileIO::OpenMode::Write);
        file.clear();
    }
}
//-------------------------------------------------------------------------------------------------
void_t
File::remove() const
{
    FileInfo info(_filePath);
    xCHECK_DO(!info.isExists(), return);

    /// TODO: [skynowa] maybe not work ???!!!
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

        ThreadCurrent::currentSleep(a_timeoutMsec);
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

				for (const auto it_byte : bytes) {
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
File::CopyError
File::copy(
    std::ctstring_t &a_filePathTo,
    cbool_t          a_isFailIfExists
) const
{
    xTEST(!a_filePathTo.empty());
    xTEST_NA(a_isFailIfExists);

	bool_t isCopyOk {true};

	// errors
	std::ctstring_t errorDestFileExists = xT("File - Destination file is exists");
	std::ctstring_t errorCopyFail       = xT("File - Copy fail");
	std::ctstring_t errorFilesDiffrent  = xT("File - Files are diffrent");

	xCHECK_RET(a_isFailIfExists && FileInfo(a_filePathTo).isExists(), CopyError::DestFileExists);

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
			return CopyError::CopyFail;
		}

		if (FileInfo(_filePath).size() != FileInfo(a_filePathTo).size()) {
			File(a_filePathTo).remove();
			return CopyError::FilesDiffrent;
		}
	}

    return CopyError::Ok;
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

} // namespace
