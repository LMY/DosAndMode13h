//Graph Functions
void SetVideoMode(int Mode);
void PutPixel(int x, int y, char Color);
void PutPixel(int x, int y, char Color, unsigned int where);
unsigned char GetPixel(int x, int y);
void Line(int x1, int y1, int x2, int y2, unsigned char Color);
void OLine(int x1,int x2, int y, unsigned char Color);
void VLine(int y1,int y2, int x, unsigned char Color);
void ClearScreen();
void ClearScreen(unsigned char Color);
void WtSync();
void GetColor(unsigned char ColorNo, unsigned char &R, unsigned char &G, unsigned char &B );
void SetColor(unsigned char ColorNo, unsigned char R, unsigned char G, unsigned char B );
void SetPalette(unsigned char Pal[]);
void GetPalette(unsigned char Pal[]);
void NegativePal();
void FadeOut();
void FadeOut(unsigned char Speed);
void BrightIn();
void BrightIn(unsigned char Speed);
void FadeToPal(unsigned char Pal[]);
void FadeToPal(unsigned char Pal[],unsigned char Speed);
void Flip(unsigned int source,unsigned int dest);
//TextMode Functions
void DrawChar(unsigned int x,unsigned int y,unsigned char Color,unsigned char Char);
unsigned int GetChar (unsigned int x,unsigned int y);
void CLS(char Color,char Char);
void CLS();
//Math Functions
int Round(double x);
int Round(float x);
float Abs(float x);
unsigned int Abs(signed int x);
void Exchg(float &rA, float &rB);
void Exchg(int &rA, int &rB);

const unsigned int VGA = 40960;
const unsigned int TEXT = 47104;

