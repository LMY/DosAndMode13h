#include <fstream.h>

int main()
{
int Key[64] = { 5, 8, 7, 4, 9, 6, 10, 12, 11, 15, 21, 29, 39, 30, 43, 14, 23, 17, 44, 33, 51, 56, 27, 58, 60, 36, 1, 26, 62, 19, 48, 38, 40, 20, 54, 63, 41, 31, 64, 55, 22, 3, 32, 42, 13, 47, 28, 53, 52, 57, 24, 45, 34, 16, 46, 35, 37, 50, 61, 18, 2, 49, 59, 25 };
char FileName[] = "Key.kry";

ofstream fout (FileName);

	for (int i=0; i<64; i++)
	{
	fout << (char) Key[i];
	}
	fout.close();
	return 0;
}