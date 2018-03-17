#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "t.c"
#define BUFSIZE 4096

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

void copy(char *from, char *to)
{
	char czas[255];
	int fromfd = -1, tofd = -1;
	ssize_t nread;
	char buf[BUFSIZE];
	
	if((fromfd = open(from, O_RDONLY))==-1){
		perror("Open: fromfd = -1");
		exit(-1);
	}
	if((tofd = open(to, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR))==-1){
		perror("Open: tofd = -1");
		exit(-1);
	}
	timestart();
	while ((nread = readallmy(fromfd, buf, sizeof(buf))) > 0){
		writeallmy(tofd, buf, nread);
	}
	timestop(czas);
    close(fromfd);
	close(tofd);
	return;
}


int main(int argc, char **argv){
	if (argc != 3)
	{
		fprintf(stderr,"usage: %s from_pathname to_pathname\n", argv[0]);
		return 1;
	}
	copy(argv[1], argv[2]);
	return 0;
}
