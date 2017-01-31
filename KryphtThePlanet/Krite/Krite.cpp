// Sono le 1.59.32 am di mercoledì 14 luglio 1999, ce l'ho fatta!!!!!!!!!
// non so neanche che cavolo sono riuscito a fare
// Infatti adesso ci sono tante di quelle procedure di controllo che non ho la minima idea
// di cosa faccia il mio programma... =)

#include <iostream.h>
#include <stdio.h>

int main()
{
int Key[64] = { 5, 8, 7, 4, 9, 6, 10, 12, 11, 15, 21, 29, 39, 30, 43, 14, 23, 17, 44, 33, 51, 56, 27, 58, 60, 36, 1, 26, 62, 19, 48, 38, 40, 20, 54, 63, 41, 31, 64, 55, 22, 3, 32, 42, 13, 47, 28, 53, 52, 57, 24, 45, 34, 16, 46, 35, 37, 50, 61, 18, 2, 49, 59, 25 };
char Word[9];
int Dec[8]; // gli 8 decimali delle lettere...
int Bin[8][8]; // i 64 binari che ne vengono fuori...
int Tok[64]; // 8*8 a 64
int Kry[64]; // i 64 shufflati

cout << "\n"; // impaginare...
cout << "Word To Krypht: ";
cin.get(Word,9); // legge 8 byte e li mette in Word ( e il carattere di terminazione che NON uso)

/*
Dec[0] = 119;	// w
Dec[1] = 97;	// a
Dec[2] = 116;	// t
Dec[3] = 101;	// e
Dec[4] = 114;	// r
Dec[5] = 115;	// s
Dec[6] = 116;	// t
Dec[7] = 114;	// r

Word[0] = 'w' ;
Word[1] = 'a' ;
Word[2] = 't' ;
Word[3] = 'e' ;
Word[4] = 'r' ;
Word[5] = 's' ;
Word[6] = 't' ;
Word[7] = 'r' ;
*/

// ** adesso convertire Word nei decimali Dec[8];
for ( int i=0 ; i<8 ; i++ )
{
Dec[i] = (char) Word[i];
}

/*procedura per visualizzare i decimali
cout << "\n";
for ( int i= 0 ; i<8 ; i++ )
{
cout << Dec[i] << "_";
}
*/

// convertire Dec[n] in binario Bin[8][8];
for ( int i=0 ; i<8 ; i++ )
{
	for ( int o=0 ; o<8 ; o++ )
	{
	Bin[i][o] = Dec[i] % 2;
	Dec[i] = Dec[i] / 2;
	}
}
/* procedura per visualizzare i valori binari
for ( int i=0 ; i<8; i++)
{
	for ( int a=0; a<8 ; a++)
	{
	cout << Bin[i][a];
	}
cout << "_";
}
*/
//convertire Bin[8][8] in Tok[64];
for ( int i=0 ; i<8 ; i++ )
{
	for ( int p=0 ; p<8 ; p++ )
	{
	Tok[i*8+p] = Bin[i][7-p]; //7-p, la ribalta!
	}
}

/*visualizzare i valori di Tok
cout << "\n";
for ( int i=0; i<64 ; i++ )
{
cout << Tok[i];
if (i % 8 == 7) cout << "_";	// per spaziare ogni 8
}
*/

// Kryphta la stringa
for ( int i=0 ; i<64 ; i++ )
{
Kry[i] = Tok[Key[i]-1];		//il -1 perchè la chiave non ha lo 0 e l'array si
}

/*visualizza i valori binari kryptati
cout << "\n";
for (int i=0 ; i<64 ; i++ )
{
cout << Kry[i];
if (i % 8 == 7) cout << "_";	// spazia a 8
}
*/

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

/*visualizza Dec[i];
cout << "\n";
for ( int i=0 ; i<8 ; i++)
{
cout << Dec[i] << "_";
}
*/

// Visualizzare la stringa kryphtata
cout << "Kryphted it's : ";
for ( int i=0 ; i<8 ; i++ )
{
	putchar(Dec[i]);
}

cout << "\n"; //impaginare...
return 0;
}