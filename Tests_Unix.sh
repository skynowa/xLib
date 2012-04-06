MAKE=
TARGET_DIR=


clear
echo -e "Build xLib ($OSTYPE) ... "
echo -e

# prepare
if   [[ 'linux'*   == $OSTYPE ]]; then
    MAKE=make
    TARGET_DIR=./Contrib/G++_linux/Release
elif [[ 'freebsd'* == $OSTYPE ]]; then
    MAKE=gmake
    TARGET_DIR=./Contrib/G++_freebsd/Release
else
    echo -e "Unknown OS"
fi

# execute
mkdir -p $TARGET_DIR
$MAKE --directory=$TARGET_DIR --makefile=../../../Tests.mk

# finished
echo -e
echo -e "Finished."
echo -e
