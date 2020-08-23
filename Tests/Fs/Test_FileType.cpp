/**
 * \file   Test_FileType.cpp
 * \brief
 */


#include <xLib/xLib.h>

//-------------------------------------------------------------------------------------------------
using namespace xl;

xTEST_CLASS(Test_FileType)
xTEST_UNIT(Test_FileType)
//-------------------------------------------------------------------------------------------------
/* virtual */
bool_t
Test_FileType::unit()
{
    std::ctstring_t filePath = getData().tempDirPath + Const::slash() + xT("Test.txt");
    const auto      value    = FileType::Type::RegularFile;

    // prepare
    {
        // cleanup
		{
			FileInfo info(filePath);
			if ( info.isExists() ) {
				info.chmod(FileInfo::PermissionMode::Write);
			}

			File file;
			file.create(filePath, File::OpenMode::Write);
			file.remove();
		}

        File file;
        file.create(filePath, File::OpenMode::ReadWrite);
        file.close();

        m_bRv = FileInfo(filePath).isExists();
        xTEST(m_bRv);
    }

    xTEST_CASE("set, get")
    {
        FileType type(filePath);

        type.set( static_cast<FileType::types_t>(value) );

        FileType::ctypes_t faRes = type.get();
        xTEST_EQ((ulong_t)value, (ulong_t)faRes);
    }

    xTEST_CASE("add")
    {
        FileType type(filePath);

        type.clear();
        type.add(value);

        m_bRv = type.isExists(value);
        xTEST(m_bRv);
    }

    xTEST_CASE("remove")
    {
    #if   xENV_WIN
        FileType type(filePath);

        const auto attr  = FileType::Type::Hidden;
        const auto value = FileType::Type::ReadOnly;

        type.clear();
        type.add(attr);

        m_bRv = type.isExists(attr);
        xTEST(m_bRv);

        type.add(value);

        m_bRv = type.isExists(value);
        xTEST(m_bRv);

        // remove
        type.remove(value);

        m_bRv = type.isExists(value);
        xTEST(m_bRv);

        m_bRv = type.isExists(attr);
        xTEST(m_bRv);

        FileType::types_t faRv = type.get();
        xTEST_EQ((int_t)attr, (int_t)faRv);
    #elif xENV_UNIX
        // file
        {
            FileType type(filePath);

            m_bRv = type.isExists(FileType::Type::RegularFile);
            xTEST(m_bRv);

            m_bRv = type.isExists(FileType::Type::RegularFile);
            xTEST(m_bRv);
        }

        // dir
        {
            std::ctstring_t dirPath = getData().tempDirPath;

            FileType type(dirPath);

            m_bRv = type.isExists(FileType::Type::Directory);
            xTEST(m_bRv);

            m_bRv = type.isExists(FileType::Type::Directory);
            xTEST(m_bRv);
        }
    #endif
    }

    xTEST_CASE("modify")
    {
        FileType type(filePath);

        const FileType::Type removeValue = value;
    #if   xENV_WIN
        const FileType::Type addValue    = FileType::Type::Hidden;
    #elif xENV_UNIX
        const FileType::Type addValue    = FileType::Type::SymbolicLink;
    #endif

        type.modify(removeValue, addValue);
    }

    xTEST_CASE("isExists")
    {
        FileType type(filePath);

        const auto attr = FileType::Type::RegularFile;

        type.clear();

        m_bRv = type.isExists(attr);
        xTEST(m_bRv);
    }

    xTEST_CASE("clear")
    {
        FileType type(filePath);

        type.clear();

        FileType::ctypes_t faRv = type.get();
        xTEST_EQ((ulong_t)FileType::Type::RegularFile, (ulong_t)faRv);
    }

    xTEST_CASE("isFile")
    {
        m_bRv = FileType(filePath).isFile();
        xTEST(m_bRv);

        m_bRv = FileType(getData().tempDirPath).isFile();
        xTEST(!m_bRv);
    }

	xTEST_CASE("isExecutable")
	{
		const Data2<std::tstring_t, bool_t> datas[]
		{
			{filePath,              false},
			{getData().tempDirPath, false},
			{xT("wrong_path"),      false},
		#if   xENV_WIN
			{xT("C:\\Windows\\System32\\attrib.exe"), true},
		#elif xENV_UNIX
			{xT("/bin/ls"),         true},
		#endif
			{xT("."),               false}
		};

		for (const auto &it_data : datas) {
			m_bRv = FileType(it_data.test).isExecutable();
			xTEST_EQ(m_bRv, it_data.expect);
		}
	}

	// cleanup
	{
		FileInfo(filePath).chmod(FileInfo::PermissionMode::Write);

		File file;
		file.create(filePath, File::OpenMode::Write);
		file.remove();
	}

    return true;
}
//-------------------------------------------------------------------------------------------------
