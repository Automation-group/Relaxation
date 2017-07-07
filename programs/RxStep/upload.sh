#!/bin/sh
  
HOST='srvlab5ld'
USER='aapavlyukov'
DIR='/home/ftp/Distr/APT'
FILE='RxStep-1.0.0.3-Linux.deb'
  
ftp -n $HOST <<END_SCRIPT
user $USER
cd $DIR
put $FILE
bye
END_SCRIPT

ssh $USER@$HOST sh $DIR/reindexDEB.sh
exit 0
