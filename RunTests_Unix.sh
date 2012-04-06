TARGET_DIR=


# prepare
clear
echo -e "Test xLib ($OSTYPE) ... "
echo -e

clear
./Tests_Unix.sh

if   [[ linux-gnu == $OSTYPE ]]; then
    TARGET_DIR=./Contrib/G++_linux/Release
elif [[ freebsd   == $OSTYPE ]]; then
    TARGET_DIR=./Contrib/G++_freebsd/Release
else
    echo -e "Unknown OS"
fi

# execute
$TARGET_DIR/xlib_r 1 1 1 1

# finished
echo -e
echo -e "Finished."
echo -e
