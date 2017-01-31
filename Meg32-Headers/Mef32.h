#include <io.h>			//for lseek and its constants, read, open, close
#include <fcntl.h>		//for O_RDONLY and O_BINARY

unsigned char DrawPcx(unsigned int Xoff, unsigned int Yoff, unsigned char File[]);
void GetPcxImg(unsigned char File[],unsigned char Image[]);
unsigned char SetPal(unsigned char File[]);
unsigned char SetPcxPal(unsigned char File[]);
unsigned char GetPcxPal(unsigned char File[],unsigned char Pal[]);
void PutFrame(unsigned char Pointer[],unsigned int x,unsigned int y,unsigned int Xsize, unsigned int Ysize);
void PutFrame(unsigned char Pointer[],unsigned int x,unsigned int y,unsigned int Xsize, unsigned int Ysize,unsigned int where);
void PcxTile(unsigned char File[],unsigned int where);

unsigned char DrawPcx(unsigned int Xoff, unsigned int Yoff, unsigned char File[])
{
	int handle;
	if ((handle = open(File, O_RDONLY | O_BINARY )) == -1) return 0;
	unsigned char *F = new unsigned char[100000];
	read(handle,F,128);
	unsigned int Xsize=(F[8]+F[9]*256)-(F[4]+F[5]*256)+1;
	unsigned int Ysize=(F[10]+F[11]*256)-(F[6]+F[7]*256)+1;
	read(handle,&F[1],filelength(handle)-896);
	close(handle);
	unsigned int y=0,x=0;
	unsigned char Count=0,k=0;
	unsigned long int P=0;
	while (y<Ysize)
	{
	x=0;
		while (x<Xsize)
		{
		P++;
		if (F[P]>=192)
			{
			Count=F[P]-192;
			P++;
			for (k=0;k<Count;k++) PutPixel(x+k+Xoff,y+Yoff,F[P]);
			x+=Count;
			}
		else { PutPixel(x+Xoff,y+Yoff,F[P]); x++; }
		}
	y++;
	}
	delete F;
	return 1;
}
void GetPcxImg(unsigned char File[],unsigned char Image[])
{
	int handle;
	if ((handle = open(File, O_RDONLY | O_BINARY )) != -1)
	{
		unsigned char *F = new unsigned char[100000];
		read(handle,F,128);
		unsigned int Xsize=(F[8]+F[9]*256)-(F[4]+F[5]*256)+1;
		unsigned int Ysize=(F[10]+F[11]*256)-(F[6]+F[7]*256)+1;
		read(handle,&F[1],filelength(handle)-896);
		close(handle);
		unsigned int y=0,x=0;
		unsigned char Count=0,k=0;
		unsigned long int P=0;
		while (y<Ysize)
		{
		x=0;
			while (x<Xsize)
			{
			P++;
			if (F[P]>=192)
				{
				Count=F[P]-192;
				P++;
				for (k=0;k<Count;k++) Image[x+k+Xsize*y]=F[P];
				x+=Count;
				}
			else { Image[x+Xsize*y]=F[P]; x++; }
			}
		y++;
		}
		delete F;
	}
}
unsigned char SetPal(unsigned char File[])
{
	int x,handle;
	if ((handle = open(File, O_RDONLY | O_BINARY )) == -1) return 0;
	unsigned char Pal[768];
	read(handle,Pal,768);
//	for (x=0;x<256;x++) SetColor(x,Pal[x*3] SHR 2,Pal[x*3+1] SHR 2,Pal[x*3+2] SHR 2);
	for (x=0;x<256;x++) SetColor(x,Pal[x*3]/4,Pal[x*3+1]/4,Pal[x*3+2]/4);
	close(handle);
	return 1;
}
unsigned char SetPcxPal(unsigned char File[])
{
	int x,handle;
	if ((handle = open(File, O_RDONLY | O_BINARY )) == -1) return 0;
	unsigned char Pal[768];
	lseek(handle,filelength(handle)-768,SEEK_SET);
	read(handle,Pal,768);
	for (x=0;x<256;x++) SetColor(x,Pal[x*3]/4,Pal[x*3+1]/4,Pal[x*3+2]/4);
//	for (x=0;x<256;x++) SetColor(x,Pal[x*3] SHR 2,Pal[x*3+1] SHR 2,Pal[x*3+2] SHR 2);
	close(handle);
	return 1;
}
unsigned char GetPcxPal(unsigned char File[],unsigned char Pal[])
{
	int x,handle;
	if ((handle = open(File, O_RDONLY | O_BINARY )) == -1) return 0;
	lseek(handle,filelength(handle)-768,SEEK_SET);
	read(handle,Pal,768);
	for (x=0;x<768;x++) Pal[x]/=4;
	close(handle);
	return 1;
}
void PutFrame(unsigned char Pointer[],unsigned int x,unsigned int y,unsigned int Xsize, unsigned int Ysize)
{
	for (unsigned int a=0;a<Ysize;a++)
		for (unsigned int b=0;b<Xsize;b++)
			if ((Pointer[Xsize*a+b])&&(b+x<320)&&(a+y<200)) PutPixel(b+x,a+y,Pointer[Xsize*a+b]);
}
void PutFrame(unsigned char Pointer[],unsigned int x,unsigned int y,unsigned int Xsize, unsigned int Ysize,unsigned int where)
{
	for (unsigned int a=0;a<Ysize;a++)
		for (unsigned int b=0;b<Xsize;b++)
			if ((Pointer[Xsize*a+b])&&(b+x<320)&&(a+y<200)) PutPixel(b+x,a+y,Pointer[Xsize*a+b],where);
}
void PcxTile(unsigned char File[],unsigned int where)
{
	unsigned char *Image = new unsigned char[64000];
	int handle;
	unsigned int y=0,x=0;
	unsigned int Xsize,Ysize;
	if ((handle = open(File, O_RDONLY | O_BINARY )) != -1)
	{
		unsigned char *F = new unsigned char[100000];
		read(handle,F,128);
		Xsize=(F[8]+F[9]*256)-(F[4]+F[5]*256)+1;
		Ysize=(F[10]+F[11]*256)-(F[6]+F[7]*256)+1;
		read(handle,&F[1],filelength(handle)-896);
		close(handle);
		unsigned char Count=0,k=0;
		unsigned long int P=0;
		while (y<Ysize)
		{
		x=0;
			while (x<Xsize)
			{
			P++;
			if (F[P]>=192)
				{
				Count=F[P]-192;
				P++;
				for (k=0;k<Count;k++) Image[x+k+Xsize*y]=F[P];
				x+=Count;
				}
			else { Image[x+Xsize*y]=F[P]; x++; }
			}
		y++;
		}
		delete F;
	}
	for (y=0;y<200;y+=Ysize)
		for (x=0;x<320;x+=Xsize)
			PutFrame(Image,x,y,Xsize,Ysize,where);
	delete Image;
}