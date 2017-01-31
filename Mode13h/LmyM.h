//Mouse Library by LMY
//WARNING: most mouse drivers move the pointer in a 640x200 virtual screen

unsigned char HowManyButtons();
void HidePointer();
void ShowPointer();
void GetXY(unsigned int &X,unsigned int &Y,unsigned char &B1, unsigned char &B2, unsigned char &B3);
void GetXY(unsigned int &X,unsigned int &Y,unsigned char &B1, unsigned char &B2);
void GetXY(unsigned int &X,unsigned int &Y,unsigned char &B1);
void GetXY(unsigned int &X,unsigned int &Y);
void GotoXY(unsigned int X, unsigned int Y);
void Limit(unsigned int Xr, unsigned int Xl, unsigned int Yu, unsigned int Yd);
void SetMask(unsigned int handler, unsigned char Mask);
void GetStatus(unsigned int &X,unsigned int &Y,unsigned char &B1, unsigned char &B2, unsigned char &B3);
void GetStatus(unsigned int &X,unsigned int &Y,unsigned char &B1, unsigned char &B2);
void GetStatus(unsigned int &X,unsigned int &Y,unsigned char &B1);

unsigned char HowManyButtons()
{
	unsigned int b;
	asm {
	xor ax,ax
	int 33h
	cmp ax,0
	je NO
	mov b,bx
	NO:
	}
	return b;
}

void HidePointer()
{
	asm {
	mov ax,2
	int 33h
	}
}
void ShowPointer()
{
	asm {
	mov ax,1
	int 33h
	}
}
void GetXY(unsigned int &X,unsigned int &Y,unsigned char &B1, unsigned char &B2, unsigned char &B3)
{
	unsigned int Temp,x,y;
	asm {
	mov ax,3
	int 33h
	mov x,cx
	mov y,dx
	mov Temp,bx
	}
	X=x;
	Y=y;
	B1=Temp%2;
	Temp/=2;
	B2=Temp%4;
	Temp/=4;
	B3=Temp%8;
}
void GetXY(unsigned int &X,unsigned int &Y,unsigned char &B1, unsigned char &B2)
{
	unsigned int Temp,x,y;
	asm {
	mov ax,3
	int 33h
	mov x,cx
	mov y,dx
	mov Temp,bx
	}
	X=x;
	Y=y;
	B1=Temp%2;
	Temp/=2;
	B2=Temp%4;
}
void GetXY(unsigned int &X,unsigned int &Y,unsigned char &B1)
{
	unsigned int Temp,x,y;
	asm {
	mov ax,3
	int 33h
	mov x,cx
	mov y,dx
	mov Temp,bx
	}
	X=x;
	Y=y;
	B1=Temp%2;
}
void GetXY(unsigned int &X,unsigned int &Y)
{
	unsigned int x,y;
	asm {
	mov ax,3
	int 33h
	mov x,cx
	mov y,dx
	}
	X=x;
	Y=y;
}
void GotoXY(unsigned int X, unsigned int Y)
{
	asm {
	mov cx,X
	mov dx,Y
	mov ax,4
	int 33h
	}
}
void Limit(unsigned int Xr, unsigned int Xl, unsigned int Yu, unsigned int Yd)
{
	asm {
	mov cx,Xr
	mov dx,Xl
	mov ax,7
	int 33h
	inc ax
	mov cx,Yu
	mov dx,Yd
	int 33h
	}
}
void SetMask(unsigned int handler, unsigned char Mask)
{
	asm {
	mov ax,0Ch
	mov cl,Mask
	xor ch,ch
	les bx,handler
	mov es,bx
	lea dx,handler
	int 33h
	}
}
void GetStatus(unsigned int &X,unsigned int &Y,unsigned char &B1, unsigned char &B2, unsigned char &B3)
{
	unsigned int Temp,x,y;
	asm {
	mov x,cx
	mov y,dx
	mov Temp,bx
	}
	X=x;
	Y=y;
	B1=Temp%2;
	Temp/=2;
	B2=Temp%4;
	Temp/=4;
	B3=Temp%8;
}
void GetStatus(unsigned int &X,unsigned int &Y,unsigned char &B1, unsigned char &B2)
{
	unsigned int Temp,x,y;
	asm {
	mov x,cx
	mov y,dx
	mov Temp,bx
	}
	X=x;
	Y=y;
	B1=Temp%2;
	Temp/=2;
	B2=Temp%4;
}
void GetStatus(unsigned int &X,unsigned int &Y,unsigned char &B1)
{
	unsigned int Temp,x,y;
	asm {
	mov x,cx
	mov y,dx
	mov Temp,bx
	}
	X=x;
	Y=y;
	B1=Temp%2;
}