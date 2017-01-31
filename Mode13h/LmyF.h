unsigned char exist(unsigned char FN[]);	//return 1 if file exists, 0 if not
void create(unsigned char FN[]);			//create file
void del(unsigned char FN[]);				//delete file
int open(unsigned char FN[]);				//open file, return handle
void close(int Handle);						//close file
void write(int Handle, unsigned char Ascii[],unsigned int N);		//write Array to file
unsigned int read(int Handle, unsigned char String[], unsigned int N);	//read file, load into array
void SetAttrib(unsigned char FN[], unsigned char At[]);		//set File Attribs	(hrsa,d)
void GetAttrib(unsigned char FN[], unsigned char Atr[]);	//Get File Attribs	(hrsa,d)
void MkDir(unsigned char DN[]);				//Create Dir
void RmDir(unsigned char DN[]);				//Remove Dir
double Size(unsigned char FN[]);


double Size(unsigned char FN[])
{
	double size;
	asm {
	mov dx,&FN
	mov ah,23h
	int 21h
	mov size,ah
	}
	return size;
}

unsigned char exist(unsigned char FN[])
{
	unsigned char e;
	asm {
	mov ah,4Eh
	mov dx,&FN
	mov cx,4Eh
	int 21h
	jc Ne
	mov e,1
	Ne:
	}
	return e;
}
void create(unsigned char FN[])
{
	asm {
	mov dx,&FN
	mov ah,3Ch
	xor cx,cx
	int 21h
	}
}
void del(unsigned char FN[])
{
	asm {
	mov dx,&FN
	mov ah,41h
	int 21h
	}
}
int open(unsigned char FN[])
{
	int handle;
	asm {
	mov dx,&FN
	mov ah,3Dh
	mov al,2
	int 21h
	mov [handle],ax
	}
	return handle;
}

void close(int Handle)
{
	asm {
	mov ah,3Eh
	mov bx,Handle
	int 21h
	}
}
void write(int Handle, unsigned char Ascii[],unsigned int N)
{
	asm {
	mov dx,&Ascii
	mov cx,N
	mov ah,40h
	mov bx,Handle
	int 21h
	}
}
unsigned int read(int Handle, unsigned char String[], unsigned int N)
{
	unsigned int HowMany;
	asm {
	mov dx,&String
	mov bx,Handle
	mov ah,3Fh
	mov cx,N
	int 21h
	mov HowMany,ax
	}
	if (HowMany<N) String[HowMany+1]= 0;
	return HowMany;
}
void SetAttrib(unsigned char FN[], unsigned char At[])
{
	int Counter;
	unsigned int Attr=0;
	for (Counter=0;1;Counter++)
		if (!At[Counter]) break;
	for (Counter;Counter>=0;Counter--)
		{
		if (At[Counter]=='r') Attr++;
		if (At[Counter]=='h') Attr+=2;
		if (At[Counter]=='s') Attr+=4;
		if (At[Counter]=='d') Attr+=16;
		if (At[Counter]=='a') Attr+=32;
		}
	asm {
	mov dx,&FN
	mov ax,4301h
	mov cx,Attr
	int 21h
	}
}
void GetAttrib(unsigned char FN[], unsigned char Atr[])
{
	unsigned int At,i=0;
	unsigned char A[5];
	asm {
	mov ax,4300h
	mov dx,&FN
	int 21h
	mov At,cx
	}
	if (At%2) A[0]='r';
	At-=(At%2);
	if (At%4) A[1]='h';
	At-=(At%4);
	if (At%8) A[2]='s';
	At-=(At%8);
	if (At%32) A[3]='d';
	At-=(At%32);
	if (At%64) A[4]='a';

	for (At=0;At<5;At++)
		if ((A[At]=='r')||(A[At]=='h')||(A[At]=='s')||(A[At]=='d')||(A[At]=='a')) { Atr[i]=A[At]; i++; }
}

void MkDir(unsigned char DN[])
{
	asm {
	mov ah,39h
	mov dx,&DN
	int 21h
	}
}
void RmDir(unsigned char DN[])
{
	asm {
	mov ah,3Ah
	mov dx,&DN
	int 21h
	}
}