#include <iostream.h>
#include <io.h>
#include <fcntl.h>

//Global Vars Definitions.
const unsigned short int Dim = 4096;
unsigned short int *Key1 = new unsigned short int[Dim];
unsigned short int *Key2 = new unsigned short int[Dim];
unsigned short int *Key3 = new unsigned short int[Dim];
unsigned short int *KeyU = new unsigned short int[Dim];
unsigned char *Bin = new unsigned char[Dim];
unsigned char *Kry = new unsigned char[Dim];
unsigned char *Word = new unsigned char[Dim/8];

//Krypht Procedures
void InitArrays();
void ShutDown();
unsigned int ReadKeyFile();	//return BlockSize
unsigned int OpenInFile(int &handle); // return FileSize
int CreateOutFile(); // return handle2
unsigned char ReadBlock(int handle, unsigned int Size);
void Krypht(unsigned int Size);
void KryphtKeys(unsigned int Size);
void AdjustKeysForLastKrypht(unsigned int Size);

int main()
{
	InitArrays();
	unsigned int BlockSize = ReadKeyFile();
	if (!BlockSize) { ShutDown(); return 0; }
	//Keys are ok, now read InPut File
	int handle1, handle2;
	unsigned int InSize = OpenInFile(handle1);
	if (!InSize) return 0;
	handle2=CreateOutFile();
	if (!handle2) { close(handle1); return 0; }
	unsigned int Times = InSize / BlockSize;
	unsigned int LastBlockSize = InSize % BlockSize;

//	if BlockSize==32 -> Key1[0..255] &&(Key1[256]=0)
// InFile=81->	BlockSize=32(KeyL=256),LastBlockSize=17,Times=2=>OK

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
	AdjustKeysForLastKrypht(LastBlockSize);
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
	unsigned short int i;
	for (i=0;i<Dim;i++) { Key1[i]=0; Key2[i]=0; Key3[i]=0; KeyU[i]=0; Bin[i]=0; Kry[i]=0; }
	for (i=0;i<(Dim/8);i++) Word[i]=0;
}
void ShutDown()
{
	InitArrays(); //Wipe Mem
	delete Key1;
	delete Key2;
	delete Key3;
	delete KeyU;
	delete Bin;
	delete Kry;
	delete Word;
}
unsigned int ReadKeyFile()
{
	unsigned int BlockSize=0;
	int handle,x;
	if ((handle = open("Key.kry", O_RDONLY | O_BINARY )) == -1)
	{
	cout << "Error Reading Key.\n";
	return 0;
	}
	int KeyLength = filelength(handle);
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
		Key1[x]=TempKey[x*2] + TempKey[x*2+1];
	}
	else cout << "Unsupported Key.";

	close(handle);
	delete TempKey;
	for (unsigned int x=0;x<BlockSize;x++)
		{
		Key2[x]=Key1[x];
		Key3[x]=Key1[x];
		}
	return (BlockSize/8);	//Byte->Bits
}
unsigned int OpenInFile(int &handle)
{
if ((handle = open("OutPut.txt", O_RDONLY | O_BINARY )) == -1)
	{
	cout << "Error Opening InPut File.\n";
	ShutDown();
	return 0;
	}
else return filelength(handle);
}
int CreateOutFile()
{
int handle;
if ((handle = open("OutPut2.txt", O_CREAT | O_BINARY | O_EXCL)) == -1)
	{
	cout << "Error Creating OutPut File.\n";
	ShutDown();
	return 0;
	}
else return handle;
}
unsigned char ReadBlock(int handle, unsigned int Size)
{
	unsigned int N,x,y;
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
void Krypht(unsigned int Size)
{
	unsigned long int i;

	for (i=0;i<Size*8;i++) KeyU[Key1[i]-1]=i;
	for (i=0;i<Size*8;i++) Kry[i] = Bin[KeyU[i]-1];
	for (i=0;i<Size;i++) Word[i] = ( 128*Bin[8*i] + (64 * Bin[8*i+1]) + (32 * Bin[8*i+2]) + (16 * Bin[8*i+3]) + (8 * Bin[8*i+4]) + (4 * Bin[8*i+5]) + (2 * Bin[8*i+6]) + (Bin[8*i+7]));

}
void KryphtKeys(unsigned int Size)
{
	unsigned int i;
	Key2[0] = Key1[Size-1];
	for (i=1;i<Size;i++)
		Key2[i] = Key1[i+1];
	for (i=0;i<Size;i++)
		Key3[i] = Key1[Key2[i]-1];
	for (i=0;i<Size;i++)
		Key1[i] = Key3[i];
}
void AdjustKeysForLastKrypht(unsigned int Size)
{
	unsigned long int x,y=0;
	for (x=0;x<Dim;x++)
	{
	if (Key1[x]<Size)
		{
		Key2[y]=Key1[x];
		++y;
		}
	}
	for (x=0;x<Size;x++)
		Key1[x]=Key2[x];
}