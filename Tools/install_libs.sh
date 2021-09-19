#!/usr/bin/env bash
#
# https://stackoverflow.com/questions/394230/how-to-detect-the-os-from-a-bash-script
#

echo "OSTYPE: ${OSTYPE}"

if [[ "$OSTYPE" == "linux-gnu"* ]]; then
	sudo rm -rf /var/lib/apt/lists/*

	sudo apt-get update
	sudo apt-get install -y --no-install-recommends \
		libx11-xcb-dev \
		libssl-dev \
		libssh2-1-dev \
		default-libmysqlclient-dev \
		\
		libcurl4-openssl-dev
		# libcurl4-nss-dev
		# libcurl4-gnutls-dev

	sudo apt-get clean
	sudo rm -rf /var/lib/apt/lists/*

	sudo pip install pygments
elif [[ "$OSTYPE" == "darwin"* ]]; then
	# libssl
	# https://qastack.ru/superuser/1089390/how-to-install-libssl-dev-libffi-dev-on-mac-os
	export LDFLAGS="-L/usr/local/opt/openssl@1.1/lib"
	export CPPFLAGS="-I/usr/local/opt/openssl@1.1/include"
elif [[ "$OSTYPE" == "cygwin" ]]; then
	echo ""
elif [[ "$OSTYPE" == "msys" ]]; then
	echo ""
elif [[ "$OSTYPE" == "win32" ]]; then
	echo ""
elif [[ "$OSTYPE" == "freebsd"* ]]; then
	echo ""
else
	echo ""
fi
