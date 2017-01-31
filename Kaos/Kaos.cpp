#include <conio.h>
#include <iostream.h>
#include <time.h>
#include "LmyG.h"

void DrawAxis(unsigned char Color);
void DrawBis(unsigned char Color);
void DrawPar(unsigned char Color);
signed int CorX(float X);
signed int CorY(float Y);
float F(float x);
void Initialize(float &B, float InitValue);
unsigned char delayk(unsigned long int Millisecs);
void exit(unsigned char Code);

float A=2.5;
float InitValue=0.3;
float Factor=199;
short signed int TrUp=0,TrRg=0;

void main()
{
	cout << "Kaos v2.4.12 Coded By LMY from Middle Earth Swz.\n\nKEY\tFUNCTION" << endl;
	cout << "Up\tIncrement A Value" << endl << "Down\tDecrement A Value" << endl << "A\tInsert new A Vaulue" << endl;
	cout << "Right\tIncrement Init Value" << endl << "Left\tDecrement Init Value" << endl << "N\tInsert new Init Value" << endl;
	cout << "+/-\tZoom In/Out" << endl << "F\tInsert new Zoom Factor" << endl;
	cout << "I/M\tTranslate Up/Down" << endl;
	cout << "J/K\tTranslate Left/Right" << endl;
	cout << "O\tCenter" << endl;
	cout << "P\tPause" << endl << "ESC\tExit Program" << endl;
	cout << "\nA=" << A << "  InitValue=" << InitValue << endl;
	cout << "\nPress Any Key to Continue..."; getch();
	float B,D=0;
	unsigned long int Passi=1;
	unsigned char C,Quit=0;
	SetVideoMode(19);
	Initialize(B,InitValue);
	delayk(1000);

	while (1)
	{
	C=delayk(600);
		switch (C)
		{

		case 'p':	getch(); break;
		case '+':	if (Factor<20000) {
						Factor *=2;
						Initialize(B,InitValue);
						Passi=1;
						Quit=2;
					}
					break;
		case '-':	Factor /=2;
					Initialize(B,InitValue);
					Passi=1;
					Quit=2;
					break;
		case 'i':	TrUp-=5;
					Initialize(B,InitValue);
					Passi=1;
					Quit=2;
					break;
		case 'm':	TrUp+=5;
					Initialize(B,InitValue);
					Passi=1;
					Quit=2;
					break;
		case 'k':	TrRg+=5;
					Initialize(B,InitValue);
					Passi=1;
					Quit=2;
					break;
		case 'j':	TrRg-=5;
					Initialize(B,InitValue);
					Passi=1;
					Quit=2;
					break;
		case 'o':	TrUp=0;
					TrRg=0;
					Initialize(B,InitValue);
					Passi=1;
					Quit=2;
					break;
		case 75 :	if (InitValue>0.1)
					{
					InitValue-=0.025;
					Initialize(B,InitValue);
					Passi=1;
					}
					Quit=2;
					break;
		case 77 :	if (InitValue<0.9)
					{
					InitValue+=0.025;
					Initialize(B,InitValue);
					Passi=1;
					}
					Quit=2;
					break;
		case 72 :	if (A<3.9)
					{
					A+=0.05;
					Initialize(B,InitValue);
					Passi=1;
					}
					Quit=2;
					break;
		case 80 :	if (A>0.1)
					{
					A-=0.05;
					Initialize(B,InitValue);
					Passi=1;
					}
					Quit=2;
					break;
		case 'a':	cout << "New A value:";
					cin >> D;
					gotoxy(1,1);
					if ((D>=0)&&(D<4)) A=D;
					B=A;
					Initialize(B,InitValue);
					Passi=1;
					break;
		case 'n':	cout << "New Init Value:";
					cin >> D;
					gotoxy(1,1);
					if ((D>0.1)&&(D<0.9)) InitValue = D;
					Initialize(B,InitValue);
					Passi=1;
					break;
		case 'f':	cout << "New Factor Value:";
					cin >> D;
					if (D) Factor=D;
					gotoxy(1,1);
					Initialize(B,InitValue);
					Passi=1;
					break;
		case 27 :	Quit=1; break;
		case  0 :
		default :	break;
		}
	if (Quit==1) break;
	else if (Quit==2) Quit=0;
	else {
		Passi++;
		VLine(CorY(B),CorY(F(B)),CorX(B),3);
		OLine(CorX(B),CorX(F(B)),CorY(F(B)),3);
		B=F(B);
		}
	}
	SetVideoMode(3);
	cout << "After " << Passi << " Passes  With  A=" << A << "  Xn=" << B;
}

void DrawAxis(unsigned char Color)
{
	OLine(0,319,199+TrUp,Color);
	VLine(0,199,0+TrRg,Color);
}
float F(float x)
{
	return (A*x*(1-x));
}
void DrawBis(unsigned char Color)
{
	Line(CorX(0),CorY(0),CorX(1),CorY(1),Color);
}
void DrawPar(unsigned char Color)
{
	for (unsigned int x=1;x<=Factor;x++) Line(x-1+TrRg,CorY(F( (float) (x-1)/Factor )),x+TrRg,CorY(F( (float) x/Factor )),Color);
}
signed int CorX(float X)
{
	return Round(X*Factor)+TrRg;
}
signed int CorY(float Y)
{
	return Round(199-Y*Factor)+TrUp;
}
void Initialize(float &B, float InitValue)
{
	B=InitValue;
	WtSync();
	for (unsigned char y=0;y<200;y++) OLine(0,320,y,0);
	DrawAxis(5);
	DrawBis(2);
	DrawPar(4);
	VLine(CorY(0),CorY(F(B)),CorX(B),3);
	OLine(CorX(B),CorX(F(B)),CorY(F(B)),3);
	B=F(B);
}
unsigned char delayk(unsigned long int Millisecs)
{
	clock_t T2,T1=clock();
	while (1)
	{
	T2=clock();
	if (kbhit()) return (getch());
	if (T2>=T1+Millisecs*CLK_TCK/1000) return 0;
	}
}
void exit(unsigned char Code)
{
	asm {
	mov ah,4Ch
	mov al,[Code]
	int 21h
	}
}