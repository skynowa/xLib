sudo apt-get install \
	libx11-xcb-dev \
	libssl-dev \
	libssh2-1-dev \
	default-libmysqlclient-dev \
	# libcurl4-openssl-dev
	# libcurl4-nss-dev
	# libcurl4-gnutls-dev

# libcurl
TEMP_DEB="$(mktemp)" &&
wget -O "$TEMP_DEB" 'http://security.ubuntu.com/ubuntu/pool/main/c/curl/libcurl4-openssl-dev_7.68.0-1ubuntu2.2_amd64.deb' &&
sudo dpkg -i "$TEMP_DEB"
rm -f "$TEMP_DEB"
