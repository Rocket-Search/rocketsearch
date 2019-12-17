#include <iostream>
#include <iomanip>
#include <stdio.h>


//tagLib Header
//Full Featured ;-)
#include </usr/include/taglib/aifffile.h>
#include </usr/include/taglib/aiffproperties.h>
#include </usr/include/taglib/apefile.h>
#include </usr/include/taglib/apefooter.h>
#include </usr/include/taglib/apeitem.h>
#include </usr/include/taglib/apeproperties.h>
#include </usr/include/taglib/apetag.h>
#include </usr/include/taglib/asfattribute.h>
#include </usr/include/taglib/asffile.h>
#include </usr/include/taglib/asfpicture.h>
#include </usr/include/taglib/asfproperties.h>
#include </usr/include/taglib/asftag.h>
#include </usr/include/taglib/attachedpictureframe.h>
#include </usr/include/taglib/audioproperties.h>
#include </usr/include/taglib/chapterframe.h>
#include </usr/include/taglib/commentsframe.h>
#include </usr/include/taglib/eventtimingcodesframe.h>
#include </usr/include/taglib/fileref.h>
#include </usr/include/taglib/flacfile.h>
#include </usr/include/taglib/flacmetadatablock.h>
#include </usr/include/taglib/flacpicture.h>
#include </usr/include/taglib/flacproperties.h>
#include </usr/include/taglib/generalencapsulatedobjectframe.h>
#include </usr/include/taglib/id3v1genres.h>
#include </usr/include/taglib/id3v1tag.h>
#include </usr/include/taglib/id3v2extendedheader.h>
#include </usr/include/taglib/id3v2footer.h>
#include </usr/include/taglib/id3v2frame.h>
#include </usr/include/taglib/id3v2framefactory.h>
#include </usr/include/taglib/id3v2header.h>
#include </usr/include/taglib/id3v2synchdata.h>
#include </usr/include/taglib/id3v2tag.h>
#include </usr/include/taglib/infotag.h>
#include </usr/include/taglib/itfile.h>
#include </usr/include/taglib/itproperties.h>
#include </usr/include/taglib/modfile.h>
#include </usr/include/taglib/modfilebase.h>
#include </usr/include/taglib/modproperties.h>
#include </usr/include/taglib/modtag.h>
#include </usr/include/taglib/mp4atom.h>
#include </usr/include/taglib/mp4coverart.h>
#include </usr/include/taglib/mp4file.h>
#include </usr/include/taglib/mp4item.h>
#include </usr/include/taglib/mp4properties.h>
#include </usr/include/taglib/mp4tag.h>
#include </usr/include/taglib/mpcfile.h>
#include </usr/include/taglib/mpcproperties.h>
#include </usr/include/taglib/mpegfile.h>
#include </usr/include/taglib/mpegheader.h>
#include </usr/include/taglib/mpegproperties.h>
#include </usr/include/taglib/oggfile.h>
#include </usr/include/taglib/oggflacfile.h>
#include </usr/include/taglib/oggpage.h>
#include </usr/include/taglib/oggpageheader.h>
#include </usr/include/taglib/opusfile.h>
#include </usr/include/taglib/opusproperties.h>
#include </usr/include/taglib/ownershipframe.h>
#include </usr/include/taglib/podcastframe.h>
#include </usr/include/taglib/popularimeterframe.h>
#include </usr/include/taglib/privateframe.h>
#include </usr/include/taglib/relativevolumeframe.h>
#include </usr/include/taglib/rifffile.h>
#include </usr/include/taglib/s3mfile.h>
#include </usr/include/taglib/s3mproperties.h>
#include </usr/include/taglib/speexfile.h>
#include </usr/include/taglib/speexproperties.h>
#include </usr/include/taglib/synchronizedlyricsframe.h>
#include </usr/include/taglib/tableofcontentsframe.h>
#include </usr/include/taglib/tag.h>
#include </usr/include/taglib/tag_c.h>
#include </usr/include/taglib/taglib.h>
#include </usr/include/taglib/taglib_config.h>
#include </usr/include/taglib/taglib_export.h>
#include </usr/include/taglib/tbytevector.h>
#include </usr/include/taglib/tbytevectorlist.h>
#include </usr/include/taglib/tbytevectorstream.h>
#include </usr/include/taglib/tdebuglistener.h>
#include </usr/include/taglib/textidentificationframe.h>
#include </usr/include/taglib/tfile.h>
#include </usr/include/taglib/tfilestream.h>
#include </usr/include/taglib/tiostream.h>
#include </usr/include/taglib/tlist.h>
#include </usr/include/taglib/tmap.h>
#include </usr/include/taglib/tpropertymap.h>
#include </usr/include/taglib/trefcounter.h>
#include </usr/include/taglib/trueaudiofile.h>
#include </usr/include/taglib/trueaudioproperties.h>
#include </usr/include/taglib/tstring.h>
#include </usr/include/taglib/tstringlist.h>
#include </usr/include/taglib/uniquefileidentifierframe.h>
#include </usr/include/taglib/unknownframe.h>
#include </usr/include/taglib/unsynchronizedlyricsframe.h>
#include </usr/include/taglib/urllinkframe.h>
#include </usr/include/taglib/vorbisfile.h>
#include </usr/include/taglib/vorbisproperties.h>
#include </usr/include/taglib/wavfile.h>
#include </usr/include/taglib/wavpackfile.h>
#include </usr/include/taglib/wavpackproperties.h>
#include </usr/include/taglib/wavproperties.h>
#include </usr/include/taglib/xingheader.h>
#include </usr/include/taglib/xiphcomment.h>
#include </usr/include/taglib/xmfile.h>
#include </usr/include/taglib/xmproperties.h>

