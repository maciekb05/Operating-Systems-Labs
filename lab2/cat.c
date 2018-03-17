#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define BUFSIZE 512

ssize_t writeallmy(int fd, const void *buf, size_t nbyte){
	ssize_t nwritten = 0, n;

	do {
		if ((n = write(fd, &((const char *)buf)[nwritten], nbyte - nwritten)) == -1) {
			printf("WRITE\n");
			perror("writeall");
			if (errno == EINTR) {
				continue;
			}
			else {
				return -1;
			}
		}
		else if(n == 0){
			return 0;
		}
		nwritten += n;
	} while (nwritten < nbyte);
	
	return nwritten;
}
ssize_t readallmy(int fd, void *buf, size_t nbyte){
	ssize_t nread = 0, n;
	
	do {
		if((n = read(fd, &((char *)buf)[nread], nbyte - nread)) == -1) {
			printf("READ\n");
			perror("readall");
			if(errno == EINTR){
				continue;
			}
			else{
				return -1;
			}
		}
		if(n == 0){
			return nread;
		}
		nread += n;
	} while (nread < nbyte);
	
	return nread;
}

void cat(char *from)
{
	int fromfd = -1, tofd = 1;
	ssize_t nread;
	char buf[BUFSIZE];
	if(from=="0"){
		fromfd = 0;
	}
	else if((fromfd = open(from, O_RDONLY))==-1){
		perror("Open: fromfd = -1");
		exit(-1);
	}
	while ((nread = read(fromfd, buf, sizeof(buf))) > 0){
		write(tofd, buf, nread);
	}
		
    close(fromfd);
	close(tofd);
	return;
}

void catnum(char *from)
{
	int fromfd = -1;
	ssize_t nread;
	char buf[BUFSIZE];
	int licznik = 1;
	int i=0;
	
	if((fromfd = open(from, O_RDONLY))==-1){
		perror("Open: fromfd = -1");
		exit(-1);
	}
	printf("  0  ");
	while ((nread = read(fromfd, buf, sizeof(buf))) > 0){
		for(i=0;i<nread;i++){
			if(buf[i] == '\n'){
				printf("\n  %d  ",licznik++);
			}
			else{
				printf("%c",buf[i]);
			}
		}
	}
		
    close(fromfd);
	return;
}


int main(int argc, char **argv){
	if (argc == 1) {
		cat("0");
	}
	else if (argc == 2) {
		cat(argv[1]);
	}
	else if (argc == 3) {
		catnum(argv[2]);
	}
	return 0;
}
