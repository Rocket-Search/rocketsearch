//rm -frv pdf_read.o; clear; g++-7 -g -fPIC -Wall -o pdf_read pdf_read.cpp
//rm -frv pdf_read.o; clear; g++-7 -g -fPIC -Wall -c pdf_read.cpp
#include <iostream>
#include <iomanip>
#include <stdio.h>


using namespace std;

//extern string pfad_uebergabe_mp3;
extern string pfad_uebergabe_pdf;
extern string pdf_file_info_magic;
extern string pdf_content; 
extern string pdf_read_max_lines;

void pdf_read()
{
	
	//gs -dBATCH -dNOPAUSE -sDEVICE=txtwrite -dTextFormat=3 -sOutputFile=- libre_office_writer_pdf.pdf	
	
	//cout<<"Ghost Script "<<endl;
	
	string gs_command = "gs -dBATCH -dNOPAUSE -sDEVICE=txtwrite -dTextFormat=3 -sOutputFile=- '" + pfad_uebergabe_pdf + "'" ;
	//cout<<metaflac_command<<endl;
	char *gs_command_char = {(char *) gs_command.c_str()}; 
	FILE *pipe;
	char str[50000];
	pipe = popen (gs_command_char, "r" );
	if(pipe == NULL)
	{
		perror("open failed");
		pclose(pipe);
		exit(0);
	}
	//metaflac_command = string(str);
	//cout<<metaflac_command<<endl;
	string pdf_data = "";
	int i = 0;
	int j = 0;
	//cout<<"pdf_read_max_lines#"<<pdf_read_max_lines<<endl;
	int pdf_read_max_lines_int = atoi(pdf_read_max_lines.c_str());
	//cout<<"pdf_read_max_lines_int#"<<pdf_read_max_lines_int<<endl;
	 
	while(fgets ( str, 49999, pipe ) != NULL)
	{
		//flac_metat_data.append(string(str));
		i++ ;	//Zähler für die ersten fünf Zeilen, da dort nur die Versionsinformationen von gs ausgegeben werden
				
		if (i < 5)
		{
			continue;
		}
		
		//cout<<"string(str)#"<<string(str)<<endl;
		//cout<<"j#"<<j<<endl;
		if (j < pdf_read_max_lines_int)
		{
			j++ ;	//Zähler für die max. einzulsenden Zeilen des PDF Docs
			pdf_data.append(string(str));
			//cout<<"pdf_data#"<<pdf_data<<"j#"<<j<<endl;
		}
	}
	
	pclose(pipe);
	
	//cout<<"pdf_data#"<<pdf_data<<endl;
	pdf_content = pdf_data;
}



