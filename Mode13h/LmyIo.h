//OutPut
void putc(unsigned char A);
void puts(unsigned char String[]);
void crlf();
//InPut
unsigned char getc();
void gets(unsigned char String[]);

//Functions
void putc(unsigned char A)
{
	asm {
	mov dl,&A
	mov ah,2
	int 21h
	}
}
void puts(unsigned char String[])
{
	unsigned int Counter;
	for (Counter=0;1;Counter++)
		if (!String[Counter]) break;
	String[Counter+1]='$';
	asm {
	mov ah,9
	mov dx,&String
	int 21h
	}
}
unsigned char getc()
{
	unsigned char A;
	asm {
	xor ah,ah
	int 16h
	mov &A,al
	}
	return A;
}
void gets(unsigned char String[])
{
	asm {
	mov ah,0Ah
	mov dx,&String
	int 21h
	}
}
void crlf()
{
	asm {
	mov ah,2
	mov dl,10
	int 21h
	add dl,13
	int 21h
	}
}