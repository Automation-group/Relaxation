#!/bin/bash

# built qextserialport
cd ../qextserialport/src/
qmake-qt4
make -j2

#build qlfDevise
cd ../../qlfdevices/
cmake .
make -j2

#build QRlxLib
cd ../QRlxLib/
cmake .
make -j2

#build RXstep
cd ../RxStep/
cmake -DQLFDEVICES_DIR=../qlfdevices/ -DQEXTSERIALPORT_DIR=../qextserialport/ -DQRLXLIB_DIR=../QRlxLib/ .
make -j2

#package RxStep
make package