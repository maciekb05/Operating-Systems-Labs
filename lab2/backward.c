#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

void backward(char *path)
{
	char s[256], c;
	int i, fd;
	off_t where;
	char w[10][256];
	int wiersz = 9;
	int j=0;
	int k=0;
	int size = 0;
 
	fd = open(path, O_RDONLY);
	where = lseek(fd, 1, SEEK_END);
	i = sizeof(s) - 1;
	s[i] = '\0';
	
	for(k=0;k<10;k++){
		while ((pread(fd, &c, 1, where--))==1) {
			size++;
			if (c == '\n') {
				for(j=0;j<size;j++){
					if(s[i+j+1]=='\0'){
						w[wiersz][j] = '\0';
						size = 0;
						break;
					}
					w[wiersz][j] = s[i+j];
				}
				wiersz--;
				if(wiersz == -1){
					goto end;
				}
				i = sizeof(s) - 1;
				s[i] = '\0';
			}
			s[--i] = c;
		}
	}
end:	
	for(j=0;j<10;j++){
		printf("\n%s",w[j]);
	}
	
	close(fd);
	return;
}

int main(int argc, char **argv){
	if (argc == 1) {
		printf("Argument !!");
	}
	else if (argc == 2) {
		backward(argv[1]);
	}
	return 0;
}
