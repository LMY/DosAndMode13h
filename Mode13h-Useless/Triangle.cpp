#include <conio.h>
#include <dos.h>
#include "LmyG.h"

void DrawTri(unsigned char X);
int Tri[3][2] = { {160,40}, {40,120} , {200,100} };

void main()
{
	unsigned int Flag[3][2] = { {0,0}, {0,1} , {1,1} };
	unsigned int x;
	SetVideoMode(19);
	SetColor(2,0,60,0);
	DrawTri(1);
	getch();
	DrawTri(0);
	while(inportb(0x60)!=1)
	{
		DrawTri(1);
		WtSync();
		DrawTri(0);
		for (x=0;x<3;x++)
		{
		if (Tri[x][0]==318) Flag[x][0]=1;
		if (Tri[x][1]==198) Flag[x][1]=1;
		if (Tri[x][0]==1) Flag[x][0]=0;
		if (Tri[x][1]==1) Flag[x][1]=0;
		if (Flag[x][0]) Tri[x][0]--;
		else Tri[x][0]++;
		if (Flag[x][1]) Tri[x][1]--;
		else Tri[x][1]++;
		}
	}
	getch();
	SetVideoMode(3);
}

void DrawTri(unsigned char X)
{
	if (X==1) X++;
	Line(Tri[0][0],Tri[0][1],Tri[1][0],Tri[1][1],X);
	Line(Tri[0][0],Tri[0][1],Tri[2][0],Tri[2][1],X);
	Line(Tri[2][0],Tri[2][1],Tri[1][0],Tri[1][1],X);
}