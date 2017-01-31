#include "LmyG.h"		//for SetVideoMode, SetColor, PutPixel
#include "MEfiles.h"
#include <conio.h>
#include <dos.h>
#include <iostream.h>
#include <time.h>
#include <stdlib.h>

void Arrow(unsigned char What);
void Led(unsigned char What);
void Par(unsigned char What);
void ReleCT();
void Engine(unsigned char What);
void Init();
void Outro();
void Lite();
void send(unsigned int Port, unsigned char Ch);
unsigned int atoi(char *String, unsigned char &M);
unsigned int Power(unsigned char X, int Y);
void OutP(unsigned int Port, unsigned char C);
void Stars();
void Process(unsigned char C,unsigned char &Quit);
void ScrollDown(unsigned char What);
void ScrollUp(unsigned char What);
void Rele(unsigned char What);
void reset();
void DoIt(unsigned char What);


unsigned char EngineStatus=0;
unsigned char Velocity=0;
unsigned char Flag=0;
unsigned char MenuPointer=2;
unsigned char Menu=1;
unsigned char Res=0;
unsigned char Rele1=0;
unsigned char Rele2=0;
unsigned char ReleC=0;
unsigned int adress;

// Constants	->> non puoi chiamarle costanti o non va niente :)
unsigned char Button[4][2][12] = {
{"EnExit.pcx" , "DisExit.pcx" },
{"EnTest.pcx", "DisTest.pcx" },
{"EnMovs.pcx", "DisMovs.pcx"},
{"EnScrS.pcx", "DisScrS.pcx"}
};
unsigned char Pannel[4][12] = { "Exit.pcx" , "Test.pcx" , "Movs.pcx" , "ScrSrv.pcx" };
unsigned char ButtonY[4] = { 177, 154, 130, 106 };
unsigned char Vel[3][12] = { "Vel0.pcx" , "Vel1.pcx" , "Vel2.pcx" };
unsigned char SwCord[6][2] = { {124,101} , {124,118} , {124,135} , {124,151} , {124,168} , {124,185} };


int main(int argc, char *argv[])
{
	unsigned int far *point;
	unsigned int Lpt;
	unsigned char A;
	point = (unsigned int far*) 0x00000408;
	for (Lpt=0;Lpt<3;Lpt++)
	{
	adress = *point;
	if (adress) { cout << "Adress assigned to LPT" << Lpt+1 << " is " << hex << adress << dec << "h." << endl; break; }
	*point++;
	}
	if (!adress) { cout << "ERROR: No LPT Ports."; return 1; }
	if (argc)
	{
	for (int x=1;x<=argc;x++)
		if (argv[x][1]=='p')
			{
			adress = atoi(argv[x+1],A);
			if (!adress) { cout << "ERROR: Invalid port number."; return 1; }
			cout << "Using port " << hex << adress << dec << A << "." << endl;
			}
	}
	Init();
//	Lite();
	unsigned char Quit=0,C=0;
	clock_t Timer1,Timer2,Timer3,Timer4;
	Res=255; send(adress,Res);
	unsigned char Banner[][12] = { "az.pcx" , "az2.pcx" , "poke.pcx" , "micro.pcx" , "micro2.pcx" , "web.pcx" , "script.pcx" , "Works.pcx" };
	unsigned char BPointer=0;
	Timer1=clock(); Timer3=Timer1; Timer2=0; Timer4=0;
	while(Quit!=1)
	{
		Timer2=clock();
		if (Timer2>=Timer1+5*CLK_TCK)
			{
			Timer1=Timer2;
			DrawPcx(0,0,Banner[BPointer]);
			if (BPointer==7) BPointer=0;				// QUANTI_BANNER-1 CAMBIAAAAALO!
			else BPointer++;
			}
		Timer4=clock();
		if ((Timer4>=Timer3+60*CLK_TCK)||(Quit==2))
			{
			Quit=0;
			unsigned char Pal[768];
			GetPalette(Pal);
			FadeOut();
			ClearScreen();
			Stars();
			DrawPcx(0,0,"Intrfc.pcx");
			DrawPcx(0,0,Banner[BPointer]);
			Engine(EngineStatus);
			DrawPcx(40,92,Pannel[MenuPointer]);
			if (ReleC==0) DrawPcx(253,150,"Off.pcx");
			else DrawPcx(253,150,"On.pcx");

			if ((Rele1==0)||(Rele1==1)) DrawPcx(253,122,"Off.pcx");
			if ((Rele1==2)||(Rele1==3)) DrawPcx(253,122,"On.pcx");
			if ((Rele2==0)||(Rele2==1)) DrawPcx(253,136,"Off.pcx");
			if ((Rele2==2)||(Rele2==3)) DrawPcx(253,136,"On.pcx");

			DrawPcx(0,ButtonY[MenuPointer],Button[MenuPointer][1]);

			if (MenuPointer==1)
			{
			for(unsigned char Hg=0;Hg<6;Hg++)
				if (Hg!=Flag)
					DrawPcx(SwCord[Hg][0],SwCord[Hg][1],"red.pcx");
			DrawPcx(SwCord[Flag][0],SwCord[Flag][1],"green.pcx");
			}

			if (MenuPointer==0)
			{
			if (Flag==0) { DrawPcx(50,170,"No!.pcx"); DrawPcx(100,170,"Yes.pcx"); }
			else { DrawPcx(50,170,"No.pcx"); DrawPcx(100,170,"Yes!.pcx"); }
			}

			FadeToPal(Pal);
			Timer3=clock();
			}
		
		if (kbhit())
		{
			Timer3 = clock();
			Process(getch(),Quit);
		}
	}	
	FadeOut();
	Outro();
	SetVideoMode(3);
	cout << "Shuting down Interface... Ok" << endl;
	cout << "Closing link with " << hex << adress << dec << "h...";
	delay(700);
	cout << " Ok.";
	return 0;
}

