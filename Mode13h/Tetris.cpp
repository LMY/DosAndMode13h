#include "LmyG.hpp"
#include <time.h>
#include <stdlib.h>
#include <dos.h>
#include <iostream.h>

void DrawQuad(int x, int y, char Color);
unsigned char Pause();

int main()
{
	randomize();
	unsigned char Screen[11][25];
	signed short int Pos[2];
	unsigned char Cheat=0;
	unsigned short int Rot = 0, i = 0, h=0,x=0,y=0,Break=0;
	unsigned long int Punti=0;
	unsigned char Tetris[7][4][21] = {
	{ {1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,9,4,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,6,4,4,4,4},{1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,9,4,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,6,4,4,4,4} },
	{ {0,0,0,0,2,0,0,0,2,2,0,0,2,0,0,0,8,4,3,0,0},{0,0,0,0,0,0,0,0,2,2,2,0,0,2,0,0,7,3,4,3,0},{0,0,0,0,0,2,0,0,2,2,0,0,0,2,0,0,8,3,4,0,0},{0,0,0,0,0,0,0,0,0,2,0,0,2,2,2,0,7,4,4,4,0} },
	{ {0,0,0,0,3,3,0,0,3,0,0,0,3,0,0,0,8,4,2,0,0},{0,0,0,0,0,0,0,0,3,3,3,0,0,0,3,0,7,3,3,4,0},{0,0,0,0,0,3,0,0,0,3,0,0,3,3,0,0,8,4,4,0,0},{0,0,0,0,0,0,0,0,3,0,0,0,3,3,3,0,7,4,4,4,0} },
	{ {0,0,0,0,4,4,0,0,0,4,0,0,0,4,0,0,8,2,4,0,0},{0,0,0,0,0,0,0,0,0,0,4,0,4,4,4,0,7,4,4,4,0},{0,0,0,0,4,0,0,0,4,0,0,0,4,4,0,0,8,4,4,0,0},{0,0,0,0,0,0,0,0,4,4,4,0,4,0,0,0,7,4,3,3,0} },
	{ {0,0,0,0,5,0,0,0,5,5,0,0,0,5,0,0,8,3,4,0,0},{0,0,0,0,0,0,0,0,0,5,5,0,5,5,0,0,7,4,4,3,0},{0,0,0,0,5,0,0,0,5,5,0,0,0,5,0,0,8,3,4,0,0},{0,0,0,0,0,0,0,0,0,5,5,0,5,5,0,0,7,4,4,3,0} },
	{ {0,0,0,0,0,6,0,0,6,6,0,0,6,0,0,0,8,4,3,0,0},{0,0,0,0,0,0,0,0,6,6,0,0,0,6,6,0,7,3,4,4,0},{0,0,0,0,0,6,0,0,6,6,0,0,6,0,0,0,8,4,3,0,0},{0,0,0,0,0,0,0,0,6,6,0,0,0,6,6,0,7,3,4,4,0} },
	{ {0,0,0,0,0,0,0,0,7,7,0,0,7,7,0,0,8,4,4,0,0},{0,0,0,0,0,0,0,0,7,7,0,0,7,7,0,0,8,4,4,0,0},{0,0,0,0,0,0,0,0,7,7,0,0,7,7,0,0,8,4,4,0,0},{0,0,0,0,0,0,0,0,7,7,0,0,7,7,0,0,8,4,4,0,0} },
	};
	unsigned char Line[4];
	unsigned char Key,Quit = 0;
	unsigned char Fig = random(7);

	Pos[0]=5;
	Pos[1]=-1;
	if (Fig==6) Pos[1]=-2;
	if (Fig==0) Pos[1]=0;

	for (h=1;h<11;h++)
	{
		Screen[h][24]=4;
		for (i=0;i<24;i++)
			{
			Screen[h][i]=0;
			Screen[0][i]=4;
			Screen[10][i]=4;
			}
	}
	SetVideoMode(19);

	cout << "\n\n\n\n\t      Select Level";
	unsigned int Level=5;
	unsigned char dir2;
	while (1)
	{
		while (!kbhit())
		{
		for (int i=0;i<10;i++)
			if (i!=Level) DrawQuad(1+i,12,32+i);
		DrawQuad(1+Level,11,8);
		DrawQuad(1+Level,12,8);
		DrawQuad(1+Level,13,8);
		}
		dir2=getch();
		if ((dir2==77)||(dir2=='6')) if (Level!=9) {
						Level++;
						DrawQuad(Level,11,0);
						DrawQuad(Level,13,0);
						}
		if ((dir2==75)||(dir2=='4')) if (Level!=0) {
						Level--;
						DrawQuad(2+Level,11,0);
						DrawQuad(2+Level,13,0);
						}
		if (dir2==13) break;
		if (dir2==27) { SetVideoMode(3);
						return 0;
					  }
	}
	asm {
	push 0a000h
	pop es
	mov cx,64000
	mov al,0
	xor di,di
	rep stosb
	}
	SetColor(64,63,63,63);
	SetColor(63,20,20,40);

	for (i=0;i<25;i++)
	{
	DrawQuad(10,i,63);
	DrawQuad(0,i,63);
	}
	for (i=0;i<9;i++)
		DrawQuad(i+1,24,63);

	while (Quit!=1)
	{
		for (i=0;i<16;i++)
			if (Tetris[Fig][Rot][i]) DrawQuad(Pos[0]+(i%4),Pos[1]+(i/4),Tetris[Fig][Rot][i]);
		delay(20*(10-Level));
		WtSync();
		for (i=0;i<16;i++)
			if (Tetris[Fig][Rot][i]) DrawQuad(Pos[0]+(i%4),Pos[1]+(i/4),0);

		Break=0;
		for (i=0;i<4;i++)
			if ((Tetris[Fig][Rot][17+i])&&(Screen[Pos[0]+i][Pos[1]+Tetris[Fig][Rot][17+i]]))
			{
				for (x=0;x<16;x++)
				{
				if (Tetris[Fig][Rot][x]) { 
					Screen[Pos[0]+(x%4)][Pos[1]+(x/4)]=Tetris[Fig][Rot][x];
					DrawQuad(Pos[0]+(x%4),Pos[1]+(x/4),Tetris[Fig][Rot][x]);
					}
				}
				if (Pos[1]<0) { Break=1; break; }
				Fig = random(7);
				if (Cheat==1) Fig=0;
				Pos[0]=5;
				if (Fig==0)	Pos[1]=0;
				else {
						Pos[1]=-2;
						if (Fig==6) Pos[1]=-3;
						if (Fig==0) Pos[1]=-1;
					}
				Rot=0;
			}
		if (Break==1) { getch(); break; }
		Pos[1]++;
		Break=0;
		if (kbhit()) {
			Key = getch();
			switch (Key)
			{
			case '6':
			case 77 :	if (Pos[0]<Tetris[Fig][Rot][16]) Pos[0]++;
						break;
			case '4':
			case 75 :	if (Pos[0]>1) Pos[0]--;
						break;
			case '1':	if ((Pos[0]>7)&&(Fig!=6)) {
							if ((Fig==0)&&(Rot%2==0)) Pos[0]=6;
							if ((Fig==1)&&(Rot%2==0)) Pos[0]--;
							if (((Fig==2)||(Fig==3))&&(Rot%2==0)) Pos[0]=7;
							if (((Fig==4)||(Fig==5))&&(Rot%2==0)) Pos[0]--;
						}
						if (Rot!=0) x=Rot-1;
						else x=3;
						for (i=0;i<17;i++) if (Screen[Pos[0]+(i%4)][Pos[1]+(1/4)]&&Tetris[Fig][x][i])
												{
												Break=1;
												break;
												}
						if (Break==0) {
						if (Rot!=0) Rot--;
						else Rot=3;
						}
						Break=0;
						break;
			case '3':	if ((Pos[0]>7)&&(Fig!=6)) {
							if ((Fig==0)&&(Rot%2==0)) Pos[0]=6;
							if ((Fig==1)&&(Rot%2==0)) Pos[0]--;
							if (((Fig==2)||(Fig==3))&&(Rot%2==0)) Pos[0]=7;
							if (((Fig==4)||(Fig==5))&&(Rot%2==0)) Pos[0]--;
						}
						if (Rot!=3) x=Rot+1;
						else x=0;
						for (i=0;i<17;i++) if (Screen[Pos[0]+(i%4)][Pos[1]+(1/4)]&&Tetris[Fig][x][i])
												{
												Break=1;
												break;
												}
						if (Break==0) {
						if (Rot!=3) Rot++;
						else Rot=0;
						}
						Break=0;
						break;
			case 'p':
			case 'P':	Line[0]=Pause();
						if (Line[0]==1) 
							{
							if (Cheat==0)Cheat++;
							else Cheat--;
							}
						if (Line[0]==2) {	
							for (y=0;y<24;y++)
								{
								for (x=1;x<10;x++)
									{
									DrawQuad(x,y,0);
									Screen[x][y]=0;
									}
								}
						}							
						break;
			case 27 :	Quit = 1;
			}
		}
		Line[0]=0;
		Line[1]=0;
		Line[2]=0;
		Line[3]=0;
		for (y=0;y<24;y++)
		{
			Break=0;
			for (x=0;x<10;x++)
				if (Screen[x][y]) Break++;
			if (Break==10)
				{
				if (!Line[0]) { Line[0] = y; Punti++; continue; }
				else if (!Line[1]) { Line[1] = y; Punti++; continue; }
				else if (!Line[2]) { Line[2] = y; Punti++; continue; }
				else if (!Line[3]) { Line[3] = y; Punti++; continue; }
				}
		}
		if ((Line[0])&&(Line[1])&&(Line[2])&&(Line[3])) Punti+=6;
		for (y=0;y<6;y++)
		{
			for (i=0;i<4;i++)
				if (Line[i])
					for (x=1;x<10;x++)
						DrawQuad(x,Line[i],64);
			if (Line[0]) WtSync();
			for (i=0;i<4;i++)
				if (Line[i])
					for (x=1;x<10;x++)
						DrawQuad(x,Line[i],0);
		}
		i=0;
		while (i!=4)
		{
			if (Line[i])
			{
			for (y=Line[i];y>0;y--)
				for (x=1;x<10;x++)
				{
				Screen[x][y]=Screen[x][y-1];
				DrawQuad(x,y,Screen[x][y]);
				}
			}
			i++;
		}
	}
	SetVideoMode(3);
	cout << "Game Over." << endl <<  "Your Score Is: " << (Punti*(Level+1));
	return 0;
}

