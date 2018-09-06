#!/bin/bash

sudo apt-get -y install curl
curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
apt-get install -y nodejs

npm install -g npm

sudo apt-get -y install build-essential libtool autoconf automake uuid-dev
sudo apt-get -y install libzmq-dev libuv

wget https://github.com/zeromq/zeromq4-1/releases/download/v4.1.5/zeromq-4.1.5.tar.gz
tar xvzf zeromq-4.1.5.tar.gz
cd zeromq-4.1.5
./configure
make
sudo make install
sudo ldconfig


