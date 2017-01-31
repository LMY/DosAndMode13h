//KeyCreator: It can made key of: {1k,2k,4k,8k)
#include <iostream.h>
#include <fcntl.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	const unsigned short int Dim = 16384;
	unsigned short int *KeyN = new unsigned short int[Dim];
	char Key[2];
	unsigned short int Rdn;
	unsigned short int ChD;
	int handle;
	char ch;
	randomize();

	Eh:
	cout << "Select KeySize:\n1\t1024 bytes\n2\t2048 bytes\n3\t4096 bytes\n4\t8192 bytes\n5\t16384 bytes\n> ";
	cin >> ch;
	switch (ch)
	{
	case '1': ChD = 1024;
				break;
	case '2': ChD = 2048;
				break;
	case '3': ChD = 4096;
				break;
	case '4': ChD = 8192;
				break;
	case '5': ChD = 16384;
				break;
	default : cout << "ERROR:Invalid KeySize.\n";
				return 1;
	}

	cout << "Creating Key, Please Wait...\n";
	for (long int i=ChD;i>0;i--)
	{
		Rdn = random(i-1)+1;	//Rdn = Num(1..256) [256valori]
		for (long int t=ChD-1;t>=0;t--)	//esegui 255 volte
		{
			if (KeyN[t] == 0) Rdn--;	//Se è uno spazio vuoto Rdn--
			if (Rdn == 0)			//Se Rdn è finalmente arrivato a 0
				{					//ma cavolo arriverà al massimo a 1!!!
				KeyN[t]=i+1;
				break;
				}
		}
	}
	Rdn = random(ChD);
	KeyN[0]=KeyN[Rdn];
	KeyN[Rdn]=0;						// Così 00h va in una posizione casuale!!!

	if ((handle = open("KeyA.kry", O_CREAT | O_BINARY | O_EXCL)) == -1)
	{
		cout << "Error Creating Key.\n";
		return 1;
	}
	for (long int i=0; i<ChD; i++)
	{
	Key[0] = (char) (KeyN[i]/256);
	Key[1] = (char) (KeyN[i]%256);
	write(handle,Key,2);
	}
	close(handle);
	return 0;
}