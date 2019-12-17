#!/bin/bash

set -x

DIRECTORY=$(cd `dirname $0` && pwd)
#echo $DIRECTORY
#cd /tmp
#cd $DIRECTORY
#pwd
#sleep 30

#LibreSSL###################################################################################################################################
#cd /tmp
#echo "compile LibreSSL"
#wget  https://ftp.openbsd.org/pub/OpenBSD/LibreSSL/libressl-2.7.3.tar.gz
#tar -xzf libressl-2.7.3.tar.gz
#cd libressl-2.7.3/
#./configure --bindir=/usr/bin --sbindir=/usr/sbin --libdir=/usr/lib64 --includedir=/usr/include --enable-windows-ssp --enable-extratests
#make
#make install
#cp -frv crypto/.libs/* /lib
#cp -frv crypto/.libs/* /lib64/
#cp -frv include/* /usr/include/
#openssl version
#rm -fr /tmp/libressl*
######################################################################################################################################

#Samba######################################################################################################################################
#cd /tmp
#echo "compile Samba"
#zypper --non-interactive --no-gpg-checks install libacl-devel python-devel gnutls-devel gnutls libacl-devel openldap2-devel
#wget https://download.samba.org/pub/samba/stable/samba-4.8.2.tar.gz
#tar -xzf samba-4.8.2.tar.gz 
#cd samba-4.8.2/
#./configure --bindir=/usr/bin --sbindir=/usr/sbin --sysconfdir=/etc/samba --localstatedir=/var --libdir=/usr/lib64 --includedir=/usr/include
#make
#mkdir /etc/samba
#mkdir /var/log/samba
#make install
#mkdir /var/locks/usershares
#chown -R root:root /var/locks/usershares
#chmod -R 600 /var/locks/usershares
#chmod -R +t /var/locks/usershares
#smbd --version
#nmbd --version
#rm -fr /tmp/samba*
######################################################################################################################################

#NFS#####################################################################################################################################
#echo "Install NFS Server"
#zypper --non-interactive --no-gpg-checks install nfs-client nfs-kernel-server 
######################################################################################################################################

#Block RAM Device######################################################################################################################################
echo "configure Block RAM Device"
modprobe brd rd_size=256000
mknod -m 660 /dev/ram0 b 1 0
ls -al /dev/ram*
mkfs.ext3 -F /dev/ram0
mkdir /tmp/ram_dev
mount /dev/ram0 /tmp/ram_dev
######################################################################################################################################

#GNU Tools#####################################################################################################################################
#timeout --version
#xargs --version
#find --version
######################################################################################################################################

#Nginx#####################################################################################################################################
cd /tmp
echo "compile nginx"
wget http://nginx.org/download/nginx-1.14.0.tar.gz
tar -xzf nginx-1.14.0.tar.gz
cd nginx-1.14.0/
mkdir -p /usr/local/nginx/sbin
./configure --prefix=/usr/local/nginx --sbin-path=/usr/local/nginx/sbin
make
make install
ln -s /usr/local/nginx/sbin/nginx /usr/sbin/nginx
rm -fr /tmp/nginx*
######################################################################################################################################

#PHP######################################################################################################################################
zypper --non-interactive --no-gpg-checks install libxml2-2 libxml2-devel

cd /tmp
wget ftp://xmlsoft.org/libxml2/libxml2-2.9.8.tar.gz
tar -xvzf libxml2-2.9.8.tar.gz
cd libxml2-2.9.8
./configure --bindir=/usr/bin --sbindir=/usr/sbin --libdir=/usr/lib64 --includedir=/usr/include
make
make install
rm -fr /tmp/libxml*

cd /tmp
git clone https://gitlab.gnome.org/GNOME/libxslt.git
cd libxslt
./autogen.sh
./configure --bindir=/usr/bin --sbindir=/usr/sbin --libdir=/usr/lib64 --includedir=/usr/include
make
make install
rm -fr /tmp/libxslt*

cd /tmp
wget http://www.php.net/distributions/php-7.2.6.tar.xz
tar -xf php-7.2.6.tar.xz
cd php-7.2.6
mkdir -p /usr/local/nginx/php
sed -i 's/defined (LIBRESSL_VERSION_NUMBER)/(defined(LIBRESSL_VERSION_NUMBER) \&\& LIBRESSL_VERSION_NUMBER < 0x20700000L)/g' ext/openssl/openssl.c
./configure --with-openssl --with-zlib --enable-calendar --enable-mbstring --enable-zip --with-gd --with-gettext --enable-bcmath --enable-sockets --with-xsl --enable-fpm
make
make install
cp -frv php.ini-production /usr/local/lib64/php.ini
cp -frv nginx.con /usr/local/nginx/conf/
rm -fr /tmp/php*
#
#nohup php-cgi -b 127.0.0.1:9000 &
#nginx
######################################################################################################################################

#redis######################################################################################################################################
cd /tmp
wget http://download.redis.io/releases/redis-4.0.9.tar.gz
tar -xzf redis-4.0.9.tar.gz
cd redis-4.0.9
make
make install
rm -fr /tmp/redis*
redis-server &
sleep 10
redis-cli config set save ""
redis-cli config set appendonly no
/usr/local/bin/redis-cli config set protected-mode no
swapoff -a
echo 1 > /proc/sys/vm/overcommit_memory
echo never > /sys/kernel/mm/transparent_hugepage/enabled
echo 1 > /proc/sys/net/ipv4/tcp_tw_reuse
######################################################################################################################################

#LibreOffice######################################################################################################################################
zypper  --non-interactive --no-gpg-checks install libreoffice
######################################################################################################################################

