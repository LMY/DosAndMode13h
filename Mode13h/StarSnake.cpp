#include <iostream.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>	//4random
#include <time.h> //4randomize

void DrawQuad(int x, int y, char Color);
void SetVideoMode(int Mode);
void WtSync();
void PutPixel(int x, int y, char Color);

int main()
{
	randomize();
	signed short int Length=9,Snake[500][2],Quit=0,Bonus[2]={20,12},Punti=0,Pause=0;
	signed short int Stars1[100][2],Stars2[50][2],Stars3[25][2];
	unsigned char dir=2,dir2;
	signed int Level;
	for (int i=0;i<100;i++)
	{
		Stars1[i][0]=random(304)+8;
		Stars1[i][1]=random(184)+8;
	}
	for (int i=0;i<50;i++)
	{
		Stars2[i][0]=random(304)+8;
		Stars2[i][1]=random(184)+8;
	}
	for (int i=0;i<25;i++)
	{
		Stars3[i][0]=random(304)+8;
		Stars3[i][1]=random(184)+8;
	}
	
	SetVideoMode(19);
	cout << "\n\n\n\n\t      Select Level";
	Level=5;
	
	while (1)
	{
		while (!kbhit())
		{
		for (int i=0;i<10;i++)
			if (i!=Level) DrawQuad(15+i,12,32+i);
		DrawQuad(15+Level,11,8);
		DrawQuad(15+Level,12,8);
		DrawQuad(15+Level,13,8);
		}
		dir2=getch();
		if (dir2==77) if (Level!=9) {
						Level++;
						DrawQuad(14+Level,11,0);
						DrawQuad(14+Level,13,0);
						}
		if (dir2==75) if (Level!=0) {
						Level--;
						DrawQuad(16+Level,11,0);
						DrawQuad(16+Level,13,0);
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

	for (int i=0;i<=Length;i++)
	{	Snake[i][0] = Length-i;
		Snake[i][1] = 13;
	}
	for (int i=0;i<25;i++)
	{
	DrawQuad(0,i,4);
	DrawQuad(39,i,4);
	}
	for (int i=1;i<39;i++)
	{
	DrawQuad(i,0,4);
	DrawQuad(i,24,4);
	}

	while(1)
	{
	

	for (int i=0;i<25;i++)
	{	Stars3[i][0]+=3;
		if (Stars3[i][0]>=312) Stars3[i][0]=9;
	}
	for (int i=0;i<50;i++)
	{	Stars2[i][0]+=2;
		if (Stars2[i][0]>=312) Stars2[i][0]=9;
	}
	for (int i=0;i<100;i++)
	{	Stars1[i][0]++;
		if (Stars1[i][0]>=312) Stars1[i][0]=9;
	}
	
	if (Pause!=1) {
	if ((Snake[0][0]==Bonus[0])&&(Snake[0][1]==Bonus[1]))
		{
		recalc:
		Bonus[0]=random(38)+1;
		Bonus[1]=random(23)+1;
		for (int i=0;i<Length;i++)
			if ((Snake[i][0]==Bonus[0])&&(Snake[i][1]==Bonus[1])) goto recalc;
		sound(320+Punti*5);
		++Punti;
		Length++;
		Snake[Length-1][0]=Snake[Length-1][0];
		Snake[Length-1][1]=Snake[Length-1][1];
		}
	for (int i=Length;i>0;i--)
	{
	Snake[i][0]=Snake[i-1][0];
	Snake[i][1]=Snake[i-1][1];
	}
	}
	for (int i=0;i<25;i++)
		PutPixel(Stars3[i][0],Stars3[i][1],22);
	for (int i=0;i<50;i++)
		PutPixel(Stars2[i][0],Stars2[i][1],20);
	for (int i=0;i<100;i++)
		PutPixel(Stars1[i][0],Stars1[i][1],18);
	for (int i=0;i<=Length;i++)
		DrawQuad(Snake[i][0],Snake[i][1],1);
	DrawQuad(Bonus[0],Bonus[1],50+Punti);
	delay(100-10*Level);
	nosound();
	WtSync();
	
	if (kbhit())
	{	
		Pause=0;
		dir2=getch();
		switch (dir2)
		{
		case 27 : Quit=1;
				  break;
		case 'w':
		case 72: if (dir!=3) dir = 1;
				 break;
		case 'd':
		case 77: if (dir!=4) dir = 2;
				 break;
		case 'x':
		case 80: if (dir!=1) dir = 3;
				 break;
		case 'a':
		case 75: if (dir!=2) dir = 4;
				 break;
		case 'p': Pause=1;
				  break;
		default: dir2 = dir;
		}
	}
	if (Pause!=1)
	{
	switch (dir)
	{
	case 1 : Snake[0][1]--;
			 break;
	case 2 : Snake[0][0]++;
			 break;
	case 3 : Snake[0][1]++;
			 break;
	case 4 : Snake[0][0]--;
	}
	
	for (int i=1;i<=Length;i++)	//Scontrato???
			if((Snake[0][0]==Snake[i][0])&&(Snake[0][1]==Snake[i][1])) Quit=1;
	if ((Snake[0][0]==39)||(Snake[0][0]==0)||(Snake[0][1]==0)||(Snake[0][1]==24)||(Quit==1)) break;
	}
	if (Quit==0)
		{
		for (int i=0;i<25;i++) PutPixel(Stars3[i][0],Stars3[i][1],0);
		for (int i=0;i<50;i++) PutPixel(Stars2[i][0],Stars2[i][1],0);
		for (int i=0;i<100;i++) PutPixel(Stars1[i][0],Stars1[i][1],0);
		for (int i=0;i<=Length;i++) DrawQuad(Snake[i][0],Snake[i][1],0);
		DrawQuad(Bonus[0],Bonus[1],0);
		}
	}
	getch();
	SetVideoMode(3);
	cout << "Ooh, I Think U died...\nYour Score Is: " << (Punti*(Level+1));
	return 0;
}

void DrawQuad(int x, int y, char Color)
{
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