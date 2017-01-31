#include <conio.h>
#include <stdlib.h>
#include <iostream.h>
#include <time.h>
#include "LmyG.h"

typedef struct
{
unsigned int x1,x2,x3,y1,y2,y3;
// int z1,z2,z3;
} Triangle;

void DrawTriangle(Triangle T, unsigned char Color);
void FillTriangle(Triangle T, unsigned char Color);

void main()
{
	SetVideoMode(19);
	Triangle Alpha;
	unsigned char Colore;
	double HowMany=0;
	clock_t T1,T2;
	T1=clock();
	while (!kbhit())
	{
	Colore=random(256);
	Alpha.x1=random(320); Alpha.y1=random(200);
	Alpha.x2=random(320); Alpha.y2=random(200);
	Alpha.x3=random(320); Alpha.y3=random(200);
	DrawTriangle(Alpha,Colore);
	HowMany++;
//	WtSync();
	}

	T2=clock()-T1;
	getch();
	SetVideoMode(3);
	cout << "Triangles: " << HowMany << endl;
	cout << "Speed: " << HowMany/T2*CLK_TCK << " tr/s";
}

void DrawTriangle(Triangle T, unsigned char Color)
{
	Line(T.x1,T.y1,T.x2,T.y2,Color);
	Line(T.x1,T.y1,T.x3,T.y3,Color);
	Line(T.x2,T.y2,T.x3,T.y3,Color);
	FillTriangle(T,Color);
}

void FillTriangle(Triangle T, unsigned char Color)
{
float M,Q;
int y1=T.y1, y2=T.y2, y3=T.y3, x1=T.x1, x2=T.x2, x3=T.x3;
if (y1>y2) { Exchg(y2,y1); Exchg(x2,x1); }
if (y2>y3) { Exchg(y2,y3); Exchg(x2,x3); }
if (y1>y2) { Exchg(y2,y1); Exchg(x2,x1); }

if ((y1==y2)&&(y2==y3)) OLine(x1,x3,y1,Color);
else if ((x1==x2)&&(x2==x3)) VLine(y1,y3,x1,Color);
else {
	unsigned short int Ar[200][2];
	unsigned short int x;
	for (x=0;x<200;x++) { Ar[x][0]=0; Ar[x][1]=0; }
	
	if (x1==x2) for (x=y1;x<=y2;x++) Ar[x][0]=x1;
	else {
		M = (float) (y1-y2)/(x1-x2);
		Q = (float) y1 - M*x1;
		for (x=y1;x<y2;x++) Ar[x][0]=Round((float) (x-Q)/M);
		}
	if (x2==x3) for (x=y2;x<=y3;x++) Ar[x][0]=x2;
	else if (y2==y3) OLine(x2,x3,y2,Color);
	else {
		M = (float) (y2-y3)/(x2-x3);
		Q = (float) y2 - M*x2;
		for (x=y2;x<y3;x++) Ar[x][0]=Round((float) (x-Q)/M);
		}
	if (x1==x3) for (x=y1;x<=y3;x++) Ar[x][1]=x1;
	else {
		M = (float) (y1-y3)/(x1-x3);
		Q = (float) y3 - M*x3;
		for (x=y1;x<=y3;x++) Ar[x][1]=Round((float) (x-Q)/M);
		}
	for (x=0;x<200;x++) if ((Ar[x][0])&&(Ar[x][1])) OLine(Ar[x][0],Ar[x][1],x,Color);
	}
}