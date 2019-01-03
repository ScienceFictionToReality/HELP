#include <stdio.h>
#include <process.h>
#include <Windows.h>


unsigned _stdcall Thread(void *arg)
{
	while (1)
	{
		printf("Hello\n");
		Sleep(1000);
	}
}

void main() 
{
	_beginthreadex(NULL, 0, Thread, 0, 0, NULL);
	printf("hi\n");
	Sleep(10000);
}
	/*	char c = '0';
	while(1) {
		c = getc(stdin);
		if(c)
			break;
	} */
