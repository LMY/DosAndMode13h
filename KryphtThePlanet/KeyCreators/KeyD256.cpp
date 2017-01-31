//KeyCreator 4 256bits Keys
#include <iostream.h>
#include <fcntl.h>
#include <io.h>
#include <time.h>
#include <stdlib.h>

int main()
{
	randomize();
	int handle, Rdn;
	char Key[256];

	for (int i=0;i<256;i++)
		Key[i] = 0;

	for (int i=256;i>0;i--)
	{
		Rdn = random(i-1)+1;	//Rdn = Num(1..256) [256valori]
		for (int t=255;t>=0;t--)	//esegui 255 volte
		{
			if (Key[t] == 0) Rdn--;	//Se è uno spazio vuoto Rdn--
			if (Rdn == 0)			//Se Rdn è finalmente arrivato a 0
				{					//ma cavolo arriverà al massimo a 1!!!
				Key[t]=i+1;
				break;
				}
		}
	}
	Rdn = random(256);
	Key[0]=Key[Rdn];
	Key[Rdn]=0;						// Così 00h va in una posizione casuale!!!

	if ((handle = open("Key256.kry", O_CREAT | O_BINARY | O_EXCL)) == -1)
	{
		cout << "Error Creating Key.\n";
		return 1;
	}
	write(handle, Key, 256);
	close(handle);
	return 0;
}