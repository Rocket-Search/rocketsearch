//##################
//## Einzeiler# clear; rm -frv mp3_read.o; g++-7 -Wall -O3 -c mp3_read.cpp;rm -frv flac_read.o; g++-7 -O3 -fPIC -Wall -c flac_read.cpp ; rm -frv pdf_read.o; g++-7 -O3 -fPIC -Wall -c pdf_read.cpp ;rm -frv read_file_infos.o; g++-7 -O3 -fPIC -Wall -c read_file_infos.cpp ; rm -frv read_file_infos; g++-7 -O3 -fPIC -Wall -pthread -lboost_system -lboost_filesystem -lmagic -lssl -lcrypto -licui18n -licuuc -licudata -o read_file_infos read_file_infos.o mp3_read.o flac_read.o pdf_read.o -static-libstdc++ -ltag -lz
//##################
//C_C++ Header
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string>
//algorithm fürs string klein machen
#include <algorithm>
//Zum Casten von Char Hex Array nach string (bei md5sum)
#include <iomanip>
#include <iostream>
#include <vector>
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <thread>
#include <time.h>
//File Time Modification####
#include <utime.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <cstdlib>
//Error Handling und Singal
//perror
#include <errno.h>
#include <signal.h>
#include <malloc.h>
#include <errno.h>
#include <sys/mman.h>
#include <csignal>
#include <iterator>
//Netzwerk Socket API
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <netdb.h>

//OpenSSL (LibreSSL) Header für md5sum
#include <openssl/md5.h>
//#
//Decrypt aes-256-cbc lizenz
//#include <openssl/conf.h>
//#include <openssl/evp.h>
//#include <openssl/err.h>
//#include <openssl/aes.h>

//Boost Header für libmagic
#include <boost/filesystem.hpp>

//file libmagic Header
#include <magic.h>

//redis Header
//#include <cpp_redis/cpp_redis>

//ICU4C Unicode Header
#include "unicode/ucnv.h"
#include <unicode/unistr.h>
#include <unicode/ucnv.h>
#include <unicode/uchar.h>
#include <unicode/utypes.h>
#include "unicode/ucsdet.h"
#include "unicode/uclean.h"

//Boost trimmen. Wird zur Zeit nicht genutzt
//#include <boost/algorithm/string.hpp>
//#im code boost::trim_right(datei_inhalt);

using namespace std;
using namespace boost;

namespace fs = filesystem;

//Offentliche String Variabel fuer den Rueckgabwert der DB
//std::string public_string_rueckgabewert = "";

//Offentliche String Variabel fuer den SIGSEGV Pfad+Datei
std::string SIGSEGV_pfad_datei = "";

//Variablen für Object File mp3_read.o
string pfad_uebergabe_mp3;
string pfad_fuer_mp3;
string mp3_file_info_magic;
string mp3_tags_content;
//Variablen für Object File flac_read.o
string pfad_uebergabe_flac;
string pfad_fuer_flac;
string flac_file_info_magic;
string flac_tags_content;
//Variablen für Object File pdf_read.o
string pfad_uebergabe_pdf;
string pfad_fuer_pdf;
string pdf_file_info_magic;
string pdf_content;
string pdf_read_max_lines;

void signalHandler( int signum) 
{
	//cout << "Interrupt signal (" << signum << ") received.\n";
	//cout<<"PROBLEM read file info"<<endl;
	// cleanup and close up stuff here  
	//terminate program  

	//cout<<SIGSEGV_pfad_datei<<endl;
	
	string signum_string;
	std::stringstream ConvertStream_1;
	ConvertStream_1<<signum;
	ConvertStream_1>>signum_string;

	//SIGSEGV in Log File schreiben
	//cout<<"SIGSEGV"<<SIGSEGV_pfad_datei<<endl;
	
	//aktuelle System Zeit in variable schreiben###################
	time_t Zeitstempel;
    tm *nun;
    Zeitstempel = time(0);
    nun = localtime(&Zeitstempel);
	
	//Tag
	int tag;
	tag = nun->tm_mday;
	string current_tag_string;
	std::stringstream ConvertStream_2;
	ConvertStream_2<<tag;
	ConvertStream_2>>current_tag_string;
	//Formatierung falls die Zahl nur aus einer Ziffer besteht, eine Null vorn dran hängem
	int anzahl_ziffern = current_tag_string.length();
	//cout<<"anzahl_ziffern"<<anzahl_ziffern<<endl;
	if (anzahl_ziffern < 2)
	{
		current_tag_string = "0" + current_tag_string;
		//cout<<"current_tag_string"<<current_tag_string<<endl;
	}
	//cout<<current_tag_string<<endl;
	
	//Monat
	int monat;
	monat = nun->tm_mon+1;
	//cout << "The local date and time is: " << asctime(monat) << endl;
	string current_monat_string;
	std::stringstream ConvertStream_3;
	ConvertStream_3<<monat;
	ConvertStream_3>>current_monat_string;
	//cout<<current_monat_string<<endl;
	anzahl_ziffern = current_monat_string.length();
	if (anzahl_ziffern < 2)
	{
		current_monat_string = "0" + current_monat_string;
		//cout<<"current_stunde_string"<<current_stunde_string<<endl;
	}
	
	//Jahr
	int current_jahr;
	current_jahr = nun->tm_year+1900;
	string current_jahr_string;
	std::stringstream ConvertStream_4;
	ConvertStream_4<<current_jahr;
	ConvertStream_4>>current_jahr_string;
	//cout<<current_jahr_string<<endl;
	
	//Stunde
	int current_stunde;
	current_stunde = nun->tm_hour;
	string current_stunde_string;
	std::stringstream ConvertStream_5;
	ConvertStream_5<<current_stunde;
	ConvertStream_5>>current_stunde_string;
	//cout<<current_stunde_string<<endl;
	anzahl_ziffern = current_stunde_string.length();
	if (anzahl_ziffern < 2)
	{
		current_stunde_string = "0" + current_stunde_string;
		//cout<<"current_stunde_string"<<current_stunde_string<<endl;
	}
	
	//Minute
	int current_minute;
	current_minute = nun->tm_min;
	string current_minute_string;
	std::stringstream ConvertStream_6;
	ConvertStream_6<<current_minute;
	ConvertStream_6>>current_minute_string;
	//cout<<current_minute<<endl;
	anzahl_ziffern = current_minute_string.length();
	if (anzahl_ziffern < 2)
	{
		current_minute_string = "0" + current_minute_string;
		//cout<<"current_minute_string"<<current_minute_string<<endl;
	}
	
	//Sekunde
	int current_sekunde;
	current_sekunde = nun->tm_sec;
	string current_sekunde_string;
	std::stringstream ConvertStream_7;
	ConvertStream_7<<current_sekunde;
	ConvertStream_7>>current_sekunde_string;
	//cout<<current_sekunde_string<<endl;
	anzahl_ziffern = current_sekunde_string.length();
	if (anzahl_ziffern < 2)
	{
		current_sekunde_string = "0" + current_sekunde_string;
		//cout<<"current_sekunde_string"<<current_sekunde_string<<endl;
	}
	
	//Millisekunde
	int current_msec;
	timeval time;
	gettimeofday(&time, NULL);
	current_msec = time.tv_usec;
	string current_msec_string;
	std::stringstream ConvertStream_8;
	ConvertStream_8<<current_msec;
	ConvertStream_8>>current_msec_string;
	//cout<<current_msec_string<<endl;
	//Zeitstempel zusammenbauen
	string current_timestamp;
	current_timestamp = current_tag_string + "." + current_monat_string + "." + current_jahr_string + " " + current_stunde_string + ":" + current_minute_string + ":" + current_sekunde_string + "." + current_msec_string ;
	//cout<<"Systemzeit:"<<current_timestamp<<endl; 
	//##################

	ofstream sigsegv_file;
	sigsegv_file.open ("/var/log/rs_error.log", ios::app );
	sigsegv_file<<current_timestamp<<" # "<<SIGSEGV_pfad_datei<<endl;
	sigsegv_file.close();
		
	/*
	//in redis schreiben
	cpp_redis::client client;
	client.connect();
	SIGSEGV_pfad_datei = "#SIGSEGV# " + SIGSEGV_pfad_datei;
	//cout<<SIGSEGV_pfad_datei<<endl;
	client.set(SIGSEGV_pfad_datei, signum_string);
	client.sync_commit();
	*/
	exit(0);
	//exit(signum);  
}

