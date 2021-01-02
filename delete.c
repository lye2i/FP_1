#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
	char buf1[BUF_SIZE];
	char buf2[BUF_SIZE];
	int fd,length;
	off_t offset, fsize;
	int bytes;

	if(argc!=4){ //파일명, 오프셋, 삭제 바이트수를 인자로 받아 총 인자의 갯수가 4개
		fprintf(stderr, "Usage : %s file offset bytes\n", argv[0]);
		exit(1);
	}

	if((fd=open(argv[1],O_RDONLY))<0){ //읽기,쓰기 전용으로 파일을 오픈
		fprintf(stderr, "open error for %s\n", argv[1]);
		exit(1);
	}

	offset = atol(argv[2]); //입력받은 오프셋
	bytes = atoi(argv[3]); //입력받은 삭제 바이트 수
	fsize = lseek(fd, 0, SEEK_END); //입력받은 파일의 총 바이트 수

	if(fsize-offset<=1){ //오프셋 인자가 파일의 크기보다 크거나 같다면 에러
                fprintf(stderr, "offset >= fsize\n");
                exit(1);}

	if(lseek(fd, 0, SEEK_SET)<0){ //파일의 처음으로 오프셋을 이동한다.
		fprintf(stderr,"lseek_1 error\n");
		exit(1);
	}

	if(read(fd,buf1,offset)<0){ //인자받은 오프셋의 전까지의 데이터를 buf1에 저장한다.
		fprintf(stderr, "read_1 error\n");
		exit(1);
	}

	if(bytes<fsize-offset){ //인자로 받은 삭제 바이트의 수 보다 더 많은 데이터가 존재한다면
		lseek(fd,bytes,SEEK_CUR);		
		length=read(fd, buf2, BUF_SIZE);} //삭제한 다음의 바이트부터 파일의 마지막 바이트 까지의 데이터를 buf2에 저장한다.

	close(fd); //파일을 닫는다.
	
	fd=open(argv[1],O_WRONLY|O_CREAT|O_TRUNC,0644); //이전의 데이터를 전부 잃고 오픈한다.

	if(write(fd, buf1, offset)!=offset){ //새로 오픈한 파일에 아까 저장했던 파일의 처음부터 오프셋 전까지의 데이터를 쓴다.
		fprintf(stderr, "write error1\n");
		exit(1);
	}

	if(bytes<fsize-offset){
		if(write(fd,buf2,length)!=length){ //새로 오픈한 파일에 아까 저장했던 삭제된 다음 오프셋부터 파일의 끝까지의 데이터를 저장한다.
			fprintf(stderr, "write error2\n");
			exit(1);
		}
	}
	exit(0);
}