void DrawQuad(int x, int y, char Color)
{
	x+=14;
	if (y<0) goto Sorry;	//Just To Prevent Bugs...
	asm
	{
	push 0a000h
	pop es
	mov dx,y
	shl dx,2
	add dx,y
	shl dx,9
	mov ax,x
	shl ax,3
	add dx,ax
	mov di,dx
	mov bx,8
	mov al,Color
	hhh:
	mov cx,8
	rep stosb
	dec bx
	jz hh
	add di,312
	jmp hhh
	hh:
	}
	Sorry:
}
unsigned char Pause()
{
	char ch;
	No:
	ch = getch();
	if ((ch=='W')||(ch=='w'))
	{
		ch = getch();
		if ((ch=='l')||(ch=='L'))
			{
			ch = getch();
			if ((ch=='m')||(ch=='M'))
				{
				ch = getch();
				if ((ch=='y')||(ch=='Y')) return 1;
				else goto No;
				}
			else goto No;
		}
		else goto No;
	}
	if ((ch=='l')||(ch=='L'))
	{
		ch = getch();
		if ((ch=='a')||(ch=='A'))
			{
			ch = getch();
			if ((ch=='n')||(ch=='N'))
				{
				ch = getch();
				if ((ch=='y')||(ch=='Y'))
					{
					ch = getch();
					if ((ch=='d')||(ch=='D'))
						{
						ch = getch();
						if ((ch=='a')||(ch=='A')) return 2;
						else goto No;
						}
					else goto No;
					}
				else goto No;
			}
			else goto No;
		}
		else goto No;
	}
	return 0;
}