wget -q -O - http://files.viva64.com/etc/pubkey.txt | \
  sudo apt-key add -

sudo wget -O /etc/apt/sources.list.d/viva64.list \
  http://files.viva64.com/etc/viva64.list

sudo apt-get update
sudo apt-get install pvs-studio
