# Требования к ПО
#	Cmake (2.6 >=)
#	g++ (v4.4 >=)
#	Qt4 (v4.4.6.2 >=) 
#	QWT (0.2.7 >=)
#	Boost (v1.4 >=)

# Сборка проекта
# 1. Необходимо получить и собрать QExtSerialPort
cd /tmp
hg clone http://bitbucket.org/lexaficus/qextserialport
cd qextserialport
qmake-qt4
make

# 2. Необходимо получить и собрать QlfDevices
cd /tmp
hg clone http://bitbucket.org/lexaficus/qlfdevices
cd qlfdevices
mkdir build
cd build
cmake .
make

# 3. Необходимо собрать QRlxLib
cd /tmp
svn co https://srvlab5l/svn/aapavlyukov/Релаксация/QRlxLib
cd QRlxLib
mkdir build
cd build
cmake .
make

# 4. Собрать RxStep
cd /tmp 
svn co https://srvlab5l/svn/aapavlyukov/Релаксация/RxStep/trunk/RxStep
cd RxStep
mkdir build
cd build
cmake -DQLFDEVICES_DIR=../qlfdevices/ -DQEXTSERIALPORT_DIR=../qextserialport/ -DQRLXLIB_DIR=../QRlxLib/ .
make -j4

# 5. Cборка deb пакета
make package
