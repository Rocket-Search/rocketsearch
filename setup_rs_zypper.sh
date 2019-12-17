#!/bin/bash

#set -x

DIRECTORY=$(cd `dirname $0` && pwd)

#LibreSSL###################################################################################################################################
#zypper --non-interactive --no-gpg-checks install libressl libressl-devel
#zypper --non-interactive --no-gpg-checks  install --force-resolution libressl libressl-devel
###################################################################################################################################

#Samba######################################################################################################################################
#zypper --non-interactive --no-gpg-checks  install --force-resolution  samba samba-client
###################################################################################################################################

#NFS#####################################################################################################################################
#zypper --non-interactive --no-gpg-checks  install --force-resolution   nfs-client nfs-kernel-server
######################################################################################################################################

#Block RAM Device######################################################################################################################################
echo "configure Block RAM Device"
modprobe brd rd_size=256000
ls -al /dev/ram*
mkfs.ext3 -F /dev/ram0
mkdir /tmp/ram_dev
mount /dev/ram0 /tmp/ram_dev
######################################################################################################################################

#GNU Tools#####################################################################################################################################
#timeout --version
#xargs –version
#find –version
######################################################################################################################################

#Nginx#####################################################################################################################################
zypper --non-interactive --no-gpg-checks  install --force-resolution nginx
######################################################################################################################################

#PHP######################################################################################################################################
zypper --non-interactive --no-gpg-checks install --force-resolution libxml2-2 libxml2-devel php7 php7-devel php7-fastcgi
######################################################################################################################################

#redis######################################################################################################################################
zypper --non-interactive --no-gpg-checks install --force-resolution redis
redis-server &
sleep 10
redis-cli config set save ""
redis-cli config set appendonly no
redis-cli config set protected-mode no
swapoff -a
echo 1 > /proc/sys/vm/overcommit_memory
echo never > /sys/kernel/mm/transparent_hugepage/enabled
echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse
######################################################################################################################################

######################################################################################################################################

#LibreOffice######################################################################################################################################
zypper  --non-interactive --no-gpg-checks install --force-resolution libreoffice
######################################################################################################################################

#wine######################################################################################################################################
zypper --non-interactive --no-gpg-checks install --force-resolution wine wine-devel wine-devel-32bit
timeout 10s winecfg
killall -9 wineboot.exe services.exe rundll32.exe explorer.exe control.exe wineserver
wget http://dl.winehq.org/wine/wine-mono/4.7.3/wine-mono-4.7.3.msi
wine64 msiexec /i wine-mono-4.7.3.msi
cd $DIRECTORY
cp -frv ../rs-extra-libs/wine_ms_dll/x86/* /usr/bin
######################################################################################################################################

#wget  https://raw.githubusercontent.com/Winetricks/winetricks/master/src/winetricks
#chmod 777 winetricks
#winetricks forcemono
######################################################################################################################################

#Boost Libs######################################################################################################################################
#zypper --non-interactive --no-gpg-checks install --force-resolution libboost_filesystem1_66_0 libboost_filesystem1_66_0-devel libboost_system1_66_0 libboost_system1_66_0-devel
######################################################################################################################################

#ICU4C######################################################################################################################################
#zypper --non-interactive --no-gpg-checks install --force-resolution icu libicu-devel
######################################################################################################################################

#Libmagic######################################################################################################################################
#zypper --non-interactive --no-gpg-checks install --force-resolution file-magic file-devel libmagic1
mkdir -p /usr/local/share/misc/
cp -frv /usr/share/misc/magic* /usr/local/share/misc/
######################################################################################################################################

#gcc/g++######################################################################################################################################
#g++ --version
######################################################################################################################################

#cpp redis######################################################################################################################################
#cd /tmp
#zypper --non-interactive --no-gpg-checks install cmake
#git clone https://github.com/Cylix/cpp_redis.git
#cd cpp_redis
#git submodule init && git submodule update
#mkdir build && cd build
#cmake .. -DCMAKE_BUILD_TYPE=Release
#make
#make install
#rm -fr /tmp/cpp_redis*
######################################################################################################################################

#ghostscript######################################################################################################################################
zypper --non-interactive --no-gpg-checks install --force-resolution ghostscript ghostscript-devel ghostscript-fonts ghostview
######################################################################################################################################

#flac######################################################################################################################################
zypper --non-interactive --no-gpg-checks install --force-resolution flac flac-devel
######################################################################################################################################

#JsGrid######################################################################################################################################
cd /tmp
wget https://github.com/tabalinas/jsgrid/archive/v1.5.3.tar.gz
tar -xzf v1.5.3.tar.gz
cp -frv jsgrid-1.5.3 /srv/www/htdocs/
cd /srv/www/htdocs/
mv jsgrid-1.5.3 jsgrid
rm -fr /tmp/v1.5.3*
rm -fr /tmp/jsgrid*
######################################################################################################################################

#Rocket Search######################################################################################################################################
cd $DIRECTORY
cp -frv ../rs-backend/read_file_infos /usr/bin
cp -frv ../rs-backend/start_index /usr/bin
cp -frv ../rs-backend/get_exe_dll_info_v2.exe /usr/bin
#
mkdir -p /etc/rs
cp -frv  ../rs-backend/config.cfg /etc/rs
ln -s /etc/rs/config.cfg /usr/bin/config.cfg
#
cp -frv ../rs-frontend/client.php /srv/www/htdocs
cp -frv ../rs-frontend/back.css /srv/www/htdocs
cp -frv ../rs-frontend/button.css /srv/www/htdocs
cp -frv ../rs-frontend/css-input.css /srv/www/htdocs
cp -frv ../rs-frontend/config.cfg /srv/www/htdocs
##
#Libs kopieren
cp -frv ../rs-extra-libs/* /usr/lib64/
ldconfig
#
#Nginx starten#########
cp -frv ../rs-frontend/nginx_suse_cfg/* /etc/nginx/
nohup php-cgi -b 127.0.0.1:9000 &
nginx
######################################################################################################################################







