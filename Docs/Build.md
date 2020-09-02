# xLib

## Pre-requisites

- bash-compatible Unix command shell (for Unix)
- Doxygen 1.8.2: `sudo apt-get install doxygen`
- `sudo apt-get install cmake pkg-config`
- `/home/skynowa/Projects/CMakeLib/install.sh`

## Dependencies

- Linkage flags

    Windows:
        - MinGW: -lws2_32 -lnetapi32 -lpsapi -luuid -lole32 -lmpr -ldbghelp -libeay32 -lmysqlclient

    Unix:
        - Unix:    -lxcb -ldl -pthread -lrt -lm -lz -lmysqlclient
        - FreeBSD: -lxcb -lc -lpthread -lexecinfo -lmysqlclient

    Apple:
        - MacOS: -lexecinfo

## Switch compiler (Ubuntu)

`sudo update-alternatives --config c++`

## Installation

```bash
cd ./Build
./[platform_script]
cd [build_directory]
sudo make install (Unix, Apple)
```

## Test

MySQL:

```bash
sudo apt-get install mysql-server
sudo service mysql restart
```

```bash
sudo mysql
mysql> ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY 'root';

sudo mysql -u root

SHOW DATABASES;
SHOW SCHEMAS;

SELECT DATABASE();

use mysql
SHOW TABLES;
```

## CI Badges

- https://shields.io/category/build

## Known issues

- n/a
