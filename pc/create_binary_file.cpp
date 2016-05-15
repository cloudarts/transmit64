#include <stdio.h>

int main()
{
	FILE* file;
	file = fopen("payload.bin", "wb");

	char buffer[256];

	for( int i = 0; i < 256; i++)
	{
		buffer[i] = i;
	}

	fwrite(buffer, sizeof(char), sizeof(buffer), file);

	fclose(file);
	return 0;
}
