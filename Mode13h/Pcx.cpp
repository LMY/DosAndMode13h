#include "LmyG.h"		//for SetVideoMode, SetColor, PutPixel
#include "LmyIo.h"		//for getc
#include <io.h>			//for lseek and its constants, read, open, close
#include <fcntl.h>		//for O_RDONLY and O_BINARY

int main(int argc, char *argv[])
{
	int handle;
	if (argc!=2) { puts("Usage: #Pcx <filename>"); return 1; }
	if ((handle = open(argv[1], O_RDONLY | O_BINARY )) == -1) { puts("Error Reading File."); return 1; }
	unsigned char *Header = new unsigned char[128];
	read(handle,Header,128);
	unsigned int Xsize=(Header[8]+Header[9]*256)-(Header[4]+Header[5]*256)+1;
	unsigned int Ysize=(Header[10]+Header[11]*256)-(Header[6]+Header[7]*256)+1;
	delete Header;
	unsigned int k=0,y=0,x=0,Count=0;
	unsigned char C;
	SetVideoMode(19);
	unsigned char Pal[768];
	lseek(handle,filelength(handle)-768,SEEK_SET);
	read(handle,Pal,768);
	for (x=0;x<256;x++) SetColor(x,Pal[x*3]/4,Pal[x*3+1]/4,Pal[x*3+2]/4);
	lseek(handle,128,SEEK_SET);
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
			for (k=0;k<Count;k++) PutPixel(x+k,y,C);
			x+=Count;
			}
		else { PutPixel(x,y,C); x++; }
		}
	y++;
	}
	close(handle);
	getc();
	SetVideoMode(3);
	return 0;
}