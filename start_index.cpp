//##################
//Test Compile: clear; rm -frv start_index; clear; g++-7 -g -fPIC -Wall -lpthread start_index.cpp -o start_index;
//PRD Compile:  clear; rm -frv start_index; clear; g++-7 -O3 -fPIC -Wall -lpthread start_index.cpp -o start_index;
//PRD Compile STATIC LINKED:  clear; rm -frv start_index; g++-7 -O3 -fPIC -Wall -lpthread start_index.cpp -o start_index -static-libstdc++;
//Start Command: date; time ./start_index /tmp/ 4
//SIGSEGV auslösen kill -11 $(ps -ef | grep -i "./start_index /root" | grep -v grep | head -n 1 | awk -F " " '{print $2}' )
//##################

//##################
//C_C++ Header
#include <dirent.h>
#include <errno.h>
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
#include <thread>
#include <time.h>
//File Time Modification####
#include <utime.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <cstdlib>
//Error Handling und Singal
//#include <errno.h>
//perror
#include <errno.h>
#include <signal.h>
#include <malloc.h>
#include <errno.h>
#include <sys/mman.h>
#include <csignal>
#include <iterator>
//Network Header
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <netdb.h> 
#include <string.h>
#include <stdlib.h> 
#include <vector>
//Posix Thread
#include <pthread.h>
//Header für setrlimit (ulimits setzen)
#include <sys/resource.h>
//#include <ulimit.h>
//OpenSSL Header zur Versions prüfung
//#include "openssl/ssl.h"
//Linux Version
//#include <sys/utsname.h>

using namespace std;

//Public Variable für Thread 0
std::string anzahl_xargs_prozesse;
std::string pfad;
//###
std::string key_uebergabe_read_file_info;
//##
std::string redis_server;
std::string redis_port;
std::string distri_vers;
int debian_gefunden = 666 ;

void signalHandler( int signum) 
{
	cout<<"PROBLEM, siehe error log"<<endl;
	cout<<"Signal: "<<signum<<endl;
	//cout<<"Segmentation fault"<<endl;
	// cleanup and close up stuff here  
	//terminate program  


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


	//################################################################
	//ps -ef einfangen
	string ps_ef_command;
	ps_ef_command = "ps -ef";
	//cout<<ps_ef_command<<endl;
	char *ps_ef_command_char = {(char *) ps_ef_command.c_str()}; 
	FILE *pipe;
	//char str[1000];
	char str[50000];
	pipe = popen (ps_ef_command_char, "r" );
	if(pipe == NULL)
	{
		perror("open failed");
		pclose(pipe);
		exit(0);
	}
	//cout<<"Status popen signalHandler pipe# "<<pipe<<endl;
	//cout<<ps_ef_command_char<<endl;
	//ps -ef Ausgabe einlesen
	string ps_ef_rueckgabe_temp = "";
	string ps_ef_rueckgabe = "";
	while(fgets ( str, 49999, pipe ) != NULL)
		{
			ps_ef_rueckgabe_temp = string(str);
			ps_ef_rueckgabe.append(ps_ef_rueckgabe_temp);
		}
	pclose(pipe);
	//cout<<"ps_ef_rueckgabe#"<<ps_ef_rueckgabe<<endl;
	//################################################################

	//################################################################
	//;timeout 2 redis-cli monitor# Auszug der letzten Einträge der DB in FIle schreiben
	string redis_cli_monitor_command;
	redis_cli_monitor_command = "timeout 1 redis-cli monitor";
	//cout<<redis_cli_monitor_command<<endl;
	char *redis_cli_monitor_command_char = {(char *) redis_cli_monitor_command.c_str()}; 
	FILE *pipe2;
	char str2[50000];
	pipe2 = popen (redis_cli_monitor_command_char, "r" );
	if(pipe2 == NULL)
	{
		perror("open failed");
		pclose(pipe2);
		exit(0);
	}
	//cout<<"Status popen signalHandler pipe2# "<<pipe2<<endl;
	//cout<<redis_cli_monitor_command_char<<endl;
	string redis_cli_monitor_command_temp = "";
	string redis_cli_monitor_command_rueckgabe = "";
	while(fgets ( str2, 49999, pipe2 ) != NULL)
		{
			redis_cli_monitor_command_temp = string(str2);
			redis_cli_monitor_command_rueckgabe.append(redis_cli_monitor_command_temp);
		}
	pclose(pipe2);
	//cout<<"redis_cli_monitor_command_rueckgabe#"<<redis_cli_monitor_command_rueckgabe<<endl;
	//################################################################
	
	//in Datei schreiben
	ofstream sigsegv_file;
	sigsegv_file.open ("/var/log/rs_error.log", ios::app );
	//sigsegv_file<<"\n########################\n"<<current_timestamp<<"\n"<<" # "<<ps_ef_rueckgabe<<"\n###\n"<<redis_cli_monitor_command_rueckgabe<<endl;
	sigsegv_file<<"\n########################\n"<<current_timestamp<<"\n"<<" # "<<"\n###\n"<<"redis monitor # "<<redis_cli_monitor_command_rueckgabe<<endl;
	sigsegv_file.close();

	//################################################################
	//Alle Prozesse killen. Oder Kontrollieren ob noch die find und xargs prozesse laufen und start_index safe neu starten.
	string killall;
	
	killall = "killall -9 soffice.bin 2&>1";
	system(killall.c_str());
	killall = "killall -9 oosplash 2&>1";
	system(killall.c_str());
	killall = "killall -9 read_file_infos 2&>1";
	system(killall.c_str());
	killall = "killall -9 xargs 2&>1";
	system(killall.c_str());
	killall = "killall -9 libreoffice 2&>1";
	system(killall.c_str());
	killall = "killall -9 find 2&>1";
	system(killall.c_str());
	
	//alle "sh <defunct>" child prozesse beenden.
	signal(SIGCHLD, SIG_IGN);
	
	//##########################################################################
	//1 und 2 löschen
	string rm_1 = "rm -fr 1";
	string rm_2 = "rm -fr 2";
	system(rm_1.c_str());
	system(rm_2.c_str());
	
	exit(0);
	//exit(signum);  
}

