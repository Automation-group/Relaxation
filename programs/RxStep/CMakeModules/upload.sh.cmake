#!/bin/sh
  
HOST='@UPLOAD_HOST@'
USER='@UPLOAD_USERNAME@'
DIR='@UPLOAD_DEST_DIR@'
FILE='@UPLOAD_FILE_NAME@.deb'
  
ftp -n $HOST <<END_SCRIPT
user $USER
cd $DIR
put $FILE
bye
END_SCRIPT

ssh $USER@$HOST sh $DIR/reindexDEB.sh
exit 0