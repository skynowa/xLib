/**
 * \file  Process.inl
 * \brief process
 */


xNAMESPACE_BEGIN2(xl, sync)


/**************************************************************************************************
*    public, static
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/* static */
Process::id_t
Process::_idByName_impl(
    std::ctstring_t &a_processName
)
{
    id_t ulRv;

    int_t pid = -1;

    // open the /proc directory
    DIR *dir = ::opendir("/proc");
    xTEST_PTR(dir);

    // enumerate all entries in directory until process found
    for ( ; ; ) {
        dirent *dirEntry = ::readdir(dir);
        xCHECK_DO(dirEntry == xPTR_NULL, break);

        // skip non-numeric entries
        int_t id = ::atoi(dirEntry->d_name);
        xCHECK_DO(0 >= id, continue);

        // read contents of virtual /proc/{pid}/cmdline file
        std::string   cmdPath = std::string("/proc/") + dirEntry->d_name + "/cmdline";
        std::ifstream cmdFile(cmdPath.c_str());

        std::string cmdLine;
        std::getline(cmdFile, cmdLine);
        xCHECK_DO(cmdLine.empty(), continue);

        // keep first cmdline item which contains the program path
        size_t pos = cmdLine.find('\0');
        if (pos != std::string::npos) {
            cmdLine = cmdLine.substr(0, pos);
        }

        if (a_processName == Path( xA2T(cmdLine) ).fileName()) {
            pid = id;
            break;
        }
    }

    int_t iRv = ::closedir(dir); dir = xPTR_NULL;
    xTEST_DIFF(iRv, - 1);

    ulRv = pid;

    return ulRv;
}
//-------------------------------------------------------------------------------------------------
/* static */
void_t
Process::_ids_impl(
    std::vector<Process::id_t> *a_ids
)
{
    std::vector<id_t> vidRv;

    std::vec_tstring_t dirPaths;

    Finder::dirs(xT("/proc"), Const::maskAll(), false, &dirPaths);

    // skip non-numeric entries
    xFOR_EACH_CONST(std::vec_tstring_t, it, dirPaths) {
        int_t pid = 0;
        {
            std::tstring_t dirName = Path(*it).fileName();

            pid = String::cast<int_t>( dirName.c_str() );
            xCHECK_DO(0 >= pid, continue);
        }

        vidRv.push_back( static_cast<id_t>( pid ));
    }

    // out
    a_ids->swap(vidRv);
}
//-------------------------------------------------------------------------------------------------

xNAMESPACE_END2(xl, sync)