//###########################################################################
void *find_xargs(void *threadid_0)
{
	
		//sleep(2);
		//return(0);
		//cout<<"threadid 0:"<<threadid_0<<endl;
		//cout<<"Thread pfad 0:"<<pfad<<endl;	
		//cout<<"Thread  anzahl_xargs_prozesse 0:"<<anzahl_xargs_prozesse<<endl;	
		//sleep(5);
		cout<<"Starte Systemdurchlauf..."<<endl;
		string command;
		//command = "find " + pfad + " -type f -print0 | xargs -P" + anzahl_xargs_prozesse + " -0 -I'{}' timeout 500s ./read_file_infos {} 2&>1";
		
		//#########################################
		if (debian_gefunden >= 0)
		{
			//command = "find '" + pfad + "' -type f -print0 | xargs -P" + anzahl_xargs_prozesse + " -0 -I'{}' timeout 500s ./read_file_infos {} " + key_uebergabe_read_file_info;				//DEV für Debian
			command = "find '" + pfad + "' -type f -print0 | xargs -P" + anzahl_xargs_prozesse + " -0 -I'{}' timeout 500s read_file_infos {} " + key_uebergabe_read_file_info;				//PRD für Debian
		}
		else
		{
			//command = "find '" + pfad + "' -type f -print0 | xargs -P" + anzahl_xargs_prozesse + " -0 -I'{}' timeout 500s ./read_file_infos {} " + key_uebergabe_read_file_info + " 2&>1";	//DEV für Suse
			command = "find '" + pfad + "' -type f -print0 | xargs -P" + anzahl_xargs_prozesse + " -0 -I'{}' timeout 500s read_file_infos {} " + key_uebergabe_read_file_info + " 2&>1";		//PRD für Suse
		}
		//#########################################

		//command = "find '" + pfad + "' -type f -print0 | xargs -P" + anzahl_xargs_prozesse + " -0 -I'{}' timeout 500s ./read_file_infos {} " + key_uebergabe_read_file_info + " 2&>1";		//PRD
		//command = "find '" + pfad + "' -type f -print0 | xargs -P" + anzahl_xargs_prozesse + " -0 -I'{}' timeout 500s ./read_file_infos {} " + key_uebergabe_read_file_info;					//DEBUG
		//cout<<"command#"<<command<<endl;
		
		//Bei ARM Rasperian kein "2&>1" da sonst der Thread gleich joint und die main beendet wird.################################
		//command = "find '" + pfad + "' -type f -print0 | xargs -P" + anzahl_xargs_prozesse + " -0 -I'{}' timeout 500s ./read_file_infos {} " + key_uebergabe_read_file_info;
		
		//cout<<"command:"<<command<<endl;
		char *command_char = {(char *) command.c_str()}; 
		system(command_char);
		//popen (command_char, "r" );

		pthread_exit(NULL);
}

