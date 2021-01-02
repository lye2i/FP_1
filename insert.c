#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define BUF_SIZE 1024
int main(int argc, char *argv[])
{
        char buf[BUF_SIZE];
        int fd;
        off_t fsize, offset;

        if(argc!=4){ //파일명,오프셋,데이터를 인자로 받아야 하므로 총 4개가 나와야함
                fprintf(stderr, "Usage : %s file offset data\n", argv[0]);
                exit(1);
        }

        if((fd=open(argv[1],O_RDWR))<0){ //읽기,쓰기의 파일을 오픈한다.
                fprintf(stderr, "open error for %s\n", argv[1]);
                exit(1);
        }

        offset = atol(argv[2]); //오프셋 인자 
        fsize = lseek(fd,0,SEEK_END); //입력받은 파일의 크기

        if(fsize-offset<1){ //파일의 크기보다 오프셋이 크다면 오류
                fprintf(stderr, "offset > fsize\n");
                exit(1);}

        lseek(fd,offset,SEEK_SET); //입력받은 오프셋으로 이동

        if(read(fd,buf,BUF_SIZE)<0){ //원래 파일의 데이터 중 입력받은 오프셋의 다음부터의 데이터를 buf에 저장한다. 
                fprintf(stderr,"read error\n");
                exit(1);
        }

        lseek(fd,offset,SEEK_SET); //입력받은 오프셋으로 이동

        if(write(fd, argv[3], strlen(argv[3]))!=strlen(argv[3])){ //입력받은 데이터를 오프셋에 쓰기
                fprintf(stderr,"write_1 error\n");
                exit(1);
        }

        if(write(fd, buf, fsize-offset)!=fsize-offset){ //buf에 저장했던 데이터를 쓰기
                fprintf(stderr,"write_2 error\n");
                exit(1);}

        exit(0);
}
