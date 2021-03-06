//Linker Additional Libs
//C:\Program Files (x86)\Windows Kits\8.1\Lib\winv6.3\um\x86\Version.Lib


#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <windows.h>//Header fuer die Version detection
#include <tchar.h>//Header fuer die charcter Konventionen
#include <string>
#include <msclr\marshal_cppstd.h>
//Try-Catch-Exception Header
#include <exception>

#using <System.dll>

using namespace msclr::interop;
using namespace std;
using namespace System;
using namespace System::IO;
using namespace System::Diagnostics;

int main(int argc, char *argv[])
{
	string pfad_plus_dateiname;
	//cout << "Test" << endl;
	pfad_plus_dateiname = argv[1];		//PRD
	//pfad_plus_dateiname = "notepad.exe";			//Für Debugging
	//pfad_plus_dateiname = "MartinLutherKing-IHaveADream.mp3";			//Für Debugging
	//cout << pfad_plus_dateiname << endl;

try{
	System::String^ systemString = msclr::interop::marshal_as<System::String^>(pfad_plus_dateiname);

	FileVersionInfo^ myFileVersionInfo = FileVersionInfo::GetVersionInfo(systemString);
	
	std::string std_string_FileDescription = msclr::interop::marshal_as<std::string>(myFileVersionInfo->FileDescription);
	std::string std_string_FileVersion = msclr::interop::marshal_as<std::string>(myFileVersionInfo->FileVersion);
	std::string std_string_CompanyName = msclr::interop::marshal_as<std::string>(myFileVersionInfo->CompanyName);
	std::string std_string_ProductVersion = msclr::interop::marshal_as<std::string>(myFileVersionInfo->ProductVersion);
	std::string std_string_ProductName = msclr::interop::marshal_as<std::string>(myFileVersionInfo->ProductName);

	cout << " FileDescription: " << std_string_FileDescription << endl;
	cout << " FileVersion: " << std_string_FileVersion << endl;
	cout << " CompanyName: " << std_string_CompanyName << endl;
	cout << " ProductVersion: " << std_string_ProductVersion << endl;
	cout << " ProductName: " << std_string_ProductName << endl;
}
catch (Exception ^e)
{
	//throw gcnew Exception(marshal_as<String^>(e.what()));
	//throw gcnew Exception("Unknown C++ exception");
	cout << "Keine Versionsinformationen gefunden" << endl;
	exit(0);
	//throw;
}
	
	//#####################
	//Console::WriteLine(" FileDescription: " + myFileVersionInfo->FileDescription);
	//Console::WriteLine(" FileVersion: " + myFileVersionInfo->FileVersion);
	//Console::WriteLine(" CompanyName: " + myFileVersionInfo->CompanyName);
	//Console::WriteLine(" ProductVersion: " + myFileVersionInfo->ProductVersion);
	//Console::WriteLine(" ProductName: " + myFileVersionInfo->ProductName);
	//####################################################

	return (0);
}