string read_content (string &extension, string &filename, string &pfad_plus_dateiname, string &datei_inhalt, string &file_type, string &file_encoding, string ms_word_para, string ms_excel_para, string ascii_read_max_lines, string ascii_read_max_chars, string exe_dll_info, string exe_dll_info_binary, string excel_ram_dev, string mp3_para, string pdf_para)
{
	
	//cout<<"In funktion EXT: "<<extension<<endl;
	//cout<<"In funktion Filename: "<<filename<<endl;
	//cout<<"In funktion Pfad: "<<pfad_plus_dateiname<<endl;
	//cout<<"In funktion Inhalt: "<<datei_inhalt<<endl;
	//datei_inhalt = "Test aus Funktion";
	//cout<<"file_type#"<<file_type<<endl;
	
	//Parameter##
	//cout<<ms_word_para<<endl;
	//cout<<ms_excel_para<<endl;
	//cout<<ascii_read_max_lines<<endl;
	//cout<<ascii_read_max_chars<<endl;
	//cout<<exe_dll_info<<endl;
	
	//Extension klein machen damit if keine probleme hat
	transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
	//cout<<"EXT klein: "<<extension<<endl;
	
	//Fileoperation mittels ifstream
	ifstream fileoperation;
	
	//variable leeren
	datei_inhalt = "" ; 
	
	//Standard ASCII Files##############################################################
	if (file_type == "text/plain")
			{
				//datei_inhalt = "Test aus funkt/if";
				//cout<<"file_encoding: "<<file_encoding<<endl;
				//cout<<file_type<<endl;
				//cout<<"In funktion EXT: "<<extension<<endl;
				//cout<<"In funktion Pfad: "<<pfad_plus_dateiname<<endl;
				fileoperation.open(pfad_plus_dateiname, ios::in); 
				string datei_inhalt_2 = "";
				int i = 0;
					
				//Die ersten 5 Zeilen des ASCII Files lesen und alles in einen String schreiben
				//cout<<"ascii_read_max_lines:"<<ascii_read_max_lines<<endl;
				//cout<<"ascii_read_max_lines:"<<atoi(ascii_read_max_lines.c_str())<<endl;
				
				while ( i != atoi(ascii_read_max_lines.c_str()))
					{
						getline(fileoperation, datei_inhalt_2);
						//cout<<"datei_inhalt_2: "<<datei_inhalt_2<<endl;
						//Klein machen für die bessere Suche da redis case sensitive ist
						transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
						//##############################################################################################################						
						//Characters nach UTF8 wandeln und nicht durckbare Zeichen durch Leerzeichen ersetzten##
						//Charset Detector
						UErrorCode uerr = U_ZERO_ERROR;
						UCharsetDetector *ucd = ucsdet_open ( &uerr );
						ucsdet_setText(ucd, datei_inhalt_2.c_str(), datei_inhalt_2.size(), &uerr);
						UCharsetMatch const * match = ucsdet_detect(ucd, &uerr);
						//printf("Name: %s\n", ucsdet_getName(match, &uerr));
						//printf("Lang: %s\n", ucsdet_getLanguage(match, &uerr));
						//printf("Confidence: %u\n", ucsdet_getConfidence(match, &uerr));
						string charset_name;
						charset_name = ucsdet_getName(match, &uerr);
						//cout<<"charset_name: "<<charset_name<<endl;
						ucsdet_close(ucd);
						u_cleanup();
						//######################
						//Falls kein UTF-8 vorliegt, diese Charcters umwandeln.
						//cout<<"pfad_plus_dateiname: "<<pfad_plus_dateiname<<endl;
						//cout<<"file_encoding in UTF detector: "<<file_encoding<<"#"<<endl;

						//ggf. IBM424_ltr nochmal extra behandeln
						
						if (file_encoding == "ISO-8859 text, with very long lines, with no line terminators\\012- data")
						{
							datei_inhalt_2 = " ####ISO-8859 text, with very long lines, with no line terminators - data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						int wo_ist_iso_8859 = 0;
						wo_ist_iso_8859 = file_encoding.find("ISO-8859 text, with very long lines, with no line terminators\\012- data");
						if (wo_ist_iso_8859 > 0)
						{
							//cout<<"wo_ist_iso_8859"<<wo_ist_iso_8859;
							datei_inhalt_2 = " ####ISO-8859 text, with very long lines, with no line terminators - data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (file_encoding == "ASCII text, with very long lines, with no line terminators\\012- data")
						{
							datei_inhalt_2 = " ####ASCII text, with very long lines, with no line terminators- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (file_encoding == "ISO-8859 text, with very long lines, with no line terminators, with escape sequences\\012- data")
						{
							datei_inhalt_2 = " ####ISO-8859 text, with very long lines, with no line terminators, with escape sequences- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (file_encoding == "ASCII text, with very long lines, with CR line terminators\\012- data")
						{
							datei_inhalt_2 = " ####ASCII text, with very long lines, with CR line terminators- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (file_encoding == "Non-ISO extended-ASCII text, with very long lines, with CR, NEL line terminators\\012- data")
						{
							datei_inhalt_2 = " ####Non-ISO extended-ASCII text, with very long lines, with CR, NEL line terminators- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (file_encoding == "Non-ISO extended-ASCII text, with very long lines, with CR, LF line terminators\\012- data")
						{
							datei_inhalt_2 = " ####Non-ISO extended-ASCII text, with very long lines, with CR, LF line terminators012- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (file_encoding == "ISO-8859 text, with very long lines\\012- data")
						{
							datei_inhalt_2 = " ####ISO-8859 text, with very long lines012- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (file_encoding == "Non-ISO extended-ASCII text, with very long lines\\012- data")
						{
							datei_inhalt_2 = " ####Non-ISO extended-ASCII text, with very long lines012- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (file_encoding == "ISO-8859 text, with very long lines, with CRLF, LF line terminators\\012- data")
						{
							datei_inhalt_2 = " ####ISO-8859 text, with very long lines, with CRLF, LF line terminators012- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}

						if (file_encoding == "ISO-8859 text, with very long lines, with CR, LF line terminators\\012- data")
						{
							datei_inhalt_2 = " ####ISO-8859 text, with very long lines, with CR, LF line terminators- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (file_encoding == "ISO-8859 text, with very long lines, with CRLF, CR, LF line terminators\\012- data")
						{
							datei_inhalt_2 = " ####ISO-8859 text, with very long lines, with CRLF, CR, LF line terminators012- data Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						int wo_ist_verylong_line = 0;
						wo_ist_verylong_line = file_encoding.find("with very long lines");
						if (wo_ist_verylong_line > 0)
						{
							//cout<<"wo_ist_iso_8859"<<wo_ist_iso_8859;
							datei_inhalt_2 = " ####" + file_encoding +" Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						
						//int wo_ist_pdf_file = 0;
						//wo_ist_pdf_file = file_encoding.find("PPD file, version \"4.3\"\\012- , ASCII text, with CR line terminators\\012- data");
						//if (wo_ist_pdf_file > 0)
						if (file_encoding == "PPD file, version \"4.3\"\\012- , ASCII text, with CR line terminators\\012- data")
						{
							//cout<<"PPD file"<<wo_ist_pdf_file;
							//cout<<"PPD file"<<endl;
							datei_inhalt_2 = " ####" + file_encoding +" Zeichenketten Problem### ";
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						if (charset_name == "UTF-16BE")
						{
							string datei_inhalt_utf16;
							UErrorCode status = U_ZERO_ERROR;
							char target[atoi(ascii_read_max_chars.c_str())];
							//cout<<"datei_inhalt_2 vor UTF-16:"<<datei_inhalt_2<<endl;
							//ucnv_convert("UTF-16", charset_name.c_str(), target, sizeof(target), (const char*)datei_inhalt_2.data(), datei_inhalt_2.size() * sizeof(char32_t), &status);
							ucnv_convert("UTF-16BE", charset_name.c_str(), target, sizeof(target), (const char*)datei_inhalt_2.data(), datei_inhalt_2.size() * sizeof(char32_t), &status);
							datei_inhalt_utf16 = target;
							//cout<<"datei_inhalt_utf16: "<<datei_inhalt_utf16<<endl;
							memset(target, 0, sizeof(target));		//Zeichen leeren
							transform(datei_inhalt_utf16.begin(), datei_inhalt_utf16.end(), datei_inhalt_utf16.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_utf16);
							
							//datei_inhalt_2 = " ####UTF-16BE Zeichenketten Problem### ";
							//datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						
						/*
						if (charset_name == "GB18030")
						{
							datei_inhalt_2 = " ####GB18030 Zeichenketten Problem### ";
							datei_inhalt.append(datei_inhalt_2);
							i++;
							continue;
						}
						*/

						if (charset_name != "UTF-8")
						{
							string datei_inhalt_utf8;
							//Die richtige convertierung nach UTF8 vornehmen
							UErrorCode status = U_ZERO_ERROR;
							char target[atoi(ascii_read_max_chars.c_str())];
							//char target[999999];		//999999 Max Char Characters :-(
							//char *target;		//999999 Max Char Characters :-(
							//target=new char[999999];
							//char target[] = "test";
						//prüfen falls datei_inhalt_2 länge zu groß
							//cout<<"datei_inhalt_2 vor UTF-8:"<<datei_inhalt_2<<endl;
							//int32_t len = ucnv_convert("UTF-8", "UTF-8", target, sizeof(target), (const char*)datei_inhalt_2.data(), datei_inhalt_2.size() * sizeof(char32_t), &status);
							ucnv_convert("UTF-8", charset_name.c_str(), target, sizeof(target), (const char*)datei_inhalt_2.data(), datei_inhalt_2.size() * sizeof(char32_t), &status);
							//ucnv_convert("UTF-16", charset_name.c_str(), target, sizeof(target), (const char*)datei_inhalt_2.data(), datei_inhalt_2.size() * sizeof(char32_t), &status);
							datei_inhalt_utf8 = target;
							//cout<<"TEST"<<endl;
							//cout<<"sizeof(target): "<<sizeof(target)<<endl;
							//cout<<"strlen(target): "<<strlen(target)<<endl;
							//cout<<"datei_inhalt_utf8: "<<datei_inhalt_utf8<<endl;
							memset(target, 0, sizeof(target));		//Zeichen leeren
							//char target[] = {0};
							//cout<<"strlen(target): "<<strlen(target)<<endl;
							//cout<<"sizeof(target): "<<sizeof(target)<<endl;
							//char target leeren
							//######################
							/*
							//Character Unicode detector
							UConverter *conv;
							char *unicode_buchstabe_AE;
							int32_t     len;
							UChar target2[1024];
							UErrorCode status2 = U_ZERO_ERROR;
							conv = ucnv_open("utf-8", &status2);
							assert(U_SUCCESS(status2));
							len = ucnv_toUChars(conv, target2, 10, (const char*)datei_inhalt_utf8.data(), datei_inhalt_utf8.size() * sizeof(char32_t), &status2);
							//len = ucnv_toUChars("UTF-8", target2, sizeof(target2), (const char*)datei_inhalt_utf8.data(), datei_inhalt_utf8.size() * sizeof(char32_t), &status2);
							cout<<"IUC4C Convert Status: "<<len<<endl;
							ucnv_close(conv);
							cout<<"Dezimal: "<<*target2<<endl;
							cout<<"Hex: "<<hex<<*target2<<endl;
							std::stringstream ConvertStream;
							ConvertStream<<hex<<*target2;
							string unicode_string;
							ConvertStream>>unicode_string;
							int unicode_zeichen_laenge = 0;
							unicode_zeichen_laenge = unicode_string.length();
							cout<<"unicode_zeichen_laenge: "<<unicode_zeichen_laenge<<endl;
							cout<<"Unicode ID: "<<unicode_string<<endl;
							*/
							//######################
							//cout<<"TEST1"<<endl;
							transform(datei_inhalt_utf8.begin(), datei_inhalt_utf8.end(), datei_inhalt_utf8.begin(), ::tolower);
							//cout<<"TEST2"<<endl;
							datei_inhalt.append(datei_inhalt_utf8);
						}
						else
						{
							
							//datei_inhalt.append("#DATEIINHALT#"+datei_inhalt_2);
							transform(datei_inhalt_2.begin(), datei_inhalt_2.end(), datei_inhalt_2.begin(), ::tolower);
							datei_inhalt.append(datei_inhalt_2);		//Falls schon vorher ein UTF 8 vorliegt diesen in DB schreiben
						}
						//##############################################################################################################						
						
						//cout<<"in while:"<<datei_inhalt_2<<endl;
						//datei_inhalt.append(datei_inhalt_2);
						i++;
						//cout<<i<<endl;
					}
				 fileoperation.close();
				//continue;	
			}
			
		fileoperation.close();
	//###########################################################
		
	//Word Handling#################################################
	//cout<<file_type<<endl;
	//cout<<"In funktion EXT: "<<extension<<endl;
	//cout<<"In funktion Pfad: "<<pfad_plus_dateiname<<endl;
	//M$ Word
	//cout<<"ms_word_para"<<ms_word_para<<endl;
	if (ms_word_para == "true")
	{
	if (file_type == "application/msword" || file_type == "application/vnd.openxmlformats-officedocument.wordprocessingml.document")
		{	
			//libreoffice --cat --headless /root/cloud/Router.doc
			//cout<<"application/msword"<<endl;
			//cout<<file_type<<endl;
			//cout<<"In funktion EXT: "<<extension<<endl;
			//cout<<"In funktion Pfad: "<<pfad_plus_dateiname<<endl;
			string libreoffice_command;
			libreoffice_command = "timeout 30 libreoffice --cat --headless \"" + pfad_plus_dateiname + "\"";
			//cout<<libreoffice_command<<endl;
			char *libreoffice_command_char = {(char *) libreoffice_command.c_str()}; 
			FILE *pipe;
			//char str[1000];
			char str[50000];
			pipe = popen (libreoffice_command_char, "r" );
			if(pipe == NULL)
			{
				perror("open failed");
				pclose(pipe);
				return(0);
			}
			//libreoffice_command = string(str);
			//cout<<libreoffice_command<<endl;
			string datei_inhalt_3 = "";
			//for (int i = 0; i > 10 ; i++)
			int i = 0;
			//Die ersten fünf Zeilen einlesen
			//while(fgets ( str, 1000, pipe ) != NULL)
			while(fgets ( str, 49999, pipe ) != NULL)
				{
					datei_inhalt_3 = string(str);
					datei_inhalt.append(datei_inhalt_3);
					//cout<<"datei_inhalt: "<<datei_inhalt<<endl;
					//cout<<libreoffice_command<<endl;
					//Nur die ersten 5 Zeilen lesen########
					//cout<<"i:"<<i<<endl;
					i++;
					if (i > 5)
						{	
							//continue;
							break;
						}
					//#################
				}
			//pipe = popen ("exit", "r" );
			pclose(pipe);
			//cout<<"datei_inhalt#"<<datei_inhalt<<endl;
			//signal(SIGCHLD, SIG_IGN);
			//sleep(5);
		}
	}
	//cout<<"In funktion Filename: "<<filename<<endl;
	
	//M$ Excel Handling###########################################################################
	//cout<<"ms_excel_para"<<ms_excel_para<<endl;
	//cout<<"excel_ram_dev"<<excel_ram_dev<<endl;	
	if (ms_excel_para == "true")
	{
	if (file_type == "application/vnd.ms-excel" || file_type == "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet")
		{	
			//libreoffice --convert-to csv "/root/cloud/Docs/Diverse Docs/Telefon_Liste.xls" --outdir /tmp/ram_dev/; cat /tmp/ram_dev/Telefon_Liste.csv; rm -fr /tmp/ram_dev/Telefon_Liste.csv;
			//cout<<"application/vnd.openxmlformats-officedocument.wordprocessingml.document"<<endl;
			//cout<<file_type<<endl;
			//cout<<"In funktion EXT: "<<extension<<endl;
			//cout<<"In funktion Pfad: "<<pfad_plus_dateiname<<endl;
			string libreoffice_command;
			string filename_csv = filename;
			//cout<<filename<<endl;
			//cout<<extension<<endl
			
			if (extension == "xls")
				{
					filename_csv = filename_csv.replace(filename_csv.length() -3,3,"csv");
					//cout<<"filename_csv#"<<filename_csv<<endl;
				}
				else
				{
					filename_csv = filename_csv.replace(filename_csv.length() -4,4,"csv");
					//cout<<"filename_csv#"<<filename_csv<<endl;
				}
			//cout<<filename_csv<<endl;
			//cout<<"In funktion Filename: "<<filename<<endl;
			
			//libreoffice convert von xls(x) nach csv######
			//libreoffice_command = "timeout 30 libreoffice --convert-to csv \"" + pfad_plus_dateiname + "\" --outdir " + excel_ram_dev; 
			libreoffice_command = "timeout 30 libreoffice --convert-to csv --infilter=csv:44,34,76 \"" + pfad_plus_dateiname + "\" --outdir " + excel_ram_dev; 
			//cout<<"libreoffice_command#"<<libreoffice_command<<endl;
			char *libreoffice_command_char = {(char *) libreoffice_command.c_str()}; 
			FILE *pipe;
			//char str[1000];
			char str[50000];
			pipe = popen (libreoffice_command_char, "r" );
			if(pipe == NULL)
			{
				perror("open failed");
				pclose(pipe);
				return(0);
			}
			//libreoffice_command = string(str);
			//cout<<libreoffice_command<<endl;
			//while(fgets ( str, 1000, pipe ) != NULL)
			while(fgets ( str, 49999, pipe ) != NULL)
				{	
					//cout<<"str#"<<str<<endl;
				}
			//pipe = popen ("exit", "r" );
			pclose(pipe);
			//signal(SIGCHLD, SIG_IGN);
			//sleep(1);

			
			//cat csv datei und einfangen der Ausgabe#################
			string cat_command;
			cat_command = "timeout 30 cat \"" + excel_ram_dev + filename_csv + "\"";
			//cout<<"cat_command#"<<cat_command<<endl;
			char *cat_command_char = {(char *) cat_command.c_str()}; 
			FILE *pipe_2;
			//char str_2[1000];
			char str_2[50000];
			pipe_2 = popen (cat_command_char, "r" );
			if(pipe_2 == NULL)
			{
				perror("open failed");
				pclose(pipe_2);
				return(0);
			}
			string datei_inhalt_4 = "";
			//for (int i = 0; i > 10 ; i++)
			int i = 0;
			//sleep(1);
			
			//Die ersten fünf Zeilen einlesen
			//while(fgets ( str_2, 1000, pipe_2 ) != NULL)
			while(fgets ( str_2, 49999, pipe_2 ) != NULL)
				{
					datei_inhalt_4 = string(str_2);
					//cout<<"datei_inhalt_4#"<<datei_inhalt_4<<endl;
					datei_inhalt.append(datei_inhalt_4);
					//cout<<"datei_inhalt#"<<datei_inhalt<<endl;
					//cout<<cat_command<<endl;
					//Nur die ersten 5 Zeilen lesen########
					//cout<<"i:"<<i<<endl;
					i++;
					if (i > 5)
						{	
							//continue;
							break;
						}
					//#################
				}
			//pipe_2 = popen("exit", "r" );				
			pclose(pipe_2);
			//signal(SIGCHLD, SIG_IGN);
			
			//Datei löschen#################
			string rm_command;
			//rm_command = "timeout 10 rm -fr \"/tmp/ram_dev/" + filename_csv + "\"" ;
			rm_command = "timeout 30 rm -fr \"" + excel_ram_dev + filename_csv + "\"" ;
			//cout<<rm_command<<endl;
			char *rm_command_char = {(char *) rm_command.c_str()}; 
			FILE *pipe_3;
			//char str_3[1000];
			char str_3[50000];
			pipe_3 = popen (rm_command_char, "r" );
			if(pipe_3 == NULL)
			{
				perror("open failed");
				pclose(pipe_3);
				return(0);
			}
			//while(fgets ( str_3, 1000, pipe_3 ) != NULL)
			while(fgets ( str_3, 49999, pipe_3 ) != NULL)
				{
				}
			//pipe_3 = popen("exit", "r" );
			pclose(pipe_3);
			//signal(SIGCHLD, SIG_IGN);
			//cout<<datei_inhalt<<endl;
			//sleep(5);
		}
	}

	//###########################################################
	
//Exe und DLL infos mittels wine//###########################################################
	//AUSGABE "datei_inhalt" NOCHMALS PRÜFEN !!!!!
	
	//cout<<exe_dll_info<<endl;
	if (exe_dll_info == "true")
	{
	//cout<<exe_dll_info_binary<<endl;
	if (file_type == "application/x-dosexec" )
		{	
			//cout<<"pfad_plus_dateiname: "<<pfad_plus_dateiname<<endl;
			//in wine windows info 32 bit prog ausführen#################
			string wine_command;
			//wine_command = "timeout 10 wine \"/root/cloud/Tech Docs/Programmieren/FileSearchEngine/Linux Version/filesearch_engine_neuer_ansatz/get_exe_dll_info/get_exe_dll_info_v2/Release/get_exe_dll_info_v2.exe\" \"" + pfad_plus_dateiname + "\"";
			wine_command = "timeout 30 bash -c 'WINEDEBUG=fixme-all,err-all,warn+cursor,-all wine \"" + exe_dll_info_binary + "\" \"" + pfad_plus_dateiname + "\"'";
			//cout<<"wine_command# "<<wine_command<<endl;
			char *wine_command_char = {(char *) wine_command.c_str()}; 
			FILE *pipe_4;
			//char str_4[1000];
			char str_4[50000];
			pipe_4 = popen (wine_command_char, "r" );
			if(pipe_4 == NULL)
			{
				perror("open failed");
				pclose(pipe_4);
				return(0);
			}
			string datei_inhalt_5 = "";

			//while(fgets ( str_4, 1000, pipe_4 ) != NULL)
			while(fgets ( str_4, 49999, pipe_4 ) != NULL)
				{
					datei_inhalt_5 = string(str_4);
					transform(datei_inhalt_5.begin(), datei_inhalt_5.end(), datei_inhalt_5.begin(), ::tolower);
					datei_inhalt.append(datei_inhalt_5);
					//cout<<datei_inhalt<<endl;
				}
			//pipe_4 = popen("exit", "r" );
			pclose(pipe_4);
			//signal(SIGCHLD, SIG_IGN);
			//cout<<datei_inhalt<<endl;
		}
	}
	//###########################################################
	
//MP3/FLAC Tags ###########################################################
//####################################################################
	//exterens Modul Object File aufrufen TEST !!!!!
	
	//cout<<"mp3_para#"<<mp3_para<<endl;
	//cout<<"file_encoding#"<<file_encoding<<endl;
	
	if (mp3_para == "true")
	{
		//if (file_type == "audio/mpeg" || file_type == "audio/flac")
		if (file_type == "audio/mpeg")
		{	
	
			//Object File definieren
			void mp3_read();

			//pfad_uebergabe_mp3 = "/tmp/lied.mp3";
			
			//cout<<"file_type#"<<file_type<<endl;
			//cout<<"pfad_plus_dateiname#"<<pfad_plus_dateiname<<endl;
			//cout<<"file_encoding#"<<file_encoding<<endl;
			//cout<<"pfad_uebergabe aus Main#"<<pfad_uebergabe_mp3<<endl;
			pfad_fuer_mp3 = pfad_plus_dateiname;
			mp3_file_info_magic = file_encoding;
			mp3_tags_content = "";
			
			//Object File Funktion aufrufen
			mp3_read();
			
			//cout<<"mp3_tags_content aus object file#"<<mp3_tags_content<<endl;
			datei_inhalt.append(mp3_tags_content);
		}
		
		if (file_type == "audio/flac")
		{
			void flac_read();
			
			pfad_uebergabe_flac = pfad_plus_dateiname;
			flac_file_info_magic = file_encoding;
			flac_tags_content = "";
			
			flac_read();
			
			//cout<<"flac_tags_content aus object file#"<<flac_tags_content<<endl;
			datei_inhalt.append(flac_tags_content);
			
		}
		
		 
	}
//####################################################################
//PDF Lese####################################################################
//cout<<"pdf_para#"<<pdf_para;

if (pdf_para == "true")
	{
		//cout<<"file_type#"<<file_type<<endl;
		
		if (file_type == "application/pdf")
		{
			//cout<<"Call object file pdf"<<endl;
			void pdf_read();
			
			pfad_uebergabe_pdf = pfad_plus_dateiname;
			pdf_file_info_magic = file_encoding;
			pdf_content = "";
			pdf_read_max_lines = ascii_read_max_lines;
			
			pdf_read();
			
			//cout<<"pdf_content aus object file#"<<pdf_content<<endl;
			datei_inhalt.append(pdf_content);
		}
		
	}
//###########################################################
//####################################################################

	//Video File Info/###########################################################
	
	//###########################################################
	
	
	//cout<<"Rückgabe: "<<datei_inhalt<<endl;
	return (datei_inhalt);
}

//MD5 Sum mittels OpenSSL API
string hash_wert (string &pfad_plus_dateiname, string &md5sum)
{

	//cout<<"pfad_plus_dateiname: "<<pfad_plus_dateiname<<endl;
	//cout<<"md5sum: "<<md5sum<<endl;
	
	unsigned char digest[MD5_DIGEST_LENGTH];
	
	char *filename;
	filename = (char *) pfad_plus_dateiname.c_str();
		
	int i = 0;
	
	//FILE *inFile = fopen (filename, "rb");
	FILE *fileoperation = fopen (filename, "rb");
	
	MD5_CTX mdContext;
	int bytes;
	unsigned char data[1024];

	if (fileoperation == NULL) 
	{
		//Überlegen wie das Protokiolliert wird ???
		//printf ("%s can't be opened.\n", filename);
		//cout<<"fileoperation Problem"<<endl;
		
		//exit(0) damit das Programm beendet wird aber der warpper weiter läuft. Ggf. hier den signal handl auslösen.
		exit(0);
		//return 0;
	}

	MD5_Init (&mdContext);
	
	while ((bytes = fread (data, 1, 1024, fileoperation)) != 0)
	{
		MD5_Update (&mdContext, data, bytes);
	}
	
	MD5_Final (digest,&mdContext);
	
	//cout<<"digest:"<<c<<endl;
	
	//string md5sum_2;
	stringstream md5sum_2;
	
	for(i = 0; i < MD5_DIGEST_LENGTH; i++) 
	{	
	
		//Konvertierung von const char array nach string
		 md5sum_2 << std::setw(2) << std::setfill('0') << std::hex << static_cast<unsigned>(digest[i]);
	
	}
	//printf (" %s\n", filename);
	fclose (fileoperation);
    
	//cout<<"md5sum: "<<md5sum_2.str()<<endl;	
	md5sum = md5sum_2.str();
	
	return (md5sum);
}

//###################################################################################################################
//Config File Lesen Funktion
string read_config_file (vector<string> &config_file_parameter)
{
	//cout<<"read config"<<endl;
	ifstream fileoperation_conf;

	//fileoperation_conf.open("config.cfg", ios::in); 
	fileoperation_conf.open("/etc/rs/config.cfg", ios::in); 
	
	string config_parameter = "";
	string config_parameter_2 = "";
	
	int gleich_gefunden = 0;
	
	//Die ersten 5 Zeilen des ASCII Files lesen und alles in einen String schreiben
	while (!fileoperation_conf.eof())
	{
		getline(fileoperation_conf, config_parameter);
		//cout<<"config_parameter: "<<config_parameter<<endl;
		//Filter der einzelnen Parameter######
		
		if (config_parameter == "")
		{
			//cout<<"leer config_parameter_2"<<config_parameter<<endl;
			continue;
		}
		
		gleich_gefunden = config_parameter.find_last_of("=");
		//cout<<"config_parameter: "<<config_parameter.substr(gleich_gefunden + 1 ,99)<<endl;
		config_parameter_2 = config_parameter.substr(gleich_gefunden + 2 ,999);
		//cout<<config_parameter_2<<endl;
		config_file_parameter.push_back(config_parameter_2);
		
	}
	
	fileoperation_conf.close();
	
	//cout<<config_file_parameter.size()<<endl;
	//cout<<config_file_parameter[1]<<endl;

	return("nix");
	//return(NULL);
	//return(config_file_parameter);
	//return datei_inhalt_vektor;
	//return(datei_inhalt_vektor);
	//return(&datei_inhalt_vektor);
	//return(datei_inhalt_vektor);
	//return datei_inhalt_vektor;

}
//###################################################################################################################

//###################################################################################################################
//Lizenz Check
/*
string check_license (string &config_file_parameter_12)
{	
	//cout<<"Lizenz Key aus Funktion:"<<config_file_parameter_12<<endl;

	//decrypt Lizenz
	//echo "U2FsdGVkX18voP94s4gd3zuUM72tlm6lX45siijojn+1KbgnBGNEK5TZc8zKv+sF" | openssl aes-256-cbc -a -d -salt -k Mjk5OWZlYTZhMzc1ZGIzNzdmMTAK
	//entschl#	22945b33d078b3d9840c
	
	string openssl_command;
	string key = "Mjk5OWZlYTZhMzc1ZGIzNzdmMTAK";
	
	//ersten key bis zum # filtern
	int gatter_gefunden = 0;
	gatter_gefunden = config_file_parameter_12.find("#");
	string pass_key;
	pass_key = config_file_parameter_12.substr(0,gatter_gefunden);
	//cout<<"pass_key#"<<pass_key<<endl;
	openssl_command = "echo \""+ pass_key + "\" | openssl aes-256-cbc -a -d -salt -k " + key;
	//cout<<openssl_command<<endl;
	char *openssl_command_char = {(char *) openssl_command.c_str()}; 
	FILE *pipe_1;
	char str_1[1000];
	pipe_1 = popen (openssl_command_char, "r" );
	string pass_1 = "";
	while(fgets ( str_1, 1000, pipe_1 ) != NULL)
		{
			pass_1 = string(str_1);
			
		}
		
   //cout<<"pass_1:"<<pass_1<<endl;

	//Lieznez Abschnitt filtern
	gatter_gefunden = 0;
	//cout<<"config_file_parameter_12:"<<config_file_parameter_12<<endl;
	gatter_gefunden = config_file_parameter_12.find("#");
	//cout<<"gatter_gefunden#"<<gatter_gefunden<<endl;
	string lizenz;
	lizenz = config_file_parameter_12.substr(gatter_gefunden + 1,999);
	//cout<<"lizenz:"<<lizenz<<endl;
	//# durch = ersetzen
	replace(lizenz.begin(), lizenz.end(), '#', '=');
	//cout<<"lizenz:"<<lizenz<<endl;
	//echo -e "U2FsdGVkX1/yqBodTiuP7qhyb8FBkLQYDnJqNqAr3D8KgdJ3DC29Yx9+FN1F26Rn\nZKDg+wDOVBlotVqOQ8JVvjILKsjihRAFvztQubyi3ui2PPEpu+pUQrXHNBiIWFJ5\nTMxb6DLLfI/US1vWAXEF7A==" | openssl aes-256-cbc -a -d -salt -k 22945b33d078b3d9840c
	openssl_command = "echo -e \""+ lizenz + "\" | openssl aes-256-cbc -a -d -salt -k " + pass_1;
	//cout<<openssl_command<<endl;
	char *openssl_command_char_2 = {(char *) openssl_command.c_str()}; 
	FILE *pipe_2;
	char str_2[1000];
	pipe_2 = popen (openssl_command_char_2, "r" );
	string lizenz_2 = "";
	while(fgets ( str_2, 1000, pipe_2 ) != NULL)
		{
			lizenz_2 = string(str_2);
			
		}
	cout<<"lizenz_2:"<<lizenz_2<<endl;

	
	//return(0);	
	return("nix");
}
*/
//###################################################################################################################

int main(int argc, char *argv[]) 
{
	
//####################################################################
	//Error Signals
	signal(SIGSEGV, signalHandler);
	signal(SIGABRT, signalHandler);
	signal(SIGFPE, signalHandler);
	signal(SIGILL, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGINT, signalHandler);
	
//####################################################################
//exterens Modul Object File aufrufen TEST !!!!!
//void greet();
//greet();
//####################################################################

//###################################################################################################################
	//Uebergabeparameter einfangen
	//cout<<"Test"<<endl;
	//ARGVs lesen
	string verzeichnis_plus_datei_name;
	string lizenz_key;
	
	//verzeichnis_plus_datei_name=argv[1];
	verzeichnis_plus_datei_name = argv[1];
	lizenz_key = argv[2];
	SIGSEGV_pfad_datei=verzeichnis_plus_datei_name;
	//cout<<"argv 1:"<<verzeichnis_plus_datei_name<<endl;	
	//cout<<"argv 2:"<<lizenz_key<<endl;	
//###################################################################################################################
	//Lizenz Prüfung, schauen ob mkey signatur in Ordnung
	//cout<<"lizenz_key aus read_file_info#"<<lizenz_key<<endl;
	//string openssl_command = "echo -n \"985e5b8715bc435e7e8d\" | openssl md5";
	//Password im Code verstecken
	string openssl_command = "echo \"985e5b8715bc435e7e8d\" | openssl md5";
	//cout<<"openssl_command#"<<openssl_command<<endl;
	
	char *openssl_command_char_1 = {(char *) openssl_command.c_str()}; 
	FILE *pipe_1;
	char str_1[1000];
	pipe_1 = popen (openssl_command_char_1, "r" );
	if(pipe_1 == NULL)
	{
		perror("open failed");
		pclose(pipe_1);
		return(0);
	}
	string md5_key = "";
	while(fgets ( str_1, 1000, pipe_1 ) != NULL)
		{
			md5_key = string(str_1);
		}
	//pipe_1 = popen("exit", "r" );
	pclose(pipe_1);
	//signal(SIGCHLD, SIG_IGN);
	md5_key = md5_key.substr(9,32); //32 = länge md5 hash
	//cout<<"md5_key aus             #"<<md5_key<<"#"<<endl;
	//cout<<"lizenz_key aus übergabe #"<<lizenz_key<<"#"<<endl;
	if(md5_key != lizenz_key)
	{
		//cout<<"NIX GUT"<<endl;
		
		//Community Edition Lizenz Check
		//##################################################	
		string openssl_command_2 = "echo \"Community Edition\" | openssl md5";
		//cout<<"openssl_command_2#"<<openssl_command_2<<endl;

		char *openssl_command_char_2 = {(char *) openssl_command_2.c_str()}; 
		FILE *pipe_2;
		char str_2[1000];
		pipe_2 = popen (openssl_command_char_2, "r" );
		if(pipe_2 == NULL)
		{
			perror("open failed");
			pclose(pipe_2);
			return(0);
		}
		string md5_key_2 = "";
		while(fgets ( str_2, 1000, pipe_2 ) != NULL)
			{
				md5_key_2 = string(str_2);
			}
		//pipe_2 = popen("exit", "r" );
		pclose(pipe_2);
		//signal(SIGCHLD, SIG_IGN);
		md5_key_2 = md5_key_2.substr(9,32); //32 = länge md5 hash
		//cout<<"md5_key Community Edition #"<<md5_key_2<<"#"<<endl;
		if(md5_key_2 != lizenz_key)
		{
			//cout<<"Keine Lizenz gefunden"<<endl;
			exit(-1);
		}
		else
		{
			//cout<<"Gültige Lizenz gefunden :-)"<<endl;
			goto sprung;
		}
		//##################################################
		
		cout<<"Keine Lizenz gefunden"<<endl;
		exit(-1);
	}
	
	sprung:
	//cout<<"Gültige Lizenz gefunden :-)"<<endl;
	
	
	
//###################################################################################################################
	//Config File einlesen
	//string redis_server, redis_port, ms_word, ms_exel, ascii_file_max_read_lines,ascii_file_max_read_chars, exe_dll_infos, md5sum_conf;
	
	vector<string> config_file_parameter;
		
	read_config_file(config_file_parameter);
	
	//cout<<"redis server:"<<config_file_parameter[0]<<endl;
	//cout<<"redis port:"<<config_file_parameter[1]<<endl;
	//cout<<"exe_dll_binary:"<<config_file_parameter[7]<<endl;
	//cout<<"Lizenz Key:"<<config_file_parameter[12]<<endl;
	
	//check_license(config_file_parameter[12]);
	
//###################################################################################################################
	//Filter Dateiname
	int slash_gefunden;
	slash_gefunden = 0;
	string pfad;
	string dateiname;
	
	slash_gefunden = verzeichnis_plus_datei_name.find_last_of("/\\");
	//cout<<"Pfad:"<<verzeichnis_plus_datei_name.substr(0,slash_gefunden)<<endl;
	//cout<<"Datei:"<<verzeichnis_plus_datei_name.substr(slash_gefunden+1)<<endl;
	pfad = verzeichnis_plus_datei_name.substr(0,slash_gefunden);
	dateiname = verzeichnis_plus_datei_name.substr(slash_gefunden+1);
	//cout<<pfad<<endl;
	//cout<<dateiname<<endl;
	//File Extension################
	int punkt_gefunden = 0 ;
	string extension ;
	punkt_gefunden = verzeichnis_plus_datei_name.find_last_of(".");
	extension = verzeichnis_plus_datei_name.substr(punkt_gefunden+1);
	//cout<<extension<<endl;

//###################################################################################################################
	//von jeder Datei die Infos einholen
	
	
	//Stat Fileinofrmationen#########################
	//Attribute structuren //aus <sys/stat.h>
	struct stat attribut;
	
	//Convert String in pointer char für stat
	char *verzeichnis_plus_datei_name_char;
	verzeichnis_plus_datei_name_char = (char *) verzeichnis_plus_datei_name.c_str();
	
	//stat file
	stat(verzeichnis_plus_datei_name_char, &attribut);
		  
	//File information mit libmagic finden################
	string filename;
	filename = verzeichnis_plus_datei_name;
	magic_t magic;
	assert( (magic = magic_open(MAGIC_MIME_TYPE)) != nullptr );
	assert( magic_load(magic, nullptr) == 0 );
	//magic_load(magic, nullptr) == 0 ;
	//if (magic_load(magic, nullptr) == 0 )
	//{
	//	cout<<"Porblem loading libmagic libs (magic_load(magic, nullptr) "<<endl;
	//}
	char const * mime;
	assert( (mime = magic_file(magic, filename.c_str())) != nullptr );
	//mime = magic_file(magic, filename.c_str());
	//if (mime != nullptr)
	//{
	//	cout<<"Porblem loading libmagic libs mime != nullptr"<<endl;
	//}
	string file_type;
	file_type = mime;
	//cout<<file_type<<endl;
	magic_close(magic);
	//Encoding/Charset feststellen###########
	//assert( (magic = magic_open(MAGIC_MIME_ENCODING)) != nullptr );
	assert( (magic = magic_open(MAGIC_CONTINUE)) != nullptr );
	assert( magic_load(magic, nullptr) == 0 );
	//assert( (mime = magic_file(magic, filename.c_str())) != nullptr );
	mime = magic_file(magic, filename.c_str());
	string file_encoding;
	if (mime != nullptr)
	{
		//cout<<"GUT"<<endl;
		file_encoding = mime;
		//cout<<file_encoding<<endl;
		magic_close(magic);
	}
	else
	{	
		//cout<<"problem"<<endl;
		file_encoding = "File Endcoding Detection Problem";
		//cout<<file_encoding<<endl;
		magic_close(magic);
		//exit(666);
	}
	//mime = magic_file(magic, "/root/temp/NWBC.exe");
	//mime = magic_file(magic, "/root/database/DATABASE_1/Database/Appz/WinX/C\`T\ CDs/2.\ Halbjahres\ CD\ 2001/HTML/01/23/028/PIC01.JPG");
	//cout<<mime<<endl;
	//####################################

	//atime###
	//atime neu stezten nachdem auslesen.
	//Ausgabe in string
	//cout<<ctime( &attribut.st_atime )<<endl;
	string letzter_zugriff;
	//letzter_zugriff = ctime(&attribut.st_atime);
	//Formatierte Ausgabe##
	time_t st_atime_format = attribut.st_atime;
	//cout<<"tt:"<<tt<<endl;
	char zeit_format_ausgabe[99];
	//strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&tt));
	strftime(zeit_format_ausgabe, sizeof(zeit_format_ausgabe), "%Y-%m-%d %H:%M:%S", std::localtime(&st_atime_format));
	//cout<<"mbstr:"<<zeit_format_ausgabe<<endl;
	letzter_zugriff = zeit_format_ausgabe;
	//cout<<"letzter_zugriff:"<<letzter_zugriff +"." <<endl;
	//Epoch Zeit herausfinden von atime################
	time_t atime;
	//struct utimbuf new_times2;
	atime = attribut.st_atime;
	//cout<<"Epoch atime:"<<atime<<endl;
	//Nano Sekunden des Zugriffs herausfinden#####
	long st_atime_nsec; 		//das Gleiche wie //__time_t st_atime_nsec; 
	st_atime_nsec = attribut.st_atim.tv_nsec;
	//cout<<"st_atime_nsec: "<<st_atime_nsec<<endl;
	//###########################################
	letzter_zugriff = letzter_zugriff.erase(letzter_zugriff.find_last_not_of(" \n\r\t")+1);
	//cout<<"atime: "<<letzter_zugriff<<endl;
	
	//mtime###
	string letzter_modifikation;
	//letzter_modifikation = ctime(&attribut.st_mtime);
	//Formatierte Ausgabe##
	time_t st_mtime_format = attribut.st_mtime;
	//cout<<"tt:"<<tt<<endl;
	//char zeit_format_ausgabe[99];
	//strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&tt));
	strftime(zeit_format_ausgabe, sizeof(zeit_format_ausgabe), "%Y-%m-%d %H:%M:%S", std::localtime(&st_mtime_format));
	//cout<<"mbstr:"<<zeit_format_ausgabe<<endl;
	letzter_modifikation = zeit_format_ausgabe;
	//cout<<"letzter_zugriff:"<<letzter_zugriff<<endl;
	//Epoch Zeit herausfinden von mtime################
	time_t mtime2;
	//struct utimbuf new_times2;
	mtime2 = attribut.st_mtime;
	//cout<<"mtime2: "<<mtime2<<endl;
	//Nano Sekunden des zugriffs herausfindehn#####
	//unsigned long st_mtime_nsec; 		//das Gleiche wie //__time_t st_atime_nsec; 
	long st_mtime_nsec; 		//das Gleiche wie //__time_t st_atime_nsec; 
	st_mtime_nsec = attribut.st_mtim.tv_nsec;
	//cout<<"st_mtime_nsec: "<<st_mtime_nsec<<endl;
	//###########################################
	letzter_modifikation = letzter_modifikation.erase(letzter_modifikation.find_last_not_of(" \n\r\t")+1);
	//cout<<"mtime: "<<letzter_modifikation<<endl;
	
	//ctime###ggf. hier weglassen, da durch die Änderungen von mtime und atime hier sich auch die ctime auf die aktuelle systemzeit ändern ??????
	string letzter_change;
	letzter_change = ctime(&attribut.st_ctime);
	letzter_change = letzter_change.erase(letzter_change.find_last_not_of(" \n\r\t")+1);
	//cout<<"ctime: "<<letzter_change<<endl;
	
	//Size###
	string size;
	//cout<<(*verzeichnis_plus_datei_name_char,attribut.st_size);
	//cout<<attribut.st_size<<endl;
	//Char nach string konvertieren
	std::stringstream ConvertStream_1;
	ConvertStream_1<<attribut.st_size;
	ConvertStream_1>>size;
	//cout<<size<<endl;
	
//###################################################################################################################
	//Content##############################
	//Docs, XLS, PPT, TXT (ASCII Files), MP3 Tags, Videos, JPG Header,
	string datei_inhalt;
	//cout<<dateiname<<endl;
	//aufruf sub funktion###
	//Schalter Parameter
	//cout<<"config_file_parameter[16]"<<config_file_parameter[16]<<endl;
	//cout<<"file_encoding#"<<file_encoding<<endl;
	//cout<<"file_type#"<<file_type<<endl;
	read_content (extension, dateiname, verzeichnis_plus_datei_name, datei_inhalt, file_type, file_encoding, config_file_parameter[2],config_file_parameter[3],config_file_parameter[4], config_file_parameter[5], config_file_parameter[6], config_file_parameter[7], config_file_parameter[8], config_file_parameter[16], config_file_parameter[17] );
	//cout<<dateiname<<endl;
	//cout<<"datei_inhalt HAUPTFUNKTION#"<<datei_inhalt<<endl;
	/*
	if (datei_inhalt != "")
		{
			cout<<verzeichnis_plus_datei_name<<endl;
			cout<<"ausserhalb funktion INHALT: "<<datei_inhalt<<endl;
		}
	*/
//###################################################################################################################

	//md5sum##############################
	string md5sum;
	//md5sum = "eeaf871e0b6c70084a8e9ae79a453440";
	//mdhash_wert = "nix";
	//Aufruf der Sub Funktion###
	
	//cout<<"md5sum:"<<config_file_parameter[9]<<endl;
	if (config_file_parameter[9] == "true")
	{
		hash_wert (verzeichnis_plus_datei_name, md5sum);
	}
	else
	{
		md5sum = "nicht berechnet";
	}
	//cout<<md5sum<<endl;
//###################################################################################################################
	//aktuelle System Zeit in variable schreiben###################
	time_t Zeitstempel;
    tm *nun;
    Zeitstempel = time(0);
    nun = localtime(&Zeitstempel);
	
	//Tag
	int tag;
	tag = nun->tm_mday;
	string current_tag_string;
	std::stringstream ConvertStream_2;
	ConvertStream_2<<tag;
	ConvertStream_2>>current_tag_string;
	//cout<<current_tag_string<<endl;
	int anzahl_ziffern = current_tag_string.length();
	if (anzahl_ziffern < 2)
	{
		current_tag_string = "0" + current_tag_string;
		//cout<<"current_tag_string"<<current_tag_string<<endl;
	}
	
	//Monat
	int monat;
	monat = nun->tm_mon+1;
	//cout << "The local date and time is: " << asctime(monat) << endl;
	string current_monat_string;
	std::stringstream ConvertStream_3;
	ConvertStream_3<<monat;
	ConvertStream_3>>current_monat_string;
	//cout<<current_monat_string<<endl;
	anzahl_ziffern = current_monat_string.length();
	if (anzahl_ziffern < 2)
	{
		current_monat_string = "0" + current_monat_string;
		//cout<<"current_monat_string"<<current_monat_string<<endl;
	}
	
	//Jahr
	int current_jahr;
	current_jahr = nun->tm_year+1900;
	string current_jahr_string;
	std::stringstream ConvertStream_4;
	ConvertStream_4<<current_jahr;
	ConvertStream_4>>current_jahr_string;
	//cout<<current_jahr_string<<endl;
	
	//Stunde
	int current_stunde;
	current_stunde = nun->tm_hour;
	string current_stunde_string;
	std::stringstream ConvertStream_5;
	ConvertStream_5<<current_stunde;
	ConvertStream_5>>current_stunde_string;
	//cout<<current_stunde_string<<endl;
	anzahl_ziffern = current_stunde_string.length();
	if (anzahl_ziffern < 2)
	{
		current_stunde_string = "0" + current_stunde_string;
		//cout<<"current_stunde_string"<<current_stunde_string<<endl;
	}
	
	//Minute
	int current_minute;
	current_minute = nun->tm_min;
	string current_minute_string;
	std::stringstream ConvertStream_6;
	ConvertStream_6<<current_minute;
	ConvertStream_6>>current_minute_string;
	//cout<<current_minute<<endl;
	anzahl_ziffern = current_minute_string.length();
	if (anzahl_ziffern < 2)
	{
		current_minute_string = "0" + current_minute_string;
		//cout<<"current_minute_string"<<current_minute_string<<endl;
	}
	
	//Sekunde
	int current_sekunde;
	current_sekunde = nun->tm_sec;
	string current_sekunde_string;
	std::stringstream ConvertStream_7;
	ConvertStream_7<<current_sekunde;
	ConvertStream_7>>current_sekunde_string;
	//cout<<current_sekunde_string<<endl;
	anzahl_ziffern = current_sekunde_string.length();
	if (anzahl_ziffern < 2)
	{
		current_sekunde_string = "0" + current_sekunde_string;
		//cout<<"current_sekunde_string"<<current_sekunde_string<<endl;
	}
	
	//Millisekunde
	int current_msec;
	timeval time;
	gettimeofday(&time, NULL);
	current_msec = time.tv_usec;
	string current_msec_string;
	std::stringstream ConvertStream_8;
	ConvertStream_8<<current_msec;
	ConvertStream_8>>current_msec_string;
	//cout<<current_msec_string<<endl;
	//Zeitstempel zusammenbauen
	string current_timestamp;
	current_timestamp = current_tag_string + "." + current_monat_string + "." + current_jahr_string + " " + current_stunde_string + ":" + current_minute_string + ":" + current_sekunde_string + "." + current_msec_string ;
	//cout<<"Systemzeit:"<<current_timestamp<<endl; 
	//##########################################
	
	//###################################################################################################################
	//File a time zurücksetzen, wegen zugriff via md5sum und der dadurch verursachten atime änderung
	//verzeichnis_plus_datei_name.c_str()
	struct stat stat2;
	//time_t mtime;
	struct utimbuf new_times;
	stat(verzeichnis_plus_datei_name.c_str(), &stat2);
	//mtime = foo.st_mtime; /* seconds since the epoch */
	//mtime = foo.st_atime; /* seconds since the epoch */
	//new_times.actime = foo.st_mtime; /* keep atime unchanged */
	//st_atime_nsec;
	new_times.actime = atime;
	new_times.modtime = mtime2;
	//new_times.modtime = time(NULL);    /* set mtime to current time */
	utime(verzeichnis_plus_datei_name.c_str(), &new_times);
	//############
	//Nano Sekunden Festlegen
	struct timespec times[2] = {{.tv_sec = atime, .tv_nsec = st_atime_nsec},{.tv_sec = mtime2, .tv_nsec = st_mtime_nsec}};
	utimensat(0, verzeichnis_plus_datei_name.c_str(), times, 0);
	//############
	//cout<<"new_times: "<<new_times<<endl;

//###################################################################################################################
	//in redis schreiben
	//redis "key-value" string zusammenbauen

	//via Socket API send() in redis schreiben
	struct hostent *host;//Hostname struktuieren
	//Aus Config lesen
	//cout<<"redis server:"<<config_file_parameter[0]<<endl;
	//cout<<"redis port:"<<config_file_parameter[1]<<endl;
	//host = gethostbyname("172.17.190.78"); //eventuell die IP in DNS Namen umwandeln
	string redis_server = config_file_parameter[0];
	//cout<<"redis_server#"<<redis_server<<"#"<<endl;
	host = gethostbyname(redis_server.c_str()); //eventuell die IP in DNS Namen umwandeln
	//##
	struct sockaddr_in addr;
	addr.sin_addr = *(struct in_addr*)host->h_addr;
	int s; 
	s = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	//cout<<"Socket Aufbau RC (s) #"<<s<<endl;
	
	//addr.sin_port = htons(6379);//Connection Portnummer des Servers festlegen
	string redis_port = config_file_parameter[1] ;
	//cout<<"redis_port#"<<redis_port<<"#"<<endl;
	int redis_port_int = atoi(redis_port.c_str());
	//##
	addr.sin_port = htons(redis_port_int);//Connection Portnummer des Servers festlegen
	addr.sin_family = AF_INET; 
	connect(s,(struct sockaddr*)&addr, sizeof(addr));
	//string suchmuster = argv[1];

	//Pfad klein machen und Dateinam. Dateinhalt klein machen. Dateinihalt wird bei ICU4C (UTF) klein gemacht aber nur bei ASCII Files. Obacht, erszt hier klein machen da "dateiname" und "verzeichnis_plus_datei_name" in anderen Funktionen noch im Original gebarcht werden.
	transform(dateiname.begin(), dateiname.end(), dateiname.begin(), ::tolower);
	transform(verzeichnis_plus_datei_name.begin(), verzeichnis_plus_datei_name.end(), verzeichnis_plus_datei_name.begin(), ::tolower);
	transform(datei_inhalt.begin(), datei_inhalt.end(), datei_inhalt.begin(), ::tolower);
	string set_redis_string;
	
	//redis set kommando zusammenbaue
	//cout<<"datei_inhalt VOR redis_string#"<<datei_inhalt<<"#"<<endl;
	//Dateiinhalt trimmen
	//datei_inhalt = datei_inhalt.erase(datei_inhalt.find_last_not_of(" \n\r\t")+1);
	//datei_inhalt = datei_inhalt.erase(datei_inhalt.find_last_not_of("\n")+1);
	//boost::trim_right(datei_inhalt);
	//cout<<"datei_inhalt NACH trim#"<<datei_inhalt<<"#"<<endl;

	//Zeilenumbrüche entfernen. Sonst Gibts Probleme mit dem socket request und redis kann das nicht entgegenenemen da zuviel " Zeichen im String sind. Siehe Debug "tcpdump -i lo -nnn port 6379"
	datei_inhalt.erase(std::remove(datei_inhalt.begin(), datei_inhalt.end(), '\n'), datei_inhalt.end());
	//cout<<"datei_inhalt#"<<datei_inhalt<<endl;
	
	//Alle ' und" aus dem Pfad entfernen entfernen und durch ein leerzeichn ersetzen
	//verzeichnis_plus_datei_name.erase(std::remove(verzeichnis_plus_datei_name.begin(), verzeichnis_plus_datei_name.end(), '\''), verzeichnis_plus_datei_name.end());
	replace(verzeichnis_plus_datei_name.begin(), verzeichnis_plus_datei_name.end(), '\'', ' ');
	replace(verzeichnis_plus_datei_name.begin(), verzeichnis_plus_datei_name.end(), '\"', ' ');
	
	
	set_redis_string = "set '#PFAD#" + verzeichnis_plus_datei_name + "#DATEINAME#" + dateiname + "#LETZ.ZUG#" +  letzter_zugriff + "#LETZT.MOD#" + letzter_modifikation + "#CREATE.DATAE#" + letzter_change + "#SIZE#" + size + "#MD5#" + md5sum + "#INHALT#" + datei_inhalt + "@@ENDE@@' " + "'" + current_timestamp + "'" + "\r\n";
	//set_redis_string = "set '#PFAD#" + verzeichnis_plus_datei_name + "#DATEINAME#" + dateiname + "#LETZ.ZUG#" +  letzter_zugriff + "#LETZT.MOD#" + letzter_modifikation + "#CREATE.DATAE#" + letzter_change + "#SIZE#" + size + "#MD5#" + md5sum + "#INHALT#" + datei_inhalt + "@@ENDE@@' " + "'" + current_timestamp + "'";
	//#DEBUG TEST DATENSATZ # set_redis_string = "set BLABBLA, TEST";
	//cout<<"set_redis_string"<<set_redis_string<<endl;
	//string redis_command = "set BLfdsszdgsfdgsfdA, 123\r\n";

	//int wo_ist_ende = 0;
	//suchmuster = suchmuster.insert(0,"KEYS \"*");
	//wo_ist_ende =  suchmuster.size();
	//suchmuster = suchmuster.insert(wo_ist_ende,"*\"\r\n");
	//set_redis_string.erase(std::remove(set_redis_string.begin(), set_redis_string.end(), '\"'), set_redis_string.end());
	//set_redis_string.erase(std::remove(set_redis_string.begin(), set_redis_string.end(), '"'), set_redis_string.end());

	char* request = (char*)set_redis_string.c_str();
	//char* request = set_redis_string.c_str();
	//const char* request = set_redis_string.c_str();
	//cout<<"request####"<<request<<"####"<<endl;
	//int send_return_code = 666;
	//send_return_code = send(s, request, strlen(request),0);//Daten senden
	send(s, request, strlen(request),0);//Daten senden
	//send_return_code = send(s, request, 311,0);//Daten senden
	//send(s, request, strlen(request),0);//Daten senden
	//cout<<"send_return_code#"<<send_return_code<<endl;
	//cout<<"i"<<i<<endl;

	string redis_quit_command;
	redis_quit_command = "quit\r\n";
	char* request_quit = (char*)redis_quit_command.c_str();
	send(s, request_quit, strlen(request_quit),0);//Daten senden
	
	close(s);
	
//ALT mit cpp_redis, NICHT -static-libstdc++ fähig#######################################################	
/*
	cpp_redis::client client;
	client.connect();
	
	//string key;
	//string value;
	
	//client.set("hello", "45");
	//key = "schluessel" ;
	//value = "wert1234";
		
	//client.set(dateiname, letzter_zugriff);
	//cout<<verzeichnis_plus_datei_name<<endl;
	//client.set(verzeichnis_plus_datei_name, pfad + "##_##" + dateiname + "##_##" + pfad + "##_##" +  letzter_zugriff + "##_##" + letzter_modifikation + "##_##" + letzter_change + "##_##" + size + "##_##" + md5sum + "##_##" + datei_inhalt + "##_##" + current_timestamp);
	string set_redis_string;
	//set_redis_string = verzeichnis_plus_datei_name + "##_##" + pfad + "##_##" + dateiname + "##_##" + pfad + "##_##" +  letzter_zugriff + "##_##" + letzter_modifikation + "##_##" + letzter_change + "##_##" + size + "##_##" + md5sum + "##_##" + datei_inhalt + "##_##" + current_timestamp;
	//#####GGF. Einen Datemsatzcouter einbauen?????
	
	//Pfad klein machen und Dateinam. Dateinihalt wird bei ICU4C (UTF) klein gemacht. Obacht, erszt hier klein machen da "dateiname" und "verzeichnis_plus_datei_name" in anderen Funktionen noch im Original gebarcht werden.
	transform(dateiname.begin(), dateiname.end(), dateiname.begin(), ::tolower);
	transform(verzeichnis_plus_datei_name.begin(), verzeichnis_plus_datei_name.end(), verzeichnis_plus_datei_name.begin(), ::tolower);

	set_redis_string = "#PFAD#" + verzeichnis_plus_datei_name + "#DATEINAME#" + dateiname + "#LETZ.ZUG#" +  letzter_zugriff + "#LETZT.MOD#" + letzter_modifikation + "#CREATE.DATAE#" + letzter_change + "#SIZE#" + size + "#MD5#" + md5sum + "#INHALT#" + datei_inhalt + "@@ENDE@@"; 
	//set_redis_string = datei_inhalt;
	//client.set(set_redis_string, "nix");
	//alles klein machen
	//transform(set_redis_string.begin(), set_redis_string.end(), set_redis_string.begin(), ::tolower);
	//cout<<"set_redis_string klein"<<set_redis_string<<endl;
	client.set(set_redis_string, current_timestamp);

	//###########################
	//eigentlich nicht notwendig
	////client.get("hello", [](cpp_redis::reply& reply) { std::cout << reply << std::endl;});
	////string test;
	//client.send({"GET", "schluessel"}, [] (cpp_redis::reply& reply) 
	//{
    //    //cout << reply.as_string();
	//	//string test;
	//	public_string_rueckgabewert = reply.as_string();
	//	//cout<<test<<endl;
    //});	
	////cout<<public_string_rueckgabewert<<endl;
	//###########################
	client.sync_commit();
*/
//##############################################################################################################

//###################################################################################################################
	
	//alle "sh <defunct>" child prozesse beenden. Werden von "read_file_infos -> popen" erzeugt bzw. hinterlassen. !!!!
	signal(SIGCHLD, SIG_IGN);

	return (0);
}