#wine######################################################################################################################################
zypper --non-interactive --no-gpg-checks install gcc-32bit gcc-c++-32bit gcc-go-32bit gcc7-c++-32bit libX11-devel-32bit libXRes1-32bit libXres-devel-32bit freetype2-devel-32bit libftgl2-32bit libXrender-devel-32bit libxml2-2-32bit libxml2-devel-32bit \
libxml++-2_6-2-32bit libxslt-devel-32bit libgnutls-devel-32bit libjpeg62-32bit libjpeg62-devel-32bit libjpeg62-devel-32bit libtiff5-32bit \
libpng16-devel-32bit libpng12-devel-32bit png++-devel libpng16-compat-devel-32bit libpng16-tools \
libgnutls-devel-32bit Mesa-libGL1-32bit openldap2-devel-32bit libXcursor-devel-32bit libXi-devel-32bit libxshmfence-devel \
libxcb-shape0-32bit libXxf86vm-devel-32bit libXrandr-devel-32bit libXfixes-devel-32bit libXinerama-devel-32bit libXcomposite-devel-32bit \
libXrandr-devel-32bit libglue-devel-32bit libOSMesa-devel-32bit opencl-cpp-headers libclc libpcap-devel-32bit libdbus-c++-1-1-32bit \
libglut3-32bit libOpenCL1 libdbus-c++-glib-1-1-32bit libncurses5-32bit libv4l-devel-32bit 
cd /tmp
wget https://dl.winehq.org/wine/source/3.0/wine-3.0.tar.xz
tar -xf wine-3.0.tar.xz
cd wine-3.0
./configure --bindir=/usr/bin --sbindir=/usr/sbin --libdir=/usr/lib64 --includedir=/usr/include
make
make install
timeout 10s winecfg
killall -9 wineboot.exe services.exe rundll32.exe explorer.exe control.exe wineserver
wget http://dl.winehq.org/wine/wine-mono/4.7.3/wine-mono-4.7.3.msi
wine msiexec /i wine-mono-4.7.3.msi
rm -fr /tmp/wine*
cd $DIRECTORY
cp -frv ../rs-extra-libs/wine_ms_dll/x86/* /usr/bin
######################################################################################################################################

#Boost Libs######################################################################################################################################
#cd /tmp
#wget https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.gz
#tar -xzf boost_1_67_0.tar.gz
#cd boost_1_67_0
#./bootstrap.sh
#./b2 install --prefix=/usr/
#rm -fr /tmp/boost*
######################################################################################################################################

#ICU4C######################################################################################################################################
#cd /tmp
#wget http://download.icu-project.org/files/icu4c/61.1/icu4c-61_1-src.tgz
#tar -xzf icu4c-61_1-src.tgz
#cd icu/source
#chmod +x runConfigureICU configure install-sh
#./runConfigureICU Linux
#make
#make install
#rm -fr /tmp/icu*
######################################################################################################################################

#Libmagic######################################################################################################################################
cd /tmp
wget ftp://ftp.astron.com/pub/file/file-5.33.tar.gz
tar -xzf file-5.33.tar.gz 
cd file-5.33/
./configure --bindir=/usr/bin --sbindir=/usr/sbin --libdir=/usr/lib64 --includedir=/usr/include
make
make install
file --version 
rm -fr /tmp/file*
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

#JsGrid######################################################################################################################################
cd /tmp
wget https://github.com/tabalinas/jsgrid/archive/v1.5.3.tar.gz
tar -xzf v1.5.3.tar.gz
cp -frv jsgrid-1.5.3  /usr/local/nginx/html/
cd /usr/local/nginx/html/
mv jsgrid-1.5.3 jsgrid
rm -fr /tmp/v1.5.3*
rm -fr /tmp/jsgrid*
######################################################################################################################################

#ghostscript######################################################################################################################################
cd /tmp
wget https://github.com/ArtifexSoftware/ghostpdl-downloads/releases/download/gs923/ghostscript-9.23.tar.gz
tar -xzf ghostscript-9.23.tar.gz 
cd ghostscript-9.23/
./autogen.sh 
./configure --bindir=/usr/bin --sbindir=/usr/sbin --libdir=/usr/lib64 --includedir=/usr/include
make
make install
rm -fr cd /tmp/ghost*
######################################################################################################################################

#libtag ??######################################################################################################################################
######################################################################################################################################

#flac (libflac)######################################################################################################################################
cd  /tmp/
wget https://ftp.osuosl.org/pub/xiph/releases/flac/flac-1.3.2.tar.xz
tar -xf flac-1.3.2.tar.xz
cd flac-1.3.2
./autogen.sh
./configure --bindir=/usr/bin --sbindir=/usr/sbin --libdir=/usr/lib64 --includedir=/usr/include
make
make install
rm -frv /tmp/flac*
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
cp -frv ../rs-frontend/client.php /usr/local/nginx/html
cp -frv ../rs-frontend/back.css /usr/local/nginx/html
cp -frv ../rs-frontend/button.css /usr/local/nginx/html
cp -frv ../rs-frontend/css-input.css /usr/local/nginx/html
cp -frv ../rs-frontend/config.cfg /usr/local/nginx/html
##
#Libs kopieren
cp -frv ../rs-extra-libs/* /usr/lib64/
ldconfig
#
#Nginx starten#########
cp -frv ../rs-frontend/nginx_self_compiled/* /usr/local/nginx/conf/
nohup php-cgi -b 127.0.0.1:9000 &
nginx
######################################################################################################################################
















