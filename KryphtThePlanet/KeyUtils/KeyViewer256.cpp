//KeyViewer256
#include <iostream.h>
#include <fcntl.h>
#include <io.h>

int main()
{
	int handle, Rdn;
	unsigned char Key[256];

	if ((handle = open("Key256.kry", O_BINARY)) == -1)
	{
		cout << "Error Opening Key.\n";
		return 1;
	}
	read(handle, Key, 256);
	
	for (int t=0;t<16;t++)
	{
		for (int i=0;i<16;i++)
		{
		if ((int) Key[t*16+i]<100) cout << " ";
		if ((int) Key[t*16+i]<10) cout << " ";
		cout << (int) Key[t*16+i] << " ";
		}
	cout << endl;
	}

	close(handle);
	return 0;
}