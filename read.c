#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024
int main(int argc, char *argv[])
{
	char buf[BUF_SIZE];
	int fd;
	off_t fsize, offset;
	int bytes;
	int length;

	if(argc!=4){ //파일이름, 오프셋, 읽을 바이트의 수를 인자로 다 받았는지 확인
		fprintf(stderr, "Usage : %s filename offset Bytes\n",argv[0]);
		exit(1);
	}

	if((fd=open(argv[1],O_RDONLY))<0){ //읽기 전용의 파일 오픈
		fprintf(stderr, "open error for %s\n",argv[1]);
		exit(1);
	}

	fsize = lseek(fd,0,SEEK_END); //파일의 크기
	offset = atol(argv[2]); //오프셋 인자
	bytes = atoi(argv[3]); //읽을 바이트의 수

	if(fsize-offset<=1){ //오프셋 인자가 파일의 크기보다 크거나 같다면 에러
		fprintf(stderr, "offset >= fsize\n");
		exit(1);}

	if(lseek(fd,offset,SEEK_SET)<0){ //인자로 받은 offset으로 이동
		fprintf(stderr,"lseek error\n");
		exit(1);}

	if(bytes>fsize-offset) //읽어야 하는 바이트만큼의 데이터가 존재하지 않으면
		length = read(fd,buf,BUF_SIZE); //파일의 마지막 바이트까지 읽기
	else
		length = read(fd,buf,bytes); //아니면 인자로 받은 바이트 수만큼 읽기

	write(1,buf,length);
	exit(0);
	
}
