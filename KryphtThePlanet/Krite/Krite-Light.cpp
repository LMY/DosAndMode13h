#include <iostream.h>

int main()
{
char Key[64] = { 5, 8, 7, 4, 9, 6, 10, 12, 11, 15, 21, 29, 39, 30, 43, 14, 23, 17, 44, 33, 51, 56, 27, 58, 60, 36, 1, 26, 62, 19, 48, 38, 40, 20, 54, 63, 41, 31, 64, 55, 22, 3, 32, 42, 13, 47, 28, 53, 52, 57, 24, 45, 34, 16, 46, 35, 37, 50, 61, 18, 2, 49, 59, 25 };
char Bin[64], Kry[64], Word[9];

cout << "\nWord To Krypht: ";
cin.get(Word,9);

for (int i=0; i<8; i++)
{
	for (int o=0; o<8; o++)
	{
	Bin[i*8+7-o] = Word[i] % 2;
	Word[i] /= 2;
	}
}

// Kryphta la stringa
for ( int i=0 ; i<64 ; i++ )
	Kry[i] = Bin[Key[i]-1];

//Tok = Kry ribaltato, se vuoi togliere questo togli anche il "7-" nella prossimo
for ( int i=0 ; i<64 ; i++)
	Bin[63-i] = Kry[i];

// adesso  Riconvertire Bin[64] (binario) in Dec[8];
for ( int i=0 ; i<8 ; i++ )
	Word[7-i] =( Bin[8*i] + (2 * Bin[8*i+1]) + (4 * Bin[8*i+2]) + (8 * Bin[8*i+3]) + (16 * Bin[8*i+4]) + (32 * Bin[8*i+5]) + (64 * Bin[8*i+6]) + (128 * Bin[8*i+7]));

cout << "Kryphted it's : ";
for ( int i=0 ; i<8 ; i++ )
	cout << (char) Word[i];
cout << endl;
return 0;
}