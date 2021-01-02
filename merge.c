#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024
int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	int fd1, fd2;
	int fsize;

	if(argc!=3){ //인자로 파일을 2개 받아야함
		fprintf(stderr, "Usage : %s file1 file2\n", argv[0]);
		exit(1);
	}

	if((fd1=open(argv[1],O_RDWR|O_APPEND))<0){ //파일을 읽기와 쓰기가 모두 가능하도록 오픈
		fprintf(stderr,"open error for %s\n", argv[1]);
		exit(1);
	}


	if((fd2=open(argv[2],O_RDONLY))<0){ //읽기 전용의 파일을 오픈
		fprintf(stderr, "open error for %s\n", argv[2]);
		exit(1);
	}

	fsize = read(fd2,buf,BUF_SIZE); //fd2의 파일의 크기 구하기

	if(write(fd1,buf,fsize)!=fsize){ //buf에 저장된 데이터를 파일1의 데이터 뒤에 쓴다.
		fprintf(stderr, "buf write error\n");
		exit(1);
	}

	exit(0);
}
