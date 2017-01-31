#include <conio.h>
#include <dos.h>
#include <iostream.h>

int main()
{
	unsigned char A,B;
	while (A!=1)
	{
	A=inportb(96);
	if (A!=B) { cout << (int) A << endl; B=A; }
	}
	return 0;
}