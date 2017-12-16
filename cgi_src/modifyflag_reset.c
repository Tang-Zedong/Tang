#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	printf("Content-Type: text/html\r\n\r\n");
	system("echo \"0\">modify_flag 2>/dev/null");
	return 0;
}
