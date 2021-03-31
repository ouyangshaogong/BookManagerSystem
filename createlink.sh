#!/bin/sh

export HOME_DIR=$(cd $(dirname $0); pwd)

cd /usr/local/lib

if [ -L "libmsgproto.so" ]
then
    echo "libmsgproto.so is exist"
else
    sudo ln -s $HOME_DIR/lib/libmsgproto.so /usr/local/lib
fi

if [ -L "libtaskmgr.so" ]
then
    echo "libtaskmgr.so is exist"
else
    sudo ln -s $HOME_DIR/lib/libtaskmgr.so /usr/local/lib
fi

if [ -L "libmsgcomclient.so" ]
then
    echo "libmsgcomclient.so is exist"
else
    sudo ln -s $HOME_DIR/lib/libmsgcomclient.so /usr/local/lib
fi

if [ -L "libbookutils.so" ]
then
    echo "libbookutils.so is exist"
else
    sudo ln -s $HOME_DIR/lib/libbookutils.so /usr/local/lib
fi

if [ -L "libbookmodel.so" ]
then
    echo "libbookmodel.so is exist"
else
    sudo ln -s $HOME_DIR/lib/libbookmodel.so /usr/local/lib
fi

if [ -L "libbookmgrdao.so" ]
then
    echo "libbookmgrdao.so is exist"
else
    sudo ln -s $HOME_DIR/lib/libbookmgrdao.so /usr/local/lib
fi

if [ -L "libbookmgrservice.so" ]
then
    echo "libbookmgrservice.so is exist"
else
    sudo ln -s $HOME_DIR/lib/libbookmgrservice.so /usr/local/lib
fi

if [ -L "libusermgrservice.so" ]
then
    echo "libusermgrservice.so is exist"
else
    sudo ln -s $HOME_DIR/lib/libusermgrservice.so /usr/local/lib
fi

if [ -L "libmvcframe.so" ]
then
    echo "libmvcframe.so is exist"
else
    sudo ln -s $HOME_DIR/lib/libmvcframe.so /usr/local/lib
fi


cd $HOME_DIR
