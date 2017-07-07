#!/bin/bash

# built qextserialport
cd ../qextserialport/src/
qmake-qt4
make -j2

#build qlfDevise
cd ../../qlfdevices/
cmake .
make -j2

#build TUBTest
cd ../SMDTest/
cmake -DQLFDEVICES_DIR=../qlfdevices/ -DQEXTSERIALPORT_DIR=../qextserialport/ .
make -j2