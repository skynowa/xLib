
#!/bin/bash
#
# Install AMP C++
#

set -ex

CURL_VERSION="7.79.1"
CURL_ARCHIVE="curl.tar.gz"

echo ""
echo "[Download...]"
curl -L https://github.com/curl/curl/releases/download/curl-7_79_1/curl-${CURL_VERSION}.tar.gz -o ${CURL_ARCHIVE}


echo ""
echo "[Unpack...]"
tar zxpf ${CURL_ARCHIVE}
rm ${CURL_ARCHIVE}

echo ""
echo "[Build...]"

mkdir curl-${CURL_VERSION}_build
cd curl-${CURL_VERSION}_build
cmake ../curl-${CURL_VERSION}_build
cmake --build . -- -j4

echo ""
echo "[Install...]"
cmake --build . --target install
