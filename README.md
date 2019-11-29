# rocket-search


in-memory file index search engine

Based on redis in-memory NoSQL database.

Indexing fetaures:

	doc and docx files
	xls and xlsx files
	PDF
	ascii files
	EXE Fileversion
	DLL Fileversion
	MP3 Tags
	FLAC Tags
	create md5 hash from each file
	changetime of file
	modificationtime of file
	size of file
	of every file, name and path
	
you can parallelize the indexing process releated to you amount of cores.

Prerequirements:

	Wine + wine-mono Libs
	libreoffice
	Block RAM Device (für excel Libreoffice)
	timeout
	xargs
	find
	LibreSSL (OpenSSL)
	jsGrid
	libmagic (file)
	ICU4C
	Gcc 7 / gcc 6 for debian
	nginx
	php for nginx
	redis
	nohup
	Boost
	shell (sh)
	ulimt = unlimited
	cat
	tagLib
	flac  (metaflac) libflag
	gs (Ghost Script)
	Visual Studio 2017 Community Edition (C++/CLR)

easy setup with install script
Web frontend and Linux commandline client is included

Program is written in c++ .
Static linked executables. You can run the programm without compiling.

best usage for SMB and NFS file shares

If you want to join the programming team,
please email to software.moore@gmail.com
or register under http://register.ddns.net/index.php

online Demo: http://rocketsearch.ddns.net:8081/client.php

