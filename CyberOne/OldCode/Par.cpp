// #include <stdlib.h>
#include <dos.h>	//for delay();
#include <conio.h>	//for kbhit() and getch();
#include <iostream.h>	// for cout	{debug only...}

void send(unsigned int Port, unsigned char Ch);
unsigned int atoi(char *String, unsigned char &M);
unsigned int Power(unsigned char X, int Y);
void OutP(unsigned int Port, unsigned char C);

int main(int argc, char *argv[])
{
	unsigned int far *point;
	unsigned int adress;
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

	unsigned char Res=255,Key,Quit=0;
	while (Quit==0)
	{
		if (kbhit())
		{	
			Key=getch();
			switch (Key)
			{
			/*case ';' :
			case ',' : 
			case ':' :
			case '.' : 
			case 'Q' :
			case 'q' : send(adress,4); break;
			case 'A' :
			case 'a' : send(adress,2); break;
			case 'Z' :
			case 'z' : send(adress,1); break;
			case 'W' :
			case 'w' : send(adress,32); break;
			case 'S' :
			case 's' : send(adress,16); break;
			case 'X' :
			case 'x' : send(adress,8); break;*/
			
			case '1' : Res ^=1; send(adress,Res); break;
			case '2' : Res ^=2; send(adress,Res); break;
			case '3' : Res ^=4; send(adress,Res); break;
			case '4' : Res ^= 8; send(adress,Res); break;
			case '5' : Res ^= 16; send(adress,Res); break;
			case '6' : Res ^= 32; send(adress,Res); break;
			case '7' : Res ^= 64; send(adress,Res); break;
			case '8' : Res ^= 128; send(adress,Res); break;
			case '9' : Res = 255; send(adress,Res); break;
			case 32  : Res=0; send(adress,Res); break;
			case 27  : Quit = 1; break ; //send(adress,0); 
			default  : break;
			}
		}
	}
	cout << "Closing link with " << hex << adress << dec << "h...";
	delay(700);
	cout << " Ok.";
	return 0;
}
void send(unsigned int Port, unsigned char Ch)
{
	cout << "Sending to port: " << hex << Port << dec << " value: " << (int) Ch << endl;
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