#include <io.h>			//for lseek and its constants, read, open, close
#include <fcntl.h>		//for O_RDONLY and O_BINARY

unsigned char DrawPcx(unsigned int Xoff, unsigned int Yoff, unsigned char File[]);
unsigned char SetPcxPal(unsigned char File[]);
unsigned char GetPcxPal(unsigned char File[],unsigned char Pal[]);

unsigned char DrawPcx(unsigned int Xoff, unsigned int Yoff, unsigned char File[])
{
	int handle;
	if ((handle = open(File, O_RDONLY | O_BINARY )) == -1) return 0;
	unsigned char Header[12];
	read(handle,Header,12);
	unsigned int Xsize=(Header[8]+Header[9]*256)-(Header[4]+Header[5]*256)+1;
	unsigned int Ysize=(Header[10]+Header[11]*256)-(Header[6]+Header[7]*256)+1;
	lseek(handle,128,SEEK_SET);

	unsigned int k=0,y=0,x=0,Count=0;
	unsigned char C;
	while (y<Ysize)
	{
	x=0;
		while (x<Xsize)
		{
		read(handle,&C,1);
		if (C>=192)
			{
			Count=C-192;
			read(handle,&C,1);
			for (k=0;k<Count;k++) if ((x+k+Xoff<320)&&(y+Yoff<200)) PutPixel(x+k+Xoff,y+Yoff,C);
			x+=Count;
			}
		else { if ((x+Xoff<320)&&(y+Yoff<200)) PutPixel(x+Xoff,y+Yoff,C); x++; }
		}
	y++;
	}
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