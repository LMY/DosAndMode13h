// Img = LmyG + [Ncolori] + Pal + W[2],H[2] + index
#include "LmyG.h"
#include "LmyF.h"
#include "LmyIo.h"

unsigned char ReadHeader(int Handle,unsigned char &ColN);
void ReadPal(int Handle,unsigned char ColN);
void DrawImg(int Handle);
void DrawQuad(int x,int y,unsigned char C);

unsigned char *Image = new unsigned char[40000];
unsigned char *Palt = new unsigned char[768];

int main(int argc, char *argv[])
{
	unsigned char Temp,R,G,B,ColN,Sel=0;
	unsigned int x,y,handle;
	unsigned char Header[5]= { 76, 109, 121, 71, 16 };
	unsigned char File[]="Ciao.LmG";
	unsigned char Size[] = { 0, 200,0,200 };
	for (x=0;x<40000;x++) Image[x]=0;
	x=0;
	if ((argc==2)&&(argv[1][0]=='d'))
		{
		SetVideoMode(19);
		SetColor(254,63,63,63);
		SetColor(253,0,0,0);
				
//usa 16colori.... A,Z color++/--	S,X r++/--	D,C g++/--	F,v b++/--
//enter draw	cursor move		esc exit and prompt save(y/n)->FileName

		for (Temp=0;Temp<16;Temp++)
			DrawQuad(318,Temp*2,Temp);
		DrawQuad(316,0,254);

		for (x=0;x<256;x++)
		{
		GetColor(x,R,G,B);
		Palt[x*3]=R; Palt[x*3+1]=G; Palt[x*3+2]=B;
		}
		
		x=0;
		y=0;
		Temp=0;
		PutPixel(0,0,254);
			while(1)
			{
				Temp = getc();
				switch (Temp)
				{
				case 27 :	SetVideoMode(3);
							create(File);
							if (!exist(File)) { puts("Error Creating File."); delete Image; delete Palt; return 0; }
							handle = open(File);
							write(handle,Header,5);
							write(handle,Palt,48);
							write(handle,Size,4);
							write(handle,Image,40000);
							close(handle);

							puts("Save Image?(y/n)");
							Temp=getc();
							putc(Temp);
							if ((Temp!='y')&&(Temp!='Y')) del(File);
							delete Image;
							delete Palt;
							return 1;
				case 'A':
				case 'a':	DrawQuad(316,Sel*2,253);
							if (Sel!=0) Sel--;
							else Sel=15;
							DrawQuad(316,Sel*2,254);
							break;
				case 'Z':
				case 'z':	DrawQuad(316,Sel*2,253);
							if (Sel!=15) Sel++;
							else Sel=0;
							DrawQuad(316,Sel*2,254);
							break;
				
				case 'S':
				case 's':	GetColor(Sel,R,G,B);
							if (R<63) R++;
							else R=0;
							SetColor(Sel,R,G,B);
							Palt[Sel*3]=R;
							Palt[Sel*3+1]=G;
							Palt[Sel*3+2]=B;
							break;
				case 'X':
				case 'x':	GetColor(Sel,R,G,B);
							if (R>0) R--;
							else R=63;
							SetColor(Sel,R,G,B);
							Palt[Sel*3]=R;
							Palt[Sel*3+1]=G;
							Palt[Sel*3+2]=B;
							break;

				case 'D':
				case 'd':	GetColor(Sel,R,G,B);
							if (G<63) G++;
							else G=0;
							SetColor(Sel,R,G,B);
							Palt[Sel*3]=R;
							Palt[Sel*3+1]=G;
							Palt[Sel*3+2]=B;
							break;
				case 'C':
				case 'c':	GetColor(Sel,R,G,B);
							if (G>0) G--;
							else G=63;
							SetColor(Sel,R,G,B);
							Palt[Sel*3]=R;
							Palt[Sel*3+1]=G;
							Palt[Sel*3+2]=B;
							break;

				case 'F':
				case 'f':	GetColor(Sel,R,G,B);
							if (B<63) B++;
							else B=0;
							SetColor(Sel,R,G,B);
							Palt[Sel*3]=R;
							Palt[Sel*3+1]=G;
							Palt[Sel*3+2]=B;
							break;
				case 'V':
				case 'v':	GetColor(Sel,R,G,B);
							if (B>0) B--;
							else B=63;
							SetColor(Sel,R,G,B);
							Palt[Sel*3]=R;
							Palt[Sel*3+1]=G;
							Palt[Sel*3+2]=B;
							break;

				case '6':
				case 77 :	PutPixel(x,y,Image[x+200*y]);
							if (x!=255) x++;
							else x=0;
							PutPixel(x,y,254);
							break;

				case '4':
				case 75 :	PutPixel(x,y,Image[x+200*y]);
							if (x!=0) x--;
							else x=255;
							PutPixel(x,y,254);
							break;

				case '8':
				case 72 :	PutPixel(x,y,Image[x+200*y]);
							if (y!=0) y--;
							else y=199;
							PutPixel(x,y,254);
							break;

				case '2':
				case 80 :	PutPixel(x,y,Image[x+200*y]);
							if (y!=199) y++;
							else y=0;
							PutPixel(x,y,254);
							break;

				case 13 :	PutPixel(x,y,Sel);
							Image[x+200*y]=Sel;
							break;

				default :	break;
				
				}
			}
	}
	else if ((argc==3)&&(argv[1][0]=='v'))
		{
			handle=open(argv[2]);
			if (!handle)
			{
			puts("Can't Open File.");
			return 0;
			}
		Temp=ReadHeader(handle,ColN);
			if (Temp==0)
			{
			puts("Can't read File.");
			return 0;
			}
			if (Temp==1)
			{
			puts("Invalid LmG file.");
			return 0;
			}
		SetVideoMode(19);
		ReadPal(handle,ColN);
		DrawImg(handle);
		getc();
		SetVideoMode(3);
		return 2;
		}
	else {
		puts("Usage: LmyV v [FileName] to view a .LmG file or\n\rLmyV d to create a new filename.");
		return 1;
		}
}