void *dbsize_eintraege(void *threadid_1)
{
	
		//return(0);
		//sleep(3);
		//cout<<"threadid 1:"<<threadid_1<<endl;
		//cout<<"Thread pfad 1:"<<pfad<<endl;	
		//cout<<"Thread  anzahl_xargs_prozesse 1:"<<anzahl_xargs_prozesse<<endl;	
		//sleep(12);
		/*
		while (1)
		{
			sleep(1);
			cout<<"Test Loop"<<endl;
		}
		*/
	//###################################################################################################################
	//alle "sh <defunct>" child prozesse beenden. Werden von "read_file_infos -> popen" erzeugt bzw. hinterlassen. !!!!
	signal(SIGCHLD, SIG_IGN);
	
//long unsigned stacksize;
//pthread_attr_t attr;
//pthread_attr_init(&attr);
//pthread_attr_getstacksize(&attr, &stacksize);
//printf("Thread stack size = %d bytes \n", stacksize);

//Anzahl einträge in DB######################################################
	while(1)
	{
		//Alle 10 sekunde aufrufen bis der find_xargs beendet ist
		sleep (10);
		
		int socket_desc;
		struct sockaddr_in server;
		char message[36] = "dbsize\r\n";

		 //Create socket
		socket_desc = socket(AF_INET , SOCK_STREAM , 0);
		if (socket_desc == -1)
		{
			cout<<"Could not create socket"<<endl;
		}

		//Aus Config lesen
		//server.sin_addr.s_addr = inet_addr("127.0.0.1");
		//server.sin_addr.s_addr = inet_addr("172.17.190.78");
		//cout<<"redis_server#"<<redis_server<<endl;
		server.sin_addr.s_addr = inet_addr(redis_server.c_str());
		//##
		server.sin_family = AF_INET;
		int redis_port_int = atoi(redis_port.c_str());
		//cout<<"redis_port_int#"<<redis_port_int<<"#"<<endl;
		server.sin_port = htons(redis_port_int);

		//Connect to remote server
		if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
		{
			cout<<"connect error"<<endl;
			//return 1;
		}
		
		int msg_len = strlen(message);
		//int result = 0;
		//result = send(socket_desc, message, msg_len, 0);
		send(socket_desc, message, msg_len, 0);

		//cout<<"socket_desc: "<<socket_desc<<endl;
		//cout<<"result: "<<result<<endl;
		//cout<<"message: "<<message<<endl;	
		
		//Empfang
		char server_reply[6000];
		recv(socket_desc,server_reply,6000,0);
		//Formtierte Ausgabe mit line refresh#####
		*std::remove(server_reply, server_reply+strlen(server_reply), '\n') = '\0';
		//cout.flush();
		cout << "  Erfasste Datensätze " << server_reply << " \r";
		cout.flush();
		//###
		//cout<<"socket_desc: "<<socket_desc<<endl;
		//cout<<"sizeof(server_reply): "<<sizeof(server_reply)<<endl;
		close(socket_desc);
		
		//Lizenz decodieren#####Zum Prüfen ob eine Comunnity Edition vorliegt oder eine Vollversion.##############################################################
		//cout<<"key_uebergabe_read_file_info"<<key_uebergabe_read_file_info<<endl;
		//key_uebergabe_read_file_info = key_uebergabe_read_file_info.substr(0, key_uebergabe_read_file_info.length() - 1);	//das letzte \n abschneiden
		string openssl_command = "echo \"985e5b8715bc435e7e8d\" | openssl md5";
		//cout<<"openssl_command#"<<openssl_command<<endl;

		char *openssl_command_char_1 = {(char *) openssl_command.c_str()}; 
		FILE *pipe_1;
		char str_1[50000];
		pipe_1 = popen (openssl_command_char_1, "r" );
		if(pipe_1 == NULL)
		{
			perror("open failed");
			pclose(pipe_1);
			exit(-1);
			continue;
		}
		string md5_key = "";
		while(fgets ( str_1, 49999, pipe_1 ) != NULL)
			{
				md5_key = string(str_1);
			}
		md5_key = md5_key.substr(9,32); //32 = länge md5 hash
		//cout<<"md5_key für Prof Edi#"<<md5_key<<endl;
		pclose(pipe_1);
		
		if(md5_key != key_uebergabe_read_file_info)
		{
			//cout<<"NIX GUT"<<endl;
			
			//Community Edition Lizenz Check
			//##################################################	
			string openssl_command_2 = "echo \"Community Edition\" | openssl md5";
			//cout<<"openssl_command_2#"<<openssl_command_2<<endl;

			char *openssl_command_char_2 = {(char *) openssl_command_2.c_str()}; 
			FILE *pipe_2;
			char str_2[50000];
			pipe_2 = popen (openssl_command_char_2, "r" );
			if(pipe_2 == NULL)
			{
				perror("open failed");
				pclose(pipe_2);
				exit(-1);
				continue;
			}
			string md5_key_2 = "";
			while(fgets ( str_2, 49999, pipe_2 ) != NULL)
			{
				md5_key_2 = string(str_2);
			}
			pclose(pipe_2);
			
			md5_key_2 = md5_key_2.substr(9,32); //32 = länge md5 hash
			//cout<<"md5_key Community Edition #"<<md5_key_2<<"#"<<endl;
			
			//if(md5_key_2 == key_uebergabe_read_file_info)
			//cout<<"md5_key_2                   #"<<md5_key_2<<"#"<<endl;
			//cout<<"key_uebergabe_read_file_info#"<<key_uebergabe_read_file_info<<"#"<<endl;
			if (md5_key_2.compare(key_uebergabe_read_file_info) == 0)
			{
				//cout<<"Community Edition max. 1000 DB Datensätze"<<endl;
				//cout<<"server_reply#"<<server_reply<<"#"<<endl;
				int dbsize_max_count = 0;
				//server_reply chompen und trim
				string server_reply_string = server_reply;
				server_reply_string = server_reply_string.substr(1,999); //das : vom reply sub stringen
				//cout<<"server_reply_string#"<<server_reply_string<<"#"<<endl;
				server_reply_string.erase(0,server_reply_string.find_first_not_of(" ")); //führende Leerzeichen entfernen
				server_reply_string.erase(server_reply_string.find_last_not_of(" ")+1);  //Leerzeichen am Ende entfernen
				server_reply_string.erase(server_reply_string.find_last_not_of(" \n\r\t")+1);
				server_reply_string.erase(std::remove(server_reply_string.begin(), server_reply_string.end(), 'n'),server_reply_string.end());
				//cout<<"server_reply_string#"<<server_reply_string<<"#"<<endl;
				
				dbsize_max_count = atoi(server_reply_string.c_str()); //dbsize reply von string nach integer
				//dbsize_max_count = stoi(server_reply_string);
				//cout<<"dbsize_max_count"<<dbsize_max_count<<endl;
				
				if (dbsize_max_count >= 1000)
				{
					cout<<"Community Edition max. 1000 DB Datensätze"<<endl;
					//cout<<dbsize_max_count<<endl;
									
					//ggf. alle Progas in der Community edition killen
					//char die[1024]; 
					string killall;
					
					killall = "killall -9 read_file_infos 2&>1";
					//killall = "pkill read_file_infos";
					system(killall.c_str());
					
					//strcpy (die, "killall -9 find\n");
					killall = "killall -9 find 2&>1";
					//killall = "pkill find";
					system(killall.c_str());
				
					killall = "killall -9 xargs 2&>1";
					//killall = "pkill xargs";
					system(killall.c_str());
					
					//pthread_kill(0, SIGALRM);
					
					exit(0);
				}
				
			}
			//##################################################
		}
//#########################################
		
		/*
		//Empfang
		int i = 0;
		int n = 0;
		bool ende = true;

		while(ende)
		{
			//char buf[1024] = {0};
			//char buf[1024];
			//std::cout << message;
			cout<<"socket_desc: "<<socket_desc<<endl;
			cout<<"sizeof(message) "<<sizeof(message)<<endl;
			cout<<"i: "<<i<<endl;
			cout<<"n: "<<n<<endl;
			cout<<"message: "<<message<<endl;
			//n = recv(socket_desc,message,1024,2);
			//n = recv(socket_desc,message,1024,1);
			n = recv(socket_desc,message,1024,0);
			//recv(socket_desc,message,1024,2);
			//recv(socket_desc,message,1024,0);
			cout<<"message: "<<message<<endl;
			cout<<"socket_desc: "<<socket_desc<<endl;
			cout<<"sizeof(message): "<<sizeof(message)<<endl;
			cout<<"n: "<<n<<endl;		
			//n = recv(socket_desc, &message, 50, MSG_PEEK | MSG_DONTWAIT);
			//bzero (message, sizeof(message));
			i++;
			if (n == 0)
			{	
			//break;
				close(socket_desc);
				cout<<"socket_desc: "<<socket_desc<<endl;
				cout<<"sizeof(message) "<<sizeof(message)<<endl;
				cout<<"message: "<<message<<endl;
				//break;
				ende = false;
			}

			if (n < 1024)
			{	
				close(socket_desc);
				cout<<"socket_desc: "<<socket_desc<<endl;
				cout<<"sizeof(message) "<<sizeof(message)<<endl;
				cout<<"message: "<<message<<endl;
				//break;
				ende = false;
			}

			if (n == -1)
			{	
				close(socket_desc);
				cout<<"socket_desc: "<<socket_desc<<endl;
				cout<<"sizeof(message) "<<sizeof(message)<<endl;
				cout<<"message: "<<message<<endl;
				//break;
				ende = false;
			}
			
		}
		*/
	}
//##########################################################################

		pthread_exit(NULL);
}
/*
void *test(void *threadid_2)
{
	
		//return(0);
		sleep(1);
		cout<<"threadid 2:"<<threadid_2<<endl;
		cout<<"Thread pfad 2:"<<pfad<<endl;	
		cout<<"Thread  anzahl_xargs_prozesse 2:"<<anzahl_xargs_prozesse<<endl;	
		sleep(10);
		pthread_exit(NULL);
}
*/

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
		//cout<<"config_parameter_2:"<<config_parameter_2<<endl;
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
string check_license (string &config_file_parameter_12, string &config_file_parameter_13)
{	
	//cout<<"Lizenz Key aus Funktion:"<<config_file_parameter_12<<endl;

	//decrypt Lizenz
	
	string openssl_command;
	//string key = "Start Key";
	string key = config_file_parameter_13;
	
	//ersten key bis zum # filtern
	int gatter_gefunden = 0;
	gatter_gefunden = config_file_parameter_12.find("#");
	string pass_key;
	pass_key = config_file_parameter_12.substr(0,gatter_gefunden);
	//cout<<"pass_key#"<<pass_key<<endl;
	//Alt //openssl_command = "echo \"" + pass_key + "\" | openssl aes-256-cbc -a -d -salt -k " + key;				//Sues LibreSSL Kompatibel
	openssl_command = "echo \"" + pass_key + "\" | openssl aes-256-cbc -a -d -salt -md md5 -k " + key;				//Debian 9 mit "OpenSSL 1.1.0f  25 May 2017" kompatibel
	
/*
	//SSL_library_init ();											//Nur openssl nicht libressl
	//cout <<cout << SSLeay_version(SSLEAY_VERSION)<<endl;
	///string openssl_version = SSLeay_version(SSLEAY_VERSION);
	cout<<"openssl_version#"<<openssl_version<<endl;
	int erstes_leerzeichen_gefunden = openssl_version.find(" ");
	cout<<"erstes_leerzeichen_gefunden#"<<erstes_leerzeichen_gefunden<<endl;
	openssl_version = openssl_version.substr(0, erstes_leerzeichen_gefunden);
	cout<<"openssl_version#"<<openssl_version<<endl;
	//if (openssl_version == "LibreSSL")
	//{
	//	//SUSE mit Libressl command
	openssl_command = "echo \"" + pass_key + "\" | openssl aes-256-cbc -a -d -salt -k " + key;
	//}
	//bei Debian 9 mit openssl OpenSSL 1.1.0f  25 May 2017 # echo -e "U2FsdGVkX1+/+B3kAlKOjYCT4QegoasjcQdWFo42DTArxkzOnxe6WsT+lFWmkDpF" | openssl aes-256-cbc -a -d -salt -md md5 -k N2Q0YmFmNmIzZTM0MTFkMTVmMDYK
	//geht nur mit Schalter -md md5
	
	
	struct utsname sysinfo;
	uname(&sysinfo);
	cout << "System Name: "<<sysinfo.sysname<<endl;
	cout << "Host Name: "<<sysinfo.nodename<<endl;
	cout << "Release(Kernel) Version: "<<sysinfo.release<<endl;
	cout << "Kernel Build Timestamp: "<<sysinfo.version<<endl;
	cout << "Machine Arch: "<<sysinfo.machine<<endl;
	cout << "Domain Name: "<<sysinfo.domainname<<endl;
*/
//##########################
	//Linux Distribution mittels cat /etc/issue filtern
	//char *openssl_command_char = {(char *) openssl_command.c_str()}; 
	FILE *pipe_0;
	char str_0[1000];
	pipe_0 = popen ("cat /etc/issue", "r" );
	if(pipe_0 == NULL)
	{
		perror("open failed");
		pclose(pipe_0);
		exit(-1);
		return(0);
	}
	//string distri_vers = "";
	int i = 0;
	while(fgets ( str_0, 1000, pipe_0 ) != NULL)
		{
			distri_vers = string(str_0);
			//cout<<"distri_vers in fgets:"<<distri_vers<<endl;
			transform(distri_vers.begin(), distri_vers.end(), distri_vers.begin(), ::tolower);
			//cout<<"distri_vers in fgets lower:"<<distri_vers<<endl;
			
			i++;
			if (i >= 1)
			{	
				//continue;
				break;
			}
		}
	pclose(pipe_0);
//##########################################


	//cout<<openssl_command<<endl;
	char *openssl_command_char = {(char *) openssl_command.c_str()}; 
	FILE *pipe_1;
	char str_1[1000];
	pipe_1 = popen (openssl_command_char, "r" );
	if(pipe_1 == NULL)
	{
		perror("open failed");
		pclose(pipe_1);
		exit(-1);
		return(0);
	}
	string pass_1 = "";

	while(fgets ( str_1, 1000, pipe_1 ) != NULL)
		{
			pass_1 = string(str_1);
			//cout<<"pass_1 in fgets:"<<pass_1<<endl;
		}
	pclose(pipe_1);
	
	//cout<<"pass_1:"<<pass_1<<endl;

	//Liznez Abschnitt filtern
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
	//cout<<"pass_1:"<<pass_1<<endl;
	
	//####################################################	
	//int debian_gefunden = 666 ;
	debian_gefunden = distri_vers.find("debian");
	//cout<<"debian_gefunden#"<<debian_gefunden<<endl;

	if (debian_gefunden >= 0)
	{
		openssl_command = "echo \'"+ lizenz + "\' | openssl aes-256-cbc -md md5 -d -a -salt -k " + pass_1;		//Debian Kompatibel (sh environment)
		//cout<<"openssl_command für debain"<<openssl_command<<endl;
		//Test # sh -c ' echo "U2FsdGVkX1/uNgnvPy7mA9uby0gpc05mj5NbmaPNaQdGFWlBilpPuIF0I0a/bbuG\npOho1HMBsYome5AuVi6LgiD/LEuSI5FlkydwFqkiLCq4683x7fo9YI1eSXC23tK1\nE2t3HdAkMEyCsnRc5bbrpA==" | openssl aes-256-cbc -a -d -base64 -md md5 -salt -k 6ec9520ed4c124b1d016 '
	}
	else
	{
		openssl_command = "echo -e \""+ lizenz + "\" | openssl aes-256-cbc -md md5 -a -d -salt -k " + pass_1;				//Reicht für Suse/SLES (sh environment)
		//cout<<"openssl_command für REST"<<openssl_command<<endl;
	}
	//openssl_command = "";
	//openssl_command = "echo -e \""+ lizenz + "\" | openssl aes-256-cbc -a -d -salt -k " + pass_1;				//Reicht für Suse/SLES (sh environment)
	//openssl_command = "echo -e \'"+ lizenz + "\' | openssl aes-256-cbc -md md5 -d -a -salt -k " + pass_1;		//Debian Kompatibel (sh environment)
	//cout<<"openssl_command#"<<openssl_command<<endl;
	//cout<<system(openssl_command.c_str());
	//cout<<system("echo \"U2FsdGVkX1/uNgnvPy7mA9uby0gpc05mj5NbmaPNaQdGFWlBilpPuIF0I0a/bbuG\npOho1HMBsYome5AuVi6LgiD/LEuSI5FlkydwFqkiLCq4683x7fo9YI1eSXC23tK1\nE2t3HdAkMEyCsnRc5bbrpA==\" | openssl aes-256-cbc -a -d -base64 -md md5 -salt -k 6ec9520ed4c124b1d016")<<endl;
	//####################################################

	char *openssl_command_char_2 = {(char *) openssl_command.c_str()}; 
	FILE *pipe_2;
	char str_2[1001];
	pipe_2 = popen (openssl_command_char_2, "r" );

	 //wenn pipe_2 gleich "bad magic number" dann problem mit openssl
	
	if(pipe_2 == NULL)
	{
		perror("open failed");
		pclose(pipe_2);
		exit(-1);
		//return(0);
	}
	string lizenz_2 = "";
	while(fgets ( str_2, 1000, pipe_2 ) != NULL)
		{
			lizenz_2 = string(str_2);
			//cout<<"lizenz_2#"<<lizenz_2<<endl;
		}
	pclose(pipe_2);
	
	//cout<<"lizenz_2 nach pclose:"<<lizenz_2<<endl;
	
	//Lizenz_2 in Public Variable für Übergabe nach read_file_info
	//mkey filter
	//Bilfinger GIT;alexander.moore@bilfinger.com;expire:20180801;mkey=985e5b8715bc435e7e8d
	int letzes_semikolon_gefunden = 0;
	//cout<<"lizenz_2 in fur pub var#"<<lizenz_2<<endl;
	letzes_semikolon_gefunden = lizenz_2.find_last_of(";");
	//cout<<"letzes_semikolon_gefunden"<<letzes_semikolon_gefunden<<endl;
	string mkey;
	mkey = lizenz_2.substr(letzes_semikolon_gefunden + 6,999);
	//cout<<"mkey"<<mkey<<endl;
	
	//Aus mkey einen md5 key machen
	//echo -n "985e5b8715bc435e7e8d" | openssl md5
	openssl_command = "echo -n \""+ mkey + "\" | openssl md5";
	//cout<<"openssl_command"<<endl;
	
	char *openssl_command_char_3 = {(char *) openssl_command.c_str()}; 
	FILE *pipe_3;
	char str_3[1000];
	pipe_3 = popen (openssl_command_char_3, "r" );
	if(pipe_3 == NULL)
	{
		perror("open failed");
		pclose(pipe_3);
		exit(-1);
		return(0);
	}
	string md5_uebergabe_key = "";
	while(fgets ( str_3, 1000, pipe_3 ) != NULL)
		{
			md5_uebergabe_key = string(str_3);
		}
	pclose(pipe_3);
	
	//cout<<"md5_uebergabe_key:"<<md5_uebergabe_key<<endl;
	
	//(stdin)= weg machen
	md5_uebergabe_key = md5_uebergabe_key.substr(9,999);
	key_uebergabe_read_file_info = md5_uebergabe_key;
	key_uebergabe_read_file_info = key_uebergabe_read_file_info.substr(0, key_uebergabe_read_file_info.length() - 1);	//das letzte \n abschneiden
	//cout<<"key_uebergabe_read_file_info"<<key_uebergabe_read_file_info<<endl;
	
	//return(0);	
	return("nix");
}

