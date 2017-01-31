#include <conio.h>
#include "Meg.h"
#include "MeF32.h"

int main()
{

/*	unsigned char **Array;
	Array = new unsigned char *[30];
	for (unsigned char x=0;x<10;x++)
		Array[x] = new unsigned char[10];
	delete Array;
*/
	SetVideoMode(19);
	SetPcxPal("middle.pcx");
	DrawPcx(0,0,"middle.pcx");
	getch();

	SetVideoMode(3);
	return 0;
}