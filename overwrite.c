#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
	char buf[BUFFER_SIZE];
	int fd;
	off_t offset,fsize;

	if(argc!=4){ //파일명, 오프셋, 데이터를 인자로 받았는지 확인
		fprintf(stderr, "Usage : %s filename offset data\n", argv[0]);
		exit(1);
	}

	if((fd=open(argv[1],O_RDWR))<0){ //파일을 읽기와 쓰기가 모두 가능하도록 오픈
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	offset = atol(argv[2]); //입력받은 오프셋 인자
	fsize = lseek(fd,0,SEEK_END); //입력받은 파일의 크기

	if(fsize-offset<1){ //파일의 크기보다 오프셋이 크다면 오류
                fprintf(stderr, "offset > fsize\n");
                exit(1);}


	if(lseek(fd,offset,SEEK_SET)<0){ //입력받은 오프셋 위치로 이동
		fprintf(stderr, "lseek error\n");
		exit(1);
	}

	if(write(fd,argv[3],strlen(argv[3]))!=strlen(argv[3])){ 
	       fprintf(stderr, "write error\n");
	       exit(1);
	}

	exit(0);
}