//###################################################################################################################

int main(int argc, char *argv[]) 
{
	
//###################################################################################################################
	//Error Signals
	signal(SIGSEGV, signalHandler);
	signal(SIGABRT, signalHandler);
	signal(SIGFPE, signalHandler);
	signal(SIGILL, signalHandler);
	signal(SIGTERM, signalHandler);
	signal(SIGINT, signalHandler);

//###################################################################################################################
	//Resource limit vergroessern (ulimit). Wird an Child Prozesse vererbt
	struct rlimit rl;
	//getrlimit (RLIMIT_CPU, &rl);
	rl.rlim_cur = RLIM_INFINITY;		//#RLIM_INFINITY = unlimited
	rl.rlim_max = RLIM_INFINITY;		//#RLIM_INFINITY = unlimited
	
	//#http://man7.org/linux/man-pages/man2/getrlimit.2.html		#cat /proc/<PID>/limits
	setrlimit(RLIMIT_AS, &rl);
	setrlimit(RLIMIT_CORE,&rl);
	setrlimit(RLIMIT_CPU,&rl);
	setrlimit(RLIMIT_DATA,&rl);
	setrlimit(RLIMIT_FSIZE,&rl);
	setrlimit(RLIMIT_LOCKS,&rl);
	setrlimit(RLIMIT_MEMLOCK,&rl);
	setrlimit(RLIMIT_MSGQUEUE,&rl);
	setrlimit(RLIMIT_NPROC,&rl);
	setrlimit(RLIMIT_RSS,&rl);
	setrlimit(RLIMIT_RTPRIO,&rl);
	setrlimit(RLIMIT_RTTIME,&rl);
	setrlimit(RLIMIT_SIGPENDING,&rl);
	setrlimit(RLIMIT_STACK,&rl);
	
	//#########
	//Number of open file. Nimmt INFINITY nicht an
	struct rlimit rl_open_files;
	rl_open_files.rlim_cur = 1024;
	rl_open_files.rlim_max = 999999;
	setrlimit(RLIMIT_NOFILE,&rl_open_files);
	//#############
	
	//echo "999999999" > /proc/sys/fs/pipe-max-size
//###################################################################################################################

	//putenv("XTERM_LOCALE=en_US.UTF-8");
	//putenv("LC_CTYPE=en_US.UTF-8");
	
//###################################################################################################################

	cout<<"Lösche alte DB Einträge"<<endl;
	string redis_cli_flushdb = "redis-cli flushdb";
	system(redis_cli_flushdb.c_str());
	
//###################################################################################################################

	//Uebergabeparameter einfangen
	//cout<<"Test"<<endl;
	//ARGVs lesen
	//string pfad, anzahl_xargs_prozesse;
	
	pfad=argv[1];
	anzahl_xargs_prozesse=argv[2];
	
	//cout<<"pfad:"<<pfad<<endl;	
	//cout<<"anzahl_xargs_prozesse:"<<anzahl_xargs_prozesse<<endl;	

//###################################################################################################################
	//Config File einlesen
	//string redis_server, redis_port, ms_word, ms_exel, ascii_file_max_read_lines,ascii_file_max_read_chars, exe_dll_infos, md5sum_conf;
	
	vector<string> config_file_parameter;
		
	read_config_file(config_file_parameter);
	
	//cout<<"redis server:"<<config_file_parameter[0]<<endl;
	//cout<<"redis port:"<<config_file_parameter[1]<<endl;
	//cout<<" license key:"<<config_file_parameter[12]<<endl;
	
	check_license(config_file_parameter[12], config_file_parameter[13]);
	
	redis_server = config_file_parameter[0];
	redis_port = config_file_parameter[1];

//###################################################################################################################

	//###################################################################################################################
	
	//pthreads starten
	//cout<<"Starte Thread !!!"<<endl;
	pthread_t threads[3];
	int rueckgabe_wert_0 = 666;
	//int rueckgabe_wert_1;
	
	int thread_nummer_0 = 0 ;
	//int thread_nummer_0 = (intptr_t) 0;
	int thread_nummer_1 = 1 ;
	//int thread_nummer_2 = 2 ;
	//rueckgabe_wert_0 = pthread_create(&threads[0], NULL, find_xargs,(void *)thread_nummer_0);
	rueckgabe_wert_0 = pthread_create(&threads[0], NULL, find_xargs,(void *)&thread_nummer_0);
	//rueckgabe_wert_1 = pthread_create(&threads[1], NULL, dbsize_eintraege,(void *)thread_nummer_1);
	//pthread_create(&threads[1], NULL, dbsize_eintraege,(void *)thread_nummer_1);
	pthread_create(&threads[1], NULL, dbsize_eintraege,(void *)&thread_nummer_1);
	//rueckgabe_wert = pthread_create(&threads[2], NULL, test,(void *)thread_nummer_2);
	//sleep(15);
	
	//Clean Up Thread für Zombies:
	//root     30175 27703  0 15:54 pts/3    00:00:00 [sh] <defunct>
	//signal(SIGCHLD, SIG_IGN);
	
	//warten bis find_xargs thread zu ende ist###
	void *status;
	rueckgabe_wert_0 = pthread_join(threads[0], &status);
	if (rueckgabe_wert_0)
	{
		cout<<"Error: unable to join thread 0"<<rueckgabe_wert_0<<endl;
		exit(-1);
	}
	 //######
	//cout<<"Threads 2 beendet !!!"<<endl;	 
	//cout<<"rueckgabe_wert_0: "<<rueckgabe_wert_0<<endl;
	//cout<<"rueckgabe_wert_1: "<<rueckgabe_wert_1<<endl;
				
	//###################################################################################################################
	/*
	string command;
	command = "find " + pfad + " -type f -print0 | xargs -P" + anzahl_xargs_prozesse + " -0 -I'{}' timeout 500s ./read_file_infos {}";
	//cout<<"command:"<<command<<endl;
	char *command_char = {(char *) command.c_str()}; 
	system(command_char);
	//popen (command_char, "r" );
	*/
	
	//Such Status ausgebeb
/*
//Anzahl einträge in DB######################################################
	int socket_desc;
	struct sockaddr_in server;
	char *message = "dbsize\r\n";

	 //Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		cout<<"Could not create socket"<<endl;
	}
	 
	server.sin_addr.s_addr = inet_addr("127.0.0.1");
	server.sin_family = AF_INET;
	server.sin_port = htons( 6379 );

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		cout<<"connect error"<<endl;
		//return 1;
	}
	int msg_len = strlen(message);
	int result = 0;
	result = send(socket_desc, message, msg_len, 0);

	cout<<"socket_desc: "<<socket_desc<<endl;
	cout<<"result: "<<result<<endl;
	cout<<"message: "<<message<<endl;	
	*/
//##########################################################################
	
	//Commandlien Line Animation
	
	//Uhrzeit
	
	//##########################################################################
	//1 und 2 löschen
	string rm_1 = "rm -fr 1";
	string rm_2 = "rm -fr 2";
	system(rm_1.c_str());
	system(rm_2.c_str());
						
//######################################################

	//alle "sh <defunct>" child prozesse beenden. Werden von "read_file_infos -> popen" erzeugt bzw. hinterlassen. !!!!
	signal(SIGCHLD, SIG_IGN);

	return (0);
}
