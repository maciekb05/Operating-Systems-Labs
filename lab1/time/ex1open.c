#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "t.h"
 
#define BUFSIZE 1024
 
int main (int argc, char **argv) {
    int f1, c;
    char b[BUFSIZE], *n1;
    char message[100];
 
    c = 100;
    n1 = argv[1];
 
    f1 = open (n1, O_RDONLY);
	timestart();
	for(int i=0;i<999999999;i++){};
    read (f1, b, c);
    timestop(message);
    printf("%s: Przeczytano %d znakow z pliku %s: \"%s\"\n",
	   argv[0], c, n1, b);
	printf("Czas: %s",message);
    close(f1);
 
    return(0);
}
