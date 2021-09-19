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
sudo pip install pygments

sudo apt-get clean
sudo rm -rf /var/lib/apt/lists/*
