#!/bin/bash

#set -x

DIRECTORY=$(cd `dirname $0` && pwd)

echo "Setup für Debian 9"
echo "Es müssen noch einige Packete installiert werden..."
#sleep 10

apt-get --assume-yes install gcc-6-locales locales locales-all util-linux-locales

export XTERM_LOCALE=en_US.UTF-8
export LC_CTYPE=en_US.UTF-8
export LANG=en_US.UTF-8
export LANGUAGE=en_US.UTF-8

locale
 
#OpenSSL 1.1.0f  25 May 2017
apt-get --assume-yes install openssl

apt-get --assume-yes install samba samba-libs smbclient cifs-utils

apt-get --assume-yes install nfs-common nfs-kernel-server nfswatch nfstrace

#Block RAM Device######################################################################################################################################
apt-get --assume-yes install kmod
echo "configure Block RAM Device"
modprobe brd rd_size=256000
mknod -m 660 /dev/ram0 b 1 0
ls -al /dev/ram*
mkfs.ext3 -F /dev/ram0
mkdir /tmp/ram_dev
mount /dev/ram0 /tmp/ram_dev
######################################################################################################################################

apt-get --assume-yes install nginx nginx-common nginx-full

apt-get --assume-yes install php7.0 php7.0-dev php7.0-cgi php7.0-fpm

apt-get --assume-yes install redis-server redis-tools

apt-get --assume-yes install libreoffice libreoffice-base-core libreoffice-base-drivers

apt-get --assume-yes install wine  wine64 wine64-preloader wine64-tools libwine-development libwine-development-dev wine-development
dpkg --add-architecture i386 && apt-get update && apt-get --assume-yes install wine32
################
timeout 10s winecfg
killall -9 wineboot.exe services.exe rundll32.exe explorer.exe control.exe wineserver
cd /tmp/
wget http://dl.winehq.org/wine/wine-mono/4.7.3/wine-mono-4.7.3.msi -P /tmp/
wine msiexec /i /tmp/wine-mono-4.7.3.msi
rm -fr /tmp/wine*
cd $DIRECTORY
cp -frv ../rs-extra-libs/wine_ms_dll/x86/* /usr/bin
################

apt-get --assume-yes install libboost-all-dev libboost-dev libboost-filesystem-dev libboost-system-dev libboost-filesystem1.62-dev

apt-get --assume-yes install icu-devtools libicu57
 
apt-get --assume-yes install libmagic-dev libmagic1 file

apt-get --assume-yes install gcc g++       

apt-get --assume-yes install libtag-extras-dev libtag-extras1 libtaglib-cil-dev libtaglib2.1-cil

apt-get --assume-yes install flac libflac++-dev libflac-dev

apt-get --assume-yes install ghostscript ghostscript-dbg ghostscript-x gsfonts gsfonts-x11

#Nginx starten######################################################################################################################################
cp -frv ../rs-frontend/nginx_debian_cfg/default /etc/nginx/sites-available/default
nginx
nohup php-cgi -b 127.0.0.1:9000 &
######################################################################################################################################

#Rocket Search######################################################################################################################################
cd $DIRECTORY
cp -frv ../rs-backend/read_file_infos /usr/bin
cp -frv ../rs-backend/start_index /usr/bin
cp -frv ../rs-backend/get_exe_dll_info_v2.exe /usr/bin
#
mkdir /etc/rs
cp -frv  ../rs-backend/config.cfg /etc/rs
ln -s /etc/rs/config.cfg /usr/bin/config.cfg
#
cp -frv ../rs-frontend/client.php /var/www/html/
cp -frv ../rs-frontend/back.css /var/www/html/
cp -frv ../rs-frontend/button.css /var/www/html/
cp -frv ../rs-frontend/css-input.css /var/www/html/
cp -frv ../rs-frontend/config.cfg /var/www/html/
##
#Libs kopieren
cp -frv ../rs-extra-libs/* /usr/lib/
ldconfig
######################################################################################################################################

#JsGrid######################################################################################################################################
apt-get --assume-yes install wget
cd /tmp
wget https://github.com/tabalinas/jsgrid/archive/v1.5.3.tar.gz
tar -xzf v1.5.3.tar.gz
mv -v jsgrid-1.5.3  /var/www/html/
cd /var/www/html/
mv jsgrid-1.5.3 jsgrid
######################################################################################################################################


#Redis Starten#####################################################################################################################################
nohup redis-server &
sleep 10
redis-cli config set save ""
redis-cli config set appendonly no
redis-cli config set protected-mode no
#swapoff -a
echo 1 > /proc/sys/vm/overcommit_memory
echo never > /sys/kernel/mm/transparent_hugepage/enabled
echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse
######################################################################################################################################

#Ready to use######################################################################################################################################
echo "Konfig erfolgreich angeschlossen ..."
echo "Indizierung kann gestartet werden"
######################################################################################################################################

