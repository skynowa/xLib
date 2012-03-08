#
# xxxxxxxx
#


# vars
MAKE=


clear
echo -e "Install xLib ($OSTYPE) ... "
echo -e

# prepare
if   [ "$OSTYPE" = "linux-gnu"   ]; then
    MAKE=make
elif [ "$OSTYPE" = "FreeBSD" ]; then
    MAKE=gmake
else
    echo -e "Unknown OS"
    exit 1
fi

# execute
$MAKE install -f ./Lib.mk

# finished
echo -e
echo -e "Finished."
echo -e
