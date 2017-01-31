//Draw a 2dibensional spiral on the screen.
#include <conio.h>
#include <math.h>
#include <dos.h>
#include <stdlib.h>

void PutPixel(int x, int y, char Color);
void SetVideoMode(int Mode);
double GetX(int D, double Th);
double GetY(int D, double Th);
int Round(double x);
void WtSync();

void main()
{
	double D,Th;
	int x,y;
	SetVideoMode(19);

	while(inportb(0x60) != 1)
	{
	D = Round(Th/16);
	x=Round(GetX(D,Th));
	y=Round(GetY(D,Th));
	for (int i=16;i>0;i--)
	{
	if ((x>=160)||(x<=-160)||(y+i<=-100)||(y+i>=100)) goto NoDraw;
	PutPixel(x,y+i,128+i);
	NoDraw:
	}
	WtSync();
	Th+=0.5;
	}
	SetVideoMode(3);
}

void PutPixel(int x, int y, char Color)
{
int Ofs = 320*(y+100)+(x+160);

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
double GetX(int D, double Th)
{
 Th = (Th * 3.1416)/180;
 return (D*cos(Th));
}
double GetY(int D, double Th)
{
 Th = (Th * 3.1416)/180;
 return (D*sin(Th));
}
int Round(double x)
{
	if ((x - (int) x)<0.5) return ((int) x);
	else return ((int) x +1);
}