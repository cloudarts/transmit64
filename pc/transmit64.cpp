#include <iostream>
#include <fstream>

using namespace std;

void printUsage(char* progName)
{
	cout << endl;
	cout << "Usage: " << endl;
	cout <<  progName << " <fileToTransmit> </dev/yourSerialDevice>";
	cout << endl;
	cout << endl;
}

int main(int argc, char* argv[])
{
	cout << endl << "Transmit64 Copyright 2016 W.A.Jurczyk" << endl << endl;

	if( argc != 3 )
	{
		printUsage(argv[0]);
		return -1;
	}

	ifstream ifs(argv[1], ios_base::in | ios_base::binary);

	if( !ifs )
	{
		cerr << "Error reading file " << argv[1] << endl;
		return -1;
	}

	char currentChar;
	while (ifs.read(&currentChar, 1) )
	{
		cout << currentChar;	
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
	return 0;
}
