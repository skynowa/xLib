xLib - C++ cross-platform library


Authors: skynowa
E-mail:  skynowa@gmail.com
Skype:   skynowa777
Jabber:  skynowa@jabber.ru
ICQ:     627713628
Web:     https://bitbucket.org/skynowa/xlib
         https://github.com/skynowa/xLib
         https://sourceforge.net/p/x-lib

Feature list:
    - platforms: Windows, Linux, FreeBSD, Mac OS
    - architecture: x86, x64
    - header only
    - unicode support

Pre-requisites:
    - bash-compatible Unix command shell (for Unix)
    - Doxygen 1.8.2

Dependencies:
    - OpenSSL
        Ubuntu: deb http://security.ubuntu.com/ubuntu lucid-security main
        Ubuntu: sudo apt-get install libssl-dev

    - MySQL
        Ubuntu: sudo apt-get install libmysqlclient-dev

Repositories:
    - http://bitbucket.org
        git clone https://skynowa@bitbucket.org/skynowa/xlib.git
        git clone git@bitbucket.org:skynowa/xlib.git

    - http://github.com
        git clone https://github.com/skynowa/xLib.git
        git clone git://github.com/skynowa/xLib.git

    - http://sourceforge.net
        git clone https://skynowa@git.code.sf.net/p/x-lib/code x-lib-code
        git clone git://git.code.sf.net/p/x-lib/code x-lib-code

Tests:
    cmake ../xLib -G"Eclipse CDT4 - Unix Makefiles" -D_ECLIPSE_VERSION=3.7.2
    cmake ../xLib -DCMAKE_C_COMPILER=/usr/local/libexec/ccache/world/clang \
                  -DCMAKE_CXX_COMPILER=/usr/local/libexec/ccache/world/clang++
