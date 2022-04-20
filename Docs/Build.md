# xLib

## Pre-requisites

- bash-compatible Unix command shell (for Unix)
- Doxygen 1.8.2: `sudo apt-get install doxygen`
- `sudo apt-get install cmake pkg-config`
- `~/Projects/CMakeLib/install.sh`

## Dependencies

- Linkage flags

    Windows:
        - MinGW: -lws2_32 -lnetapi32 -lpsapi -luuid -lole32 -lmpr -ldbghelp -libeay32 -lmysqlclient

    Unix:
        - Unix:    -lxcb -ldl -pthread -lrt -lm -lz -lmysqlclient
        - FreeBSD: -lxcb -lc -lpthread -lexecinfo -lmysqlclient

    Apple:
        - MacOS: -lexecinfo
