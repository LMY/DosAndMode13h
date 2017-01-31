//Rotazione di 4 punti attorno a P(0,0)
#include <math.h>
#include <dos.h>

void PutPixel(int x, int y, char Color);
void SetVideoMode(int Mode);
int Round(double x);
void WtSync();

int main()
{
	SetVideoMode(19);
	double St[360];
	double Ct[360];
	
	for (int i=0;i<360;i++)
	{
	St[i]=sin(i*M_PI/180);
	Ct[i]=cos(i*M_PI/180);
	}

	int x=50;
	int y=50;
	PutPixel(0,0,9);
	PutPixel(0,1,9);
	PutPixel(1,1,9);
	PutPixel(1,0,9);

	while (1)
	{
		for (int i=0;i<360;i++)
		{
		PutPixel(x*St[i]-y*Ct[i],x*St[i]+y*Ct[i],4);
		PutPixel(x*St[i]-y*Ct[i]+1,x*St[i]+y*Ct[i],4);
		PutPixel(x*St[i]-y*Ct[i],x*St[i]+y*Ct[i]+1,4);
		PutPixel(x*St[i]-y*Ct[i]+1,x*St[i]+y*Ct[i]+1,4);
		if (inportb(0x60)==1) break;
		WtSync();
		PutPixel(x*St[i]-y*Ct[i],x*St[i]+y*Ct[i],0);
		PutPixel(x*St[i]-y*Ct[i]+1,x*St[i]+y*Ct[i],0);
		PutPixel(x*St[i]-y*Ct[i],x*St[i]+y*Ct[i]+1,0);
		PutPixel(x*St[i]-y*Ct[i]+1,x*St[i]+y*Ct[i]+1,0);
		}
	}
	SetVideoMode(3);
	return 0;
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

int Round(double x)
{
	if ((x - (int) x)<0.5) return ((int) x);
	else return ((int) x +1);
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