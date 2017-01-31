void LoadBmp( char* file_name );
void SetThisPalette(unsigned char Pal[768]);
void DrawPcxImg(char* file_name );


void LoadBmp( char* file_name )
{
	DWORD bytes_read;

	unsigned int Height,Width;
		
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;

	PALETTEENTRY pal[256];

	HANDLE file = CreateFile( file_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL ); 

	ReadFile( file, &file_header, sizeof( file_header ), &bytes_read, NULL );
	ReadFile( file, &info_header, sizeof( info_header ), &bytes_read, NULL );
	ReadFile( file, &pal	    , sizeof( pal )		   , &bytes_read, NULL );

	Height = info_header.biHeight;
	Width  = info_header.biWidth;

	IDirectDrawPalette* ddpal;
	pDD->CreatePalette( DDPCAPS_8BIT | DDPCAPS_ALLOW256, pal, &ddpal, NULL );
	pDDS->SetPalette(ddpal);
	pDDSBack->SetPalette(ddpal);


	DDSURFACEDESC desc;
	memset( &desc, 0, sizeof( desc ) );
	desc.dwSize = sizeof( desc );
	HRESULT ret;
	while (ret!=DD_OK) ret = pDDSBack->Lock( NULL, &desc, DDLOCK_SURFACEMEMORYPTR, NULL );
	unsigned char* dest_surface	= (unsigned char*) desc.lpSurface;

	ReadFile(file,dest_surface,Width*Height,&bytes_read, NULL );

	pDDSBack->Unlock( NULL );
	CloseHandle( file );
}
void DrawPcxImg(char* file_name )
{

	HANDLE file = CreateFile( file_name, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS, NULL ); 
	
	unsigned char Header[128];
	unsigned char* Image = new unsigned char[70000];
	unsigned char Palette[768];
	DWORD bytes_read;

	ReadFile( file, &Header, sizeof( Header ), &bytes_read, NULL );
	ReadFile( file, &Image, sizeof( Image ), &bytes_read, NULL );
	ReadFile( file, &Palette, sizeof( Palette ), &bytes_read, NULL );
	
	SetThisPalette(Palette);

	unsigned int Xsize=(Header[8]+Header[9]*256)-(Header[4]+Header[5]*256)+1;
	unsigned int Ysize=(Header[10]+Header[11]*256)-(Header[6]+Header[7]*256)+1;
	
	DDSURFACEDESC desc;
	memset( &desc, 0, sizeof( desc ) );
	desc.dwSize = sizeof( desc );
	HRESULT ret;
	while (ret!=DD_OK) ret = pDDSBack->Lock( NULL, &desc, DDLOCK_SURFACEMEMORYPTR, NULL );
	unsigned char* dest_surface	= (unsigned char*) desc.lpSurface;

	unsigned short int y=0,x=0;
	unsigned char Count=0,k=0;
	unsigned long int P=0;
	while (y<Ysize)
	{
	x=0;
		while (x<Xsize)
		{
		P++;
		if (Image[P]>=192)
			{
			Count=Image[P]-192;
			P++;
			for (k=0;k<Count;k++) dest_surface[x+k+Xsize*y]=Image[P];
			x+=Count;
			}
		else { dest_surface[x+Xsize*y]=Image[P]; x++; }
		}
	y++;
	}
	delete[] Image;
	pDDSBack->Unlock( NULL );
}
void SetThisPalette(unsigned char Pal[768])
{
	PALETTEENTRY pal[256];
	IDirectDrawPalette* ddpal;
	for( int i = 0; i < 256; i++ )
    {
		pal[i].peRed	= Pal[i];
		pal[i].peGreen	= Pal[i+1];
		pal[i].peBlue	= Pal[i+2];
		pal[i].peFlags	= (BYTE)0;
    }
	pDD->CreatePalette( DDPCAPS_8BIT | DDPCAPS_ALLOW256, pal, &ddpal, NULL );
	pDDS->SetPalette(ddpal);
	pDDSBack->SetPalette(ddpal);
}