#!/usr/bin/env bash
#
# \file  ChangeLog.sh
# \brief Generate change log from MRs
#


LOGFILE="ChangeLog.md"
GIT_REPOSITORY="https://github.com/skynowa/xLib"

# Header
echo "# Change log" > "$LOGFILE"
echo "" >> "$LOGFILE"

# Extract merge commits and format as Markdown
git log --merges --pretty=format:"## %s%n- **Commit:** [%h](${GIT_REPOSITORY}/commit/%h)%n- **Author:** %an%n- **Date:** %cd%n" --date=short >> "$LOGFILE"

echo "$LOGFILE - Saved"
