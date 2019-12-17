//##################
//Compile Command: 
	//DEBUG: rm -frv client; clear; g++-7 -g -Wall -lpthread client.cpp -o client;
	//PRD: rm -frv client; clear; g++-7 -O3 -Wall -lpthread client.cpp -o client
//##################
//Execute Command:
	//./client "mp3"

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <netdb.h> 
#include <iostream>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h> 
#include <vector>
#include <string>
#include <sys/time.h>
#include <sstream>
#include <fstream>
#include <pthread.h>
#include <thread>
#include <time.h>
#include <iterator>
//Posix Thread
#include <pthread.h>
//Error Handling und Singal
#include <errno.h>
#include <signal.h>
#include <malloc.h>
#include <errno.h>
#include <sys/mman.h>
#include <csignal>
#include <iterator>


using namespace std;

string suchmuster;
//bool animation_beenden = false;

void signalHandler( int signum) 
{
	cout << "Interrupt signal (" << signum << ") received.\n";
	cout<<"PROBLEM"<<endl;
	cout<<"Segmentation fault"<<endl;
	// cleanup and close up stuff here  
	//terminate program  

	//cout<<SIGSEGV_pfad_datei<<endl;
	

	exit(0);
	//exit(signum);  
}

void *starte_suche(void *threadid_0)
{
		
	struct hostent *host;//Hostname struktuieren
	host = gethostbyname("127.0.0.1"); //eventuell die IP in DNS Namen umwandeln
	struct sockaddr_in addr;
	addr.sin_addr = *(struct in_addr*)host->h_addr;
	int s; 
	s = socket(PF_INET, SOCK_STREAM, 0); //Socket aufbauen. wenn -1 dann ist fehlgeschlagen
	addr.sin_port = htons(6379);//Connection Portnummer des Servers festlegen
	addr.sin_family = AF_INET; 
	connect(s,(struct sockaddr*)&addr, sizeof(addr));
	//string suchmuster = argv[1];
	string redis_command = "KEYS";
	int wo_ist_ende = 0;
	suchmuster = suchmuster.insert(0,"KEYS \"*");
	wo_ist_ende =  suchmuster.size();
	suchmuster = suchmuster.insert(wo_ist_ende,"*\"\r\n");
	char* request = (char*)suchmuster.c_str();
	cout<<"request: "<<request<<endl;
//#######################################
//#Zum testen für lange suchen
sleep(10);
//Animation Thread beenden
//pthread_kill(1, SIGTERM);
//animation_beenden = true;
//#######################################
	send(s, request, strlen(request),0);//Daten senden
	char response[1024];//Empfangspuffer festlegen
	int bytes; 
	string antwort_ausgabe;
	vector<string> vektor;
	int i=0;
	bool ende = true;
	bzero (response, sizeof(response));
	while(ende)
	{
		bytes = recv(s, response, sizeof(response), 0);
		i = i + 1;
		cout<<endl<<response;
		bzero (response, sizeof(response));
		if (bytes == 0)
		{	
			close(s);
			ende = false;
		}
		if (bytes < 1024)
		{	
			close(s);
			ende = false;
		}
		if (bytes == -1)
		{	
			close(s);
			ende = false;
		}
	}
		
	pthread_exit(NULL);
}

void *starte_animation(void *threadid_1)
{

	//Damit noch der Suchtring ausggeben werden kann aus dem anderen Thread
	sleep(1);
	
	cout<<"   \/\\"<<endl;
	cout<<"   ||"<<endl;
	cout<<"   ||"<<endl;
	cout<<"   ||"<<endl;
	cout<<" \/____\\"<<endl;
	while(1)
	{
		sleep(1);
		cout<<"\b  ###\n"<<flush;
		sleep(1);
		cout<<"\b  ***\n"<<flush;
		//cout<<"\b   #\n #"<<flush;
		//sleep(1);
		//cout << "\b\*\* \n *" <<flush;
		//sleep(1);
		//cout << "\b\#" <<flush;
		//sleep(1);
		//cout << "\b\*" <<flush;
		
	}
	
	pthread_exit(NULL);
}

int main(int argc, char *argv[]) 
{
	
	signal(SIGSEGV, signalHandler);
	
//###################################################################################################################
	suchmuster = argv[1];
	
//###################################################################################################################
	//cout<<"Starte Thread !!!"<<endl;
	pthread_t threads[3];
	int rueckgabe_wert_0;
	int rueckgabe_wert_1;
	int thread_nummer_0 = 0 ;
	int thread_nummer_1 = 1 ;
	int thread_nummer_2 = 2 ;
	rueckgabe_wert_0 = pthread_create(&threads[0], NULL, starte_suche,(void *)thread_nummer_0);
	rueckgabe_wert_1 = pthread_create(&threads[1], NULL, starte_animation,(void *)thread_nummer_1);
	//rueckgabe_wert = pthread_create(&threads[2], NULL, test,(void *)thread_nummer_2);
	//sleep(15);
	
	//warten bis find_xargs thread zu ende ist###
	void *status;
	rueckgabe_wert_0 = pthread_join(threads[0], &status);
	if (rueckgabe_wert_0 != 0)
	{
		cout << "Error:unable to join," << rueckgabe_wert_0 << endl;
		exit(-1);
	}
	 //######
	 
	cout<<"rueckgabe_wert_0: "<<rueckgabe_wert_0<<endl;
	cout<<"rueckgabe_wert_1: "<<rueckgabe_wert_1<<endl;
				
//###################################################################################################################
	


	return (0);
}