/*					*/
/*	GRAPH FUNCTIONS	*/
/*					*/
void SetVideoMode(int Mode)
{
	asm
	{
	mov ax,Mode
	int 10h
	}
}
void PutPixel(int x, int y, char Color)
{
	asm
	{
	mov ax,0a000h
	mov es,ax
	mov dx,y
	shl dx,2
	add dx,y
	shl dx,6
	add dx,x
	mov di,dx
	mov al,Color
	mov [es:di],al
	}
}
void PutPixel(int x, int y, char Color, unsigned int where)
{
	asm
	{
	mov ax,[where]
	mov es,ax
	mov dx,y
	shl dx,2
	add dx,y
	shl dx,6
	add dx,x
	mov di,dx
	mov al,Color
	mov [es:di],al
	}
}
unsigned char GetPixel(int x, int y)
{
	unsigned char Color;
	asm
	{
	mov ax,0a000h
	mov es,ax
	mov dx,y
	shl dx,2
	add dx,y
	shl dx,6
	add dx,x
	mov di,dx
	mov [Color],[es:di]
	}
	return Color;
}
void ClearScreen(unsigned char Color)
{
	asm {
	mov ax,0a000h
	mov es,ax
	mov cx,32000
	mov al,Color
	mov ah,al
	xor di,di
	rep stosb
	}
}
void ClearScreen()
{
	ClearScreen(0);
}
void Line(int x1, int y1, int x2, int y2, unsigned char Color)
{
	float M,Q;
	if (y1==y2) OLine(x1,x2,y1,Color);
	else if (x2==x1) VLine(y1,y2,x1,Color);
	else {
		M= (float) (y2-y1)/(x2-x1);
		Q= (float) y1 - M*x1;
		if ((M>=-1)&&(M<=1))
			{
			if (x1>x2) { Exchg(x1,x2); Exchg(y1,y2); } 
			for (x1;x1<=x2;x1++)
				PutPixel(x1,Round(M*x1+Q),Color);
			}
		else {
			if (y1>y2) { Exchg(x1,x2); Exchg(y1,y2); } 
			for (y1;y1<=y2;y1++)
				PutPixel(Round((y1-Q)/M),y1,Color);
			}
		}
}
void OLine(int x1,int x2, int y, unsigned char Color)
{
	if (x1>x2) Exchg(x1,x2);
	if (x1==x2) PutPixel(x1,y,Color);
	else
	asm 
	{
	mov ax,0a000h
	mov es,ax
	mov dx,y
	shl dx,2
	add dx,y
	shl dx,6
	add dx,x1
	mov di,dx
	mov al,Color
	mov cx,x2
	sub cx,x1
	inc cx
	rep stosb
	}
}
void VLine(int y1,int y2, int x, unsigned char Color)
{
	if (y1>y2) Exchg(y1,y2);
	if (y1==y2) PutPixel(x,y1,Color);
	else
	asm
	{
	mov ax,0a000h
	mov es,ax
	cmp y1,y2
	jb oki1
	xchg y1,y2
	oki1:
	mov dx,y1
	shl dx,2
	add dx,y1
	shl dx,6
	add dx,x
	mov di,dx
	mov al,Color
	mov cx,y2
	sub cx,y1
	oki2:
	mov [es:di],al
	add di,320
	dec cx
	jnz oki2
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
void GetColor(unsigned char ColorNo, unsigned char &R, unsigned char &G, unsigned char &B )
{
  unsigned char rr,gg,bb;
  asm {
    mov dx,0x03C7
    mov al,[ColorNo]
    out dx,al
    add dx,2
    in  al,dx
    mov [rr],al
    in  al,dx
    mov [gg],al
    in  al,dx
    mov [bb],al
  }
  R = rr;
  G = gg;
  B = bb;
}
void SetColor(unsigned char ColorNo, unsigned char R, unsigned char G, unsigned char B)
{
  asm {
  mov dx,3C8h
  mov al,ColorNo
  out dx,al
  inc dx
  mov al,R
  out dx,al
  mov al,G
  out dx,al
  mov al,B
  out dx,al
  }
}
void SetPalette(unsigned char Pal[])
{
	asm {
	mov dx,03c8h
	xor al,al
	out dx,al
	lea si,Pal
	mov cx,768
	inc dx
	rep outsb
	}
}
void GetPalette(unsigned char Pal[])
{
	for (unsigned int x=0;x<256;x++) GetColor(x,Pal[x*3],Pal[x*3+1],Pal[x*3+2]);
}
void NegativePal()
{
	unsigned char r,g,b;
	for (unsigned short int i=0;i<256;i++)
	{
	GetColor(i,r,g,b);
	SetColor(i,63-r,63-g,63-b);
	}
}
void FadeOut(unsigned char Speed)
{
	unsigned char Pal[768];
	unsigned short int x,y;
	unsigned char t;
	for (x=0;x<256;x++)
		GetColor(x,Pal[x*3],Pal[x*3+1],Pal[x*3+2]);
	for (x=0;x<63;x++)
	{
		for (y=0;y<768;y++)
			for (t=0;t<Speed;t++)
				if (Pal[y]) Pal[y]--;
		WtSync();
		for (y=0;y<256;y++)
			SetColor(y,Pal[y*3],Pal[y*3+1],Pal[y*3+2]);
	}
}
void FadeOut()
{
	FadeOut(1);
}
void BrightIn()
{
	BrightIn(1);
}
void BrightIn(unsigned char Speed)
{
	unsigned char Pal[768];
	unsigned short int x,y;
	unsigned char t;
	for (x=0;x<256;x++)
		GetColor(x,Pal[x*3],Pal[x*3+1],Pal[x*3+2]);
	for (x=0;x<63;x++)
	{
		for (y=0;y<768;y++)
			for (t=0;t<Speed;t++)
				if (Pal[y]<63) Pal[y]++;
		WtSync();
		for (y=0;y<256;y++)
			SetColor(y,Pal[y*3],Pal[y*3+1],Pal[y*3+2]);
	}
}
void FadeToPal(unsigned char Pal[])
{
	FadeToPal(Pal,1);
}

void FadeToPal(unsigned char Pal[],unsigned char Speed)
{
	unsigned char Pale[768];
	unsigned short int x,y;
	unsigned char t;
	for (x=0;x<256;x++)
		GetColor(x,Pale[x*3],Pale[x*3+1],Pale[x*3+2]);
	for (x=0;x<63;x++)
	{
		for (y=0;y<768;y++)
			for (t=0;t<Speed;t++)
				{
				if (Pale[y]<Pal[y]) Pale[y]++;
				if (Pale[y]>Pal[y]) Pale[y]--;
				}
		WtSync();
		for (y=0;y<256;y++)
			SetColor(y,Pale[y*3],Pale[y*3+1],Pale[y*3+2]);
	}
}
void Flip(unsigned int source,unsigned int dest)
{
  asm {
	push ds
	mov ax,[dest]
	mov es,ax
	mov ax,[source]
	mov ds,ax
	xor si,si
	xor di,di
	mov cx,32000
	rep movsw
	pop ds
  }
}


/*						*/
/*	TEXTMODE FUNCTIONS	*/
/*						*/

void CLS(char Color,char Char)
{
	asm {
	mov ax,08b00h
	mov es,ax
	xor di,di
	mov cx,2000
	mov ah,Color
	mov al,Char
	rep stosw
	}
}
void CLS()
{
	CLS(0,0);
}
void DrawChar(unsigned int x,unsigned int y,unsigned char Color,unsigned char Char)
{ 
	asm{
	mov ax,0b800h
	mov es,ax
	mov di,y
	shl di,7
	mov dx,y
	shl dx,5
	add di,dx
	mov dx,x
	shl dx,1
	add di,dx
	mov ah,Color
	mov al,Char
	stosw
	}
}
unsigned int GetChar (unsigned int x,unsigned int y)
{ 
	unsigned int t;
	asm{
	mov ax,0b800h
	mov es,ax
	mov di,y
	shl di,7
	mov dx,y
	shl dx,5
	add di,dx
	mov dx,x
	shl dx,1
	add di,dx
	losw
	mov t,ax
	}
	return t;
}

/*					*/
/*	MATH FUNCTIONS	*/
/*					*/
int Round(double x)
{
	if ((x - (int) x)<0.5) return ((int) x);
	else return ((int) x + 1);
}
int Round(float x)
{
	if ((x - (int) x)<0.5) return ((int) x);
	else return ((int) x + 1);
}
float Abs(float x)
{
	if (x<0) return (x*-1);
	return x;
}
unsigned int Abs(signed int x)
{
	if (x<0) return (x*-1);
	return x;
}
void Exchg(float &rA, float &rB)
{
	float T;
	T=rB;
	rB=rA;
	rA=T;
}
void Exchg(int &rA, int &rB)
{	
	int T;
	T=rB;
	rB=rA;
	rA=T;
}