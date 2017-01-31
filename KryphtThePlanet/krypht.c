#include <stdio.h>
#include <string.h>


struct key {
	unsigned long *data;
	unsigned long size;
};
struct block {
	char *data;
	unsigned long size;
};



void parseargs(char **argv, int argc, char* dekrypht, char* keyfile);

int KeyAlloc(struct key* who, unsigned long bytes);
void KeyCopy(struct key* from, struct key* to);
void KeyDealloc(struct key* who);
int KeyKrypht(struct key* Key1, struct key* Key2, struct key* Key3);			// *****
int KeyRead(char* filename, struct key* Key, unsigned long* blockSize);
int KeyWrite(char* filename, struct key* Key);

int BlockAlloc(struct block* who, unsigned long bytes);
void BlockCopy(struct block* from, struct block* to);
void BlockDealloc(struct block* who);
int BlockKrypht(struct block* Block, struct key* Key);					// *******
int BlockRead(int handle, struct block* Block, unsigned long size);
int BlockWrite(int handle, struct block* Block);



int main(int argc, char **argv)
{
	char dekrypht;	/* 0:krypht, 1:dekrypht, 2:create_key, 3:verify_key */
	char* keyfilename;

	struct key* Key1;
	struct key* Key2;
	struct key* Key3;
	struct block *mainBlock;
	unsigned long blockSize;

/* this would be done by the costructors in c++, i'll leave this only for i fear to know
 * what mfree could do on a pointer set somewhere randomly in the green fields of memory :) */
/*	memset(Key1, '\0', sizeof(struct key));
	memset(Key2, '\0', sizeof(struct key));
	memset(Key3, '\0', sizeof(struct key));
	memset(mainBlock, '\0', sizeof(struct block));
*/




	parseargs(argv,argc,&dekrypht,keyfilename);

	if (KeyRead(keyfilename, Key1, &blockSize)) {
		fprintf(stderr,"Error reading keyfile (%s)", keyfilename);
		exit(-1);
	}
	KeyAlloc(Key2, blockSize);
	KeyCopy(Key1, Key2);
	KeyAlloc(Key3, blockSize);
	KeyCopy(Key1, Key3);


	while (BlockRead(0, mainBlock, Key1->size) != 0) {
		BlockKrypht(mainBlock, Key1);
		BlockWrite(1, mainBlock);
		KeyKrypht(Key1, Key2, Key3);
	}

	KeyDealloc(Key1);
	KeyDealloc(Key2);
	KeyDealloc(Key3);
	BlockDealloc(mainBlock);

	return 0;
}

void parseargs(char **argv, int argc, char* dekrypht, char* keyfile)
{
	int cchar;

	keyfile=0;

	carg=1;
	while (argv) {
		cchar=0;

		switch (*argv[cchar++]) {
			case '\0':
			case '\n': break;

			case '-' : continue;

			case 'h' : goto usage;
			case 'd' : *dekrypht=1; continue;
			case 'c' : *dekrypht=2; continue;
			case 'v' : *dekrypht=3; keyfile = *(++argv); break;
			case 'k' : *dekrypht=0; keyfile = *(++argv); break;
			default : fprintf(stderr,"Illegal option: %c\n",*argv[cchar-1]);
		}
		argv++;
	}

	if (keyfile == 0) {
usage:	fprintf(stderr,"Usage:\n$ %s [-d][-h][-c keysize] -{v/k} keyfile\n",argv[0]);
		exit(1);
	}
}



int KeyAlloc(struct key* who, unsigned long bytes)
{
	if (!(who->data = (void*) malloc((who->size = bytes)))) {
		who->data = 0;
		who->size = 0;
		return 1;
	}

	return 0;
}

void KeyCopy(struct key* from, struct key* to)
{
	memcpy(from->data, to->data, (to->size=from->size));
}

void KeyDealloc(struct key* who)
{
	if (who->data)
		free(who->data);
	who->data = 0;
	who->size = 0;
}

int KeyRead(char* filename, struct key* Key, unsigned long* blockSize)
{
	FILE* fhandle;
	unsigned long ElementSize;

	*blockSize = 0; 		// LMY::fsize(filename.... );
	ElementSize = (*blockSize) * 4; // LMY::switch...


	if (!(fhandle = fopen(filename,"r"))) {
errorKRead:	*blockSize = 0;
		Key->size = 0;
		Key->data = 0;
		return 1;
	}
	KeyAlloc(Key, (*blockSize) * 4);
	if ((fread(Key->data, ElementSize, (*blockSize), fhandle)) != (*blockSize) * ElementSize) {
		fclose(fhandle);
		goto errorKRead;
	}
	fclose(fhandle);

	return 0;
}

int KeyWrite(char* filename, struct key* Key)
{
	FILE* fhandle;
	unsigned long ElementSize;

	if (!(fhandle = fopen(filename,"w+"))) {
		fprintf(stderr,"Error creating file!\n");
		return 1;
	}

	ElementSize = 4; // LMY:: switch (Key->size)

	if (fwrite(Key->data, ElementSize, Key->size, fhandle) != ElementSize * Key->size)  {
		fclose(fhandle);
		fprintf(stderr,"Error writing Key-file!\n");
		return 1;
	}

	fclose(fhandle);
	return 0;
}



int BlockAlloc(struct block* who, unsigned long bytes)
{
	if (!(who->data = (void*) malloc((who->size = bytes)))) {
		who->data = 0;
		who->size = 0;
		return 1;
	}

	return 0;
}

void BlockCopy(struct block* from, struct block* to)
{
	memcpy(from->data, to->data, (to->size=from->size));
}

void BlockDealloc(struct block* who)
{
	if (who->data)
		free(who->data);
	who->data = 0;
	who->size = 0;
}

int BlockRead(int handle, struct block* Block, unsigned long size)
{
	long x;

	x = read(handle, Block->data, (Block->size = size));
	if (x < 0)
		return x;
	else return (x != size); /* returns 1 on eof */
}

int BlockWrite(int handle, struct block* Block)
{
	long x;
	return ((x = write(handle, Block->data, Block->size)) != Block->size);
}