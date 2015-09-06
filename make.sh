#!/bin/sh
./autogen.sh;
aclocal;automake --add-missing;./configure --with-incompatible-bdb;make

