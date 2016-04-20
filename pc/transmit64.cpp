#include <iostream>

using namespace std;

bool printUsage(char* progName)
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

	return 0;
}