void Arrow(unsigned char What)
{
if (What!=5) DoIt(What);
else What=2;
unsigned char t;
	for (t=0;t<5;t++)
		if (t!=What) SetColor(127-t,0,0,0);
if (What==4) SetColor(123,62,62,62);
else SetColor(127-What,10,0,50);
Engine(What);
}

void DoIt(unsigned char What)
{
unsigned char OldRes=Res;
	switch (What)
	{
	case 4 :
	case 0 :	reset();
				break;
	case 3 :	reset();
				send(adress,2);
				delay(20);
				send(adress,0);
				delay(20);
				break;
	case 2 :	reset();
				send(adress,2);
				delay(50);
				send(adress,0);
				delay(50);
				send(adress,1);
				delay(50);
				send(adress,0);
				delay(50);
				break;
	case 1 :	reset();
				send(adress,1);
				delay(20);
				send(adress,0);
				delay(20);
				break;
	default :	//reset();
				break;
	}


Res=OldRes;
}
void Engine(unsigned char What)
{
	unsigned char x;
	if (What==0)
	{
	DrawPcx(253,96,"On.pcx");
	DrawPcx(253,110,"On.pcx");
	DrawPcx(268,96,"Cw.pcx");
	DrawPcx(268,110,"Cw.pcx");
	EngineStatus=0;
	}
	else if (What==2)
	{
	DrawPcx(253,96,"On.pcx");
	DrawPcx(253,110,"On.pcx");
	DrawPcx(268,96,"Cww.pcx");
	DrawPcx(268,110,"Cww.pcx");
	EngineStatus=2;
	}	
	else if (What==4)
	{
	DrawPcx(253,96,"Off.pcx");
	DrawPcx(253,110,"Off.pcx");
	for (x=0;x<8;x++) { OLine(268,284,96+x,0); OLine(268,284,110+x,0); }
	EngineStatus=4;
	}
	else if (What==1)
	{
	DrawPcx(253,96,"On.pcx");
	DrawPcx(268,96,"Cw.pcx");
	DrawPcx(253,110,"Off.pcx");
	for (x=0;x<8;x++) OLine(268,284,110+x,0);
	EngineStatus=1;
	}
	else if (What==3)
	{
	DrawPcx(253,96,"Off.pcx");
	for (x=0;x<8;x++) OLine(268,284,96+x,0);
	DrawPcx(253,110,"On.pcx");
	DrawPcx(268,110,"Cw.pcx");
	EngineStatus=3;
	}
}
void Led(unsigned char What)
{
if (What==0) { SetColor(122,0,0,0); SetColor(121,0,0,0); SetColor(120,0,0,0); }
else if (What==4) { SetColor(122,63,0,0); SetColor(121,57,56,11); SetColor(120,0,55,0); }
else {
	unsigned char R,G,B;
	GetColor(123-What,R,G,B);
	if ((R)||(G)||(B)) SetColor(123-What,0,0,0);
	else {
		if (What==1) SetColor(122,63,0,0);
		if (What==2) SetColor(121,57,56,11);
		if (What==3) SetColor(120,0,55,0);
		}
	}
}
void Par(unsigned char What)
{
	unsigned char x,R,G,B;
	if (What==0) for(x=111;x<120;x++) SetColor(x,0,0,0);
	else if (What==9) for(x=111;x<120;x++) SetColor(x,63,0,0);
	else
	{
	What+=111;
	GetColor(What,R,G,B);
	if ((R)||(G)||(B)) SetColor(What,0,0,0);
	else SetColor(What,63,0,0);
	}
}
void Lite()
{
	SetVideoMode(19);
	SetPcxPal("Intrfc.pcx");
	Led(0); Arrow(4); Par(9);
	DrawPcx(0,0,"Intrfc.pcx");
	DrawPcx(0,130,"DisMovs.pcx");
	DrawPcx(253,150,"Off.pcx");
	DrawPcx(253,122,"Off.pcx");
	DrawPcx(253,136,"Off.pcx");
	Arrow(4);
}
void Init()
{
	cout << "Initializing Interface..."; delay(1600);
	int x;
	unsigned char Pal[768];
	SetVideoMode(19);
	SetPcxPal("Middle.pcx");
	for (x=0;x<256;x++) { GetColor(x,Pal[x*3],Pal[x*3+1],Pal[x*3+2]); SetColor(x,0,0,0); }
	DrawPcx(0,0,"Middle.pcx");
	delay(2500);
	BrightIn();
	FadeToPal(Pal);
	delay(3500);
	FadeOut();
	ClearScreen();

	SetPcxPal("&.pcx");
	for (x=0;x<256;x++) { GetColor(x,Pal[x*3],Pal[x*3+1],Pal[x*3+2]); SetColor(x,0,0,0); }
	DrawPcx(0,0,"&.pcx");
	FadeToPal(Pal);
	delay(2000);
	BrightIn();
	ClearScreen();

	GetPcxPal("cyber.pcx",Pal);
	DrawPcx(0,0,"cyber.pcx");
	FadeToPal(Pal);
	delay(2000);
	FadeOut();
	ClearScreen();

	SetPcxPal("presents.pcx");
	for (x=0;x<256;x++) { GetColor(x,Pal[x*3],Pal[x*3+1],Pal[x*3+2]); SetColor(x,0,0,0); }
	DrawPcx(0,0,"presents.pcx");
	FadeToPal(Pal);
	delay(2000);
	BrightIn();
	ClearScreen();

	GetPcxPal("cyberone.pcx",Pal);
	DrawPcx(0,0,"cyberone.pcx");
	FadeToPal(Pal);
	delay(800);
	while (!kbhit())
	{
	for (unsigned char h=182;h<200;h++) OLine(182,319,h,0);
	delay(600);
	DrawPcx(221,182,"anyon.pcx");
	delay(600);
	}
	getch();
	FadeOut();
	ClearScreen();
	
	SetPcxPal("Intrfc.pcx");
	Led(0); Arrow(4); Par(9);
	for (x=0;x<256;x++) {GetColor(x,Pal[x*3],Pal[x*3+1],Pal[x*3+2]); SetColor(x,0,0,0); }
	DrawPcx(0,0,"Intrfc.pcx");
	DrawPcx(0,130,"DisMovs.pcx");
	DrawPcx(253,122,"Off.pcx");
	DrawPcx(253,136,"Off.pcx");
	DrawPcx(253,150,"Off.pcx");
	FadeToPal(Pal);
	Arrow(4);
}
void Outro()
{
	unsigned char Pal[768];
	int x;

	SetPcxPal("credits1.pcx");
	for (x=0;x<256;x++) { GetColor(x,Pal[x*3],Pal[x*3+1],Pal[x*3+2]); SetColor(x,0,0,0); }
	DrawPcx(0,0,"credits1.pcx");
	FadeToPal(Pal);
	delay(10000);
	BrightIn();
	ClearScreen();

	GetPcxPal("credits2.pcx",Pal);
	DrawPcx(0,0,"credits2.pcx");
	FadeToPal(Pal);
	delay(16000);
	FadeOut();
	ClearScreen();

	SetPcxPal("credits3.pcx");
	for (x=0;x<256;x++) { GetColor(x,Pal[x*3],Pal[x*3+1],Pal[x*3+2]); SetColor(x,0,0,0); }
	DrawPcx(0,0,"credits3.pcx");
	FadeToPal(Pal);
	delay(16000);
	BrightIn();
}
void send(unsigned int Port, unsigned char Ch)
{
	OutP(Port+2,0);
	OutP(Port,Ch);
	OutP(Port+2,1);
}
void OutP(unsigned int Port, unsigned char C)
{
 asm {
	mov dx,Port
	mov al,C
	out dx,al
	}
}
unsigned int atoi(char *String, unsigned char &M)
{
unsigned int Res,x,Length=0;
unsigned char Mode;
Res=0;
for (Length=0;1;Length++)
	{
	if ((String[Length]=='d')||(String[Length]=='D')||(!String[Length])) { M='d'; Mode=10; break; }
	if ((String[Length]=='h')||(String[Length]=='H')) { M='h'; Mode=16; break; }
	}
for (x=0;x<Length;x++)
	{
	if ((String[x]>57)||(String[x]<48)) return 0;
	Res += ((Power(Mode,Length-x-2))*(String[x]-48));
	}
return Res;
}
unsigned int Power(unsigned char X, int Y)
{
	unsigned int RES=1;
	for (int a=0;a<=Y;a++)
		RES *= X;
	return RES;
}

