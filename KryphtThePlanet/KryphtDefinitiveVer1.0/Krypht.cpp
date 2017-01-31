#include <iostream.h>
#include <io.h>
#include <fcntl.h>

//Global Vars Definitions.
const unsigned long int Dim = 4096;
unsigned short int *Key1 = new unsigned short int[Dim];
unsigned short int *Key2 = new unsigned short int[Dim];
unsigned short int *Key3 = new unsigned short int[Dim];
unsigned char *Bin = new unsigned char[Dim];
unsigned char *Kry = new unsigned char[Dim];
unsigned char *Word = new unsigned char[Dim/8];
unsigned char D;

//Krypht Procedures
void InitArrays();
void ShutDown();
unsigned long int ReadKeyFile(unsigned char KeyFile[]);	//return BlockSize
unsigned long int OpenInFile(int &handle, unsigned char InFile[]); // return FileSize
int CreateOutFile(unsigned char OutFile[]); // return handle2
unsigned char ReadBlock(int handle, unsigned long int Size);
void Krypht(unsigned long int Size);
void KryphtKeys(unsigned long int Size);
void AdjustKeysForLastKrypht(unsigned long int Size, unsigned int TotalSize);
void Error();
unsigned long int Power(unsigned int x);

int main(int argc, char *argv[])
{
	InitArrays();
	if (argc!=5) { Error(); return 0; }
	if ((argv[1][0]=='d')||(argv[1][0]=='D')) D=1;
	else if ((argv[1][0]=='k')||(argv[1][0]=='K')) D=0;
	else { Error(); return 0; }
	unsigned long int BlockSize = ReadKeyFile(argv[2]);
	if (!BlockSize) { ShutDown(); return 0; }
	//Keys are ok, now read InPut File
	int handle1, handle2;
	unsigned long int InSize = OpenInFile(handle1,argv[3]);
	if (!InSize) return 0;
	handle2=CreateOutFile(argv[4]);
	if (!handle2) { close(handle1); return 0; }
	unsigned long int Times = InSize / BlockSize;
	unsigned long int LastBlockSize = InSize % BlockSize;

	do
	{
	if (!ReadBlock(handle1,BlockSize)) { close(handle1); close(handle2); return 0; }
	Krypht(BlockSize);
	write(handle2,Word,BlockSize);
	KryphtKeys(BlockSize);
	--Times;
	}
	while (Times);
	if (LastBlockSize)
	{
	if (!ReadBlock(handle1,LastBlockSize)) { close(handle1); close(handle2); return 0; }
	AdjustKeysForLastKrypht(LastBlockSize,BlockSize);
	Krypht(LastBlockSize);
	write(handle2,Word,LastBlockSize);
	}
	close(handle1);
	close(handle2);
	ShutDown();
	return 1;
}

void InitArrays()
{
	unsigned long int i;
	for (i=0;i<Dim;i++) { Key1[i]=0; Key2[i]=0; Key3[i]=0; Bin[i]=0; Kry[i]=0; }
	for (i=0;i<(Dim/8);i++) Word[i]=0;
}
void ShutDown()
{
	InitArrays(); //Wipe Mem
	delete Key1;
	delete Key2;
	delete Key3;
	delete Bin;
	delete Kry;
	delete Word;
}
unsigned long int ReadKeyFile(unsigned char KeyFile[])
{
	unsigned long int BlockSize=0;
	int handle,x;
	if ((handle = open(KeyFile, O_RDONLY | O_BINARY )) == -1)
	{
	cout << "Error Reading Key.\n";
	return 0;
	}
	unsigned long int KeyLength = filelength(handle);
	unsigned char *TempKey = new unsigned char[Dim*2];

	if ((KeyLength==64)||(KeyLength==256))
		{
		read(handle,TempKey,KeyLength);
			for (x=0;x<KeyLength;x++)
				Key1[x]=TempKey[x];
		BlockSize=KeyLength;
		}
	else if ((KeyLength==1024)||(KeyLength==2048)||(KeyLength==4096)||(KeyLength==8192))
	{
	BlockSize=KeyLength/2;
	read(handle,TempKey,KeyLength);
	for (x=0;x<KeyLength/2;x++)
		Key1[x]=TempKey[x*2] + 256*TempKey[x*2+1];
	}
	else cout << "Unsupported Key.";

	close(handle);
	delete TempKey;
	for (unsigned long int x=0;x<BlockSize;x++)
		{
		Key2[x]=Key1[x];
		Key3[x]=Key1[x];
		}
	return (BlockSize/8);	//Byte->Bits
}
unsigned long int OpenInFile(int &handle, unsigned char InFile[])
{
if ((handle = open(InFile, O_RDONLY | O_BINARY )) == -1)
	{
	cout << "Error Opening InPut File.\n";
	ShutDown();
	return 0;
	}
else return filelength(handle);
}
int CreateOutFile(unsigned char OutFile[])
{
int handle;
if ((handle = open(OutFile, O_CREAT | O_BINARY | O_EXCL)) == -1)
	{
	cout << "Error Creating OutPut File.\n";
	ShutDown();
	return 0;
	}
else return handle;
}
unsigned char ReadBlock(int handle, unsigned long int Size)
{
	unsigned long int N,x,y;
	N=read(handle,Word,Size);
	if (N!=Size) { cout << "Can't Read InPut File.\n"; ShutDown(); return 0; }

	for (x=0;x<Size;x++)
	{
		for (y=0;y<8;y++)
		{
		Bin[x*8+7-y] = Word[x] % 2;
		Word[x] /= 2;
		}
	}
	return 1;
}
void Krypht(unsigned long int Size)
{
	unsigned long int i,a;
		if (!D)	for (i=0;i<Size*8;i++) Kry[i] = Bin[Key1[i]];	//sarebbe -1
		else for (i=0;i<Size*8;i++) Kry[Key1[i]] = Bin[i];		//anche qui
	for (i=0;i<Size;i++)
	{
		Word[i]=0;
		for (a=0;a<8;a++)
			Word[i]+=Kry[i*8+a]*Power(7-a);
	}
}
void KryphtKeys(unsigned long int Size)
{
	unsigned long int i;
	for (i=0;i<Size*8;i++)
		Key2[i]=Key1[Key3[i]-1];
	for (i=0;i<Size*8;i++)
		Key3[i]=Key1[i];
	for (i=0;i<Size*8;i++)
		Key1[i]=Key2[i];
}
void AdjustKeysForLastKrypht(unsigned long int Size, unsigned int TotalSize)
{
	TotalSize*=8;
	unsigned long int A=Size*8;
	unsigned long int x,y=0;
	for (x=0;x<TotalSize;x++)
	{
		if (Key1[x]<A) { Key2[y]=Key1[x]; y++; }
	}
	for (x=0;x<A;x++)
		Key1[x]=Key2[x];
}
void Error()
{
cout << "Usage: #Krypht k/d [KeyFile] [InputFile] [Output File]";
ShutDown();
}
unsigned long int Power(unsigned int x)
{
	unsigned long int P=1;
	for (int i=0;i<x;i++)
		P*=2;
	return P;
}