using namespace std;
	
using namespace TagLib;
using namespace TagLib::MPEG;
using namespace TagLib::ID3v2;

//using namespace TagLib::FLAC;

//extern string pfad_uebergabe_mp3;
extern string pfad_fuer_mp3;
extern string mp3_file_info_magic;
extern string mp3_tags_content; 

void mp3_read()
  {
	//cout<<"Object File"<<endl;
	//cout<<"pfad_uebergabe_mp3 aus object file#"<<pfad_uebergabe_mp3<<endl;
	//cout<<"pfad_fuer_mp3 aus object file#"<<pfad_fuer_mp3<<endl;
	//cout<<"mp3_file_info_magic aus object file#"<<mp3_file_info_magic<<endl;
	//mp3_tags_content = "IDv3 TAGs";


	//MPEG::File f("lied.mp3");
	//TagLib::FileRef f("lied.mp3");
	TagLib::FileRef f(pfad_fuer_mp3.c_str());
	f.tag();
	TagLib::Tag *tag = f.tag();
	
	/*
	cout << "title   - \"" << tag->title()   << "\"" << endl;
	cout << "artist  - \"" << tag->artist()  << "\"" << endl;
	cout << "album   - \"" << tag->album()   << "\"" << endl;
	cout << "year    - \"" << tag->year()    << "\"" << endl;
	cout << "comment - \"" << tag->comment() << "\"" << endl;
	cout << "track   - \"" << tag->track()   << "\"" << endl;
	cout << "genre   - \"" << tag->genre()   << "\"" << endl;
	*/
	
	TagLib::AudioProperties *properties = f.audioProperties();
	
	int seconds = properties->length() % 60;
	int minutes = (properties->length() - seconds) / 60;

	/*
	cout << "bitrate     - " << properties->bitrate() << endl;
	cout << "sample rate - " << properties->sampleRate() << endl;
	cout << "channels    - " << properties->channels() << endl;
	cout << "length      - " << minutes << ":" << setfill('0') << setw(2) << seconds << endl;
	*/
	
	//convert to string
	stringstream mp3_string_stream;
	
	mp3_string_stream<<tag->title() ;
	string mp3_titel = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	mp3_string_stream<<tag->artist() ;
	string mp3_artist = mp3_string_stream.str();
	mp3_string_stream.str("");	
	
	mp3_string_stream<<tag->album() ;
	string mp3_album = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	mp3_string_stream<<tag->year() ;
	string mp3_year = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	mp3_string_stream<<tag->comment() ;
	string mp3_comment = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	mp3_string_stream<<tag->track() ;
	string mp3_track = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	mp3_string_stream<<tag->genre() ;
	string mp3_genre = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	mp3_string_stream<<properties->bitrate() ;
	string mp3_bitrate = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	mp3_string_stream<<properties->sampleRate() ;
	string mp3_sampleRate = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	mp3_string_stream<<properties->channels() ;
	string mp3_channels = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	mp3_string_stream<<minutes<<":"<<setfill('0')<<setw(2)<<seconds;
	string mp3_length = mp3_string_stream.str();
	mp3_string_stream.str("");
	
	//cout<<"mp3_tags_content#"<<mp3_tags_content<<endl;
	mp3_tags_content = "Titel:" + mp3_titel + "# Artist:" + mp3_artist + "# Album:" + mp3_album + "# Jahr:" + mp3_year + "# Kommentar:" + mp3_comment + "# Track Nr. :" + mp3_track + "# Artist:" + mp3_artist + "# Genre:" + mp3_genre + "# Länge:" + mp3_length + "# Bitrate:" + mp3_bitrate + "# sampleRate:" + mp3_sampleRate +"# Channels:" + mp3_channels + "\n";

//FLAC File####################################################
	//cout<<"mp3_file_info_magic aus object file#"<<mp3_file_info_magic<<endl;
	//TagLib::FLAC::Properties->new(pfad_fuer_mp3.c_str());
	 
	//TagLib::FLAC::File::File = File(pfad_fuer_mp3.c_str());  

	//TagLib::ASF::File file = File(pfad_fuer_mp3.c_str());	
	
	
  }
 