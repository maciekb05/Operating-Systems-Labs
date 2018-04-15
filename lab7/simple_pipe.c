#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
	int pfd[2];
	size_t nread;
	char buf[100];
	
	pipe(pfd);
	char * str ="Ur beautiful pipe example";
	if(fork() == 0){
		close(pfd[0]);
		write(pfd[1], str, strlen(str)+1);
	}
	else{
		close(pfd[1]);
		printf("Wielkosc bufora: %ld bytes.\n", fpathconf(pfd[0],_PC_PIPE_BUF));
		nread=read(pfd[0],buf, sizeof(buf));
		buf[nread+10] = 'a';
		(nread!=0)?printf("%s (%ld bytes)\n",buf,(long)nread):printf("No data\n");
	}
	
	return 0;
}
