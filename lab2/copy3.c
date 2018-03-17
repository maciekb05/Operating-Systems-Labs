#include <stdio.h>
#include "t.c"
void copy3(char *from, char *to)
{
	FILE *stfrom, *stto;
	int c;
	char czas[255];
 
	if ((stfrom = fopen(from, "r") ) == NULL){}
	if(( stto = fopen(to, "w") ) == NULL) {}
	timestart();
	while ((c = getc(stfrom)) != EOF)
		putc(c, stto);
	timestop(czas);
	fclose(stfrom);
	fclose(stto);
	return;
 
}
 
int main(int argc, char** argv){
	copy3(argv[1], argv[2]);
	return 0;
}
