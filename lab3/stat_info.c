#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <libgen.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb);
static void print_ino(const struct stat *sb);
static void print_perms(const struct stat *sb);
static void print_linkc(const struct stat *sb);
static void print_owner(const struct stat *sb);
static void print_size(const struct stat *sb);
static void print_laststch(const struct stat *sb);
static void print_lastacc(const struct stat *sb);
static void print_lastmod(const struct stat *sb);
static void print_name(const struct stat *sb, char *name);
/* -------------------------------------------------------------------------------- */

int  main(int argc, char *argv[])
{
  struct stat sb;
  
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  if (lstat(argv[1], &sb) == -1) {
    perror("stat");
    exit(EXIT_SUCCESS);
  }
  
  print_type(&sb);
  print_name(&sb, argv[1]);
  print_ino(&sb);
  print_perms(&sb);
  print_linkc(&sb);
  print_owner(&sb);
  print_size(&sb);
  print_laststch(&sb);
  print_lastacc(&sb);
  print_lastmod(&sb);
  
  exit(EXIT_SUCCESS);
}
/* -------------------------------------------------------------------------------- */

static void print_type(struct stat *sb){
  printf("File type:                ");
  switch (sb->st_mode & S_IFMT) {
           case S_IFBLK:  printf("block device\n");            break;
           case S_IFCHR:  printf("character device\n");        break;
           case S_IFDIR:  printf("directory\n");               break;
           case S_IFIFO:  printf("FIFO/pipe\n");               break;
           case S_IFLNK:  printf("symlink\n");                 break;
           case S_IFREG:  printf("regular file\n");            break;
           case S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }
}
/* -------------------------------------------------------------------------------- */

static void print_ino(const struct stat *sb){
  printf("I-node number:            %ld\n", (long) sb->st_ino);
}
/* -------------------------------------------------------------------------------- */

static void print_perms(const struct stat *sb){
  printf("Mode:                     %lo (octal)\n",(unsigned long) (sb->st_mode & 0000777));
  
  if((getpwnam(getlogin())->pw_uid) == (sb->st_uid)){
  	if((sb->st_mode & 0000700) == 64){
  		printf("User: r=0 w=0 x=1 \n");
  	}
  	else if((sb->st_mode & 0000700) == 128){
  		printf("User: r=0 w=1 x=0 \n");
  	}
  	else if((sb->st_mode & 0000700) == 192){
  		printf("User: r=0 w=1 x=1 \n");
  	}
  	else if((sb->st_mode & 0000700) == 256){
  		printf("User: r=1 w=0 x=0 \n");
  	}
  	else if((sb->st_mode & 0000700) == 320){
  		printf("User: r=1 w=0 x=1 \n");
  	}
  	else if((sb->st_mode & 0000700) == 384){
  		printf("User: r=1 w=1 x=0 \n");
  	}
  	else if((sb->st_mode & 0000700) == 448){
  		printf("User: r=1 w=1 x=1 \n");
  	}
  }
  
}
/* -------------------------------------------------------------------------------- */

static void print_linkc(const struct stat *sb){
  printf("Link count:               %ld\n", (long) sb->st_nlink);
}
/* -------------------------------------------------------------------------------- */

static void print_owner(const struct stat *sb){
  printf("Ownership:                %s(%ld)   %s(%ld)\n", getpwuid(sb->st_uid)->pw_name, (long) sb->st_uid, getgrgid(sb->st_gid)->gr_name, (long) sb->st_gid);
}
/* -------------------------------------------------------------------------------- */

static void print_size(const struct stat *sb){
  printf("Preferred I/O block size: %ld kB\n", (long) (sb->st_blksize/1024));
  printf("File size:                %ld MB\n",(long) (sb->st_size/1048576));
  printf("Blocks allocated:         %ld kB\n",(long) (sb->st_blocks/1024));
}
/* -------------------------------------------------------------------------------- */

static void print_laststch(const struct stat *sb){
  printf("Last status change:       %s", ctime(&sb->st_ctime));
  printf("%d days ago\n",(int)((difftime(time(NULL),sb->st_ctime))/60/60/24));
}
/* -------------------------------------------------------------------------------- */

static void print_lastacc(const struct stat *sb){
  printf("Last file access:         %s", ctime(&sb->st_atime));
  printf("%d days ago\n",(int)((difftime(time(NULL),sb->st_atime))/60/60/24));
}
/* -------------------------------------------------------------------------------- */

static void print_lastmod(const struct stat *sb){
  printf("Last file modification:   %s", ctime(&sb->st_mtime));
  printf("%d days ago\n",(int)((difftime(time(NULL),sb->st_mtime))/60/60/24));
}
/* -------------------------------------------------------------------------------- */

static void print_name(const struct stat *sb, char *name){
  char* bname = basename(name);
  printf("Name of the file:         %s", bname);
  if((sb->st_mode & S_IFMT) == S_IFLNK) {
  	char buf[1024];
  	int bufsize=1024;
  	int size = readlink(name,buf,bufsize);
  	buf[size] = '\0';
  	printf("->%s\n",buf);
  }else{printf("\n");}
}
/* -------------------------------------------------------------------------------- */