unsigned char ReadHeader(int Handle,unsigned char &ColN)
{
	unsigned char Header[5];
	if (read(Handle,Header,5)!=5) return 0;
	else {
		if ((Header[0]!='L')||(Header[1]!='m')||(Header[2]!='y')||(Header[3]!='G'))	return 1;
		else {
			ColN=Header[4];
			return 2;
			}
		}
}
void ReadPal(int Handle,unsigned char ColN)
{
	unsigned char Pal[3];
	for (unsigned char i=0;i<ColN;i++)
	{
	read(Handle,Pal,3);
	SetColor(i,Pal[0],Pal[1],Pal[2]);
	}
}
void DrawImg(int Handle)
{
	unsigned int W,H,x,y,Size;
	unsigned char Temp[4];
	read(Handle,Temp,4);
	W=Temp[0]*256+Temp[1];
	H=Temp[2]*256+Temp[3];
	Size=W*H;
	while(Size%40000)
	{
		read(Handle,Image,40000);
		for (y=0;y<=H;y++)
			for (x=0;x<=W;x++)
				PutPixel(x,y,Image[x+200*y]);
		Size-=40000;
	}
	if (Size)
	{
	read(Handle,Image,Size);
	for (y=0;y<=H;y++)
		for (x=0;x<=W;x++)
			PutPixel(x,y,Image[x+200*y]);
	}
//	PutPixel(200,199,0);
}
void DrawQuad(int x,int y,unsigned char C)
{
	PutPixel(x,y,C);
	PutPixel(x,y+1,C);
	PutPixel(x+1,y,C);
	PutPixel(x+1,y+1,C);
}