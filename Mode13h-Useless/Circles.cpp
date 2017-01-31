//Circles Drawer
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <time.h>
#include <stdlib.h>

void PutPixel(int x, int y, int Xc, int Yc, char Color);
void SetVideoMode(int Mode);
int GetX(int D, double Th);
int GetY(int D, double Th);
//void WtSync();

void main()
{
	randomize();
	int D = 10;
	double Th;
	SetVideoMode(19);
	Th = 0;
	int Xc,Yc;
	char Ch;
	/*for (D=100; D>0; D--)
	{
		for (Th = 0; Th<360; Th++)
		{
		PutPixel(GetX(D,Th),GetY(D,Th),4);
		}
	delay(100);
	}*/
	while(inportb(0x60) != 1)
	{	
		Xc = random(320);
		Yc = random(200);
		Ch = random(255)+1;
		for (Th = 0; Th<360; Th++)
		{
		PutPixel(GetX(D,Th),GetY(D,Th),Xc,Yc,Ch);
		}
	}

//	getch();
	SetVideoMode(3);
}

void PutPixel(int x, int y, int Xc, int Yc, char Color)
{
//x = 160 + (2*(x/z));
//y = 100 + (2*(y/z));
int Ofs = 320*(y+Yc)+(x+Xc);

	asm
	{
	push 0a000h
	pop es
	mov al,Color
	mov di,Ofs
	mov [es:di],al
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
/*void WtSync()
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
}*/
int GetX(int D, double Th)
{
 Th = (Th * 3.1416)/180;
 return (D*cos(Th));
}
int GetY(int D, double Th)
{
 Th = (Th * 3.1416)/180;
 return (D*sin(Th));
}