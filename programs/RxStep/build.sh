#!/bin/bash

# built qextserialport
cd ../qextserialport/src/
qmake-qt4
make -j5

#build qlfDevise
cd ../../qlfdevices/
cmake .
make -j5

#build QRlxLib
cd ../QRlxLib/
cmake .
make -j5

#build RXstep
cd ../RxStep/
cmake -DQLFDEVICES_DIR=../qlfdevices/ -DQEXTSERIALPORT_DIR=../qextserialport/ -DQRLXLIB_DIR=../QRlxLib/ .
make -j5

#package RxStep
#make package