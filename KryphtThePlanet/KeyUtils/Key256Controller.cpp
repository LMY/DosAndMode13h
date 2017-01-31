//Key256Controller
#include <iostream.h>
#include <io.h>
#include <fcntl.h>

int main()
{
int handle;
char Key[256];

if ((handle = open("Key256.kry", O_RDONLY | O_BINARY )) == -1)
	{
	cout << "Error Reading Key.\n";
	return 0;
	}
read(handle,Key,256);
close(handle);

int Up;
for (int t=0;t<256;t++ )
{
	Up = 0;
	for (int i=0;i<256;i++)
	{
		if (Key[i] == (char) t)
		{
		Up++;
		break;
		}
	}
	if (Up != 1) cout << t << ") " << Up << endl;
}

}