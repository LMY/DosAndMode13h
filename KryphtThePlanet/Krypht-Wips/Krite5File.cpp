//Use KeyFile (Up to 4kbits), InFile, OutFile
//Also Krite the last segment of the file.
//Using The KriteN Procedure!
//Using various file dims
#include <iostream.h>
#include <io.h>
#include <fcntl.h>

int main()
{
const unsigned short int Dim = 4096;
char *Bin = new char[Dim];
char *Kry = new char[Dim];
char *Word = new char[Dim/8];
unsigned short int *Key = new unsigned short int [Dim];
unsigned short int *Key2 = new unsigned short int [Dim];
unsigned short int *Key3 = new unsigned short int [Dim];
char Ar[2];
int handle, handle1, readed;
unsigned short int KeyLenght, InLenght;

if ((handle = open("Key2.kry", O_RDONLY | O_BINARY )) == -1)
	{
	cout << "Error Reading Key.\n";
	return 0;
	}
	KeyLenght = filelength(handle);
	InLenght = KeyLenght / 2;
if ((KeyLenght != 64) || (KeyLenght != 256) || (KeyLenght != 1024) || (KeyLenght != 2048) || (KeyLenght != 4096))
	{
	cout << "ERROR:Unsupported Key.\n";
	close(handle);
	return 1;
	}

	if (KeyLenght<=256)
	{
	read(handle,Key,KeyLenght);
	goto KeyReaded;
	}

	else {
		for (int i=0;i<InLenght;i++)
		{
		read(handle,Ar,2);
		Key[i*2]= (Ar[0]*256+1) + (Ar[1]+1);
		}
	}

KeyReaded:
close(handle);

for (int i=0; i<InLenght; i++)
	Key2[i] = Key[i];

for (int i=0; i<InLenght; i++)
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
	readed = InLenght/8;
	unsigned long int Lenght = filelength(handle);

	while (readed == InLenght/8)
	{
	readed = read(handle,Word,32);
	
	if (readed != InLenght/8)
		{
		int r=0;
		readed = Lenght%(InLenght/8);
		
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
	for (int i=0;i<(readed*8);i++) Bin[(InLenght/8-1)-i] = Kry[i];
	for (int i=0;i<InLenght/8;i++) Word[(InLenght/8-1)-i] =( Bin[8*i] + (2 * Bin[8*i+1]) + (4 * Bin[8*i+2]) + (8 * Bin[8*i+3]) + (16 * Bin[8*i+4]) + (32 * Bin[8*i+5]) + (64 * Bin[8*i+6]) + (128 * Bin[8*i+7]));
	
	write(handle1,Word,readed);
	for (int i=0;i<InLenght/8;i++)
		Word[i] = (char) 0;
	
	for (int i=0 ; i<InLenght ; i++ )
		Key2[i] = Key[Key3[i]-1];
	for (int i=0 ; i<InLenght ; i++)
		Key3[i] = Key[i];
	for (int i=0 ; i<InLenght ; i++)
		Key[i] = Key2[i];
	
	}
close(handle);
close(handle1);
return 0;
}