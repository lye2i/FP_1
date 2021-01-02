#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	int fd1,fd2; //파일 두개의 디스크립터
	int length; //저장된 데이터의 길이

	if(argc!=3){ //인자로 받은 파일의 이름이 두개가 아니라면 오류
		fprintf(stderr, "Usage : %s filein fileout\n", argv[0]);
		exit(1);
	}

	if((fd1=open(argv[1], O_RDONLY))<0){ //읽기 전용의 원본파일을 오픈
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	if((fd2=open(argv[2], O_WRONLY|O_CREAT|O_TRUNC,0644))<0){ //쓰기 전용의 파일을 생성한다.
		fprintf(stderr, "open error for %s\n", argv[2]);
		exit(1);
	}

	while((length = read(fd1,buf,100))>0) //원본파일의 100바이트의 데이터를 읽어 복사본 파일에 쓴다.
		write(fd2, buf, length);

	exit(0);
}
