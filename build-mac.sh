#!/usr/bin/env bash

wget https://invisible-island.net/datafiles/release/ncurses.tar.gz
tar -xf ncurses.tar.gz && cd ncurses || exit
./configure --enable-widec
sudo make install