void Stars()
{
	const unsigned short int MaxStars = 300;
	signed short int X,Y,i,v;
	signed short int  Stars[MaxStars*3];
	for (i=0; i<256;i++) SetColor(i,i/4,i/4,i/4);
	for (i=0;i<MaxStars;i++) { Stars[i*3]=random(320)- 60; Stars[i*3+1]=random(200)-100; Stars[i*3+2]=random(250); }
	while (!kbhit())
	{
		for (i=0;i<MaxStars;i++)
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
		for (i=0; i<MaxStars; i++)
		PutPixel(((Stars[i*3]*256)/(256-Stars[i*3+2])+160),((Stars[i*3+1]*256)/(256-Stars[i*3+2])+100),Stars[i*3+2]);
		WtSync();
		for (i=0; i<MaxStars; i++)
		PutPixel(((Stars[i*3]*256)/(256-Stars[i*3+2])+160),((Stars[i*3+1]*256)/(256-Stars[i*3+2])+100),0);

	}
	getch();
	FadeOut();
}
void Process(unsigned char C,unsigned char &Quit)
{
if (Menu==0) {
		if (MenuPointer==0)			//Exit
		{
			switch (C)
			{
			case 77 :
			case 'd':	//case 'd' e 'a' sono = !!
			case 75 :
			case 'a':	if (Flag==0) { Flag=1; DrawPcx(50,170,"No.pcx"); DrawPcx(100,170,"Yes!.pcx"); }
						else { Flag=0; DrawPcx(50,170,"No!.pcx"); DrawPcx(100,170,"Yes.pcx"); }
						break;
			case 13 :	if (Flag==1) { Res=255; send(adress,Res); Led(0); Arrow(4); Par(9); Quit=1; }
						else Menu=1;
						break;
						//else case 27 !!!
			case 27 : Menu=1;
			default : break;
			}
		}
		else if (MenuPointer==1)	//Tests
		{
			switch (C)
			{
			case 72 :
			case 'w':	if (Flag!=0) 
							{
							DrawPcx(SwCord[Flag][0],SwCord[Flag][1],"red.pcx");
							Flag--;
							DrawPcx(SwCord[Flag][0],SwCord[Flag][1],"green.pcx");
							}
						break;
			case 80 :
			case 'x':	if (Flag!=5)
							{
							DrawPcx(SwCord[Flag][0],SwCord[Flag][1],"red.pcx");
							Flag++;
							DrawPcx(SwCord[Flag][0],SwCord[Flag][1],"green.pcx");
							}
						break;
			case 13:	if (Flag==0) { if (ReleC==1) Rele(1); Res^=1; send(adress,Res); Par(1);
						if (ReleC==1) Rele(1); Res^=1; send(adress,Res); Par(1);
						}
						else if (Flag==1) { if (ReleC==1) Rele(2); Res^=2; send(adress,Res); Par(2);
						if (ReleC==1) Rele(2); Res^=2; send(adress,Res); Par(2);
						}
						else if (Flag==2) { ReleCT(); Res^=128; send(adress,Res); Par(8); }
						else if (Flag==3) { Res^=64; send(adress,Res); Led(1); Par(7); }
						else if (Flag==4) { Res^=32; send(adress,Res); Led(2); Par(6); }
						else if (Flag==5) { Res^=16; send(adress,Res); Led(3); Par(5); }
						break;
			case 27: Menu=1;
			default : break;			
			}
		}
		else if (MenuPointer==2)	//Movs
		{
			switch (C)
			{
			case 'q': Arrow(5); break;
			case 'i': send(adress,1); send(adress,Res); break;
			case 'o': send(adress,2); send(adress,Res); break;
			case 'k': send(adress,5); break;
			case 'l': send(adress,8); break;

			case '+': if (Velocity!=2) Velocity++;
						DrawPcx(0,56,Vel[Velocity]);
						if (Velocity==1) send(adress,8);
						else if (Velocity==2) send(adress,5);
						break;
			case '-': if (Velocity!=0) Velocity--;
						DrawPcx(0,56,Vel[Velocity]);
						if (Velocity==0) send(adress,0);
						else if (Velocity==1) send(adress,8);
						break;
			case 72 :
			case 'w': DrawPcx(0,56,Vel[0]); Arrow(0); break;
			case 77 :
			case 'd': DrawPcx(0,56,Vel[0]); Arrow(1); break;
			case 80 :			
			case 'x': DrawPcx(0,56,Vel[0]); Arrow(2); break;
			case 75 :
			case 'a': DrawPcx(0,56,Vel[0]); Arrow(3); break;
			
			case '1': Res^=1; if ((ReleC==0)&&(((Res%16)==1)||((Res%16)==0))) Rele(1); send(adress,Res); Par(1); break;
			case '2': Res^=2; if ((ReleC==0)&&(((Res%16)==2)||((Res%16)==0))) Rele(2); send(adress,Res); Par(2); break;
			case '3': Res^=4; send(adress,Res); Par(3); break;
			case '4': Res^=8; send(adress,Res); Par(4); break;
			case '5': Res^=16; send(adress,Res); Led(3); Par(5); break;
			case '6': Res^=32; send(adress,Res); Led(2); Par(6); break;
			case '7': Res^=64; send(adress,Res); Led(1); Par(7); break;
			case '8': ReleCT(); Res^=128; send(adress,Res); Par(8); break;
			case '9': if (Res==0) { ReleCT(); Rele(0); } Res=255; Arrow(4); send(adress,112); Led(0); Par(9); break;
			case 'u': if (Res==255) ReleCT(); Velocity=0; DrawPcx(0,56,Vel[Velocity]); Res=0; send(adress,Res); Par(0); Led(4); break;
			case 'j': reset(); break;
			case '0':
			case 's':
			case 32 : if (Res==255) ReleCT(); Velocity=0; DrawPcx(0,56,Vel[Velocity]); Res=0; Par(0); Led(4); Arrow(4); break;
			case 27 : Velocity=0; DrawPcx(0,56,Vel[Velocity]); Res=255; send(adress,Res); Led(0); Arrow(4); send(adress,255); Par(9); Menu=1; break;	//Okkio, in realtà esce dal menu
			default : break;
			}
		}	
	}
else {
		switch (C)
		{
		case 13 :	Flag=0;
					if (MenuPointer==3) Quit=2;	//Load Stars (non ha submenu)
					else Menu=0;				//Else Load Menu

					break;
		case 72 :
		case 'w':	ScrollDown(MenuPointer);
					DrawPcx(0,ButtonY[MenuPointer],Button[MenuPointer][0]);
					if (MenuPointer!=3) MenuPointer++;
					DrawPcx(0,ButtonY[MenuPointer],Button[MenuPointer][1]);
					ScrollUp(MenuPointer);
					if (MenuPointer==1)
					{ 
					DrawPcx(SwCord[0][0],SwCord[0][1],"green.pcx");
					DrawPcx(SwCord[1][0],SwCord[1][1],"red.pcx");
					DrawPcx(SwCord[2][0],SwCord[2][1],"red.pcx");
					DrawPcx(SwCord[3][0],SwCord[3][1],"red.pcx");
					DrawPcx(SwCord[4][0],SwCord[4][1],"red.pcx");
					DrawPcx(SwCord[5][0],SwCord[5][1],"red.pcx");
					}
					break;
		case 80 :
		case 'x':	ScrollDown(MenuPointer);
					DrawPcx(0,ButtonY[MenuPointer],Button[MenuPointer][0]);
					if (MenuPointer!=0) MenuPointer--;
					DrawPcx(0,ButtonY[MenuPointer],Button[MenuPointer][1]);
					ScrollUp(MenuPointer);
					if (MenuPointer==1)
					{ 
					DrawPcx(SwCord[0][0],SwCord[0][1],"green.pcx");
					DrawPcx(SwCord[1][0],SwCord[1][1],"red.pcx");
					DrawPcx(SwCord[2][0],SwCord[2][1],"red.pcx");
					DrawPcx(SwCord[3][0],SwCord[3][1],"red.pcx");
					DrawPcx(SwCord[4][0],SwCord[4][1],"red.pcx");
					DrawPcx(SwCord[5][0],SwCord[5][1],"red.pcx");
					}
					if (MenuPointer==0) { DrawPcx(50,170,"No!.pcx"); DrawPcx(100,170,"Yes.pcx"); }
					break;
		default : break;
		}
	}
}
void ScrollDown(unsigned char What)
{
	unsigned char i;
	for (unsigned char t=92;t<200;t+=13)
		{
		WtSync();
		DrawPcx(40,t,Pannel[What]);
		if (t==92) for (i=0;i<14;i++) OLine(61,157,i+t,0);
		else for (i=0;i<14;i++) OLine(40,157,i+t,0);
		}
}
void ScrollUp(unsigned char What)
{
	for (unsigned char t=199;t>=92;t-=13)
		{
		WtSync();
		DrawPcx(40,t,Pannel[What]);
		}
	DrawPcx(40,92,Pannel[What]);
}
void ReleCT()
{
	if (ReleC==0)
	{
	ReleC=1;
	DrawPcx(253,150,"On.pcx");
	}
	else
	{
	ReleC=0;
	DrawPcx(253,150,"Off.pcx");
	}
}
void Rele(unsigned char What)
{
	if (What==1)
	{
	if (Rele1==0) { Rele1++; DrawPcx(253,122,"On.pcx");}
	else if (Rele1==1) Rele1++;
	else if (Rele1==2) { Rele1++; DrawPcx(253,122,"Off.pcx"); }
	else Rele1=0;
	}
	else if (What==2)
	{
	if (Rele2==0) { Rele2++; DrawPcx(253,136,"On.pcx"); }
	else if (Rele2==1) Rele2++;
	else if (Rele2==2) { Rele2++; DrawPcx(253,136,"Off.pcx"); }
	else Rele2=0;
	}
	else if (What==0)
	{
	Rele1=0;
	Rele2=0;
	DrawPcx(253,122,"Off.pcx");
	DrawPcx(253,136,"Off.pcx");
	}
}
void reset()
{
	send(adress,0);
	delay(50);
	send(adress,255);
	delay(50);
	send(adress,5);
	delay(20);
	send(adress,0);
	delay(50);
}