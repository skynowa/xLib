/**
 * \file  GitClient.cpp
 * \brief GIT client
 */


#include "GitClient.h"


namespace xl::package
{

/**************************************************************************************************
*   public
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
GitClient::GitClient() :
	_gitPath( _binPath() )
{
}
//-------------------------------------------------------------------------------------------------
bool
GitClient::isGitDir() const
{
	std::cvec_tstring_t params {"rev-parse", "--git-dir"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);
	xCHECK_RET(!stdError.empty(), false);
	xCHECK_RET((stdOut.find(xT(".git")) == std::tstring_t::npos), false);

	return true;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Repositories
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/**
 * HTTP(s)/Git proto
 *
 * \verbatim
 * - git@bitbucket.org:skynowa/faq.git
 * - ssh://git@gitlab.maklai.dev:8999/suppliers/services-sync.git
 * - ssh://git@stash.fabrica.net.ua:7999/trav/booked.git
 *
 * - https://github.com/FIvanO/PocketBookTest
 *
 * - https://skynowa@git.code.sf.net/p/x-lib/code
 * \endverbatim
 */
std::tstring_t
GitClient::repoUrl() const
{
	xCHECK_RET(!isGitDir(), xT(""));

	std::tstring_t sRv;

	std::cvec_tstring_t params {"config", "--get", "remote.origin.url"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);

	sRv = String::trimSpace(stdOut);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
GitClient::repoUrlName() const
{
	xCHECK_RET(!isGitDir(), xT(""));

	std::ctstring_t &url = repoUrl();

	constexpr std::array protos
	{
		xT("git@"), 		// without protos
		xT("@git.code."),	// sourceforge.net
		xT("://")			// with protos
	};

	for (const auto &it_proto : protos) {
		xCHECK_DO(url.find(it_proto) == std::tstring_t::npos, continue);

		return String::cut(url, it_proto, xT(".")) ;
	}

	return {};
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
GitClient::repoName() const
{
	xCHECK_RET(!isGitDir(), xT(""));

	std::tstring_t sRv;

	std::cvec_tstring_t params {"rev-parse", "--show-toplevel"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);

	sRv = String::trimSpace( Path(stdOut).fileBaseName() );

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
GitClient::remoteRepoNames(
	std::vec_tstring_t *out_repoNames	///< [out]
) const
{
	xCHECK_DO(out_repoNames == nullptr, return);
	xCHECK_DO(!isGitDir(), return);

	out_repoNames->clear();

	std::cvec_tstring_t params {"remote"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);

	// [out]
	String::split(String::trimSpace(stdOut), Const::nl(), out_repoNames);
}
//-------------------------------------------------------------------------------------------------
std::tstring_t
GitClient::gitlabRepoGroupName() const
{
	xCHECK_RET(!isGitDir(), xT(""));

	std::tstring_t sRv;

   /**
	* URL
	*
	* \code
	* ssh://git@gitlab.maklai.dev:8999/tripnet/services.git
	* \endcode
	*/
	std::ctstring_t &url = repoUrl();
	// LogCout() << xTRACE_VAR(url);

	constexpr std::array protos
	{
		xT("git@gitlab")	// without protos
	};

	for (const auto &it_proto : protos) {
		xCHECK_DO(url.find(it_proto) == std::tstring_t::npos, continue);

		// Parse
		{
			std::ctstring_t a_str      = url;
			std::ctstring_t a_sepRight = xT("/");
			std::ctstring_t a_sepLeft  = xT("/");

			xTEST_NA(a_str);
			xTEST_NA(a_sepLeft);
			xTEST_NA(a_sepRight);

			size_t delimPosStop = a_str.rfind(a_sepRight);
			// LogCout() << xTRACE_VAR(delimPosStop);
			xCHECK_RET(delimPosStop == std::tstring_t::npos, std::tstring_t());

			delimPosStop += a_sepRight.size() - 1;

			size_t delimPosStart  = a_str.rfind(a_sepLeft, delimPosStop - 1);
			// LogCout() << xTRACE_VAR(delimPosStart);
			xCHECK_RET(delimPosStart == std::tstring_t::npos, std::tstring_t());
			xCHECK_RET(delimPosStart >= delimPosStop,         std::tstring_t());

			sRv = a_str.substr(delimPosStart + a_sepLeft.size(), delimPosStop - delimPosStart - 1);
			// LogCout() << xTRACE_VAR(sRv);

			return sRv;
		}
	}

	return {};
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Branches
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
GitClient::branchName() const
{
	xCHECK_RET(!isGitDir(), xT(""));

	std::tstring_t sRv;

	std::cvec_tstring_t params {"rev-parse", "--abbrev-ref", "HEAD"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);

	if      ( stdOut.empty() ) {
		sRv = xT("");
	}
	else if (stdOut == xT("HEAD")) {
		sRv = xT("detached●");
	}
	else {
		sRv = stdOut;
	}

	sRv = String::trimSpace(sRv);

	return sRv;
}
//-------------------------------------------------------------------------------------------------
std::size_t
GitClient::localBranchesNum() const
{
	xCHECK_RET(!isGitDir(), 0);

	std::cvec_tstring_t params {"branch"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);

	std::vec_tstring_t values;
	String::split(String::trimSpace(stdOut), Const::nl(), &values);
	xCHECK_RET(values.empty(), 0);

	// without "master"
	return values.size() - 1;
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   Statuses
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
/**
 \code{.py}
 git_states=""

 get_git_states()
 {
	local status=`git status 2>&1 | tee`

	local nocommit=`echo  "${status}" 2> /dev/null | grep "nothing to commit" &> /dev/null; echo "$?"`
	local dirty=`echo     "${status}" 2> /dev/null | grep "modified:"         &> /dev/null; echo "$?"`
	local untracked=`echo "${status}" 2> /dev/null | grep "Untracked files"   &> /dev/null; echo "$?"`
	local newfile=`echo   "${status}" 2> /dev/null | grep "new file:"         &> /dev/null; echo "$?"`
	local renamed=`echo   "${status}" 2> /dev/null | grep "renamed:"          &> /dev/null; echo "$?"`
	local deleted=`echo   "${status}" 2> /dev/null | grep "deleted:"          &> /dev/null; echo "$?"`

	 git_states=""

	if [ "${nocommit}" == "0" ]; then
		git_states="✔"
	fi

	if [ "${renamed}" == "0" ]; then
		git_states="△${git_states}"
	fi

	if [ "${newfile}" == "0" ]; then
		git_states="+${git_states}"
	fi

	if [ "${untracked}" == "0" ]; then
		git_states="…${git_states}"
	fi

	if [ "${deleted}" == "0" ]; then
		git_states="✖${git_states}"
	fi

	if [ "${dirty}" == "0" ]; then
		git_states="●${git_states}"
	fi
 }
 \endcode
*/
std::tstring_t
GitClient::filesStatuses() const
{
	xCHECK_RET(!isGitDir(), xT(""));

	std::cvec_tstring_t params {"status"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);

	cbool_t isNoCommit  = StringCI::contains(stdOut, xT("nothing to commit"));
	cbool_t isModified  = StringCI::contains(stdOut, xT("modified:"));
	cbool_t isUntracked = StringCI::contains(stdOut, xT("Untracked files"));
	cbool_t isNew       = StringCI::contains(stdOut, xT("new file:"));
	cbool_t isRenamed   = StringCI::contains(stdOut, xT("renamed:"));
	cbool_t isDeleted   = StringCI::contains(stdOut, xT("deleted:"));

	std::tstring_t sRv;

	if (isNoCommit) {
		sRv += xT("✔");
	}

	if (isRenamed) {
		sRv += xT("△");
	}

	if (isNew) {
		sRv += xT("✚");
	}

	if (isUntracked) {
		sRv += xT("…");
	}

	if (isDeleted) {
		sRv += xT("✖");
	}

	if (isModified) {
		sRv += xT("●");
	}

	return sRv;
}
//-------------------------------------------------------------------------------------------------
/**
  \code{.py}
 find_git_ahead_behind()
 {
	if ! $(is_git); then
		git_ahead_behind=""
		return
	fi

	local status=$(git rev-list --left-right --count origin/master...$branch)
	local aheadRegex="([0-9]+)"
	local behindRegex="\s(\w+)$"

	[[ $status =~ $aheadRegex ]]  && ahead="${BASH_REMATCH[1]}"  || ahead="0"
	[[ $status =~ $behindRegex ]] && behind="${BASH_REMATCH[1]}" || behind="0"

??? [[ $(git status 2> /dev/null | tail -n1) != "nothing to commit, working tree clean" ]] && git_ahead_behind=""
	[[ $ahead != "0" ]]  && git_ahead_behind="↑${ahead}"
	[[ $behind != "0" ]] && git_ahead_behind="↓${behind}"
 }
 \endcode
*/
void_t
GitClient::commitsAheadBehind(
	std::size_t *out_aheadNum,	///< [out] ahead number
	std::size_t *out_behindNum	///< [out] behind number
) const
{
	Utils::ptrAssignT(out_aheadNum,  std::size_t{});
	Utils::ptrAssignT(out_behindNum, std::size_t{});

	xCHECK_DO(!isGitDir(), return);

	std::cvec_tstring_t params {"rev-list", "--left-right", "--count", "origin/master..." + branchName()};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);

	std::vec_tstring_t values;
	String::split(stdOut, Const::ht(), &values);
	if (values.size() != 2) {
		return;
	}

	Utils::ptrAssignT(out_aheadNum,  String::cast<std::size_t>(String::trimSpace(values[0])));
	Utils::ptrAssignT(out_behindNum, String::cast<std::size_t>(String::trimSpace(values[1])));
}
//-------------------------------------------------------------------------------------------------
std::size_t
GitClient::stashesNum() const
{
	xCHECK_RET(!isGitDir(), 0);

	std::cvec_tstring_t params {"stash", "list"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);

	std::vec_tstring_t values;
	String::split(String::trimSpace(stdOut), Const::nl(), &values);

	return values.size();
}
//-------------------------------------------------------------------------------------------------
void_t
GitClient::modifiedFiles(
	std::cvec_tstring_t &a_filterFileExts,	///< (Maybe empty)
	std::vec_tstring_t  *out_filePathes		///< [out] file paths
) const
{
	xCHECK_DO(out_filePathes == nullptr, return);
	xCHECK_DO(!isGitDir(), return);

	out_filePathes->clear();

	bool_t bRv {};

	std::cvec_tstring_t params {"status", "--short"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params, &stdOut, &stdError);
#if 0
	LogCout() << xTRACE_VAR(stdOut);
	LogCout() << xTRACE_VAR(stdError);
#endif

	std::vec_tstring_t values;
	String::split(String::trimSpace(stdOut), Const::nl(), &values);
	xCHECK_DO(values.empty(), return);

	for (const auto &it_value : values) {
		std::ctstring_t &filePath = String::trimSpace(it_value);

		// Filter
		if ( !a_filterFileExts.empty() ) {
			std::ctstring_t &fileExt = Path(filePath).ext();

			bRv = Algos::isContains(a_filterFileExts, fileExt);
			xCHECK_DO(!bRv, continue);
		}

		out_filePathes->push_back(filePath);
	} // for (values)
}
//-------------------------------------------------------------------------------------------------
void_t
GitClient::trackedFiles(
	std::cvec_tstring_t &a_filterFileExts,	///< filter file extentions
	std::vec_tstring_t  *out_filePathes		///< [out] file paths
) const
{
	xCHECK_DO(out_filePathes == nullptr, return);
	xCHECK_DO(!isGitDir(), return);

	out_filePathes->clear();

	bool_t bRv {};

	/// std::cvec_tstring_t params_commit_diff {"diff", "--name-only", "--cached", "--diff-filter=ACM"};
	/// std::cvec_tstring_t params_master_diff {"diff", "--name-only", "master"};
	std::cvec_tstring_t params_master_diff {"diff", "--name-only",
		"--line-prefix=" + Dir::current().str() + "/", "master"};
	std::tstring_t      stdOut;
	std::tstring_t      stdError;

	_gitExecute(params_master_diff, &stdOut, &stdError);
#if 0
	LogCout() << xTRACE_VAR(stdOut);
	LogCout() << xTRACE_VAR(stdError);
#endif

	std::vec_tstring_t values;
	String::split(String::trimSpace(stdOut), Const::nl(), &values);
	xCHECK_DO(values.empty(), return);

	for (const auto &it_value : values) {
		std::ctstring_t &filePath = String::trimSpace(it_value);

		// Filter
		if ( !a_filterFileExts.empty() ) {
			std::ctstring_t &fileExt = Path(filePath).ext();

			bRv = Algos::isContains(a_filterFileExts, fileExt);
			xCHECK_DO(!bRv, continue);
		}

		out_filePathes->push_back(filePath);
	} // for (values)
}
//-------------------------------------------------------------------------------------------------
void_t
GitClient::modifiedFilesLineFilter() const
{
	xCHECK_DO(!isGitDir(), return);

   /**
    * \code{.py}
	* def getGitModifiedFilesLineFilter(self):
	* 	"" Get current GIT modified lines line filter (JSON) ""
	*
	* 	# strip the smallest prefix containing P slashes
	* 	p      = 1
	* 	iregex = r'.*\.(h|hh|hpp|inl|cc|cpp|cxx)'
	*
	* 	cmd = "git diff -U0 HEAD".split()
	*
	* 	out = subprocess.Popen(cmd, stdout = subprocess.PIPE, stderr = subprocess.PIPE)
	*
	* 	## result = stderr.strip().decode("utf8")
	* 	# print("stderr: ", result)
	*
	* 	# extract changed lines for each file
	* 	filename      = None
	* 	lines_by_file = {}
	*
	* 	for it_line in iter(out.stdout.readline, ''):
	* 		line = it_line.decode("utf-8")
	* 		if (not line):
	* 			break
	*
	* 		match = re.search('^\+\+\+\ \"?(.*?/){%s}([^ \t\n\"]*)' % p, line)
	* 		if (match):
	* 			filename = match.group(2)
	*
	* 		if (filename == None):
	* 			continue
	*
	* 		if (not re.match('^%s$' % iregex, filename, re.IGNORECASE)):
	* 			continue
	*
	* 		# print("C++ filename: ", filename)
	*
	* 		match = re.search('^@@.*\+(\d+)(,(\d+))?', line)
	* 		if (match):
	* 			start_line = int(match.group(1))
	* 			line_count = 1
	*
	* 			if (match.group(3)):
	* 				line_count = int(match.group(3))
	*
	* 			if (line_count == 0):
	* 				continue
	*
	* 			end_line = start_line + line_count - 1;
	* 			lines_by_file.setdefault(filename, []).append([start_line, end_line])
	* 	# for (out.stdout)
	*
	* 	if (len(lines_by_file) == 0):
	* 		print("No diffs")
	* 		sys.exit(0)
	*
	* 	line_filter_json = json.dumps(
	* 		[{"name" : name, "lines" : lines_by_file[name]} for name in lines_by_file],
	* 		separators = (',', ':'))
	*
	* 	return line_filter_json
	* \endcode
	*/
}
//-------------------------------------------------------------------------------------------------


/**************************************************************************************************
*   private
*
**************************************************************************************************/

//-------------------------------------------------------------------------------------------------
std::tstring_t
GitClient::_binPath() const
{
	std::tstring_t sRv;

	std::ctstring_t binName =
	#if   xENV_WIN
		xT("git.exe");
	#elif xENV_UNIX
		xT("git");
	#endif

	std::cvec_tstring_t dirPaths
	{
	#if   xENV_WIN
		// echo %Path%
		xT("c:\\Program Files (x86)\\Git\\bin")
	#elif xENV_UNIX
		// echo $PATH
		xT("/usr/bin"),
		xT("/usr/local/bin")
	#endif
	};

	cbool_t isRecursively {false};
	sRv = Finder::file(dirPaths, binName, isRecursively);
	xTEST(!sRv.empty());

	return sRv;
}
//-------------------------------------------------------------------------------------------------
void_t
GitClient::_gitExecute(
	std::cvec_tstring_t &a_params,		///< command line params
	std::tstring_t      *out_stdOut,	///< [out] std::cout (maybe as nullptr)
	std::tstring_t      *out_stdError	///< [out] std::cerr (maybe as nullptr)
) const
{
	Process::execute(_gitPath, a_params, out_stdOut, out_stdError);

	// Fix
	if (out_stdOut != nullptr) {
		*out_stdOut   = String::trimSpace(*out_stdOut);
	}

	if (out_stdError != nullptr) {
		*out_stdError = String::trimSpace(*out_stdError);
	}
}
//-------------------------------------------------------------------------------------------------

} // namespace
