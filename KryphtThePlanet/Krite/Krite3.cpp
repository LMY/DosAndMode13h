// Finito alle 2.34 ... Awwwwhhhh notte.
#include <iostream.h>
#include <stdio.h>

int main()
{
int Key[64] = { 5, 8, 7, 4, 9, 6, 10, 12, 11, 15, 21, 29, 39, 30, 43, 14, 23, 17, 44, 33, 51, 56, 27, 58, 60, 36, 1, 26, 62, 19, 48, 38, 40, 20, 54, 63, 41, 31, 64, 55, 22, 3, 32, 42, 13, 47, 28, 53, 52, 57, 24, 45, 34, 16, 46, 35, 37, 50, 61, 18, 2, 49, 59, 25 };
int Key2[64];
int Key3[64];
char Word[9];
int Dec[8]; // gli 8 decimali delle lettere...
int Bin[8][8]; // i 64 binari che ne vengono fuori...
int Tok[64]; // 8*8 a 64
int Kry[64]; // i 64 shufflati

for (int i=0; i<64; i++)
{
Key2[i] = Key[i];
}
for (int i=0; i<64; i++)
{
Key3[i] = Key[i];
}
//questo per rendere = le chiavi


cout << "\n"; // impaginare...
cout << "Word To Krypht: ";
cin.get(Word,9); // legge 8 byte e li mette in Word ( e il carattere di terminazione che NON uso)

for (int volte = 0 ; volte < 3 ; volte++)
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
/*prima volta 2 = A(A)=B	seconda volta 2 = B(A)=C	terza volta 2 = C(B)=D
3=A							3=B							3=C
1=B							1=C							1=D

quarta volta 2 = D(C)=E
3=D
2=E
*/	

}
// Visualizzare la stringa kryphtata
cout << "Kryphted it's : ";
for ( int i=0 ; i<8 ; i++ )
{
	putchar(Dec[i]);
}

cout << "\n"; //impaginare...
return 0;
}