MAKE=

# prepare
clear
echo -e "Install xLib ($OSTYPE) ... "
echo -e

if   [[ 'linux'*   == $OSTYPE ]]; then
    MAKE=make
elif [[ 'freebsd'* == $OSTYPE ]]; then
    MAKE=gmake
else
    echo -e "Unknown OS"
fi

# execute
$MAKE install -f ./Lib.mk

# finished
echo -e
echo -e "Finished."
echo -e
