##rm    -fr ./Contrib/G++_linux/Release
mkdir -p  ./Contrib/G++_linux/Release

make --directory=./Contrib/G++_linux/Release \
	 --makefile=../../../Tests.mk
