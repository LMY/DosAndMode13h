//Use KeyFile, InFile, OutFile
//Also Krite the last segment of the file.
#include <iostream.h>
#include <io.h>
#include <fcntl.h>

int main()
{
char Bin[64], Kry[64], Key[64], Word[8];
int handle, handle1, readed;

if ((handle = open("Key2.kry", O_RDONLY | O_BINARY )) == -1)
	{
	cout << "Error Reading Key.\n";
	return 0;
	}
readed =read(handle,Key,64);
close(handle);

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
	readed = 8;
	unsigned long int Lenght = filelength(handle);

	while (readed == 8)
	{
	readed = read(handle,Word,8);
	
	if (readed != 8)
		{
		int r=0;
		readed = Lenght%8;
		
		for (int i=0;i<64;i++)
			if (Key[i] > (readed*8)) Key[i] = 0;
		for (int i=0;i<64;i++ )
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
	for (int i=0;i<(readed*8);i++) Bin[63-i] = Kry[i];
	for (int i=0;i<8;i++)  Word[7-i] =( Bin[8*i] + (2 * Bin[8*i+1]) + (4 * Bin[8*i+2]) + (8 * Bin[8*i+3]) + (16 * Bin[8*i+4]) + (32 * Bin[8*i+5]) + (64 * Bin[8*i+6]) + (128 * Bin[8*i+7]));
	
	write(handle1,Word,readed);
	for (int i=0;i<8;i++)
		Word[i] = (char) 0;
	}
close(handle);
close(handle1);
return 0;
}