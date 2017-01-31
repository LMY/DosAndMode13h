#include <stdlib.h>
#include <time.h>
#include <conio.h>

void PutPixel(int x, int y, char Color);
void SetVideoMode(int Mode);
void WtSync();

void main()
{
	const unsigned short int MaxStars = 300;
	signed short int X,Y;
	signed short int  Stars[MaxStars*3];
	randomize();

	SetVideoMode(19);
	for (int i=0; i<256;i++)
	{
	outp(968,i);
	for (int v=0; v<3; v++)
		outp(969,i/4);
	}

	for (int i=0; i<MaxStars;i++)
	{
	Stars[i*3]= random(320) - 160;
	Stars[i*3+1]= random(200) - 100;
	Stars[i*3+2]= random(250);
	}

	while (!kbhit())
	{
		for (int i=0;i<MaxStars;i++)
		{
		X = (( Stars[i*3] * 256 ) / (256-Stars[i*3+2]) + 160);
		Y = (( Stars[i*3+1] * 256 ) / (256-Stars[i*3+2]) + 100);
		if ( (Stars[i*3+2] == 255) || (X<=0) || (X>=319) || (Y<=0) || (Y>=199) )
			{
			Stars[i*3+2] = 1;
			Stars[i*3] = random(320) -160;
			Stars[i*3+1] = random(200) -100;
			}
		else Stars[i*3+2]++;
		}
		
		for (int i=0; i<MaxStars; i++)
		{
			X = (( Stars[i*3] * 256 ) / (256-Stars[i*3+2]) + 160);
			Y = (( Stars[i*3+1] * 256 ) / (256-Stars[i*3+2]) + 100);
			PutPixel(X,Y,Stars[i*3+2]);
		}
		
		WtSync();

		for (int i=0;i<MaxStars;i++)
		{
		X = (( Stars[i*3] * 256 ) / (256-Stars[i*3+2]) + 160);
		Y = (( Stars[i*3+1] * 256 ) / (256-Stars[i*3+2]) + 100);
		PutPixel(X,Y,0);
		}
		

	}
	getch();
int h = 0;


while (h != 2560)
{
		for (int i=0;i<MaxStars;i++)
		{
		X = (( Stars[i*3] * 256 ) / (256-Stars[i*3+2]) + 160);
		Y = (( Stars[i*3+1] * 256 ) / (256-Stars[i*3+2]) + 100);
		if ( (Stars[i*3+2] == 255) || (X<=0) || (X>=319) || (Y<=0) || (Y>=199) )
			{
			Stars[i*3+2] = 1;
			Stars[i*3] = random(320) -160;
			Stars[i*3+1] = random(200) -100;
			}
		else Stars[i*3+2]++;
		}
		
		for (int i=0; i<MaxStars; i++)
		{
			X = (( Stars[i*3] * 256 ) / (256-Stars[i*3+2]) + 160);
			Y = (( Stars[i*3+1] * 256 ) / (256-Stars[i*3+2]) + 100);
			PutPixel(X,Y,Stars[i*3+2]);
		}
		
		h++;
}

unsigned char R,G,B;
for (int k=0;k<32;k++)
{
	for (int i=0;i<256;i++)
	{
		outp (0x03C7,i);
		R = inp (0x03C9);
		G = inp (0x03C9);
		B = inp (0x03C9);
		
		if (R!=0) R--;
		if (G!=0) G--;
		if (B!=0) B--;

		outp (0x03C8,i);
		outp (0x03C9,R);
		outp (0x03C9,G);
		outp (0x03C9,B);

		if (R!=0) R--;
		if (G!=0) G--;
		if (B!=0) B--;

		outp (0x03C8,i);
		outp (0x03C9,R);
		outp (0x03C9,G);
		outp (0x03C9,B);
	
	}
	WtSync();
}

SetVideoMode(3);
}

void PutPixel(int x, int y, char Color)
{
	asm
	{
	push 0a000h
	pop es
	mov dx,y
	shl dx,2
	add dx,y
	shl dx,6
	add dx,x
	mov di,dx
	mov al,Color
	stosb
	}
}
void SetVideoMode(int Mode)
{
	asm
	{
	mov ax,Mode
	int 10h
	}
}
void WtSync()
{
	asm
	{
	mov dx,3dah
	@1:
	in al,dx
	test al,8
	jne @1
	@2:
	in al,dx
	test al,8
	je @2
	}
}