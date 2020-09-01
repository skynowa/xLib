sudo apt-get install \
	libx11-xcb-dev \
	libssl-dev \
	libssh2-1-dev \
	default-libmysqlclient-dev \
	# libcurl4-openssl-dev
	# libcurl4-nss-dev
	# libcurl4-gnutls-dev

# libcurl
cd ../../xLib-data/Libs/ubuntu-20.04

sudo dpkg -i libcurl4-openssl-dev_7.68.0-1ubuntu2.2_amd64.deb
