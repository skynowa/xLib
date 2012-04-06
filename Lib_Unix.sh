MAKE=
TARGET_DIR=

# prepare
clear
echo -e "Lib xLib ($OSTYPE) ... "
echo -e

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
$MAKE all -f ./Lib.mk

# finished
echo -e
echo -e "Finished."
echo -e
