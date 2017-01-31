//Use KeyFile, InFile, OutFile
//Also Krite the last segment of the file.
//Using The KriteN Procedure!
//256bytes Files
#include <iostream.h>
#include <io.h>
#include <fcntl.h>

int main()
{
char Bin[256], Kry[256], Key[256], Key2[256], Key3[256], Word[32];
int handle, handle1, readed;

if ((handle = open("Key256.kry", O_RDONLY | O_BINARY )) == -1)
	{
	cout << "Error Reading Key.\n";
	return 0;
	}
readed =read(handle,Key,256);
close(handle);

for (int i=0;i<256;i++)
	Key[i]++;					//Da 0 a 255 ---> da 1 a 256

for (int i=0; i<256; i++)
	Key2[i] = Key[i];

for (int i=0; i<256; i++)
	Key3[i] = Key[i];

if ((handle = open("InPut.txt", O_RDONLY | O_BINARY )) == -1)
	{
	cout << "Error Reading InPut File.\n";
	return 0;
	}
if ((handle1 = open("OutPut.txt", O_CREAT | O_BINARY | O_EXCL)) == -1)
	{
	cout << "Error Creating OutPut File.\n";
	return 0;
	}
	readed = 32;
	unsigned long int Lenght = filelength(handle);

	while (readed == 32)
	{
	readed = read(handle,Word,32);
	
	if (readed != 32)
		{
		int r=0;
		readed = Lenght%32;
		
		for (int i=0;i<256;i++)
			if (Key[i] > (readed*8)) Key[i] = 0;
		for (int i=0;i<256;i++ )
			{
			if (Key[i] == 0)
				{
				r++;
				Key[i] = Key[i+r];
				Key[i+r] = 0;
				i--;
				}
			}
		}


	for (int i=0;i<readed;i++)
	{
		for (int o=0;o<8;o++)
		{
		Bin[i*8+7-o] = Word[i] % 2;
		Word[i] /= 2;
		}
	}
	
	for (int i=0;i<(readed*8);i++) Kry[i] = Bin[Key[i]-1];
	for (int i=0;i<(readed*8);i++) Bin[255-i] = Kry[i];
	for (int i=0;i<32;i++)  Word[31-i] =( Bin[8*i] + (2 * Bin[8*i+1]) + (4 * Bin[8*i+2]) + (8 * Bin[8*i+3]) + (16 * Bin[8*i+4]) + (32 * Bin[8*i+5]) + (64 * Bin[8*i+6]) + (128 * Bin[8*i+7]));
	
	write(handle1,Word,readed);
	for (int i=0;i<32;i++)
		Word[i] = (char) 0;
	
	// KeyRotating
	for (int i=0 ; i<256 ; i++ )
		Key2[i] = Key[Key3[i]-1];
	for (int i=0 ; i<256 ; i++)
		Key3[i] = Key[i];
	for (int i=0 ; i<256 ; i++)
		Key[i] = Key2[i];
	
	}
close(handle);
close(handle1);
return 0;
}