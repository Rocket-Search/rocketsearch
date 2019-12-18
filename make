#!/bin/bash

set -x

#read_file_infos
clear; rm -frv mp3_read.o; g++-7 -Wall -O3 -c mp3_read.cpp;rm -frv flac_read.o; g++-7 -O3 -fPIC -Wall -c flac_read.cpp ; rm -frv pdf_read.o; g++-7 -O3 -fPIC -Wall -c pdf_read.cpp ;rm -frv read_file_infos.o; g++-7 -O3 -fPIC -Wall -c read_file_infos.cpp ; rm -frv read_file_infos; g++-7 -O3 -fPIC -Wall -pthread -lboost_system -lboost_filesystem -lmagic -lssl -lcrypto -licui18n -licuuc -licudata -o read_file_infos read_file_infos.o mp3_read.o flac_read.o pdf_read.o -static-libstdc++ -ltag -lz

#client
rm -frv client_3; g++-7 -O3 -Wall -lpthread client_3.cpp -o client

#start_index
rm -frv start_index; g++-7 -O3 -fPIC -Wall -lpthread start_index.cpp -o start_index -static-libstdc++;

#config 
echo "redis server = 127.0.0.1" >> config.cfg
echo "redis port = 6379" >> config.cfg
echo "ms word = true" >> config.cfg
echo "ms excel = true" >> config.cfg
echo "ascii_and_pdf file max read lines = 8" >> config.cfg
echo "ascii file max read chars = 1024" >> config.cfg
echo "exe_dll infos = true" >> config.cfg
echo "exe dll info binary path = /usr/bin/get_exe_dll_info_v2.exe" >> config.cfg
echo "ms excel ram dev = /tmp/ram_dev/" >> config.cfg
echo "md5sum = true" >> config.cfg
echo "libreoffice timeout = 300" >> config.cfg
echo "read_file_info timeout = 500" >> config.cfg
echo "license key = U2FsdGVkX1+/+B3kAlKOjYCT4QegoasjcQdWFo42DTArxkzOnxe6WsT+lFWmkDpF#U2FsdGVkX1/uNgnvPy7mA9uby0gpc05mj5NbmaPNaQdGFWlBilpPuIF0I0a/bbuG\npOho1HMBsYome5AuVi6LgiD/LEuSI5FlkydwFqkiLCq4683x7fo9YI1eSXC23tK1\nE2t3HdAkMEyCsnRc5bbrpA##" >> config.cfg
echo "edition key = N2Q0YmFmNmIzZTM0MTFkMTVmMDYK" >> config.cfg
echo "network throttle = 5" >> config.cfg
echo "core usage = 4" >> config.cfg
echo "mp3_flac_tag = true" >> config.cfg
echo "pdf = true" >> config.cfg
