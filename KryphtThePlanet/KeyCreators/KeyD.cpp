//Crea Una Chiave Universale Definitiva
#include <iostream.h>	//for debugging
#include <stdlib.h>
//#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <time.h>

int main()
{

randomize();
const unsigned long int Dim = 16;
unsigned short int KeyN[Dim];
char Key[Dim*2];
unsigned long int Tr, Id, Rn;

for (int i=0; i<Dim;i++)
	KeyN[i] = 0;

for (int i=Dim; i>0; i--)
{
	Id = 0;
	Tr = 0;
	Rn = random(i)+1;
	while (Tr != Rn)
	{
		if (KeyN[Tr] == 0) Tr++;
		Id++;
	}
	cout << i << " " << Tr << " " << Id << " " < Rn << endl;
	KeyN[Id] = i;
}

for (int i=0; i<Dim; i++)
{
Key[i*2] = (char) KeyN[i] / 256;
Key[i*2+1] = (char) KeyN[i] % 256;
}

   int handle;
   if ((handle = open("KeyK.kry", O_CREAT | O_BINARY | O_EXCL)) == -1)	// -1 = errore
   {
      //perror("Error:");
	  cout << "Error Creating Key.\n";
      return 1;
   }
   write(handle, Key, Dim*2);
   close(handle);
   return 0;
}