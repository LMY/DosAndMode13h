#include <iostream.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>

void del(unsigned char FN[]);

int main(int argc, char *argv[])
{
	const unsigned long int Lim = 58000;
	if ((argc!=2)&&(argc!=3)) { cout << "Usage: Wipe [FileName] <HowManyTimes>"; return 1; }
	int handle;

	if ((handle = open(argv[1], O_RDWR | O_BINARY )) == -1)
	{
	cout << "File " << argv[1] << " doesn't exist"; return 1;
	}
	unsigned long int Size = filelength(handle);
	unsigned long int Times = Size/Lim;
	unsigned long int Last = Size%Lim;
	unsigned char *Ar = new unsigned char[Lim];
	for (unsigned long int x=0;x<Lim;x++) Ar[x]=0;
	unsigned long int Passes=1;
	if (argc==3) Passes=atoi(argv[2]);

	for (Passes;Passes!=0;Passes--)
	{
	if (Times) for (unsigned long int x=0;x<Times;x++) write(handle,Ar,Lim);
	write(handle,Ar,Last);
	}

	close(handle);
	
	del(argv[1]);

	delete Ar;
	return 0;
}

void del(unsigned char FN[])
{
	asm {
	mov dx,&FN
	mov ah,41h
	int 21h
	}
}