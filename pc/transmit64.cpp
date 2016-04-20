#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

using namespace std;

void printUsage(char* progName)
{
	cout << endl;
	cout << "Usage: " << endl;
	cout <<  progName << " <fileToTransmit> </dev/yourSerialDevice> <delayPerByte>";
	cout << endl;
	cout << endl;
}

void printCharWithBinary(const char& c)
{
	cout << "\"" << c << "\"" << ": ";
	for(int i = 7; i >= 0; --i)
	{
		cout << ((c >> i) & 1);
	}
}

int main(int argc, char* argv[])
{
	cout << endl << "Transmit64 Copyright 2016 W.A.Jurczyk" << endl << endl;

	if( argc != 4 )
	{
		printUsage(argv[0]);
		return -1;
	}

	ifstream ifs(argv[1], ios_base::in | ios_base::binary | ios_base::ate);

	if( !ifs )
	{
		cerr << "Error opening file " << argv[1] << endl;
		return -1;
	}

	int filesize = ifs.tellg();
	ifs.seekg (0, ifs.beg);

	ofstream ofs(argv[2], ios_base::out | ios_base::binary);
	if( !ofs )
	{
		cerr << "Error opening device " << argv[2] << endl;
		return -1;
	}

	int delay = atoi( argv[3] );

	char currentChar;
	int currentPos = 0;
	while (ifs.read(&currentChar, 1) )
	{
		ofs << currentChar;
		//cout << "\r";
		printCharWithBinary(currentChar);
		cout << "; written " << currentPos << "/" << filesize << endl;
		
		currentPos++;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}

	cout << endl;

	if (ifs.eof())
	{
		cout << "EOF reached." << endl;
	}
	else
	{
		cerr << "Error reading file." << endl;
	}

	ifs.close();
	ofs.close();

	return 0;
}
