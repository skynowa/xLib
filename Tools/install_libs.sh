#!/usr/bin/env bash
#
# https://stackoverflow.com/questions/394230/how-to-detect-the-os-from-a-bash-script
#


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
	# Mac OSX
	sudo brew install \
		openssl
elif [[ "$OSTYPE" == "cygwin" ]]; then
	# POSIX compatibility layer and Linux environment emulation for Windows
elif [[ "$OSTYPE" == "msys" ]]; then
	# Lightweight shell and GNU utilities compiled for Windows (part of MinGW)
elif [[ "$OSTYPE" == "win32" ]]; then
	# I'm not sure this can happen.
elif [[ "$OSTYPE" == "freebsd"* ]]; then
	# ...
else
	# Unknown
fi
