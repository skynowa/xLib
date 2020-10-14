/**
 * \file  GitClient.h
 * \brief GIT client
 */


#pragma once

#include <xLib/xLib.h>
//-------------------------------------------------------------------------------------------------
namespace xl::package
{

class GitClient
    /// GIT client
{
public:
///@name ctors, dtor
///@{
             GitClient();
    virtual ~GitClient();

    xNO_COPY_ASSIGN(GitClient)
///@}

	bool           isGitDir() const;
		///< check Git directory
	std::tstring_t repoUrlName() const;
		///< get repo URL name
	std::tstring_t repoName() const;
		///< get repository name
	std::tstring_t branchName() const;
		///< get brach name
	std::size_t    localBranchesNum() const;
		///< number of local branches
	std::tstring_t filesStatuses() const;
		///< get source files statuses
	void_t         commitsAheadBehind(std::size_t *aheadNum, std::size_t *behindNum) const;
		///< get number commits ahead behind
	std::size_t    stashesNum() const;
		///< get stashes number
	void_t         modifiedFiles(std::cvec_tstring_t &filterFileExts,
						std::vec_tstring_t *filePathes) const;
		///< get modified files
	void_t         getGitModifiedFilesLineFilter() const;
		///< get modified lines line filter (JSON)

private:
	std::tstring_t _gitPath() const;
		///< path to binary file
};

} // namespace
//-------------------------------------------------------------------------------------------------
