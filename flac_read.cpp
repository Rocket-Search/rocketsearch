#include <iostream>
#include <iomanip>
#include <stdio.h>


using namespace std;

//extern string pfad_uebergabe_mp3;
extern string pfad_uebergabe_flac;
extern string flac_file_info_magic;
extern string flac_tags_content; 

void flac_read()
	{
		//cout<<"flac object file"<<endl;
		//cout<<"flac_file_info_magic#"<<flac_file_info_magic<<endl;;
		
		string metaflac_command = "metaflac --show-total-samples --show-sample-rate --show-vendor-tag --show-bps --show-channels --export-tags-to=- '" + pfad_uebergabe_flac + "'" ;
		//cout<<metaflac_command<<endl;
		char *metaflac_command_char = {(char *) metaflac_command.c_str()}; 
		FILE *pipe;
		char str[50000];
		pipe = popen (metaflac_command_char, "r" );
		if(pipe == NULL)
		{
			perror("open failed");
			pclose(pipe);
			exit(0);
		}
		//metaflac_command = string(str);
		//cout<<metaflac_command<<endl;
		string flac_metat_data = "";
		int i = 0;
		
		string total_samples, sample_rate, vendor_tag, bps, channels, tags;
		
		while(fgets ( str, 49999, pipe ) != NULL)
			{
				//flac_metat_data = string(str);
				//cout<<"flac_metat_data#"<<flac_metat_data<<endl;
				//flac_metat_data.append(string(str));
				i++ ;
				if (i == 1)
				{
					//cout<<"--show-total-samples#"<<string(str)<<endl;
					total_samples=string(str);
				}
				if (i == 2)
				{
					//cout<<"--show-sample-rate#"<<string(str)<<endl;
					sample_rate=string(str);
				}
				if (i == 3)
				{
					//cout<<"--show-vendor-tag#"<<string(str)<<endl;
					vendor_tag=string(str);
				}
				if (i == 4)
				{
					//cout<<"--show-bps#"<<string(str)<<endl;
					bps=string(str);
				}
				if (i == 5)
				{
					//cout<<"--show-channels#"<<string(str)<<endl;
					channels=string(str);
				}
				if (i > 5)
				{
					//cout<<"--export-tags-to#"<<string(str)<<endl;
					tags.append(string(str) +"# ");
					//tags.append("\n");
				}
			}
		
		//pipe = popen ("exit", "r" );
		pclose(pipe);		
	
		double total_samples_int = atof(total_samples.c_str());
		//cout<<"total_samples_int#"<<total_samples_int<<endl;
		double sample_rate_int = atof(sample_rate.c_str());
		//cout<<"sample_rate_int#"<<sample_rate_int<<endl;
		double track_sekunden_zeit = total_samples_int / sample_rate_int;
		//cout<<"track_sekunden_zeit#"<<track_sekunden_zeit<<endl;
		double track_minuten = track_sekunden_zeit / 60;
		//cout<<"track_minuten#"<<track_minuten<<endl;

		ostringstream strs;
		strs << track_minuten;
		std::string track_minuten_string = strs.str();

		flac_tags_content = tags + "#Track Laenge:" + track_minuten_string + " Minuten \n#Sample Rate:" + total_samples + "#Bits per Sample:" + bps +"#Vendor Tag:" + vendor_tag +"#Channels:" + channels;
		
	}