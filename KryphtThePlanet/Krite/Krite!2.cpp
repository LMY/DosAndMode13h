// Finito alle 2.34 ... Awwwwhhhh notte.
#include <iostream.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
int Key[64] = { 5, 8, 7, 4, 9, 6, 10, 12, 11, 15, 21, 29, 39, 30, 43, 14, 23, 17, 44, 33, 51, 56, 27, 58, 60, 36, 1, 26, 62, 19, 48, 38, 40, 20, 54, 63, 41, 31, 64, 55, 22, 3, 32, 42, 13, 47, 28, 53, 52, 57, 24, 45, 34, 16, 46, 35, 37, 50, 61, 18, 2, 49, 59, 25 };
int Key2[64];
int Key3[64];
int Dec[8]; // gli 8 decimali delle lettere...
int Dec2[256];
int Bin[8][8]; // i 64 binari che ne vengono fuori...
char Word[256];
int Tok[64]; // 8*8 a 64
int Kry[64]; // i 64 shufflati
int Passi, Lenght, Lenght2;


if (argc < 3)
{
cout << "Usage: Krypht! [switch] <Password>\n";
cout << "Switches: [K]rypht [K3]rypht [D]eKrypht [D3]eKrypht";
return 0;
}

Lenght2 = sizeof(argv[2])/sizeof(argv[2][0]);
cout << Lenght2;


for (int i=0; i<64; i++)
{
Key2[i] = Key[i];
}
for (int i=0; i<64; i++)
{
Key3[i] = Key[i];
}
//questo per rendere = le chiavi

for (int i=0; i<256; i++)
{
Word[i] = '$';
}

cout << "\n"; // impaginare...
cout << "Word To Krypht: ";
//cin.get(Word,257);
//cin >> Word;
cin.getline(Word,256);

for (int i=0; i<256; i++)
{
if ( (Word[i] == '$') && (Word[i+1] == '$') )
	{
	Lenght = (i-1);
	break;
	}
}

for (int i=0; i<256; i++)
{
if (Word[i] == '$') Word[i] = 0;
}
//cos� i $ ridiventano 00h

Passi = (Lenght/8);
if (Lenght%8 != 0) Passi++;

for (int volte = 0 ; volte < Passi ; volte++)
{
	// ** adesso convertire Word nei decimali Dec[8];
	for ( int i=0 ; i<8 ; i++ )
	{
	Dec[i] = (char) Word[i];
	}

	// convertire Dec[n] in binario Bin[8][8];
	for ( int i=0 ; i<8 ; i++ )
	{
		for ( int o=0 ; o<8 ; o++ )
		{
		Bin[i][o] = Dec[i] % 2;
		Dec[i] = Dec[i] / 2;
		}
	}
	//convertire Bin[8][8] in Tok[64];
	for ( int i=0 ; i<8 ; i++ )
	{
		for ( int p=0 ; p<8 ; p++ )
		{
		Tok[i*8+p] = Bin[i][7-p]; //7-p, la ribalta!
		}
	}

	// Kryphta la stringa
	for ( int i=0 ; i<64 ; i++ )
	{
	Kry[i] = Tok[Key[i]-1];		//il -1 perch� la chiave non ha lo 0 e l'array si
	}

	//Tok = Kry ribaltato, se vuoi togliere questo togli anche il "7-" nella prossimo
	for ( int i=0 ; i<64 ; i++)
	{
	Tok[63-i] = Kry[i];
	}

	// adesso  Riconvertire Tok[64] (binario) in Dec[8];
	for ( int i=0 ; i<8 ; i++ )
	{
	Dec[7-i] =( Tok[8*i] + (2 * Tok[8*i+1]) + (4 * Tok[8*i+2]) + (8 * Tok[8*i+3]) + (16 * Tok[8*i+4]) + (32 * Tok[8*i+5]) + (64 * Tok[8*i+6]) + (128 * Tok[8*i+7]));
	}
	
	for (int i=0; i<8; i++)
	{
	Dec2[volte*8+i] = Dec[i];
	}
	
	//prepara un'altra chiave Key2
	for (int i=0 ; i<64 ; i++ )
	{
		Key2[i] = Key[Key3[i]-1];		// la chive che arriva va a kryptare quella dopo
	}
	//copia in Key3 la Key che � stata usata (e che nel loop precedente rappresenta quella di due volte
	//prima di kryphtare
	for (int i=0 ; i<64 ; i++)
	{
		Key3[i] = Key[i];
	}
	//copia Key2 in quella che verr� usata per Kryphtare
	for (int i=0 ; i<64 ; i++)
	{
		Key[i] = Key2[i];
	}

	for ( int i=0 ; i<8 ; i++ )
	{
	Word[i] = Word[8+i];
	}
	//cycla la stringa di 8 a sn

}
// Visualizzare la stringa kryphtata
cout << "Kryphted it's : ";
for ( int i=0 ; i<Lenght ; i++ )
{
	putchar(Dec2[i]);
}

cout << "\n"; //impaginare...
return 0;
}