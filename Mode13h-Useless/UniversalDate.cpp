#include <iostream.h>

void main()
{
unsigned char month,year,day,weekday;
	asm {
	mov ax,2A00h
	int 21h
	mov year,cx
	mov month,dh
	mov day,dl
	mov weekday,al
	}
	weekday+=2;
	if (weekday>7) weekday-=7;
	if (month==1) month=0;
	else if (month==2) { month=0; day+=40; }
	else if (month==3) month=1;
	else if (month==4) { month=1; day+=40; }
	else month -=3;
	cout << "Universal Date: " << year-20 << (int) month << (int) day << "." << (int) weekday;
}